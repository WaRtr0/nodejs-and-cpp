#include <napi.h>
#include "addition.h"
using namespace std;

Napi::Number additionCalc(const Napi::CallbackInfo& info) { 
    Napi::Env env = info.Env();
    int A = (int) info[0].ToNumber();
    int B = (int) info[1].ToNumber();
    int result = addition( A , B );

    return Napi::Number::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "additionCalc"),
        Napi::Function::New(env, additionCalc)
    );
    return exports;
}
NODE_API_MODULE(additionModule, Init)
