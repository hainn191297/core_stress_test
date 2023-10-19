/*
 * TcpReadService.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef TCPREADSERVICE_H_
#define TCPREADSERVICE_H_

#include "core/Context.h"
#include "core/Service.h"
class Server;

namespace tcp {

class TcpReadService: public core::Service
{
public:
	TcpReadService(Server* server);
	virtual ~TcpReadService();
	bool process(core::context_ptr context);
};

}  // namespace tcp
#endif /* TCPREADSERVICE_H_ */
