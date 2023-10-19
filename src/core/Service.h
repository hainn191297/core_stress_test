#ifndef SERVICE_H_
#define SERVICE_H_

#include <boost/shared_ptr.hpp>
#include "Context.h"

class Server;

namespace core
{

class Service
{
protected:
	int _type;
	Server* _server;
public:
	Service(int type, Server* server): _type(type), _server(server)
	{
	}

	int type()
	{
		return _type;
	}

	virtual ~Service()
	{
	}

	virtual bool process(context_ptr context)=0;
};

typedef boost::shared_ptr<Service> service_ptr;

}  // namespace core

#endif /* SERVICE_H_ */
