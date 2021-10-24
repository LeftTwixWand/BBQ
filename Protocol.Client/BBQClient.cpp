#include <iostream>
#include "BBQClient.h"

BBQClient::BBQClient(BBQConnection* messagingConnection, BBQConnection* notificationConnnection)
{
	this->messagingConnection = *messagingConnection;
	this->notificationConnnection = *notificationConnnection;
}

BBQClient::~BBQClient()
{
	this->messagingConnection.Close();
	this->notificationConnnection.Close();
}

void BBQClient::ListenForServerNotifications()
{
}

void BBQClient::SendRequest(BBQRequest request)
{
	int status = send(messagingConnection.GetRemoteSocket(), request.Message.c_str(), request.Message.size(), 0);
	if (status == SOCKET_ERROR)
	{
		std::cerr << "Error in request sending" << std::endl;
		return;
	}

	// Wait for response
	char buffer[4096];
	ZeroMemory(buffer, sizeof(buffer));
	
	int bytesReceived = recv(messagingConnection.GetRemoteSocket(), buffer, sizeof(buffer), 0);

	// If client disconnects - bytesReceived will be zero
	// If an error happend - result will be -1
	// So positive result is when bytesReceived > 0
	if (bytesReceived > 0)
	{
		std::cout << "Server response: " << std::string(buffer, 0, bytesReceived) << std::endl;
	}
}