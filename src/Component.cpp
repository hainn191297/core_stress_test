/*
 * Component.cpp
 *
 *  Created on: Jul 21, 2016
 *      Author: cuongtv
 */

#include "Component.h"
#include "Server.h"

Component::Component(Server* server, std::string id): _id(id), _server(server)
{
}

Component::~Component()
{
}

std::string Component::id()
{
	return _id;
}

void Component::initialize()
{
}

void Component::start()
{
}

void Component::stop()
{
}

void Component::join()
{
}
