#include "stdafx.h"
#include "recv_transport.h"

recv_transport::recv_transport() {

}


void recv_transport::open() {
	_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr;
	memset(&addr, 0, sizeof(struct sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = INADDR_ANY;

	// first bind succeeds
	int result = bind(_socket, (SOCKADDR*)&addr, sizeof(addr));
	if (result < 0) {
		//throw std::exception("int result = bind(_socket, (SOCKADDR*)&addr, sizeof(addr)) error");
	}
}

void recv_transport::recv(std::vector<char> &data) {
	char buffer[1024] = { 0 };
	struct sockaddr_in addr;
	int addrlen = sizeof(addr);
	int result = recvfrom(_socket, buffer, 1024, 0, (struct sockaddr *)&addr, &addrlen);

	if (result > 0) {
		data.insert(data.end(), buffer, buffer + result);
	}
}

void recv_transport::close() {
	closesocket(_socket);
	_socket = 0;
}


recv_transport::~recv_transport() {
	_socket = 0;
	if (_socket != 0) {
		// throw
	}
}
