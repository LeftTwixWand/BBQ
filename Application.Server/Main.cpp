#include "BBQServer.h"

void main()
{
	auto server = new BBQServer();
	server->Start(54000, 54001);

	delete server;
}