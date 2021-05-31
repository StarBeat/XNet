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

namespace impl
{
struct DefaultXnetLLImpl
{
    void Init(std::string ip, int port);
    void Send(const uint8_t*, int);
    int Recv(char*);
};

template<template<typename>class Queue> requires IQueueImpl<Queue>
struct XcontextSingleThreadImpl
{
    Queue<XInMessage> _inqueue_impl;
    Queue<XOutMessage> _outqueue_impl;
};
}  // namespace impl

struct Xconnection
{
};

template<IXnetLLImpl LLNet>
struct Xcontext
{
    using XcontextImpl = typename std::conditional_t<std::is_same_v<LLNet, impl::DefaultXnetLLImpl>, typename impl::XcontextSingleThreadImpl<std::queue>,
        typename impl::XcontextSingleThreadImpl<x::xalgorithm::lockfree::CircularCasQueue>>;

    Xcontext(){}

    void Send(const XOutMessage& msg)
    {
    }

    XInMessage Recv()
    {
        return *reinterpret_cast<XInMessage*>(nullptr);
    }
 private:
    XcontextImpl _xcontext_impl;
    LLNet _net_impl;
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
        _context.Send(msg);
    }

    XInMessage Recv()
    {
        return _context.Recv();
    }

    bool HasNewMessage()
    {
        return true;
    }
 private:
     Xcontext<impl::DefaultXnetLLImpl> _context;
};
}  // namespace x::xnet
#include "xnet.inl"

