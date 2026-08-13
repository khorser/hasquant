# Makefile for cbits, mostly for local quick tests
SRC=$(wildcard cbits/ql*.cpp)

OBJ=$(subst cbits,cobj,$(SRC:.cpp=.o))

# Third-party headers come in via -isystem, not -I, so their warnings stay out of the way:
# under -Wall -Wextra -pedantic QuantLib and boost produce ~113 warnings and cbits/ produces
# none, so a plain -I build reports nothing but noise. -isystem wins over -I for the same
# directory (verified both orders), and warnings in cbits/ are unaffected. Derived from
# quantlib-config rather than hardcoded so it survives a QuantLib version bump.
CFLAGS=-Wall -Wextra -pedantic $(subst -I,-isystem,$(shell quantlib-config --cflags)) -isystem/opt/homebrew/include

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
