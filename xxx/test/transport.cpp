#include "stdafx.h"
#include "CppUnitTest.h"

#include "..\xxx\recv_transport.h"
#include "..\xxx\send_transport.h"

#include "..\xxx\disassembler.h"
#include "..\xxx\assembler.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{		
	TEST_CLASS(Transport)
	{
	public:
		
		TEST_METHOD(Send)
		{
			send_transport send_tr;

			char data[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
			std::vector<char> send_data(data, data + sizeof(data));

			send_tr.open();
			send_tr.send(send_data);
			send_tr.close();
		}
		
		TEST_METHOD(Recv)
		{
			recv_transport recv_tr;

			char data[8] = { 0, 1, 2, 3, 4, 5, 6, 7 };
			std::vector<char> recv_data(data, data + sizeof(data));

			recv_tr.open();
			recv_tr.recv(recv_data);
			recv_tr.close();
		}
		
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
			Assert::IsTrue(send_data == recv_data);
		}

		TEST_METHOD(DasmAndAsm)
		{
			std::vector<char> packet;
			std::vector<char> data;
			std::vector<char> result;
			int count = 1024;
			char str[] = "This is test.";
			for (int i = 0; i < count; i++) {
				data.insert(data.end(), str, str+sizeof(str));
			}
			Assert::AreEqual(data.size(), sizeof(str)*count);


			disassembler dasm;
			assembler assm;

			dasm.open();
			assm.open();

			dasm.push_data(data);

			dasm.pop_packet(packet);
			while (packet.size() != 0) {
				assm.push_packet(packet);
				dasm.pop_packet(packet);
			}

			assm.pop_data(result);
			Assert::AreEqual(data.size(), result.size());
			
			assm.close();
			dasm.close();


		}

	};
}