# Makefile for cbits, mostly for local quick tests
# Override QUANTLIB_CONFIG (or QL_CFLAGS directly) to pick a QuantLib, and OBJDIR to keep
# each QuantLib's objects apart; ./q's m/M/h actions do both.
QUANTLIB_CONFIG ?= quantlib-config
QL_CFLAGS ?= $(shell $(QUANTLIB_CONFIG) --cflags)
OBJDIR ?= cobj

SRC=$(wildcard cbits/ql*.cpp)

OBJ=$(patsubst cbits/%.cpp,$(OBJDIR)/%.o,$(SRC))

# Third-party headers come in via -isystem, not -I, so their warnings stay out of the way:
# under -Wall -Wextra -pedantic QuantLib and boost produce ~113 warnings and cbits/ produces
# none, so a plain -I build reports nothing but noise. -isystem wins over -I for the same
# directory (verified both orders), and warnings in cbits/ are unaffected. Derived from
# quantlib-config rather than hardcoded so it survives a QuantLib version bump.
# -std=c++17 matches hasquant.cabal; not every quantlib-config emits it.
CFLAGS=-Wall -Wextra -pedantic -std=c++17 $(subst -I,-isystem,$(QL_CFLAGS)) -isystem/opt/homebrew/include
# -MD, not -MMD: QuantLib headers come via -isystem and must stay tracked dependencies.
DEPFLAGS=-MD -MP

all:	$(OBJDIR)/libql.a

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(OBJDIR)/libql.a: $(OBJ)
	ar cr $@ $(OBJ)

$(OBJDIR)/qlPricingEngineAux.o: cbits/qlPricingEngineAux.cpp cbits/qlPricingEngineAux.h cbits/qlStdCompat.h cbits/qlCheckedFdEngine.h | $(OBJDIR)
	g++ -c $(CFLAGS) $(DEPFLAGS) $(EXTRA) -o $@ $<

$(OBJDIR)/qlTermStructureAux.o: cbits/qlTermStructureAux.cpp cbits/qlTermStructureAux.h | $(OBJDIR)
	g++ -c $(CFLAGS) $(DEPFLAGS) $(EXTRA) -o $@ $<

$(OBJDIR)/qlPricingEngine.o: cbits/qlPricingEngine.cpp cbits/qlaux.h cbits/qlPricingEngine.h cbits/qlPricingEngineAux.h cbits/qlCheckedFdEngine.h cbits/qlExactMeanH1HwEngine.h | $(OBJDIR)

$(OBJDIR)/qlTermStructure.o: cbits/qlTermStructure.cpp cbits/qlaux.h cbits/qlTermStructure.h cbits/qlTermStructureAux.h | $(OBJDIR)

$(OBJDIR)/%.o: cbits/%.cpp cbits/qlaux.h cbits/qlStdCompat.h cbits/qlCallback.h cbits/qlCallback.hpp cbits/%.h | $(OBJDIR)
	g++ -c $(CFLAGS) $(DEPFLAGS) $(EXTRA) -o $@ $<

-include $(OBJ:.o=.d)

# vim: set ft=make:
