#include <iostream>
#include "BBQClient.h"
#include "ClientRequests.h"

void main()
{
	auto messagingConnaction = new BBQConnection("127.0.0.1", 54000);
	auto notificationConnection = new BBQConnection("127.0.0.1", 54001);

	auto client = BBQClient(messagingConnaction, notificationConnection);
	client.ListenForServerNotifications();

	client.SendRequest(BBQRequestEnumeration::Hungry);
	client.SendRequest(BBQRequestEnumeration::NoThanks);
	client.SendRequest(BBQRequestEnumeration::TakeThat);

	delete messagingConnaction;
	delete notificationConnection;
}