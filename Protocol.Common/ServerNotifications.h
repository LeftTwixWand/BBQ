#pragma once
#ifndef SERVER_NOTIFICATIONS_H
#define SERVER_NOTIFICATIONS_H

#include <string>
#include "HTTPMessage.h"

// A class, that represents BBQ protocol server responses
class BBQNotification : public HTTPMessage
{
protected:

	// Each BBQNotification will have a MessageId, that will simplify parsing
	int MessageId;

public:

	// Each notification will have some message
	std::string Message;

	BBQNotification(int messageId, const std::string& message);

	// Returns "body" for HTTP request
	std::string Body() override;
};

// Pattern "Enumeration", that makes it easier to work with pre-defined data 
class BBQNotificationEnumeration
{
public:
	static BBQNotification ChickenReady;
	static BBQNotification BeefReady;
	static BBQNotification MammothReady;
};

#endif // !SERVER_NOTIFICATIONS_H