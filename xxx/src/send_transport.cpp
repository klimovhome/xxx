//#include "stdafx.h"
#include "send_transport.h"

#include <string.h>
#include <stdio.h>


#ifdef __XXX_WINDOWS__
send_transport_windows::send_transport_windows() {

}

void send_transport_windows::open() {
	WSADATA wsa;
	unsigned short usWSAVersion = MAKEWORD(2, 2);
	//Start WSA
	WSAStartup(usWSAVersion, &wsa);
	
	_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

void send_transport_windows::send(const std::vector<char> &data) const {
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
		throw std::exception("void send_transport_windows::send(const std::vector<char> &data), result == SOCKET_ERROR");
	}
	if (result != data.size()) {
		throw std::exception("void send_transport_windows::send(const std::vector<char> &data), result != data.size()");
	}
}

void send_transport_windows::close() {
	closesocket(_socket);
	_socket = 0;

	WSACleanup( );
}

send_transport_windows::~send_transport_windows() {
	_socket = 0;
	if (_socket != 0) {
		//throw std::exception("send_transport_windows::~send_transport_windows(), _socket != nullptr");
	}
}
#endif // __XXX_WINDOWS__


#ifdef __XXX_LINUX__

#include <sys/socket.h>
#include <sys/ioctl.h>
#include <linux/if_packet.h>
#include <linux/if_ether.h>
//#include <linux/if_arp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <netinet/ether.h>
#include <net/if.h>
	
send_transport_linux::send_transport_linux() {
	_socket = 0;
}

void send_transport_linux::open() {
	char eth[] = "eth2";

	// set up the socket, which is simply an integer
	_socket = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	//format socket(int socket_family, int socket_type, int protocol);
	if (_socket == -1) {
		printf("Error creating raw socket ");
		//throw std::exception("void recv_transport_linux::open(),Error creating raw socket");
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
		//throw std::exception("void recv_transport_linux::open(),Error getting Interface index");
	}
	printf("interface %s index is %d\n", eth, ifr.ifr_ifindex);

	/* Bind our raw socket to this interface */
	sll.sll_family = AF_PACKET;
	sll.sll_ifindex = ifr.ifr_ifindex;
	sll.sll_protocol = htons(ETH_P_ALL);

	if ((bind(_socket, (struct sockaddr *)&sll, sizeof(sll))) == -1)
	{
		printf("Error binding raw socket to interface\n");
		//throw std::exception("void recv_transport_linux::open(),Error binding raw socket to interface");
	}

}

void send_transport_linux::send(const std::vector<char> &data) const {
	char source[] = "90:e2:ba:c2:ef:3d";

	//create a packet
	struct ethhdr ethernet_header;
	bzero(&ethernet_header, sizeof(ethernet_header));
	
	memcpy(ethernet_header.h_dest, (void *)(ether_aton(source)), 6);
	memcpy(ethernet_header.h_source, (void *)(ether_aton(source)), 6);
	ethernet_header.h_proto = htons(ETH_P_IP);

	printf("%s \n", source);
	//end of creating a packet

	char packet[2048] = {};
	memcpy(packet, &ethernet_header, sizeof(ethernet_header));
	memcpy(packet + sizeof(ethernet_header), (void*)data.front(), data.size() );

	//write packet to socket
	if (write(_socket, packet, data.size() + sizeof(ethernet_header)) == -1) {
		printf("Error writing bytes to the socket! \n");
	}
}

void send_transport_linux::close() {
	//close the socket
	if (::close(_socket) == -1)
	{
		printf("Error closing the socket! \n");
	}
	_socket = 0;
}

send_transport_linux::~send_transport_linux() {

}

#endif // __XXX_LINUX__

