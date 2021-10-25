#pragma once
#ifndef BBQ_SERVER_H
#define BBQ_SERVER_H

#include "BBQConnection.h"

// This is a BBQ protocol server class
class BBQServer
{
private:

	// Connection for messages sending 
	BBQConnection messagingConnection;

	// Connection for notifications sending
	BBQConnection notificationConnection;

	void HandlerIncommingMessages();

public:

	BBQServer();
	~BBQServer();

	void Start(int messagingPort, int notificationPort);
};

#endif // !BBQ_SERVER_H