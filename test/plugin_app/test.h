#include <iostream>
#include <string>
#include <boost/dll.hpp>
#include <msgpack.hpp>
#include "common/msg_codec.h"
#include "common/error_code.h"
#include <cinatra.hpp>
#include <rest_rpc.hpp>

using namespace rest_rpc;
using namespace rpc_service;
using namespace cinatra;

struct plugin_resolver{
    plugin_resolver(const std::string& dll_path) : lib_(dll_path){
        call_in_so_ = boost::dll::import_alias<std::string(const char*, size_t)>(lib_, "call_in_so");
    }

    template<typename R>
    R call(const msgpack::sbuffer& buf){
        auto str = call(buf);
        //TODO handle error code and exception
        purecpp::msg_codec codec;
        return codec.result<R>(str.data(), str.size()); //transforma failed will throw exception
    }

    std::string call(const msgpack::sbuffer& buf){
        return call(buf.data(), buf.size());
    }

    std::string call(const char* buf, size_t size){
        using namespace purecpp;

        std::string result;
        try {
            result = call_in_so_(buf, size);
        }
        catch (std::exception& e){
            msg_codec codec;
            result = codec.pack_args_str(purecpp::error_code::FAIL, e.what());
        }

        return result;
    }

private:
    boost::dll::shared_library lib_;
    std::function<std::string(const char*, size_t)> call_in_so_;
};
