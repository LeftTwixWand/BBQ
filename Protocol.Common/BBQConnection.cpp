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

SOCKET BBQConnection::InitializeListeningSocket()
{
	SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (listeningSocket == INVALID_SOCKET)
		throw new std::exception("Can't create socket, Err #" + WSAGetLastError());

	return listeningSocket;
}

SOCKET BBQConnection::GetRemoteConnection(SOCKET listeningSocket, int port)
{
	// Bind the ip address and port to the socket
	sockaddr_in hint;
	hint.sin_family = AF_INET;
	hint.sin_port = htons(port);
	hint.sin_addr.S_un.S_addr = INADDR_ANY; // Could also use inet_pton

	bind(listeningSocket, (sockaddr*)&hint, sizeof(hint));

	// Tell winsocket the socket is for listening
	listen(listeningSocket, SOMAXCONN);

	// Wait for a connection
	sockaddr_in remoteClient;
	int clientSize = sizeof(remoteClient);

	SOCKET clientSocketAddress = accept(listeningSocket, (sockaddr*)&remoteClient, &clientSize);
	if (clientSocketAddress == INVALID_SOCKET)
	{
		std::cerr << "Client socket is invalid!" << std::endl;
	}

	DisplayConnectionInfo(remoteClient);

	closesocket(listeningSocket);

	return clientSocketAddress;
}

void BBQConnection::DisplayConnectionInfo(sockaddr_in client)
{
	char host[NI_MAXHOST];		// Client's remote name
	char service[NI_MAXSERV];	// Service (i.e. port) the client is connected on

	ZeroMemory(host, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST); for Mac and Linux
	ZeroMemory(service, NI_MAXSERV);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
	{
		std::cout << host << " connected on port " << service << std::endl;
	}
	else
	{
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << " connected on port " << ntohs(client.sin_port) << std::endl;
	}
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
		this->CloseConnection();
		return;
	}
}

BBQConnection::BBQConnection()
{
	this->InitializeWinSocket();
	this->InitializeRemoteSocket();
}

BBQConnection::BBQConnection(int port)
{
	this->InitializeWinSocket();
	SOCKET listeningSocket = this->InitializeListeningSocket();
	this->remoteSocket = GetRemoteConnection(listeningSocket, port);
}

BBQConnection::BBQConnection(const std::string& remoteIp, int remotePort)
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

void BBQConnection::CloseConnection()
{
	closesocket(this->remoteSocket);
	WSACleanup();
}