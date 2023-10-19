/*
 * TcpReadService.cpp
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#include "TcpReadService.h"
#include "core/Service.h"
#include "TcpContext.h"
#include "TcpServer.h"
#include "Server.h"

namespace tcp
{

TcpReadService::TcpReadService(Server* server) :
		Service(0, server)
{

}

TcpReadService::~TcpReadService()
{
}

bool TcpReadService::process(core::context_ptr context)
{
	//DLOG(INFO)<<"Read mesage";
	static auto s = (TcpServer*) _server->component(TCP_COMP).get();
	auto ctx = static_cast<ReadContext*>(context.get());
	ctx->get_connection()->read_message(s);
	return false;
}

}  // namespace tcp

