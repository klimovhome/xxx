/// тест сокет линукс

#include <stdio.h>
#include <string.h>

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


int main_send(int argc, char** argv) {
    printf("Process to send ... to %s ...\n", argv[2]);
    
    // set up the socket, which is simply an integer
    int rawsock;
    //format socket(int socket_family, int socket_type, int protocol);
    if((rawsock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    {
	printf("Error creating raw socket: ");
	return 1;
    }
    // end of setting up socket

    // bind interface eth0 to the socket
    struct sockaddr_ll sll;
    struct ifreq ifr;

    bzero(&sll, sizeof(sll));
    bzero(&ifr, sizeof(ifr));

    /* First Get the Interface Index  */
    strncpy((char *)ifr.ifr_name, argv[2], IFNAMSIZ);
    if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
    {
	printf("Error getting Interface index !\n");
    }
    printf("interface %s index is %d\n", argv[2], ifr.ifr_ifindex);

    /* Bind our raw socket to this interface */
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(ETH_P_ALL);

    if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1)
    {
	perror("Error binding raw socket to interface\n");
    }

    //end of binding interface to socket


    //create a packet
    struct ethhdr ethernet_header;
    bzero(&ethernet_header, sizeof(ethernet_header));
    char source[] = "90:e2:ba:c2:ef:3d";
    memcpy(ethernet_header.h_dest, (void *)(ether_aton(source)), 6);
    memcpy(ethernet_header.h_source, (void *)(ether_aton(source)), 6);
    ethernet_header.h_proto = htons(ETH_P_IP);

    printf("%s \n", source);
    //end of creating a packet

    char text[16] = "0123456789abcde";
    char packet[64] = {};
    memcpy(packet, &ethernet_header,sizeof(ethernet_header));
    //memcpy(packet+sizeof(ethernet_header), text, 16 );

    //write packet to socket
    for(int i = 0; i < 10; i++){
        if(write(rawsock, packet, 64) == -1)	{
		printf("Error writing bytes to the socket! \n");
        }
        printf("send packet %d\n",i);
    }

    //close the socket
    if(close(rawsock) == -1)
    {
	printf("Error closing the socket! \n");
    }
    
    
    printf("Process to send ... finished\n");
    return 0;
}

int main_recv(int argc, char** argv) {
    printf("Process to recv ... \n");

    // set up the socket, which is simply an integer
    int rawsock;
    //format socket(int socket_family, int socket_type, int protocol);
    if((rawsock = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    {
	printf("Error creating raw socket: ");
	return 1;
    }
    // end of setting up socket

    // bind interface eth0 to the socket
    struct sockaddr_ll sll;
    struct ifreq ifr;

    bzero(&sll, sizeof(sll));
    bzero(&ifr, sizeof(ifr));

    /* First Get the Interface Index  */
    strncpy((char *)ifr.ifr_name, argv[2], IFNAMSIZ);
    if((ioctl(rawsock, SIOCGIFINDEX, &ifr)) == -1)
    {
	printf("Error getting Interface index !\n");
    }
    printf("interface %s index is %d\n", argv[2], ifr.ifr_ifindex);

    /* Bind our raw socket to this interface */
    sll.sll_family = AF_PACKET;
    sll.sll_ifindex = ifr.ifr_ifindex;
    sll.sll_protocol = htons(ETH_P_ALL);

    if((bind(rawsock, (struct sockaddr *)&sll, sizeof(sll)))== -1)
    {
	perror("Error binding raw socket to interface\n");
    }

    //end of binding interface to socket


    //create a packet
    struct ethhdr ethernet_header;
    bzero(&ethernet_header, sizeof(ethernet_header));
    char source[] = "90:e2:ba:c2:ef:3d";
    memcpy(ethernet_header.h_dest, (void *)(ether_aton(source)), 6);
    memcpy(ethernet_header.h_source, (void *)(ether_aton(source)), 6);
    ethernet_header.h_proto = htons(ETH_P_IP);

    printf("%s \n", source);
    //end of creating a packet

    char text[16] = "0123456789abcde";
    char packet[64] = {};
    memcpy(packet, &ethernet_header,sizeof(ethernet_header));
    //memcpy(packet+sizeof(ethernet_header), text, 16 );

    //write packet to socket
    for(int i = 0; i < 10; i++){
	int c = read(rawsock, packet, 64);
        printf("recv packet %d size = %d\n",i,c);
    }

    //close the socket
    if(close(rawsock) == -1)
    {
	printf("Error closing the socket! \n");
    }



    printf("Process to recv ... finished\n");
    return 0;
}

int main(int argc, char**argv){

    if (argc != 3) { 
	printf("xxx send|recv ethX\n");
	return 0;
    }
    // запускаем отправку
    if (strcmp(argv[1], "send") == 0) {
	main_send(argc, argv);
    }
    // запускаем прием
    if (strcmp(argv[1], "recv") == 0) {
	main_recv(argc, argv);
    }
    return 0;
}