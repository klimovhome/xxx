#pragma once

#include <vector>
#include <cstddef>

#define max_packet_size 256
#define header_prefix 0x0ABCDEF0

struct header {
	int _prefix; // header_prefix
	int _index;  // packet index
	int _count;  // all packet count
	int _offset;	 // data offset 
	int _len;    // len the packet
	long long _crc;    // crc of all data
	int _data_len; // len of data

	bool validate();
};

class formater
{
public:
	formater();
	virtual ~formater();

	static long long crc(const std::vector<char> &data);

};

