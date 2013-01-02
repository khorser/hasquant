mkdir obj
ghc -Wall -outputdir obj -o Test.exe Settings.hs Internal.hs Utilities.hs Error.hs Time/Calendar.hs ../Test.hs Time/Date.hs CashFlow/Leg.hs obj/qlSettings.o obj/qlUtilities.o obj/qlDate.o obj/qlLeg.o obj/qlCalendar.o -lQuantLib -L. -pgml g++ -optl-static-libstdc++ -optl-static-libgcc
