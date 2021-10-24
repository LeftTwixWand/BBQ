#include <iostream>
#include "BBQConnection.h"

void BBQConnection::InitializeWinSocket()
{
	int winSocketInitialization = WSAStartup(this->winSocketVersion, &this->winSocketData);
	if (winSocketInitialization != 0)
		throw new std::exception("Can't Initialize winsock!");
}

void BBQConnection::InitializeRemoteSocket()
{
	this->remoteSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (this->remoteSocket == INVALID_SOCKET)
		throw new std::exception("Can't create socket, Err #" + WSAGetLastError());
}

void BBQConnection::StartConnection(std::string remoteIp, int remotePort)
{
	// Fill in a hint structure
	sockaddr_in hint{};
	hint.sin_family = AF_INET;
	hint.sin_port = htons(remotePort);
	inet_pton(AF_INET, remoteIp.c_str(), &hint.sin_addr);

	// Connect to server
	int connectionResult = connect(this->remoteSocket, (sockaddr*)&hint, sizeof(hint));
	if (connectionResult == SOCKET_ERROR)
	{
		std::cerr << "Can't connect ot server, Err#" << WSAGetLastError() << std::endl;
		this->Close();
		return;
	}
}

BBQConnection::BBQConnection()
{
	this->InitializeWinSocket();
	this->InitializeRemoteSocket();
}

BBQConnection::BBQConnection(std::string remoteIp, int remotePort)
{
	InitializeWinSocket();
	InitializeRemoteSocket();
	StartConnection(remoteIp, remotePort);
}

BBQConnection::~BBQConnection()
{
	closesocket(this->remoteSocket);
	WSACleanup();
}

SOCKET BBQConnection::GetRemoteSocket()
{
	return this->remoteSocket;
}

bool BBQConnection::IsOpen()
{
	// Value -1 means, that soket is closed, so all the positiva values means, that the connection is open
	return this->remoteSocket >= 0;
}

void BBQConnection::Close()
{
	closesocket(this->remoteSocket);
	WSACleanup();
}