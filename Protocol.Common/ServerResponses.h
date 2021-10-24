#pragma once
#ifndef SERVER_RESPONSES_H
#define SERVER_RESPONSES_H

#include <string>

// A class, that represents BBQ protocol server responses
class BBQResponse
{
protected:

	// Each BBQResponse will have a MessageId, that will simplify parsing
	int MessageId;

public:

	// Each response will have some message
	std::string Message;

	BBQResponse(int messageId, const std::string& message);

	// Returns "body" for HTTP request
	std::string Body();
};


// Pattern "Enumeration", that makes it easier to work with pre-defined data 
class BBQResponseEnumeration
{
public:
	static BBQResponse Wait;
	static BBQResponse Closed;
	static BBQResponse Served;
};

#endif // !SERVER_RESPONSES_H