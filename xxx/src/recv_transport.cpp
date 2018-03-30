#include "recv_transport.h"

#ifdef __XXX_WINDOWS__  

recv_transport_windows::recv_transport_windows() {

}

void recv_transport_windows::open() {
	WSADATA wsa;
	unsigned short usWSAVersion = MAKEWORD(2, 2);
	//Start WSA
	WSAStartup(usWSAVersion, &wsa);

	_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (_socket == 0) {
		throw std::exception("_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); _socket == 0");
	}

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

void recv_transport_windows::recv(std::vector<char> &data) {
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

void recv_transport_windows::close() {
	closesocket(_socket);
	_socket = 0;

	WSACleanup();
}

recv_transport_windows::~recv_transport_windows() {
	_socket = 0;
	if (_socket != 0) {
		// throw
	}
}

#endif // __XXX_WINDOWS__


#ifdef __XXX_LINUX__

recv_transport_linux::recv_transport_linux() {
	_socket = 0;
}

void recv_transport_linux::open() {
	char eth[] = "eth2";

	// set up the socket, which is simply an integer
	 _socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	//format socket(int socket_family, int socket_type, int protocol);
	if (_socket == -1) {
		printf("Error creating raw socket ");
		throw std::exception("void recv_transport_linux::open(),Error creating raw socket");
	}
	// end of setting up socket

	// bind interface eth0 to the socket
	struct sockaddr_ll sll;
	struct ifreq ifr;

	bzero(&sll, sizeof(sll));
	bzero(&ifr, sizeof(ifr));

	/* First Get the Interface Index  */
	strncpy((char *)ifr.ifr_name, eth, IFNAMSIZ);
	if ((ioctl(_socket, SIOCGIFINDEX, &ifr)) == -1) {
		printf("Error getting Interface index !\n");
		throw std::exception("void recv_transport_linux::open(),Error getting Interface index");
	}
	printf("interface %s index is %d\n", eth, ifr.ifr_ifindex);

	/* Bind our raw socket to this interface */
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = ifr.ifr_ifindex;
	sll.sll_protocol = htons(ETH_P_ALL);

	if ((bind(_socket, (struct sockaddr *)&sll, sizeof(sll))) == -1)
	{
		printf("Error binding raw socket to interface\n");
		throw std::exception("void recv_transport_linux::open(),Error binding raw socket to interface");
	}
}

void recv_transport_linux::recv(std::vector<char> &data) {
	char packet[2048] = {};
	data.clear();

	int result = read(_socket, packet, sizeof(packet));
	if (result < 0) {
		printf("read socket error");
		return;
	}
	if (result > sizeof(ethernet_header)) {
		data.resize(result - sizeof(ethernet_header));
		std::copy(buffer + sizeof(ethernet_header), buffer + result, data.begin());
	}
}

void recv_transport_linux::close() {
	//close the socket
	if (close(_socket) == -1)
	{
		printf("Error closing the socket! \n");
	}
	_socket = 0;
}

void recv_transport_linux::~recv_transport_linux() {

}

#endif // __XXX_LINUX__