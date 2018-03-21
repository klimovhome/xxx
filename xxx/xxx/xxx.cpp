// xxx.cpp: определяет точку входа для консольного приложения.
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
#include "recv_transport.h"
#include "sender.h"
#include "receiver.h"

// вычитать данные из файла
void readfile(const char *filename, std::vector<char> &data) {
	std::ifstream s(filename, std::ios::binary);
	// copies all data into buffer
	data.insert(data.end(), std::istreambuf_iterator<char>(s), std::istreambuf_iterator<char>());
}

// записать данные в файл
void writefile(const char *filename, std::vector<char> &data) {
	std::ofstream s(filename, std::ios::binary);
	// copies all data into buffer
	//data.insert(data.end(), std::istreambuf_iterator<char>(s), std::istreambuf_iterator<char>());
	std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(s));
}



int main( int argc, char** argv)
{
	// параметры argv[1]
	// отправка send file
	// прием recv file

	if (argc != 3) {
		return 0;
	}
	// запускаем отправку
	if (strcmp(argv[1], "send") == 0) {

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
	// запускаем прием
	if (strcmp(argv[1], "recv") == 0) {

		std::vector<char> data;

		recv_transport tr;
		tr.open();

		receiver recv(&tr);

		recv.open();
		recv.recv(data);
		recv.close();

		tr.close();

		writefile(argv[2], data);
	}


    return 0;

}

