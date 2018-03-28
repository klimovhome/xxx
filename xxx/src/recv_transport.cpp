#include "stdafx.h"
#include "recv_transport.h"

recv_transport::recv_transport() {

}


void recv_transport::open() {

	WSADATA wsa;
	unsigned short usWSAVersion = MAKEWORD(2, 2);
	//Start WSA
	WSAStartup(usWSAVersion, &wsa);

	_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_socket == 0) {
		throw std::exception("_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); _socket == 0");
	}

	/*
	timeval tv;
	tv.tv_sec = 0;
	tv.tv_usec = 1024;
	// Set Timeout for recv call
	if (setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<char*>(&tv), sizeof(timeval))) {
		throw std::exception("int result = bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) error");
	}
	*/
	u_long nMode = 1; // 1: NON-BLOCKING
	if (ioctlsocket(_socket, FIONBIO, &nMode) == SOCKET_ERROR) {
		throw std::exception("ioctlsocket(_socket, FIONBIO, &nMode) == SOCKET_ERROR");
	}

	sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	// first bind succeeds
	int result = bind(_socket, (SOCKADDR*)&addr, sizeof(addr));
	if (result < 0) {
		throw std::exception("int result = bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) error");
	}
}

void recv_transport::recv(std::vector<char> &data) {
	char buffer[1024] = { 0 };
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	int result = recvfrom(_socket, buffer, 1024, 0, (struct sockaddr *)&addr, &addrlen);

	if (result > 0) {
		data.resize(result);
		//data.insert(data.end(), buffer, buffer + result);
		std::copy(buffer, buffer + result, data.begin());
	}
	else {
		data.clear();
	}
}

void recv_transport::close() {
	closesocket(_socket);
	_socket = 0;

	WSACleanup();
}


recv_transport::~recv_transport() {
	_socket = 0;
	if (_socket != 0) {
		// throw
	}
}
