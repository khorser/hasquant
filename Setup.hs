import Control.Exception(onException)
import Data.Maybe(fromJust)
import System.Process(readProcess)
import Distribution.Simple(defaultMainWithHooks, simpleUserHooks, confHook)
import Distribution.Simple.LocalBuildInfo(localPkgDescr)
import Distribution.Types.BuildInfo(cxxOptions, ldOptions)
import Distribution.Types.Library(libBuildInfo)
import Distribution.Types.PackageDescription(library)

main = defaultMainWithHooks simpleUserHooks {confHook = qlConfHook}

qlConfHook (pd, bi) f = do
  lbi <- confHook simpleUserHooks (pd, bi) f
  cxx <- readProcess "quantlib-config" ["--cflags"] "" `onException` return ""
  ld <- readProcess "quantlib-config" ["--libs"] "" `onException` return ""
  let lpd = localPkgDescr lbi
      lib = fromJust $ library lpd
      libbi = libBuildInfo lib
      libbi' = libbi {cxxOptions = cxxOptions libbi ++ words cxx,
        ldOptions = ldOptions libbi ++ filter (/= "-lQuantLib") (words ld)}
      lib' = lib {libBuildInfo = libbi'}
      lpd' = lpd {library = Just lib'}
  return $ lbi {localPkgDescr = lpd'}
