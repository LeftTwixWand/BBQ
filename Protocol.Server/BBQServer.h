#pragma once
#ifndef BBQ_SERVER_H
#define BBQ_SERVER_H

#include "BBQConnection.h"
#include "ServerNotifications.h"

// This is a BBQ protocol server class
class BBQServer
{
private:

	// Connection for messages sending 
	BBQConnection messagingConnection;

	// Connection for notifications sending
	BBQConnection notificationConnection;

	// Run asynchronus thread, that is listening for incomming messages
	void HandlerIncommingMessages();

	// Send prepared notifications to the client
	void SendNotifications();

	// Send notification to the connected client
	void SendNotification(BBQNotification notification);

public:

	BBQServer();
	~BBQServer();

	void Start(int messagingPort, int notificationPort);
};

#endif // !BBQ_SERVER_H