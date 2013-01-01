mkdir obj
g++ -c ../cpp/qlSettings.cpp -o obj/qlSettings.o -I%DEVLIBS%\QuantLib-1.2.1 -I%DEVLIBS%\boost_1_50_0
g++ -c ../cpp/qlUtilities.cpp -o obj/qlUtilities.o -I%DEVLIBS%\QuantLib-1.2.1 -I%DEVLIBS%\boost_1_50_0
g++ -c ../cpp/qlDate.cpp -o obj/qlDate.o -I%DEVLIBS%\QuantLib-1.2.1 -I%DEVLIBS%\boost_1_50_0
g++ -c ../cpp/qlLeg.cpp -o obj/qlLeg.o -I%DEVLIBS%\QuantLib-1.2.1 -I%DEVLIBS%\boost_1_50_0
g++ -c ../cpp/qlCalendar.cpp -o obj/qlCalendar.o -I%DEVLIBS%\QuantLib-1.2.1 -I%DEVLIBS%\boost_1_50_0
