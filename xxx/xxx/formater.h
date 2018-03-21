#pragma once


#define max_packet_size 256
#define header_prefix 0x0ABCDEF0

struct header {
	int _prefix; // header_prefix
	int _index;  // packet index
	int _count;  // all packet count
	int _len;    // len the packet
	int _crc;    // crc of all data
};

class formater
{
public:
	formater();
	virtual ~formater();
};

