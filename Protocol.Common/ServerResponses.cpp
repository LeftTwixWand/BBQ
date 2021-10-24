#include "ServerResponses.h"
#include "MessageTypes.h"

BBQResponse BBQResponseEnumeration::Wait = BBQResponse(201, "OK, WAIT");
BBQResponse BBQResponseEnumeration::Closed = BBQResponse(202, "CLOSED BYE");
BBQResponse BBQResponseEnumeration::Served = BBQResponse(203, "SERVED BYE");

BBQResponse::BBQResponse(int messageId, const std::string& message) : HTTPMessage(messageId)
{
	MessageType::ValidateResponseId(messageId);

	this->Message = message;
}

std::string BBQResponse::Body()
{
	// TODO: Add body JSON serialization
	return this->Message;
}