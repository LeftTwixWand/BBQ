#pragma once
#ifndef HTTP_MESSAGE_H
#define HTTP_MESSAGE_H

#include <string>

// A parent class, for all the messages, that will be sent through the BBQ protocol
class HTTPMessage
{
private:

	// Every sending message will have additional header for simplifyiing parsing
	const std::string MessageIdHeader = "BBQ-Message-Id: ";

protected:

	// Every message must contain its MessageId to simplify parsing
	int MessageId;

public:

	HTTPMessage(int messageId);

	// Additional headers
	virtual std::string Headers();

	// HTTP body 
	virtual std::string Body();
};

#endif // !HTTP_MESSAGE_H