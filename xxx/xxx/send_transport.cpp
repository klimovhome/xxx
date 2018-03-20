#include "stdafx.h"
#include "send_transport.h"


send_transport::send_transport() {

}

void send_transport::open() {
	_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

void send_transport::send(const std::vector<char> &data) {
	sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (data.size() == 0) {
		return;
	}

	int result = ::sendto(_socket, data.data(), data.size(), 0, (SOCKADDR *)&addr, sizeof(addr));
	if (result == SOCKET_ERROR) {
		//throw std::exception("void send_transport::send(const std::vector<char> &data), result == SOCKET_ERROR");
	}
	if (result != data.size()) {
		//throw std::exception("void send_transport::send(const std::vector<char> &data), result != data.size()");
	}
}

void send_transport::close() {
	closesocket(_socket);
	_socket = 0;
}

send_transport::~send_transport() {
	_socket = 0;
	if (_socket != 0) {
		//throw std::exception("send_transport::~send_transport(), _socket != nullptr");
	}
}