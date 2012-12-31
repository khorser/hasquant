ghc -Wall Settings.hs Internal.hs Utilities.hs Error.hs Test.hs Date.hs qlSettings.o qlUtilities.o qlDate.o -lQuantLib -L. -pgml g++ -optl-static-libstdc++ -optl-static-libgcc
