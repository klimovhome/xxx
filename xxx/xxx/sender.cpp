#include "stdafx.h"
#include "sender.h"

#include "disassembler.h"

sender::sender(const send_transport *st) {
	if (st == nullptr) {
		throw("sender::sender(const send_transport *st) st == nullptr");
	}

	_st = st;
}

sender::~sender() {
	_st = nullptr;
}

void sender::open() {

}

void sender::send(const std::vector<char>& data) {
	disassembler dis;

	dis.open();
	dis.push_data(data);

	std::vector<char> packet;
	dis.pop_packet(packet);
	while (packet.size() != 0) {
		_st->send(packet);
		dis.pop_packet(packet);
	}
	
	dis.close();

}

void sender::close() {

}
