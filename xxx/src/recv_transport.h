#pragma once

#ifdef __XXX_WINDOWS__
#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")
#endif // __XXX_WINDOWS__

#ifdef __XXX_LINUX__


#endif // __XXX_LINUX__

#include <vector>

#ifdef __XXX_WINDOWS__
class recv_transport_windows 
{
protected:
	SOCKET _socket = 0;
public:
	recv_transport_windows();

	void open();
	void recv(std::vector<char> &data);
	void close();

	virtual ~recv_transport_windows();
};

typedef recv_transport_windows recv_transport;
#endif // __XXX_WINDOWS__

#ifdef __XXX_LINUX__
class recv_transport_linux 
{
protected:
	int _socket = 0;
public:
	recv_transport_linux();

	void open();
	void recv(std::vector<char> &data);
	void close();

	virtual ~recv_transport_linux();
};

typedef recv_transport_linux recv_transport;
#endif // __XXX_LINUX__

