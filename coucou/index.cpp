#include <napi.h>
#include <string>
#include "coucou.h"

Napi::String coucouFonc(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string user = (std::string) info[0].ToString();
    std::string result = coucouUser( user );
    return Napi::String::New(env, result);
}
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(
        Napi::String::New(env, "coucouFonc"),
        Napi::Function::New(env, coucouFonc)
    );
    return exports;
}
NODE_API_MODULE(coucouModule, Init)
