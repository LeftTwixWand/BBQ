#include "ServerResponses.h"
#include "MessageTypes.h"
#include "ClientRequests.h"

BBQResponse BBQResponseEnumeration::Wait = BBQResponse(201, "OK, WAIT");
BBQResponse BBQResponseEnumeration::Closed = BBQResponse(202, "CLOSED BYE");
BBQResponse BBQResponseEnumeration::Served = BBQResponse(203, "SERVED BYE");

BBQResponse::BBQResponse(int messageId, const std::string& message) : HTTPMessage(messageId)
{
	MessageType::ValidateResponseId(messageId);

	this->Message = message;
}

BBQResponse BBQResponse::GetFromRequest(char* requestBuffer)
{
	std::string request(requestBuffer);

	if (request == BBQRequestEnumeration::Hungry.Message)
		return BBQResponseEnumeration::Wait;

	if (request == BBQRequestEnumeration::TakeThat.Message)
		return BBQResponseEnumeration::Served;

	return BBQResponseEnumeration::Closed;

}

std::string BBQResponse::Body()
{
	// TODO: Add body JSON serialization
	return this->Message;
}