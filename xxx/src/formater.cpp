//#include "stdafx.h"
#include "formater.h"

bool header::validate() {
	//int _prefix; // header_prefix
	if (_prefix != header_prefix) return false;

	//int _index;  // packet index
	if (_index >= _count) return false;
	
	//int _count;  // all packet count
	//if (_count + 1 > _data_len / max_packet_size) return false;
	
	//int _offset;	 // data offset 
	if (_offset >= _data_len) return false;

	// len the packet
	if ( _len <= sizeof(header) ) return false;    

	//int _crc;    // crc of all data

	// len of data
	if (_data_len > _count * max_packet_size) return false; 
	
	return true;
}



formater::formater()
{
}

long long formater::crc(const std::vector<char> &data) {
	long long crc = 0;
	long long *ptr = (long long*)&data.front();
	for (size_t i = 0; i < data.size()/sizeof(long long); i++) {
		crc = crc ^ ptr[i];
	}
	return crc;
}


formater::~formater()
{
}
