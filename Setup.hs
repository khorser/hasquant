-- adapted from `wxcore' package of wxHaskell project (http://hackage.haskell.org/package/wxcore)

import Control.Monad (filterM)
import Data.Maybe (fromJust)
import Distribution.PackageDescription hiding (includeDirs)
import Distribution.InstalledPackageInfo(includeDirs)
import Distribution.Simple
import Distribution.Simple.LocalBuildInfo (LocalBuildInfo, localPkgDescr, installedPkgs)
import Distribution.Simple.PackageIndex(SearchResult (..), searchByName)
import Distribution.Simple.Setup
import System.Directory (doesFileExist)
import System.FilePath ((</>), takeDirectory)

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

main :: IO ()
main = defaultMainWithHooks simpleUserHooks { confHook = myConfHook }

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

-- |This slightly dubious function obtains the install path for the qlc package we are using.
-- It works by finding the qlc package's installation info, then finding the include directory 
-- which contains qlc's headers and then going up a level.
-- It would be nice the path was park of InstalledPackageInfo, but it isn't.
qlcInstallDir :: LocalBuildInfo -> IO FilePath
qlcInstallDir lbi = 
    case searchByName (installedPkgs lbi) "qlc" of
        Unambiguous (qlc_pkg:_) -> do
            qlc <- filterM (doesFileExist . (</> "ql.h")) (includeDirs qlc_pkg)
            case qlc of
                [qlcIncludeDir] -> return (takeDirectory qlcIncludeDir)
                [] -> error "qlcInstallDir: couldn't find qlc include dir"
                _  -> error "qlcInstallDir: I'm confused. I see more than one qlc include directory from the same package"
        Unambiguous [] -> error "qlcInstallDir: Cabal says qlc is installed but gives no package info for it"
        _ -> error "qlcInstallDir: Couldn't find qlc package in installed packages"

-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

myConfHook :: (GenericPackageDescription, HookedBuildInfo) -> ConfigFlags -> IO LocalBuildInfo
myConfHook (pkg0, pbi) flags = do
    lbi <- confHook simpleUserHooks (pkg0, pbi) flags
    qlcDirectory <- qlcInstallDir lbi

    let lpd       = localPkgDescr lbi
    let lib       = fromJust (library lpd)
    let libbi     = libBuildInfo lib

    let libbi' = libbi
          { extraLibDirs = extraLibDirs libbi ++ [qlcDirectory]
          , extraLibs    = extraLibs    libbi ++ ["qlc"]
          , ldOptions    = ldOptions    libbi ++ ["-Wl,-rpath," ++ qlcDirectory]  }

    let lib' = lib { libBuildInfo = libbi' }
    let lpd' = lpd { library = Just lib' }

    return $ lbi { localPkgDescr = lpd' }
