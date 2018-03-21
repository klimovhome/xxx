#pragma once

#include <vector>
#include <queue>

#include "formater.h"

class disassembler
{
protected:
	std::queue< std::vector<char> > _packet_list;

public:
	disassembler();

	void open();
	void push_data(const std::vector<char> &data);
	void pop_packet(std::vector<char> &packet);
	void close();

	virtual ~disassembler();
};

