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
    queue.push(static_cast<const int&>(0));  // TODO:xyang const&版本 NOLINT
    std::is_same_v<int&, decltype(queue.pop())>;
};

namespace defaultimpl
{
struct DefaultXnetLLImpl
{
    void Init(std::string ip, int port);
    void Send(const uint8_t*, int);
    int Recv(char*);
};

}  // namespace defaultimpl

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

struct Xconnection
{
};

template<IXnetLLImpl LLNet, template<typename>class Queue> requires IQueueImpl<Queue>
struct Xcontext
{
    Xcontext(){}
 private:
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
    void Update()
    {
    }
    bool HasNewMessage()
    {
        return true;
    }
 private:
     Xcontext<defaultimpl::DefaultXnetLLImpl, x::xalgorithm::lockfree::CircularCasQueue> context;
};
}  // namespace x::xnet
#include "xnet.inl"

