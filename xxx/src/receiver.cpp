#include "stdafx.h"
#include "receiver.h"

#include "assembler.h"

receiver::receiver(recv_transport *tr){
	_tr = tr;
}


void receiver::open() {

}

void receiver::recv(std::vector<char> &data) {
	assembler assm;

	assm.open();

	std::vector<char> packet;
	
	while (!assm.complete()) {
		_tr->recv(packet);
		assm.push_packet(packet);
		packet.clear();
	}

	assm.pop_data(data);

	assm.close();
}

void receiver::close() {

}


receiver::~receiver(){
	_tr = nullptr;
}
