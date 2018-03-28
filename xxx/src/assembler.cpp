#include "stdafx.h"
#include "assembler.h"


assembler::assembler(){
	_complete = false;
	_count = 0;
}


void assembler::open() {

}

void assembler::push_packet(const std::vector<char> &packet) {
	if (packet.size() == 0) {
		//printf("Error packet packet.size() == 0");
		return;
	}

	if (packet.size() < sizeof(header) ) {
		printf("Error packet packet.size() < sizeof(header)");
		return;
	}
	
	header *hdr = (header *)&packet.front();
	if (!hdr->validate()) {
		printf("void assembler::push_packet !hdr->validate()");
		return;
	}

	// first packet
	if (_result.size() == 0) {
		_header = *hdr;
		_result.resize(hdr->_data_len);
	}

	// copy to result
	printf("\b index = %d count = %d", hdr->_index, hdr->_count);
	std::copy(packet.cbegin() + sizeof(header), packet.cend(), _result.begin() + hdr->_offset);
	_count++;

	if (hdr->_index + 1 == hdr->_count) {
		_complete = true;

		if (_count != _header._count) {
			printf("assembler: Recv not all data!");
		}

		int64_t crc = formater::crc(_result);
		if (crc != _header._crc) {
			printf("assembler: crc error!");
		}
	}

}

void assembler::pop_data(std::vector<char> &data) {
	data = _result;
}

void assembler::close() {

}

bool assembler::complete() {
	return _complete;
}

assembler::~assembler(){

}
