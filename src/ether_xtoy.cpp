#include <napi.h>
#include <netinet/ether.h>
#include <netinet/if_ether.h>
#include <string.h>
#include <uv.h>

#include <cerrno>
#include <string>

[[noreturn]] static void throwErrnoError(Napi::Env env, int code) {
    napi_value error;
    napi_create_error(env, Napi::Value::From(env, uv_err_name(-code)), Napi::Value::From(env, uv_strerror(-code)), &error);

    Napi::Error err(env, error);
    err.Set("errno", Napi::Value::From(env, code));
    throw err;
}

static Napi::Value EtherNtoA(const Napi::CallbackInfo& info) {
    const Napi::Env& env = info.Env();
    if (info.Length() != 1) {
        throw Napi::TypeError::New(env, "Wrong number of arguments");
    }

    if (!info[0].IsBuffer()) {
        throw Napi::TypeError::New(env, "The argument is expected to be a Buffer");
    }

    Napi::Buffer<ether_addr> addrBuf = info[0].As<Napi::Buffer<ether_addr> >();
    ether_addr* addr = addrBuf.Data();
    char* buf = ether_ntoa(addr);
    int bufLen = strlen(buf);
    if (!bufLen) {
        throwErrnoError(env, errno);
    }

    return Napi::Value::From(env, buf);
}

static Napi::Value EtherAtoN(const Napi::CallbackInfo& info) {
    const Napi::Env& env = info.Env();
    if (info.Length() != 1) {
        throw Napi::TypeError::New(env, "Wrong number of arguments");
    }

    if (!info[0].IsString()) {
        throw Napi::TypeError::New(env, "The argument is expected to be a string");
    }

    const Napi::String arg = info[0].As<Napi::String>();
    const std::string str_addr = arg;
	const unsigned char * addr = reinterpret_cast<const unsigned char*>(ether_aton(str_addr.c_str()));
	if(addr==NULL){
        throwErrnoError(env, errno);
	}
	return Napi::Buffer<unsigned char>::Copy(env, addr, sizeof(ether_addr));
}

static Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set("ether_ntoa", Napi::Function::New(env, EtherNtoA));
    exports.Set("ether_aton", Napi::Function::New(env, EtherAtoN));
    return exports;
}

NODE_API_MODULE(inet_xtoy, Init)
