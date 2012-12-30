ghc -Wall Settings.hs Internal.hs Utilities.hs Error.hs Test.hs qlSettings.o qlUtilities.o -lQuantLib -L. -pgml g++ -optl-static-libstdc++ -optl-static-libgcc
