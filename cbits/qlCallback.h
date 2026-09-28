#ifndef HASQUANT_CALLBACK_H
#define HASQUANT_CALLBACK_H

typedef struct QlError QlError;
typedef struct QlCallbackArgs {
  double s;
  double t1;
  double t2;
  const double* input;
  double* output;
  unsigned size;
  unsigned direction;
} QlCallbackArgs;

typedef void* (*QlCallbackFun)(const QlCallbackArgs*);
typedef void (*QlReleaseFun)(void (*)(void));
typedef void (*QlReleaseStable)(void*);

#ifdef __cplusplus
extern "C" {
#endif
  QlCallback* qlNewCallback(QlCallbackFun fn, QlReleaseFun releaseFun,
                            QlReleaseStable releaseStable, QlError** e);
  void qlFreeCallback(QlCallback* callback);
  const char* qlErrorMessage(const QlError* error);
  void* qlTakeErrorException(QlError* error);
  void qlFreeError(QlError* error);
#ifdef __cplusplus
}
#endif
#endif
