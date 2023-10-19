/*
 * Component.h
 *
 *  Created on: Jun 4, 2012
 *      Author: nhsan
 */

#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <string>
#include <boost/shared_ptr.hpp>

class Server;
class Component;
typedef boost::shared_ptr<Component> component_ptr;

class Component
{
protected:
	std::string _id;
	Server* _server;
public:
	Component(Server* server, std::string id);
	virtual ~Component();

	std::string id();

	virtual void initialize();
	virtual void start();
	virtual void stop();
	virtual void join();
};

#endif /* COMPONENT_H_ */

