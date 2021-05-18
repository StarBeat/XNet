#pragma once

#include <type_traits>
#include <functional>
#include <string>
#include "function.hpp"

namespace X::Xnet
{
    namespace X::Xnet::Default
    {
        struct DefaultXnetLLImpl;
    }
    template<typename T>
    concept IXnetLLImpl = requires()
    {
        std::is_same_v<void(std::string, int), Delta::FuncTraits_Signature<decltype(T::Init)>>;
        std::is_same_v<void(const uint8_t*, int), Delta::FuncTraits_Signature<decltype(T::Send)>>;
        std::is_same_v<int(char*), Delta::FuncTraits_Signature<decltype(T::Recv)>>;

    };

#pragma region 

    enum class XnetError : char
    {
        None = 1,
        HostClose,
        RecvFailed,
        SendFailed,
    };

    struct XNetMessage
    {
        uint16_t size;
        uint8_t* data;
        int32_t id;
    };

    using XOutMessage = XNetMessage;
    using XInMessage = XNetMessage;

    struct XConnection
    {

    };
#pragma endregion

    struct XContext
    {
    private:

        IXnetLLImpl Impl;
    };

    class Xnet
    {
    public:
        Xnet()
        {

        }

        ~Xnet()
        {

        }

        void Update()
        {

        }
    private:

    };
}
#include "xnet.inl"

