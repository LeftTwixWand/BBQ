#include <iostream>
#include <thread>
#include "BBQServer.h"

BBQServer::BBQServer()
{
}

BBQServer::~BBQServer()
{
	this->messagingConnection.CloseConnection();
	this->notificationConnection.CloseConnection();
}

void BBQServer::Start(int messagingPort, int notificationPort)
{
	auto messagingConnected = new BBQConnection(messagingPort);
	auto notificationConnected = new BBQConnection(notificationPort);

	this->messagingConnection = *messagingConnected;
	this->notificationConnection = *notificationConnected;
	// -------------------------------------------------------------

	std::thread pollingThread([this] { this->HandlerIncommingMessages(); });

	SendNotification(BBQNotificationEnumeration::BeefReady);
	SendNotification(BBQNotificationEnumeration::ChickenReady);
	SendNotification(BBQNotificationEnumeration::MammothReady);

	pollingThread.join();

	// -------------------------------------------------------------
	delete messagingConnected;
	delete notificationConnected;
}

void BBQServer::HandlerIncommingMessages()
{
	char buf[4096];
	ZeroMemory(buf, sizeof(buf));

	while (true)
	{
		// Wait for client to send data
		int bytesReceived = recv(this->messagingConnection.GetRemoteSocket(), buf, sizeof(buf), 0);
		if (bytesReceived == SOCKET_ERROR)
		{
			std::cerr << "Error in recv()" << std::endl;
			break;
		}

		// Client disconnected
		if (bytesReceived == 0)
		{
			std::cerr << "Client disconnected!" << std::endl;
			break;
		}

		// TODO: Parse a result and send a response
		send(this->messagingConnection.GetRemoteSocket(), buf, sizeof(buf), 0);
		std::cout << buf << std::endl;
		ZeroMemory(buf, sizeof(buf));
	}
}

std::string BBQServer::GetResponse(char* request)
{
	return std::string(request, sizeof(request), 0);
}

void BBQServer::SendNotification(BBQNotification notification)
{
	// TODO: Parse a result and send a response
	send(this->notificationConnection.GetRemoteSocket(), notification.Message.c_str(), notification.Message.size(), 0);
}