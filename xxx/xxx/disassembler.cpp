#include "stdafx.h"
#include "disassembler.h"


disassembler::disassembler() {
}

void disassembler::open() { 

}

void disassembler::push_data(const std::vector<char> &data) {
	if (data.size() == 0) {
		return;
	}

	int count = data.size() / max_packet_size;
	if (data.size() % max_packet_size) count++;
	int crc = formater::crc(data);

	for (int index = 0; index < count; index++) {
		int begin = index * max_packet_size;
		int end = (index + 1) * max_packet_size;
		if (end > (int)data.size()) end = (int)data.size();

		header hdr;
		hdr._prefix = header_prefix;
		hdr._index = index;
		hdr._count = count;
		hdr._offset = begin;
		hdr._len = end - begin;
		hdr._crc = crc;
		hdr._data_len = data.size();

		std::vector<char> packet;
		packet.insert(packet.end(), ((char*)&hdr), ((char*)&hdr) + sizeof(hdr));
		packet.insert(packet.end(), &data.front() + begin, &data.front() + end);
		
		_packet_list.push(packet);
	}


}

void disassembler::pop_packet(std::vector<char> &packet) {
	if (_packet_list.empty()) {
		packet.clear();
		return;
	}
	packet = _packet_list.front();
	_packet_list.pop();
}

void disassembler::close() {

}

disassembler::~disassembler() {
}
