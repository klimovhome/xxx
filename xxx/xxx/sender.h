#pragma once

class send_transport;

class sender
{
protected:
	const send_transport *_st;
public:
	sender(const send_transport *st);

	void open( );
	void send(const std::vector<char>& data);
	void close();

	virtual ~sender();
};

