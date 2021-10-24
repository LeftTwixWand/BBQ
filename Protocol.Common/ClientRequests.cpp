#include "ClientRequests.h"
#include "MessageTypes.h"

BBQRequest BBQRequestEnumeration::Hungry = BBQRequest(101, "I AM HUNGRY, GIVE ME BBQ");
BBQRequest BBQRequestEnumeration::NoThanks = BBQRequest(102, "NO THANKS");
BBQRequest BBQRequestEnumeration::TakeThat = BBQRequest(103, "I TAKE THAT!!!");

BBQRequest::BBQRequest(int messageId, const std::string& message)
{
	MessageType::ValidateRequestId(messageId);
	this->MessageId = messageId;
	this->Message = message;
}

std::string BBQRequest::Body()
{
	// TODO: Add body JSON serialization
	return this->Message;
}