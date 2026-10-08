#ifndef HASQUANT_CALLBACK_HPP
#define HASQUANT_CALLBACK_HPP

#include <exception>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace hasquant { class Callback; }
using QlCallback = std::shared_ptr<hasquant::Callback>;
#include "qlCallback.h"

struct QlError {
  explicit QlError(std::string text) : message(std::move(text)) {}
  ~QlError() { if (exception) releaseException(exception); }
  QlError(const QlError&) = delete;
  QlError& operator=(const QlError&) = delete;
  std::string message;
  std::string call, requiredVersion, linkedVersion;
  void* exception = nullptr;
  QlReleaseStable releaseException = nullptr;
};

void qlSetError(QlError** slot, const char* message);
void qlUnsupportedVersion(QlError** slot, const char* call, const char* required);
// False after reporting call as unsupported when a QuantLib <= 1.43 receives a non-default 1.44 argument.
bool ql144Default(QlError** slot, const char* call, bool isDefault);

class QlCallScope {
public:
  explicit QlCallScope(QlError** slot) noexcept;
  ~QlCallScope();
  QlCallScope(const QlCallScope&) = delete;
  QlCallScope& operator=(const QlCallScope&) = delete;
  // Deletes an object once the outermost native call on this thread returns, or at once outside one.
  static void deleteAfterCall(void* object, void (*destroy)(void*)) noexcept;
  QlError** slot;
private:
  QlCallScope* previous_;
  std::vector<std::pair<void*, void (*)(void*)>> deferred_;
};

namespace hasquant {
  class Callback {
  public:
    Callback(QlCallbackFun fn, QlReleaseStable releaseStable)
      : fn_(fn), releaseStable_(releaseStable) {}
    ~Callback() { if (releaseFun_) releaseFun_(reinterpret_cast<void (*)(void)>(fn_)); }
    Callback(const Callback&) = delete;
    Callback& operator=(const Callback&) = delete;
    void adopt(QlReleaseFun release) noexcept { releaseFun_ = release; }
    void invoke(const QlCallbackArgs& args) const;
    double scalar(double x, double y = 0.0) const {
      double result = 0.0;
      invoke(QlCallbackArgs{x, y, 0.0, nullptr, &result, 0, 0});
      return result;
    }
    double array(const double* input, unsigned size, double time = 0.0) const {
      double result = 0.0;
      invoke(QlCallbackArgs{0.0, time, 0.0, input, &result, size, 0});
      return result;
    }
  private:
    QlCallbackFun fn_;
    QlReleaseStable releaseStable_;
    QlReleaseFun releaseFun_ = nullptr;
  };
  // A finalizer run by a callback's GC must not delete an object that the interrupted call uses.
  template <class T> struct DeleteAfterCall {
    void operator()(T* object) const noexcept {
      QlCallScope::deleteAfterCall(object, [](void* p) { delete static_cast<T*>(p); });
    }
  };
  struct UnaryCallback {
    QlCallback owner;
    double operator()(double x) const { return owner->scalar(x); }
  };
  struct BinaryCallback {
    QlCallback owner;
    double operator()(double x, double y) const { return owner->scalar(x, y); }
  };
}
#endif
