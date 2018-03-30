// xxx.cpp: определяет точку входа для консольного приложения.

//#include "stdafx.h"

//#define _XXX_LINUX_
//#define _XXX_WINDOWS_

#include <iterator>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iostream>
#include <fstream>

#include "send_transport.h"
#include "recv_transport.h"
#include "sender.h"
#include "receiver.h"

// вычитать данные из файла
void readfile(const char *filename, std::vector<char> &data) {
	std::ifstream s(filename, std::ios::binary);
	if (!s.is_open()) {
		printf("File (%s) open error\n", filename);
		return;
	}
	// copies all data into buffer
	data.insert(data.end(), std::istreambuf_iterator<char>(s), std::istreambuf_iterator<char>());
}

// записать данные в файл
void writefile(const char *filename, std::vector<char> &data) {
	std::ofstream s(filename, std::ios::binary);
	if (!s.is_open()) {
		printf("File (%s) open error\n", filename);
		return;
	}
	// copies all data into buffer
	std::copy(data.begin(), data.end(), std::ostreambuf_iterator<char>(s));
}


int main_send(int argc, char** argv) {
	printf("Process to send ... \n");

	std::vector<char> data;
	readfile(argv[2], data);

	send_transport tr;
	tr.open();

	sender send(&tr);

	send.open();
	send.send(data);
	send.close();

	tr.close();

	printf("Process to send ... finished\n");
	return 0;
}

int main_recv(int argc, char** argv) {
	printf("Process to recv ... \n");

	std::vector<char> data;

#ifdef __XXX_WINDOWS__  
	recv_transport_windows tr;
#endif // __XXX_WINDOWS__

#ifdef __XXX_LINUX__
	recv_transport_linux tr;
#endif //__XXX_LINUX__

	tr.open();

	receiver recv(&tr);

	recv.open();
	recv.recv(data);
	recv.close();

	tr.close();

	writefile(argv[2], data);

	printf("Process to recv ... finished\n");
	return 0;
}


// отправка send file // прием recv file
int main( int argc, char** argv)
{
	if (argc != 3) { 
		printf("xxx send|recv file\n");
		return 0;
	}
	// запускаем отправку
	if (strcmp(argv[1], "send") == 0) {
		main_send(argc, argv);
	}
	// запускаем прием
	if (strcmp(argv[1], "recv") == 0) {
		main_recv(argc, argv);
	}
    return 0;
}

