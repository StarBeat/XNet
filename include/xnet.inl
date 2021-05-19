/*
#Copyright 2021 xyang.
*/

#pragma once
#include <string>
namespace x::xnet::default
{
struct DefaultXnetLLImpl
{
    void Init(std::string ip, int port) {}
    void Send(const uint8_t*, int) {}
    int Recv(char*) {}
};
}
