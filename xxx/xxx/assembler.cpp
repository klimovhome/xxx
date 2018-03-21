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
		return;
	}

	header *hdr = (header *)&packet.front();
	if (hdr->_prefix != header_prefix) {
		throw std::exception("void assembler::push_packet(const std::vector<char> &packet) header prefix error");
	}

	if (_result.size() == 0) {
		// first packet
		_result.resize(hdr->_data_len);
	}

	// copy to result
	//std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
	std::copy(packet.cbegin() + sizeof(header), packet.cend(), _result.begin() + hdr->_offset);
	_count++;

	if (hdr->_index + 1 == hdr->_count) {
		_complete = true;

		if (_count != hdr->_count) {
			printf("assembler: Recv not all data!");
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
