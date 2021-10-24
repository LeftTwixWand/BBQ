#include "ServerNotifications.h"
#include "MessageTypes.h"

BBQNotification BBQNotificationEnumeration::ChickenReady = BBQNotification(301, "CHICKEN READY");
BBQNotification BBQNotificationEnumeration::BeefReady = BBQNotification(302, "BEEF READY");
BBQNotification BBQNotificationEnumeration::MammothReady = BBQNotification(303, "LAST MONTH MAMMOTH READY");

BBQNotification::BBQNotification(int messageId, const std::string& message) : HTTPMessage(messageId)
{
	MessageType::ValidateNotificationId(messageId);

	this->Message = message;
}

std::string BBQNotification::Body()
{
	// TODO: Add body JSON serialization
	return this->Message;
}