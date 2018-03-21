#include "stdafx.h"
#include "formater.h"



formater::formater()
{
}

int formater::crc(const std::vector<char> &data) {
	char crc = 0;
	for (size_t i = 0; i < data.size(); i++) {
		crc = crc ^ (data[i]);
	}
	return (int)crc;
}


formater::~formater()
{
}
