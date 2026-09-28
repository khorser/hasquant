#include "qlCallback.hpp"
#include <cassert>
#include <cstdio>

namespace {
  int calls = 0, functionsFreed = 0, exceptionsFreed = 0;
  int exceptionToken;
  void* fail(const QlCallbackArgs*) { ++calls; return &exceptionToken; }
  void releaseFunction(void (*)(void)) { ++functionsFreed; }
  void releaseException(void* token) { assert(token == &exceptionToken); ++exceptionsFreed; }
  int released = 0;
  struct Released { ~Released() { ++released; } };
}

int main() {
  QlError* error = nullptr;
  QlCallback* wrapper = qlNewCallback(fail, releaseFunction, releaseException, &error);
  assert(wrapper && !error);
  auto dependent = *wrapper;
  qlFreeCallback(wrapper);
  assert(functionsFreed == 0);
  {
    QlCallScope outer(&error);
    try { dependent->scalar(1); } catch (const std::exception&) {}
    assert(error && calls == 1);
    try { dependent->scalar(1); } catch (const std::exception&) {}
    assert(calls == 1); // An upstream catch cannot resume calling a failed callback.
    QlError* innerError = nullptr;
    {
      QlCallScope inner(&innerError);
      try { dependent->scalar(2); } catch (const std::exception&) {}
      assert(innerError && innerError != error && calls == 2);
    }
    qlFreeError(innerError);
    try { dependent->scalar(3); } catch (const std::exception&) {}
    assert(calls == 2);
  }
  assert(exceptionsFreed == 1);
  void* token = qlTakeErrorException(error);
  qlFreeError(error);
  assert(exceptionsFreed == 1);
  releaseException(token);
  dependent.reset();
  assert(exceptionsFreed == 2 && functionsFreed == 1);

  // A release inside nested calls waits for the outermost scope; one outside any call is immediate.
  QlError* releaseError = nullptr;
  {
    QlCallScope outer(&releaseError);
    std::shared_ptr<Released> owner(new Released, hasquant::DeleteAfterCall<Released>());
    {
      QlError* innerError = nullptr;
      QlCallScope inner(&innerError);
      owner.reset();
    }
    assert(released == 0);
  }
  assert(released == 1 && !releaseError);
  std::shared_ptr<Released>(new Released, hasquant::DeleteAfterCall<Released>()).reset();
  assert(released == 2);
  std::puts("Native callback lifetime, nested errors, upstream catches, and deferred release: OK");
}
