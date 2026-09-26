// Test-only producers use the same allocation and deallocation paths as the shims.
#include "qlaux.h"

namespace {int liveElements = 0;}
extern "C" {
void testElements(unsigned* n, int*** out) {
  *n = 3;
  *out = retPtrArray(new int*[3]());
  for (int i = 0; i < 3; ++i) {(*out)[i] = ret(new int(i)); ++liveElements;}
}
void testFreeElement(int* p) {if (p) {--liveElements; del(p);}}
int testLiveElements() {return liveElements;}
void testDoubles(unsigned* n, double** out) {
  *n = 3;
  *out = qlAllocateDoubles(3);
  for (int i = 0; i < 3; ++i) (*out)[i] = i;
}
void testStrings(unsigned* n, char*** out) {
  *n = 2;
  *out = ret(new char*[2]());
  (*out)[0] = tracedup("alpha");
  (*out)[1] = tracedup("beta");
}
}
extern "C" int* testNewElement(int value) {++liveElements; return ret(new int(value));}
