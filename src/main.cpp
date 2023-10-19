/*
 * main.cpp
 *
 *  Created on: Mar 20, 2013
 *      Author: nhsan
 */

#include <glog/logging.h>
#include "logger/LogManager.h"
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#include "Server.h"
#include "core/Engine.h"
#include <curl/curl.h>
#include <tcp/Message.h>
#include "tcp/Connection.h"
#include "tcp/TcpContext.h"

Server* glServer = nullptr;
#ifndef BUILD_MAJOR_VERSION
#define BUILD_MAJOR_VERSION "1"
#endif // BUILD_MAJOR_VERSION
#ifndef BUILD_MINOR_VERSION
#define BUILD_MINOR_VERSION "0"
#endif // BUILD_MINOR_VERSION
#ifndef BUILD_PATCH_VERSION
#define BUILD_PATCH_VERSION "1. Test"
#endif // BUILD_PATCH_VERSION
#include "Utils.h"
int main(int argc, char **argv)
{
    // auto time = Utils::time_t();
    // std::string strID = Utils::uuid_encode(to_string(time));
    // DLOG(INFO) <<"uid: "<<strID;
    // return 0;
	bool bLogToFile = false;
	if(argc > 1)
    {
     	for (int i = 0; i < argc ; i++)
        {
            if (strcmp(argv[i], "--version") == 0)
            {
             	std::cout << BUILD_MAJOR_VERSION << "." << BUILD_MINOR_VERSION << "." << BUILD_PATCH_VERSION << std::endl;
                return 0;
            }
		}
	}

	for (int i = 0; i < argc ; i++)
	{
		if (strcmp(argv[i], "-l") == 0)
		{
			if (i + 1 < argc && strlen(argv[i]) > 0)
			{
				std::string strLogFilePath = argv[i];
				google::SetLogDestination(google::GLOG_INFO, strLogFilePath.c_str());
			}
		}
	}

	google::InitGoogleLogging(argv[0]);
	google::LogToStderr();

	DLOG(INFO)<<curl_version();
	try
	{
		cppcms::service service(argc, argv);
		auto server = boost::make_shared<Server>(service.settings());
		glServer = server.get();
		// hook_interrupt(server.get());
		int j = 0;
		/* Register components */
		// server->register_components(service);
		server->init();
        auto pEngine = boost::make_shared<core::Engine>();
        auto pService = boost::make_shared<core::Service>(1, server.get());
        pEngine->initialize();
        pEngine->register_service(pService);
        pEngine->start();

        for (int i = 0; i < 1000000; i++)
        {
            DLOG(INFO) << "Push task " << i;
            auto message_ptr = boost::make_shared<tcp::Message>(1, j++, 1);
            auto con = boost::make_shared<tcp::Connection>(1);
            auto context = boost::make_shared<tcp::TcpContext>(message_ptr, con);
            auto t = new core::Task(message_ptr->type, context);
            pEngine->enqueue(t);
            if (random() > i * 100)
            {
                usleep(5000);
            }


			VTLOG2(1, "Current_queue %d", pEngine->GetQueueSize());
        }

		/* register services */
		// auto engine = (core::Engine*)server->component(ENGINE_COMP).get();

		DLOG(INFO)<<"Server start with version: " << BUILD_MAJOR_VERSION << "." << BUILD_MINOR_VERSION << "." << BUILD_PATCH_VERSION;
		// server->start();

		DLOG(INFO)<<"Server is started";

		// server->stop();
		DLOG(INFO)<<"Server is stopped";
        return 1;
	}
	catch (std::exception const &e)
	{
		// VTLOG2(vtlog::DEBUG, "Global exception: %s", e.what());
		DLOG(INFO)<<"Global exception: " << e.what();
		return 1;
	}

	return 0;
}
