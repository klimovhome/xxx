#include "stdafx.h"
#include "sender.h"

sender::sender(const send_transport *st) {
	if (st == nullptr) {
		//throw("sender::sender(const send_transport *st) st == nullptr");
	}

	_st = st;
}

sender::~sender() {
	_st = nullptr;
}

void sender::open() {

}

void sender::send(const std::vector<char>& data) {

}

void sender::close() {

}
