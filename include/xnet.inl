#pragma once
#include <string>
namespace X::Xnet::Default
{
	struct DefaultXnetLLImpl
	{
		void Init(std::string ip, int port) {}
		void Send(const uint8_t*, int) {}
		int Recv(char*) {}
	};
}
