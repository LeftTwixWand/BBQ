#include "HTTPMessage.h"

HTTPMessage::HTTPMessage(int messageId)
{
	this->MessageId = messageId;
}

std::string HTTPMessage::Headers()
{
	return this->MessageIdHeader + std::to_string(this->MessageId);
}

std::string HTTPMessage::Body()
{
	return "The body has to be overrided";
}