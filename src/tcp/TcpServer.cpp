/*
 * TcpServer.cpp
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#include "core/Engine.h"
#include "Server.h"
#include "TcpServer.h"
#include <boost/smart_ptr/make_shared.hpp>
#include <boost/lexical_cast.hpp>
#include "commons/SocketUtil.h"
#include <sys/epoll.h>
#include "TcpContext.h"
#include "TcpReadService.h"
#include <glog/logging.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "Utils.h"

namespace tcp
{
TcpServer::TcpServer(Server* server) :
		Component(server, TCP_COMP)
{
	fds.set_empty_key(-1);
	fds.set_deleted_key(-2);
	connections.set_empty_key(-1);
	connections.set_deleted_key(-2);
    qr_tokens.set_empty_key("");
    qr_tokens.set_deleted_key(" ");
	// max_event = 512;
	max_event = server->settings().epoll_max_event();
}

TcpServer::~TcpServer()
{
	SAFE_DEL(launcher);
}

void TcpServer::initialize()
{
	engine = (core::Engine*) _server->component(ENGINE_COMP).get();
	engine->register_service(boost::make_shared<TcpReadService>(_server));
}

void TcpServer::start()
{
	epoll_fd = epoll_create1(0);
	if (epoll_fd == -1)
	{
		throw std::runtime_error("Error in epoll_create");
	}

    std::string host = _server->settings().bind_host();
    int port = _server->settings().port_server();

	listen_connection(host, port);
	running = true;
	launcher = new TcpLauncher(this);
	launcher->start();
}

void TcpServer::stop()
{
	running = false;
}
void TcpServer::join()
{
	//launcher->join();
}

bool TcpServer::watch(int fd)
{
	int s;
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
	if (s == -1)
	{
		VTLOG(vtlog::ERROR, "Error in epoll_ctl");
		return false;
	}
	return true;
}

connection_ptr TcpServer::open_connection(std::string host, int port)
{
	std::string port_str = boost::lexical_cast<std::string>(port);
	int fd = SocketUtils::socket_connection_new(host.c_str(), port_str.c_str(), 0);
	if (fd < 0) return connection_ptr();
	SocketUtils::make_socket_non_blocking(fd);
	connection_ptr conn = add_connection(fd);
	return conn;
}

int TcpServer::listen_connection(std::string host, int port)
{
	std::string mport = boost::lexical_cast<std::string>(port);

    int listen_fd = SocketUtils::create_and_bind(host.c_str(), mport.c_str());
	if (listen_fd == -1) return -1;

	int s = SocketUtils::make_socket_non_blocking(listen_fd);
	if (s == -1)
	{
		close(listen_fd);
		return -1;
	}

	s = listen(listen_fd, SOMAXCONN);
	if (s == -1)
	{
		VTLOG(vtlog::ERROR, "Error in connection listening");
		close(listen_fd);
		return -1;
	}

	if (!watch(listen_fd))
	{
		close(listen_fd);
		return -1;
	}
	VTLOG2(vtlog::DEBUG, "Start listing on %s : %d", host.c_str(), port);
	fds.insert(listen_fd);
	return listen_fd;
}

void TcpServer::close_connection(int fd)
{
	std::string strLogConCurrent;
	if (fd <= 0 ) return;

	auto con = get_connection(fd);
	if (con != nullptr)
	{
		model::Entity enPresenceSession;
		std::string strPresenceSessionID = "";
		int32_t iFd;
		con->close();
		// con.reset();
		boost::mutex::scoped_lock lock(mutex);
		connections.erase(fd);
		
		//update PresenceSession
		iFd = fd;
		db::VTDatabase* pDatabase = (db::VTDatabase*) _server->component(VT_DATABASE_COMP + string(TCP_COMP)).get();
		pDatabase->GetPresenceSessionIDByFd(iFd, strPresenceSessionID);
		pDatabase->GetPresenceSessionByID(strPresenceSessionID, enPresenceSession);
		if(enPresenceSession.has_id())
		{
			auto obPresenceSession = enPresenceSession.MutableExtension(vt::PresenceSession::PRESENCE_SESSION);
			obPresenceSession->set_fd(-1);
			pDatabase->UpdatePresenceSession(enPresenceSession);
			pDatabase->DeleteIndexFdPresenceSession(iFd);
		}
		// Add logs
		sConCurrentUser.erase(fd);
		m_pLogger->log_concurrent(GetConCurrentUser(), strLogConCurrent);
		VTSLOG2(CON_CURRENT, vtlog::INFO, "%s", strLogConCurrent.c_str());
	}
}

connection_ptr TcpServer::add_connection(int fd)
{
	int s;
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLET;
	s = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &event);
	if (s == -1)
	{
		VTLOG(vtlog::ERROR, "Error in epoll_ctl");
        return nullptr;
        //return connection_ptr();FIXME bienvv
	}
	connection_ptr conn = boost::make_shared<Connection>(fd);
	boost::mutex::scoped_lock lock(mutex);
	//DLOG(INFO)<<"Add connection:"<<fd;
	connections[fd] = conn;

	// HaiNN
	sConCurrentUser.insert(fd);

	return conn;
}

connection_ptr TcpServer::get_connection(int fd)
{
	boost::mutex::scoped_lock lock(mutex);
	auto it = connections.find(fd);
	if (it == connections.end()) return nullptr;
	return it->second;
}

qr::qrcode_ptr TcpServer::add_qrtoken(std::string qrtoken, connection_ptr connection)
{
    qr::qrcode_ptr conn = boost::make_shared<qr::QRcode>(connection);
	boost::mutex::scoped_lock lock(mutex);
    qr_tokens[qrtoken] = conn;
    return conn;
}

qr::qrcode_ptr TcpServer::get_connection_from_qrtoken(std::string qrtoken)
{
	boost::mutex::scoped_lock lock(mutex);
	auto it = qr_tokens.find(qrtoken);
	if (it == qr_tokens.end()) return nullptr;
	return it->second;
}

void TcpServer::main_loop()
{
	int s;
	struct epoll_event event;
	struct epoll_event *events;
    int iEpollTimeWait = _server->settings().GetEpollWaitTimeOut();


	/* Buffer where events are returned */
	events = (epoll_event*) calloc(max_event, sizeof event);

	VTLOG(vtlog::INFO, "Starting main loop");
	while (running)
	{
		int n, i;
		n = epoll_wait(epoll_fd, events, max_event, iEpollTimeWait);
		for (i = 0; i < n; i++)
		{
            // VTLOG2(vtlog::DEBUG, "[TcpServer] Event value: %u", events[i].events);
			if ((events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || (!(events[i].events & EPOLLIN)))
			{
				/* An error has occured on this fd, or the socket is not ready for reading (why were we notified then?) */
				// DLOG(ERROR)<< "epoll error";
				VTLOG2(vtlog::DEBUG, "[TcpServer] EPOLLERR = %llu, EPOLLHUP = %llu, EPOLLIN = %llu", (events[i].events & EPOLLERR), (events[i].events & EPOLLHUP), (!(events[i].events & EPOLLIN)));
				close_connection(events[i].data.fd);
				continue;
			}
			else if (fds.count(events[i].data.fd) > 0)
			{
				/* We have a notification on the listening socket, which means one or more incoming connections. */
				while (1)
				{
                    struct sockaddr_in6 in_addr;
					socklen_t in_len;
					int infd;
					char hbuf[NI_MAXHOST], sbuf[NI_MAXSERV];

					in_len = sizeof in_addr;
                    infd = accept(events[i].data.fd, (struct sockaddr *)&in_addr, &in_len);
					if (infd == -1)
					{
                        VTLOG2(vtlog::DEBUG, "[TcpServer] Fd value: %d, error number: %d", events[i].data.fd, errno);
						if ((errno == EAGAIN) || (errno == EWOULDBLOCK))
						{
							/* We have processed all incoming connections. */
							break;
						}
						else
						{
							perror("accept");
							break;
						}
					}

                    s = getnameinfo((struct sockaddr *)&in_addr, in_len, hbuf, sizeof hbuf, sbuf, sizeof sbuf, NI_NUMERICHOST | NI_NUMERICSERV);
					if (s == 0) VTLOG2(vtlog::DEBUG, "Accepted connection: %d (host= %s , port= %s)", infd, hbuf ,sbuf);

					/* Make the incoming socket non-blocking and add it to the list of fds to monitor. */
					s = SocketUtils::make_socket_non_blocking(infd);
					if (s == -1)
					{
						VTLOG(vtlog::DEBUG, "Close make non-blocking");
						close(infd);
						break;
					}

					connection_ptr conn = add_connection(infd);
					if (conn == NULL) close(infd);
					continue;
				}
			}
			else
			{
				/* push event to queue */
				connection_ptr con = get_connection(events[i].data.fd);
				if (con != nullptr)
				{
					con->push_read_task(engine, con);
					// VTLOG(vtlog::DEBUG, "Push read task");
				}
			}
		}
	}
	VTLOG(vtlog::INFO, "End main loop");
	free(events);
}

void TcpServer::push_task(message_ptr message, int fd)
{
//	DLOG(INFO)<<"Push tcp task:"<<message->type;
	auto con = get_connection(fd);
	if (con == nullptr) return;
	auto context = boost::make_shared<TcpContext>(message, con);
	auto t = new core::Task(message->type, context);
	engine->enqueue(t);
}

int TcpServer::GetConCurrentUser()
{
	return sConCurrentUser.size();
}

}  // namespace tcp
