/*
 * Message.h
 *
 *  Created on: Jan 10, 2012
 *      Author: nhsan
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <stdint.h>
#include <string.h>

#define PACKET_HEADER_SIZE		8
#define PACKET_MAGIC			0xEE
namespace tcp {

class Message;
typedef boost::shared_ptr<Message> message_ptr;

class Message
{
private:
	char* data;
public:
	int size;
	int type;
	uint64_t id;

	Message(int size, int type, uint64_t message_id = 0)
	{
		this->id = message_id;
		this->size = size;
		this->type = type;
		this->data = (char*) malloc(size + 8);
	}

	virtual ~Message()
	{
		if (data) free(data);
	}
	char* get_data()
	{
		return data;
	}

	char* get_content_data()
	{
		char* ret = get_data() + PACKET_HEADER_SIZE;
		if (id > 0) ret += 8;
		return ret;
	}

	int get_content_size()
	{
		int ret = size - PACKET_HEADER_SIZE;
		if (id > 0) ret -= 8;
		return ret;
	}

	static message_ptr encode(std::string data, int type, uint64_t message_id = 0)
	{
		int size = data.size() + PACKET_HEADER_SIZE;
		if (message_id > 0) size += 8;
		message_ptr ret = boost::make_shared<Message>(size, type);
		unsigned char* buf = (unsigned char*) ret->get_data();
		buf[0] = PACKET_MAGIC;
		buf[1] = PACKET_MAGIC;

		buf[2] = ((size >> 16) & 0xFF);
		buf[3] = ((size >> 8) & 0xFF);
		buf[4] = (size & 0xFF);

		buf[5] = ((type >> 8) & 0xFF);
		buf[6] = (type & 0xFF);
		buf[7] = 0;

		int offset = PACKET_HEADER_SIZE;

		if (message_id > 0)
		{
			buf[7] += 2;
			buf[offset++] = ((message_id >> 56) & 0xFF);
			buf[offset++] = ((message_id >> 48) & 0xFF);
			buf[offset++] = ((message_id >> 40) & 0xFF);
			buf[offset++] = ((message_id >> 32) & 0xFF);
			buf[offset++] = ((message_id >> 24) & 0xFF);
			buf[offset++] = ((message_id >> 16) & 0xFF);
			buf[offset++] = ((message_id >> 8) & 0xFF);
			buf[offset++] = (message_id & 0xFF);
		}

		memcpy(buf + offset, data.c_str(), data.size());
		return ret;
	}
};

}  // namespace tcp
#endif /* MESSAGE_H_ */
