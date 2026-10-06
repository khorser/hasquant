#include <ql/version.hpp>
#include "qlaux.h"

namespace {
  thread_local QlCallScope* currentCall = nullptr;
  class CallbackFailure : public std::exception {
  public:
    const char* what() const noexcept override { return "Haskell callback failed"; }
  };
}

QlCallScope::QlCallScope(QlError** error) noexcept : slot(error), previous_(currentCall) {
  currentCall = this;
}
QlCallScope::~QlCallScope() {
  currentCall = previous_;
  // Only the outermost scope collects deferred objects; no interrupted call can use them now.
  for (auto& [object, destroy] : deferred_) destroy(object);
}

void QlCallScope::deleteAfterCall(void* object, void (*destroy)(void*)) noexcept {
  QlCallScope* outermost = currentCall;
  while (outermost && outermost->previous_) outermost = outermost->previous_;
  if (outermost) {
    try { outermost->deferred_.emplace_back(object, destroy); return; } catch (...) {}
  }
  destroy(object);
}

void qlSetError(QlError** slot, const char* message) {
  if (!*slot) *slot = ret(new QlError(message));
}

void qlUnsupportedVersion(QlError** slot, const char* call, const char* required) {
  if (*slot) return;
  auto error = std::make_unique<QlError>(std::string(call) + " requires QuantLib " + required);
  error->call = call;
  error->requiredVersion = required;
  error->linkedVersion = QL_VERSION;
  *slot = ret(error.release());
}

void hasquant::Callback::invoke(const QlCallbackArgs& args) const {
  if (currentCall && *currentCall->slot) throw CallbackFailure();
  void* failure = fn_(&args);
  if (!failure) return;
  std::unique_ptr<void, QlReleaseStable> pending(failure, releaseStable_);
  if (currentCall) {
    qlSetError(currentCall->slot, "Haskell callback failed");
    (*currentCall->slot)->releaseException = releaseStable_;
    (*currentCall->slot)->exception = pending.release();
  }
  // Haskell has returned; only the native exception unwinds native frames.
  throw CallbackFailure();
}

QlCallback* qlNewCallback(QlCallbackFun fn, QlReleaseFun releaseFun,
                          QlReleaseStable releaseStable, QlError** e) {
  QlCallScope callbackScope(e);
  try {
    auto callback = std::shared_ptr<hasquant::Callback>(alloc(new hasquant::Callback(fn, releaseStable)));
    auto result = std::make_unique<QlCallback>(std::move(callback));
    // Haskell still owns the function pointer if either allocation above fails.
    (*result)->adopt(releaseFun);
    return ret(result.release());
  } catch (std::exception& error) { return handleException<QlCallback*>(e, error); }
}
void qlFreeCallback(QlCallback* callback) { del(callback); }
const char* qlErrorMessage(const QlError* error) { return error->message.c_str(); }
const char* qlErrorCall(const QlError* error) { return error->call.c_str(); }
const char* qlErrorRequiredVersion(const QlError* error) { return error->requiredVersion.c_str(); }
const char* qlErrorLinkedVersion(const QlError* error) { return error->linkedVersion.c_str(); }
void* qlTakeErrorException(QlError* error) { return std::exchange(error->exception, nullptr); }
void qlFreeError(QlError* error) { del(error); }

int qlSupports144(void) {return QL_HEX_VERSION >= 0x01440000;}
