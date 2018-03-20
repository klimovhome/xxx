#pragma once

#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")

class recv_transport
{
protected:
	SOCKET _socket = 0;
public:
	recv_transport();

	void open();
	void recv(std::vector<char> &data);
	void close();
	
	virtual ~recv_transport();
};

