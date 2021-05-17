#pragma once

#include <type_traits>
#include <functional>
#include "function.hpp"

namespace X::Xnet
{
    //template<typename T>
    //concept IXnetLLImpl = requires()
    //{
    //    
    //};
    enum class XnetError : char
    {
        None = 1,
        HostClose,
        RecvFailed,
        SendFailed,
    };

    template<typename T>
    class Xnet
    {
        
        T Impl;

    };
}
#include "xnet.inl"

