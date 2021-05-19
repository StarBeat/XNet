/*
#Copyright 2021 xyang.
*/

#pragma once

#include <type_traits>
#include <functional>
#include <string>
#include "function.hpp"
#include "util.hpp"
#include "queue.hpp"

namespace x::xnet
{
template<typename T>
concept IXnetLLImpl = requires()
{
    std::is_same_v<void(std::string, int), delta::FuncTraits_Signature<decltype(T::Init)>>;
    std::is_same_v<void(const uint8_t*, int), delta::FuncTraits_Signature<decltype(T::Send)>>;
    std::is_same_v<int(char*), delta::FuncTraits_Signature<decltype(T::Recv)>>;
};
namespace defaultimpl
{
struct DefaultXnetLLImpl;
template<IXnetLLImpl T = DefaultXnetLLImpl>
struct XContext
{
};
}  // namespace default

#pragma region typedef

enum class XnetError : char
{
    EnumNone = 1,
    EnumHostClose,
    EnumRecvFailed,
    EnumSendFailed,
};

struct XNetMessage
{
    uint16_t size;
    uint8_t* data;
    int32_t id;
};

using XOutMessage = XNetMessage;
using XInMessage = XNetMessage;
#pragma endregion

struct XConnection
{
};

template<IXnetLLImpl T>
struct XContext : defaultimpl::XContext<T>
{
 private:
    T Impl;
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
}  // namespace x::xnet
#include "xnet.inl"

