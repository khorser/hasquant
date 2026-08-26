-- |Renders the NPV profile (NPV vs. timestep, one line per scenario), optionally
-- overlaid with a PFE percentile profile, by shelling out to an installed @gnuplot@
-- binary -- the simplest way to get a plot out of this small executable without
-- pulling in a native Haskell charting library and its graphics dependencies.
-- Plotting is optional: if @gnuplot@ is missing or fails, this prints a warning and
-- does not fail the whole program, since the NPV diff summary/CSV (see "Main") are
-- the primary output.
module SofrXva.Plot
  ( plotNpvProfile
  ) where

import Control.Exception (IOException, try)
import Data.List (groupBy, sortOn)
import Data.Function (on)
import qualified Data.Map.Strict as Map
import System.FilePath (replaceExtension)
import System.Process (readProcessWithExitCode)
import System.Exit (ExitCode(..))
import Text.Printf (printf)

-- |Writes the @.dat@\/@.gp@ gnuplot inputs next to 'pngPath' (same path, @.dat@\/@.gp@
-- extensions) and invokes @gnuplot@ on the script to render 'pngPath' itself. 'pfe',
-- if non-empty, is the percentile PFE profile (see 'SofrXva.Xva.XvaResult'), one
-- value per canonical timestep in timestep order -- it is overlaid as an extra
-- dashed line on top of the per-scenario NPV lines.
plotNpvProfile :: FilePath -> Map.Map (Int, Int) Double -> [Double] -> IO ()
plotNpvProfile pngPath npvMap pfe = do
  let byScen = groupBy ((==) `on` fst . fst) (sortOn fst (Map.toList npvMap))
      datPath = replaceExtension pngPath "dat"
      pfeDatPath = replaceExtension pngPath "pfe.dat"
      gpPath = replaceExtension pngPath "gp"
      -- gnuplot separates "index"-addressable data blocks with a *pair* of blank
      -- lines, not one -- a single blank line only breaks line continuity within a
      -- block, so each block ends with an extra blank line of its own on top of the
      -- one 'unlines' inserts between list elements.
      block scen = unlines [printf "%d %.10f" ts v | ((_, ts), v) <- scen] ++ "\n"
      datContent = unlines (map block byScen)
      pfeDatContent = unlines [printf "%d %.10f" ts v | (ts, v) <- zip [(0 :: Int) ..] pfe]
      -- A wide-below legend beats the default right-hand-side one once there are more
      -- than a handful of scenarios -- one column per scenario runs off the canvas, so
      -- wrap into a grid instead, sized to fit under the plot rather than beside it.
      -- The extra canvas height keeps the plot area itself from being squeezed as the
      -- legend grid grows with the scenario count.
      nScen = length byScen
      keyCols = max 1 (min 10 nScen)
      keyRows = (nScen + keyCols - 1) `div` keyCols
      height = 600 + 16 * keyRows
      npvPlot = printf
        "for [i=0:%d] '%s' index i using 1:2 with lines title sprintf('scen %%d', i)"
        (nScen - 1) datPath
      pfePlot = printf ", '%s' using 1:2 with lines dashtype 2 lw 2 lc rgb 'red' title 'PFE'"
        pfeDatPath
      plotLine = "plot " ++ npvPlot ++ (if null pfe then "" else pfePlot)
      script = unlines
        [ printf "set terminal png size 800,%d" (height :: Int)
        , printf "set output '%s'" pngPath
        , "set title 'SOFR-OIS NPV profile'"
        , "set xlabel 'Timestep'"
        , "set ylabel 'NPV'"
        , printf "set key below maxcols %d font ',8'" keyCols
        , plotLine
        ]

  writeFile datPath datContent
  writeFile gpPath script
  if null pfe then pure () else writeFile pfeDatPath pfeDatContent

  result <- try (readProcessWithExitCode "gnuplot" [gpPath] "") :: IO (Either IOException (ExitCode, String, String))
  case result of
    Left e -> putStrLn ("sofr-xva: gnuplot plot skipped: " ++ show e)
    Right (ExitSuccess, _, _) -> putStrLn ("sofr-xva: wrote NPV profile plot to " ++ pngPath)
    Right (ExitFailure _, _, stderrOut) ->
      putStrLn ("sofr-xva: gnuplot plot skipped: " ++ stderrOut)
