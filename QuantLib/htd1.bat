mkdir obj
cd ..
ghc -Wall -outputdir QuantLib\obj --make Test1.hs -o QuantLib\Test1.exe -lQuantLib -pgml g++ -optl-static -optl-g -L%DEVLIBS%\QuantLib-1.2.1-noopt\ql\bin\d750f55955fa5ad66fec54f46f00c080 QuantLib\cpp\qlBond.o QuantLib\cpp\qlCalendar.o QuantLib\cpp\qlCurrency.o QuantLib\cpp\qlDate.o QuantLib\cpp\qlDayCounter.o QuantLib\cpp\qlEnumerations.o QuantLib\cpp\qlLeg.o QuantLib\cpp\qlPeriod.o QuantLib\cpp\qlQuote.o QuantLib\cpp\qlSchedule.o QuantLib\cpp\qlSettings.o QuantLib\cpp\qlUtilities.o
