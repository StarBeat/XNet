/*
#Copyright 2021 xyang.
*/

#pragma once
#include <string>
namespace x::xnet::defaultimpl
{

    void DefaultXnetLLImpl::Init(std::string ip, int port) {}
    void DefaultXnetLLImpl::Send(const uint8_t*, int) {}
    int DefaultXnetLLImpl::Recv(char* data)
    {
        return 0;
    }
}
