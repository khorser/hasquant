// Same ABI signatures as before 96d40db, alongside the current shared argument record.
#include "qlTypesC2HS.h"
#include "qlPricingEngine.h"

extern "C" {
using Apply = void (*)(const double*, unsigned, double, double, double*);
using Direction = void (*)(const double*, unsigned, unsigned, double, double, double*);
using Solve = void (*)(const double*, unsigned, unsigned, double, double, double, double*);
using Step = void (*)(const double*, unsigned, double, double*);
using Record = QlCallbackFun;

int probeCallbacks(Apply apply, Direction direction, Solve solve, Step step, Record record) {
  const double input[] = {11, 13, 17};
  double output[] = {123456, 0, 0, 0, 654321};
  for (unsigned i = 0; i < 1000; ++i) {
    apply(input, 3, 1.25, 2.5, output + 1);
    if (output[1] != 18.75) return 1;
    direction(input, 3, 7, 1.25, 2.5, output + 1);
    if (output[1] != 25.75) return 2;
    solve(input, 3, 7, -0.125, 1.25, 2.5, output + 1);
    if (output[1] != 25.625) return 3;
    step(input, 3, 1.25, output + 1);
    if (output[1] != 11.25) return 4;
    FdmCallbackArgs args{-0.125, 1.25, 2.5, input, output + 1, 3, 7};
    if (record(&args)) return 7;
    if (output[1] != 25.625 || output[2] != 27.625 || output[3] != 31.625) return 5;
    if (output[0] != 123456 || output[4] != 654321) return 6;
  }
  return 0;
}
void probeFields(const FdmCallbackArgs* p, double* values, unsigned* sizes,
                 const double** input, double** output) {
  values[0] = p->s; values[1] = p->t1; values[2] = p->t2;
  sizes[0] = p->size; sizes[1] = p->direction;
  *input = p->input; *output = p->output;
}
}
