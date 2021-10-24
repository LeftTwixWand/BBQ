#pragma once
#ifndef BBQ_CONNECTION_H
#define BBQ_CONNECTION_H

#include <WS2tcpip.h>
#include <string>

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
	
	void StartConnection(std::string remoteIp, int remotePort);

protected:
	SOCKET remoteSocket;

	// Returns closed socket connection
	BBQConnection();

public:

	// Returns instance of opened socket connection
	BBQConnection(std::string remoteIp, int remotePort);

	~BBQConnection();

	SOCKET GetRemoteSocket();
	bool IsOpen();
	void Close();
};

#endif // !BBQ_CONNECTION_H