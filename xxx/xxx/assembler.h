#pragma once

#include "formater.h"

#include <vector>

class assembler
{
protected:
	std::vector<char> _result;
	bool _complete;
	int _count;
public:
	assembler();

	void open();
	void push_packet(const std::vector<char> &packet);
	void pop_data(std::vector<char> &data);
	void close();

	bool complete();

	virtual ~assembler();
};

