#include <napi.h>
#include <string>
#include "hello.h"

Napi::String helloWorldFonc(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string result = helloWorld();
    return Napi::String::New(env, result);
}
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "helloWorld"),
        Napi::Function::New(env, helloWorldFonc)
    );
    return exports;
}
NODE_API_MODULE(helloModule, Init)
