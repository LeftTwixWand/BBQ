#include <iostream>
#include <thread>
#include "BBQClient.h"

BBQClient::BBQClient(BBQConnection* messagingConnection, BBQConnection* notificationConnnection)
{
	this->messagingConnection = *messagingConnection;
	this->notificationConnnection = *notificationConnnection;
}

BBQClient::~BBQClient()
{
	this->messagingConnection.CloseConnection();
	this->notificationConnnection.CloseConnection();
}

void BBQClient::ListenForServerNotifications()
{
	std::thread notificationsThread([this]
		{
			// Wait for notification
			char buffer[4096];
			ZeroMemory(buffer, sizeof(buffer));

			while (true)
			{
				int bytesReceived = recv(notificationConnnection.GetRemoteSocket(), buffer, sizeof(buffer), 0);

				// If client disconnects - bytesReceived will be zero
				// If an error happend - result will be -1
				// So positive result is when bytesReceived > 0
				if (bytesReceived > 0)
				{
					std::cout << "Server notification: " << std::string(buffer, 0, bytesReceived) << std::endl;
					ZeroMemory(buffer, sizeof(buffer));
				}
			}
		});

	notificationsThread.join();
}

void BBQClient::SendRequest(BBQRequest request)
{
	// TODO: Pack request into HTTP, using https://github.com/nodejs/http-parser
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