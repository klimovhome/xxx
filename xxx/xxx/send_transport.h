#pragma once

#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")

class send_transport
{
protected:
	SOCKET _socket = 0;
public:
	send_transport();

	void open();
	void send(const std::vector<char> &data);
	void close();

	virtual ~send_transport();
};

