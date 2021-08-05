# Makefile for cbits, mostly for local quick tests
SRC=$(wildcard cbits/ql*.cpp)

OBJ=$(subst cbits,cobj,$(SRC:.cpp=.o))

CFLAGS=-Wall -Wextra -pedantic $(shell quantlib-config --cflags)

all:	cobj/libql.a

cobj:
	mkdir cobj

cobj/libql.a: $(OBJ)
	ar cr cobj/libql.a $(OBJ)

cobj/qlPricingEngineAux.o: cbits/qlPricingEngineAux.cpp cbits/qlPricingEngineAux.h | cobj
	g++ -c $(CFLAGS) $(EXTRA) -o cobj/qlPricingEngineAux.o cbits/qlPricingEngineAux.cpp

cobj/qlTSAux.o: cbits/qlTSAux.cpp cbits/qlTSAux.h | cobj
	g++ -c $(CFLAGS) $(EXTRA) -o cobj/qlTSAux.o cbits/qlTSAux.cpp

cobj/qlPricingEngine.o: cbits/qlPricingEngine.cpp cbits/qlaux.h cbits/qlPricingEngine.h cbits/qlPricingEngineAux.h | cobj

cobj/qlDefaultTS.o: cbits/qlDefaultTS.cpp cbits/qlaux.h cbits/qlDefaultTS.h cbits/qlTSAux.h | cobj

cobj/qlVolatilityTS.o: cbits/qlVolatilityTS.cpp cbits/qlaux.h cbits/qlVolatilityTS.h cbits/qlTSAux.h | cobj

cobj/qlYieldTS.o: cbits/qlYieldTS.cpp cbits/qlaux.h cbits/qlYieldTS.h cbits/qlTSAux.h | cobj

cobj/%.o: cbits/%.cpp cbits/qlaux.h cbits/%.h | cobj
	g++ -c $(CFLAGS) $(EXTRA) -o $@ $<

# vim: set ft=make:
