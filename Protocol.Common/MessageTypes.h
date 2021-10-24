#pragma once
#ifndef MESSAGE_TYPES_H
#define MESSAGE_TYPES_H

class MessageType
{
public:

	enum class Value
	{
		Request = 100, // All the requests codes being in diapason [101-199]
		Response = 200, // All the responses codes being in diapason [201-299]
		Notification = 300, // All the notifications codes being in diapason [301-399]
	};

	Value GetValue();

	static void ValidateRequestId(int messageId);
	static void ValidateResponseId(int messageId);
	static void ValidateNotificationId(int messageId);

private:
	Value value;
};

#endif // !MESSAGE_TYPE_H