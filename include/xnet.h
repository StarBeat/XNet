/*
#Copyright 2021 xyang.
*/

#pragma once

#include <type_traits>
#include <functional>
#include <queue>
#include <string>
#include "function.hpp"
#include "util.hpp"
#include "queue.hpp"

namespace x::xnet
{
template<typename T>
concept IXnetLLImpl = requires()
{
    std::is_same_v<void(std::string, int), delta::FuncTraits_Signature<decltype(&T::Init)>>;
    std::is_same_v<void(const uint8_t*, int), delta::FuncTraits_Signature<decltype(&T::Send)>>;
    std::is_same_v<int(char*), delta::FuncTraits_Signature<decltype(&T::Recv)>>;
};
template<template<typename>class IQueue>
concept IQueueImpl = requires(IQueue<int> queue)
{
    std::is_same_v<void(const int&), decltype(delta::MemFuncOf<IQueue<int>, void(const int&)>::get(&IQueue<int>::push))>;
    std::is_same_v<void(int&&), decltype(delta::MemFuncOf<IQueue<int>, void(int&&)>::get(&IQueue<int>::push))>;
    std::is_same_v<int&, decltype(queue.pop())>;
};

namespace impl
{
struct DefaultXnetLLImpl
{
    void Init(std::string ip, int port);
    void Send(const uint8_t*, int);
    int Recv(char*);
};

struct XcontextSingleThreadImpl
{
};
}  // namespace impl

#pragma region typedef

enum class XnetError : uint8_t
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

struct Xconnection
{
};

template<IXnetLLImpl LLNet, template<typename>class Queue> requires IQueueImpl<Queue>
struct Xcontext
{
    using XcontextImpl = typename std::enable_if<std::is_same_v<LLNet, impl::DefaultXnetLLImpl>, typename impl::XcontextSingleThreadImpl>::type;

    Xcontext(){}

    void Send(const XOutMessage& msg)
    {
    }

    XInMessage Recv()
    {
        return *reinterpret_cast<XInMessage*>(nullptr);
    }
 private:
    XcontextImpl xcontext;
    LLNet net_impl;
    Queue<XInMessage> inqueue_impl;
    Queue<XOutMessage> outqueue_impl;
};

class DLL_EXPORT Xnet
{
 public:
    Xnet()
    {
    }
    ~Xnet()
    {
    }

    void Send(const XOutMessage& msg)
    {
        context.Send(msg);
    }

    XInMessage Recv()
    {
        return context.Recv();
    }

    bool HasNewMessage()
    {
        return true;
    }
 private:
     Xcontext<impl::DefaultXnetLLImpl, x::xalgorithm::lockfree::CircularCasQueue> context;
};
}  // namespace x::xnet
#include "xnet.inl"

