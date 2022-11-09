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

cobj/qlTermStructureAux.o: cbits/qlTermStructureAux.cpp cbits/qlTermStructureAux.h | cobj
	g++ -c $(CFLAGS) $(EXTRA) -o cobj/qlTermStructureAux.o cbits/qlTermStructureAux.cpp

cobj/qlPricingEngine.o: cbits/qlPricingEngine.cpp cbits/qlaux.h cbits/qlPricingEngine.h cbits/qlPricingEngineAux.h | cobj

cobj/qlTermStructure.o: cbits/qlTermStructure.cpp cbits/qlaux.h cbits/qlTermStructure.h cbits/qlTermStructureAux.h | cobj

cobj/%.o: cbits/%.cpp cbits/qlaux.h cbits/%.h | cobj
	g++ -c $(CFLAGS) $(EXTRA) -o $@ $<

# vim: set ft=make:
