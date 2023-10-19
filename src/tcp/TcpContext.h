/*
 * TcpContext.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef TCPCONTEXT_H_
#define TCPCONTEXT_H_
#include "Message.h"
#include "Connection.h"
namespace tcp
{/*
 * TcpContext.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef TCPCONTEXT_H_
#define TCPCONTEXT_H_
#include "Message.h"
#include "Connection.h"
namespace tcp
{

class TcpContext: public core::Context
{
public:
	TcpContext(message_ptr message, connection_ptr connection)
	{
		this->message = message;
		this->connection = connection;
	}

	virtual ~TcpContext()
	{
	}

	message_ptr get_message()
	{
		return message;
	}

	connection_ptr get_connection()
	{
		return connection;
	}
private:
	message_ptr message;
	connection_ptr connection;
};

class ReadContext: public core::Context
{
public:
	ReadContext(connection_ptr connection)
	{
		this->connection = connection;
	}
	virtual ~ReadContext()
	{

	}
	connection_ptr get_connection()
	{
		return connection;
	}
private:
	connection_ptr connection;
};

}  // namespace tcp
#endif /* TCPCONTEXT_H_ */


class TcpContext: public core::Context
{
public:
	TcpContext(message_ptr message, connection_ptr connection)
	{
		this->message = message;
		this->connection = connection;
	}

	virtual ~TcpContext()
	{
	}

	message_ptr get_message()
	{
		return message;
	}

	connection_ptr get_connection()
	{
		return connection;
	}
private:
	message_ptr message;
	connection_ptr connection;
};

class ReadContext: public core::Context
{
public:
	ReadContext(connection_ptr connection)
	{
		this->connection = connection;
	}
	virtual ~ReadContext()
	{

	}
	connection_ptr get_connection()
	{
		return connection;
	}
private:
	connection_ptr connection;
};

}  // namespace tcp
#endif /* TCPCONTEXT_H_ */
