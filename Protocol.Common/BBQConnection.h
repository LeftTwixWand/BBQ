#pragma once
#ifndef BBQ_CONNECTION_H
#define BBQ_CONNECTION_H

#include <WS2tcpip.h>
#include <string>

#pragma comment(lib, "Ws2_32.lib")

// A class, that incapsulate TCP/IP connection manipulations for BBQ protocol
class BBQConnection
{
private:

	// Store details of the Windows Sockets implementation
	WSADATA winSocketData;

	// Use WinSocket latest version
	WORD winSocketVersion = MAKEWORD(2, 2);

	// Checks, is it possible to use Windows socket API
	void InitializeWinSocket();

	// Trying to create a TCP/IP streaming socket 
	void InitializeRemoteSocket();

	// Initialize a new listening socket for income connections
	SOCKET InitializeListeningSocket();

	// Receivs remote income connection and initialize current remoteSocket
	SOCKET GetRemoteConnection(SOCKET listeningSocket, int port);

	// Display information about new connection
	void DisplayConnectionInfo(sockaddr_in client);

	void StartConnection(std::string remoteIp, int remotePort);

protected:

	SOCKET remoteSocket;

public:

	// Returns closed socket connection
	BBQConnection();

	// Receives a new income connection from specific port
	BBQConnection(int port);

	// Returns instance of opened socket connection
	BBQConnection(const std::string& remoteIp, int remotePort);

	~BBQConnection();

	SOCKET GetRemoteSocket();
	bool IsOpen();
	void CloseConnection();
};

#endif // !BBQ_CONNECTION_H