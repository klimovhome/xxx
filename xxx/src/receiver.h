#pragma once

#include <vector>

#include "recv_transport.h"

class receiver
{
protected:
	recv_transport *_tr;
public:
	receiver(recv_transport *tr);

	void open();
	void recv(std::vector<char> &data);
	void close();

	virtual ~receiver();
};

