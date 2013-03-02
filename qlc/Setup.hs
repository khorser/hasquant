-- adapted from `wxc' package of wxHaskell project (http://hackage.haskell.org/package/wxc)

-- configure AND build on Windows with something like:
-- cabal configure --with-gcc=g++ --extra-include-dirs=<QuantLib-incpath> --extra-include-dirs=<boost-incpath> --extra-lib-dirs=<QuantLib-libpath>
import Control.Monad (when)
import Data.List (intercalate)
import Data.Maybe (fromJust)
import Distribution.PackageDescription
import Distribution.Simple (defaultMainWithHooks, simpleUserHooks, pkgVersion, versionBranch, Version, UserHooks, instHook, buildHook, confHook)
import Distribution.Simple.InstallDirs (InstallDirs(..))
import Distribution.Simple.LocalBuildInfo (LocalBuildInfo, withPrograms, buildDir, absoluteInstallDirs, localPkgDescr)
import Distribution.Simple.Program (ConfiguredProgram (..), lookupProgram, runProgram, simpleProgram)
import Distribution.Simple.Setup (BuildFlags, InstallFlags, CopyDest(..), fromFlag, installVerbosity, ConfigFlags, configConfigurationsFlags)
import Distribution.Simple.Utils (installOrdinaryFile)
import Distribution.System (OS (..), buildOS)
import Distribution.Verbosity (verbose)
import System.Cmd (system)
import System.Directory (createDirectoryIfMissing, doesFileExist, getModificationTime)
import System.Exit (ExitCode (..))
import System.FilePath.Posix ((</>), replaceExtension, takeFileName, dropFileName, addExtension)

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

main :: IO ()
main = defaultMainWithHooks simpleUserHooks { buildHook = myBuildHook, instHook = myInstHook, confHook = myConfHook }

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

-- TODO use quantlib-config output on Unix

-- | Extend the standard build hook to build a shared library for qlc - this will statically link
-- any libraries which are unavailable as shared variants. This is mainly a work-around for the
-- fact that GHCi needs to load shared libraries at run-time, and that the Windows MinGW environment
-- is shipped with only a static version of libstdc++.
-- TODO: Does not currently create the build output directory.
myBuildHook :: PackageDescription -> LocalBuildInfo -> UserHooks -> BuildFlags -> IO ()
myBuildHook pkg_descr local_bld_info _user_hooks _bld_flags =
    do
    -- Extract the custom fields customFieldsPD where field name is x-cpp-dll-sources
    let lib = fromJust (library pkg_descr)
        lib_bi = libBuildInfo lib
        custom_bi = customFieldsBI lib_bi
        dll_name = fromJust (lookup "x-dll-name" custom_bi)
        dll_srcs = (lines . fromJust) (lookup "x-dll-sources" custom_bi)
        dll_libs = (lines . fromJust) (lookup "x-dll-extra-libraries" custom_bi)
        cc_opts = ccOptions lib_bi
        ld_opts = ldOptions lib_bi
        inc_dirs = includeDirs lib_bi
        lib_dirs = extraLibDirs lib_bi
        libs = extraLibs lib_bi
        bld_dir = buildDir local_bld_info
        progs = withPrograms local_bld_info
        gcc = fromJust (lookupProgram (simpleProgram "gcc") progs)
        ver = (pkgVersion . package) pkg_descr
        inst_lib_dir = libdir $ absoluteInstallDirs pkg_descr local_bld_info NoCopyDest
    -- Compile C/C++ sources - output directory is dist/build/src/cpp
    putStrLn "Building qlc"
    objs <- mapM (compileCxx gcc cc_opts inc_dirs bld_dir) dll_srcs
    -- Link C/C++ sources as a DLL - output directory is dist/build
    putStrLn "Linking qlc"
    linkSharedLib gcc ld_opts lib_dirs (libs ++ dll_libs) objs ver bld_dir dll_name inst_lib_dir

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

-- | Return any compiler options required to support shared library creation
osCompileOpts :: [String] -- ^ Platform-specific compile options
osCompileOpts =
    case buildOS of
      Windows -> []
      OSX -> ["-fPIC"]
      _ -> ["-fPIC"]

sharedLibName :: Version -- ^ Version information to be used for Unix shared libraries
              -> String -- ^ Name of the shared library
              -> String
sharedLibName ver basename =
    case buildOS of
      Windows -> addExtension basename ".dll"
      OSX -> "lib" ++ addExtension basename ".dylib"
      _ -> "lib" ++ basename ++ ".so." ++ full_ver
        where
          full_ver = (intercalate "." . map show . versionBranch) ver

staticLibName :: String -> String
staticLibName basename =
    case buildOS of
      Windows -> "lib" ++ addExtension basename ".a"
      _ -> error "No static libs required on this platform"

-- | Return any linker options required to support shared library creation
linkCxxOpts :: Version -- ^ Version information to be used for Unix shared libraries
            -> FilePath -- ^ Directory in which library will be built
            -> String -- ^ Name of the shared library
            -> String -- ^ Absolute path of the shared library
            -> [String] -- ^ List of options which can be applied to 'runProgram'
linkCxxOpts ver out_dir basename basepath =
    case buildOS of
      Windows -> ["-shared", 
                  "-o", out_dir </> sharedLibName ver basename,
                  "-Wl,--out-implib," ++ out_dir </> "lib" ++ addExtension basename ".a",
                  "-Wl,--enable-auto-import"]
      OSX -> ["-dynamiclib",
                  "-o", out_dir </> sharedLibName ver basename,
                  "-install_name", basepath </> sharedLibName ver basename,
                  "-Wl,-undefined,dynamic_lookup"]
      _ -> ["-shared",
                  "-Wl,-soname,lib" ++ basename ++ ".so",
                  "-o", out_dir </> sharedLibName ver basename]

-- | Compile a single source file using the configured gcc, if the object file does not yet
-- exist, or is older than the source file.
-- TODO: Does not do dependency resolution properly
compileCxx :: ConfiguredProgram -- ^ Program used to perform C/C++ compilation (gcc)
           -> [String] -- ^ Compile options provided by Cabal
           -> [String] -- ^ Include paths provided by Cabal
           -> FilePath -- ^ Base output directory
           -> FilePath -- ^ Path to source file
           -> IO FilePath -- ^ Path to generated object code
compileCxx gcc opts incls out_path cxx_src =
    do
    let includes' = map ("-I" ++) incls
        out_path' = normalisePath out_path
        cxx_src' = normalisePath cxx_src
        out_file = out_path' </> dropFileName cxx_src </> replaceExtension (takeFileName cxx_src) ".o"
        out = ["-c", cxx_src', "-o", out_file, "-DDLLSOURCE"]
        opts' = opts ++ osCompileOpts
    do_it <- needsCompiling cxx_src out_file
    when do_it $ createDirectoryIfMissing True (dropFileName out_file) >>
                 runProgram verbose gcc (includes' ++ opts' ++ out)
    return out_file

-- | Return True if obj does not exist or is older than src.
-- Real dependency checking would be nice here...
needsCompiling :: FilePath -- ^ Path to source file
               -> FilePath -- ^ Path to object file
               -> IO Bool -- ^ True if compilation required
needsCompiling src obj =
    do
    has_obj <- doesFileExist obj
    if has_obj
        then do
          mtime_src <- getModificationTime src
          mtime_obj <- getModificationTime obj
          return (mtime_obj < mtime_src)
        else
          return True

-- | Create a dynamically linked library using the configured ld.
linkSharedLib :: ConfiguredProgram -- ^ Program used to perform linking
              -> [String] -- ^ Linker options supplied by Cabal
              -> [FilePath] -- ^ Library directories
              -> [String] -- ^ Libraries
              -> [String] -- ^ Objects
              -> Version -- ^ qlCore version (qlC has same version number)
              -> FilePath -- ^ Directory in which library will be generated
              -> String -- ^ Name of the shared library
              -> String -- ^ Absolute path of the shared library
              -> IO ()
linkSharedLib gcc opts lib_dirs libs objs ver out_dir dll_name dll_path =
    do
    let lib_dirs' = map (\d -> "-L" ++ normalisePath d) lib_dirs
        out_dir' = normalisePath out_dir
        opts' = opts ++ linkCxxOpts ver out_dir' dll_name dll_path
        objs' = map normalisePath objs
        libs' =  map ("-l" ++) libs
          ++ (if buildOS == Windows
                then ["-static-libstdc++", "-static-libgcc"]
                else ["-lstdc++"])
    runProgram verbose gcc (opts' ++ objs' ++ lib_dirs' ++ libs')
    return ()

-- | The 'normalise' implementation in System.FilePath does not meet the requirements of
-- calling and/or running external programs on Windows particularly well as it does not
-- normalise the '/' character to '\\'. The problem is that some MinGW programs do not
-- like to see paths with a mixture of '/' and '\\'. Sine we are calling out to these,
-- we require a stricter normalisation.
normalisePath :: FilePath -> FilePath
normalisePath = case buildOS of
                  Windows -> dosifyFilePath
                  _ -> unixifyFilePath

-- | Replace a character in a String with some other character
replace :: Char -- ^ Character to replace
        -> Char -- ^ Character with which to replace
        -> String -- ^ String in which to replace
        -> String -- ^ Transformed string
replace old new = map replace'
    where
      replace' el = if el == old then new else el

unixifyFilePath :: FilePath -> FilePath
unixifyFilePath = replace '\\' '/'
dosifyFilePath :: FilePath -> FilePath
dosifyFilePath = replace '/' '\\'

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

-- | Run ldconfig in `path` and return a list of all the links which were created
ldconfig :: FilePath -> IO ()
ldconfig path = case buildOS of
    Windows -> return ()
    OSX -> return ()
    _ -> do
            ld_exit_code <- system ("/sbin/ldconfig -n " ++ path) 
            case ld_exit_code of
                ExitSuccess -> return ()
                _ -> error "Couldn't execute ldconfig, ensure it is on your path"

myInstHook :: PackageDescription -> LocalBuildInfo -> UserHooks -> InstallFlags -> IO ()
myInstHook pkg_descr local_bld_info user_hooks inst_flags = 
    do
    -- Perform simpleUserHooks instHook (to copy installIncludes)
    instHook simpleUserHooks pkg_descr local_bld_info user_hooks inst_flags

    -- Copy shared library
    let bld_dir = buildDir local_bld_info

        ver = (pkgVersion . package) pkg_descr
        lib = fromJust (library pkg_descr)
        lib_bi = libBuildInfo lib
        custom_bi = customFieldsBI lib_bi
        dll_name = fromJust (lookup "x-dll-name" custom_bi)
        lib_name = sharedLibName ver dll_name

        inst_lib_dir = libdir $ absoluteInstallDirs pkg_descr local_bld_info NoCopyDest

    installOrdinaryFile (fromFlag (installVerbosity inst_flags)) (bld_dir </> lib_name) (inst_lib_dir </> lib_name)
    when (buildOS == Windows)
      $ installOrdinaryFile (fromFlag (installVerbosity inst_flags))
                            (bld_dir </> staticLibName dll_name)
                            (inst_lib_dir </> staticLibName dll_name)
    ldconfig inst_lib_dir

myConfHook :: (GenericPackageDescription, HookedBuildInfo) -> ConfigFlags -> IO LocalBuildInfo
myConfHook (pkg0, pbi) flags = do
  lbi <- confHook simpleUserHooks (pkg0, pbi) flags
  let
    configFlags = configConfigurationsFlags flags
    (Just selfDep) = lookup (FlagName "addselfdep") configFlags

  if selfDep
    then return $ buildInfoMod lbi
    else return lbi

  where
    buildInfoMod lbi =
      let
        instLibDir = libdir $ absoluteInstallDirs (packageDescription pkg0) lbi NoCopyDest
        lpd       = localPkgDescr lbi
        lib       = fromJust (library lpd)
        libbi     = libBuildInfo lib

        libbi' = libbi
          { extraLibDirs = extraLibDirs libbi ++ [instLibDir]
          , extraLibs    = extraLibs    libbi ++ ["qlc"]
          , ldOptions    = ldOptions    libbi ++ ["-Wl,-rpath," ++ instLibDir]
          }

        lib' = lib { libBuildInfo = libbi' }
        lpd' = lpd { library = Just lib' }
      in lbi { localPkgDescr = lpd' }

-- vim: set ft=haskell ff=unix ts=8 sts=2 sw=2 et:
