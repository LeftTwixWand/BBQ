#pragma once
#ifndef CLIENT_REQUESTS_H
#define CLIENT_REQUESTS_H

#include <string>

// A class, that represents BBQ protocol clinet requests
class BBQRequest 
{
protected:

	// Each BBQRequest will have a MessageId, that will simplify parsing
	int MessageId;

public:

	// Each request will have some message
	std::string Message;

	BBQRequest(int messageId, const std::string& message);

	// Returns "body" for HTTP request
	std::string Body();
};

// Pattern "Enumeration", that makes it easier to work with pre-defined data 
class BBQRequestEnumeration
{
public:
	static BBQRequest Hungry;
	static BBQRequest NoThanks;
	static BBQRequest TakeThat;
};

#endif // !CLIENT_REQUESTS_H