#pragma once

class send_transport;

class sender
{
protected:
	send_transport *_st;
public:
	sender(send_transport *st);

	void open( );
	void send(std::vector<char>& data);
	void close();

	virtual ~sender();
};

