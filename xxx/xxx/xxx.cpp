// xxx.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"

#include <iterator>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

#pragma comment (lib, "Ws2_32.lib")
//#pragma comment (lib, "Mswsock.lib")
//#pragma comment (lib, "AdvApi32.lib")

#include "send_transport.h"
#include "sender.h"
#include "receiver.h"

// �������� ������ �� �����
void readfile(const char *filename, std::vector<char> &data) {
	std::ifstream s(filename, std::ios::binary);
	// copies all data into buffer
	data.insert(data.end(), std::istreambuf_iterator<char>(s), std::istreambuf_iterator<char>());
}


int main( int argc, char** argv)
{
	// ��������� argv[1]
	// �������� send file
	// ����� recv file

	if (argc != 3) {
		return 0;
	}
	// ��������� ��������
	if (strcmp(argv[1], "send")) {

		std::vector<char> data;
		readfile(argv[2], data);

		send_transport tr;
		tr.open();

		sender send(&tr);

		send.open();
		send.send(data);
		send.close();

		tr.close();
	}
	// ��������� �����
	if (strcmp(argv[1], "recv")) {

	}


    return 0;

}

