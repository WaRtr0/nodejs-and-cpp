#include <napi.h>
#include "multiplication.h"
using namespace std;

Napi::Number multiplicationCalc(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    int A = (int) info[0].ToNumber();
    int B = (int) info[1].ToNumber();
    int result = multiplication( A , B );

    return Napi::Number::New(env, result);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "multiplicationCalc"),
        Napi::Function::New(env, multiplicationCalc)
    );
    return exports;
}
NODE_API_MODULE(multiplicationModule, Init)
