#pragma once

#ifdef __XXX_WINDOWS__
#include <winsock2.h>
#pragma comment (lib, "Ws2_32.lib")
#endif // __XXX_WINDOWS__

#include <vector>


#ifdef __XXX_WINDOWS__
class send_transport_windows
{
protected:
	SOCKET _socket = 0;
public:
	send_transport_windows();

	void open();
	void send(const std::vector<char> &data) const;
	void close();

	virtual ~send_transport_windows();
};

typedef send_transport_windows send_transport;
#endif // __XXX_WINDOWS__


#ifdef __XXX_LINUX__
class send_transport_linux
{
protected:
	int _socket;// = 0;
public:
	send_transport_linux();

	void open();
	void send(const std::vector<char> &data) const;
	void close();

	virtual ~send_transport_linux();
};

typedef send_transport_linux send_transport;
#endif // __XXX_LINUX__
