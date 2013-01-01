mkdir obj
ghc -outputdir obj -Wall -o Test */*.hs *.hs ../Test.hs ../cpp/*.cpp -lQuantLib -pgml g++
