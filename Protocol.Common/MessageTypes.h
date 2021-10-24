#pragma once
#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

// BBQ protocol message type
class MessageType
{
public:

	enum class Value
	{
		Request = 100, // All the request codes being in diapason [101-199]
		Response = 200, // All the response codes being in diapason [201-299]
		Notification = 300, // All the notification codes being in diapason [301-399]
	};

	Value GetValue();

	// Validator guarantees, that all the new added BBQRequests will works stable
	static void ValidateRequestId(int messageId);

	// Validator guarantees, that all the new added BBQResponses will works stable
	static void ValidateResponseId(int messageId);

	// Validator guarantees, that all the new added BBQNotifications will works stable
	static void ValidateNotificationId(int messageId);

private:
	Value value;
};

#endif // !MESSAGE_TYPE_H