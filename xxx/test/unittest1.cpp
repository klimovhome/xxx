#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\xxx\recv_transport.h"
#include "..\xxx\send_transport.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(Transport)
	{
	public:
		
		TEST_METHOD(SendRecv)
		{
			recv_transport recv_tr;
			send_transport send_tr;

			char data[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };

			std::vector<char> send_data(data, data+sizeof(data));
			std::vector<char> recv_data;

			recv_tr.open();
			send_tr.open();

			send_tr.send(send_data);
			recv_tr.recv(recv_data);

			send_tr.close();
			recv_tr.close();

			Assert::AreEqual(send_data.size(), recv_data.size());
		}

	};
}