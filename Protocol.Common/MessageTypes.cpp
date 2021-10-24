#include <stdexcept>
#include "MessageTypes.h"

MessageType::Value MessageType::GetValue()
{
	return this->value;
}

void MessageType::ValidateRequestId(int messageId)
{
	if (messageId < 101 || messageId > 199)
		throw std::invalid_argument("Argument \"messageId\" for BBQRequest must to be in diapason [101 - 199]");
}

void MessageType::ValidateResponseId(int messageId)
{
	if (messageId < 201 || messageId > 299)
		throw std::invalid_argument("Argument \"messageId\" for BBQResponse must to be in diapason [201 - 299]");
}

void MessageType::ValidateNotificationId(int messageId)
{
	if (messageId < 301 || messageId > 399)
		throw std::invalid_argument("Argument \"messageId\" for BBQNotifications must to be in diapason [301 - 399]");
}