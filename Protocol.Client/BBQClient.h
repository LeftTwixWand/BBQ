#pragma once
#ifndef BBQ_CLIENT_H
#define BBQ_CLIENT_H

#include "BBQConnection.h"
#include "ClientRequests.h"

class BBQClient
{
private:

	// The connection, responsible for messaging communication between
	BBQConnection messagingConnection;

	// The connection, responsible for server notifications accepting
	BBQConnection notificationConnnection;

public:

	BBQClient(BBQConnection* messagingConnection, BBQConnection* notificationConnnection);
	~BBQClient();

	void ListenForServerNotifications();
	void SendRequest(BBQRequest request);
};

#endif // !BBQ_CLIENT_H