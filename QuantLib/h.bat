mkdir obj
cd ..
ghc -Wall -outputdir QuantLib\obj --make Test.hs -lQuantLib -pgml g++ -optl-static-libstdc++ -optl-static-libgcc -L%DEVLIBS%\QuantLib-1.2.1\ql\bin\15b474156460f41fe64f8ba9fcb070b1 QuantLib\cpp\qlBond.o QuantLib\cpp\qlBusinessDayConvention.o QuantLib\cpp\qlCalendar.o QuantLib\cpp\qlCurrency.o QuantLib\cpp\qlDate.o QuantLib\cpp\qlDateGenerationRule.o QuantLib\cpp\qlDayCounter.o QuantLib\cpp\qlFrequency.o QuantLib\cpp\qlLeg.o QuantLib\cpp\qlPeriod.o QuantLib\cpp\qlQuote.o QuantLib\cpp\qlSchedule.o QuantLib\cpp\qlSettings.o QuantLib\cpp\qlTimeUnit.o QuantLib\cpp\qlUtilities.o
