ghc -Wall Settings.hs Internal.hs Utilities.hs Error.hs Test.hs Date.hs Leg.hs qlSettings.o qlUtilities.o qlDate.o qlLeg.o -lQuantLib -L. -pgml g++ -optl-static-libstdc++ -optl-static-libgcc
