/*
*  screenres.cc
*  David Mark Clements 2015
*  @davidmarkclem
*
*/

#include <node.h>
#include <nan.h>
#include <string>

#include "headers.h"

using v8::Local;
using v8::Object;
using v8::Array;
using v8::Number;
using v8::String;
using v8::FunctionTemplate;

void init(Local<Object>);

NAN_METHOD(set) {
  Nan::HandleScope scope;
  int code = changeRes(Nan::To<uint32_t>(info[0]).ToChecked(), Nan::To<uint32_t>(info[1]).ToChecked());

  if (!code) {
    info.GetReturnValue().SetUndefined();
  } else {
    info.GetReturnValue().Set(Nan::New<Number>(code));
  }
}

NAN_METHOD(get) {
  Nan::HandleScope scope;
  Resolution res = fetchRes();
  Local<Array> arr = Nan::New<Array>(2);
  Nan::Set(arr, 0, Nan::New<Number>(res.width));
  Nan::Set(arr, 1, Nan::New<Number>(res.height));
  info.GetReturnValue().Set(arr);
}

NAN_MODULE_INIT (init) {
  NAN_EXPORT(target, get);
  NAN_EXPORT(target, set);
}

NODE_MODULE(screenres, init);
