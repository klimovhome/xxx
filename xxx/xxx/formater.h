#pragma once

#include <vector>

#define max_packet_size 256
#define header_prefix 0x0ABCDEF0

struct header {
	int _prefix; // header_prefix
	int _index;  // packet index
	int _count;  // all packet count
	int _offset;	 // data offset 
	int _len;    // len the packet
	int _crc;    // crc of all data
	int _data_len; // len of data
};

class formater
{
public:
	formater();
	virtual ~formater();

	static int crc(const std::vector<char> &data);

};

