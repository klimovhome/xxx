#pragma once

#include <vector>

#include "formater.h"

class assembler
{
protected:
	std::vector<char> _result;
	bool _complete;

	int _count;
	header _header;
public:
	assembler();

	void open();
	void push_packet(const std::vector<char> &packet);
	void pop_data(std::vector<char> &data);
	void close();

	bool complete();

	virtual ~assembler();
};

