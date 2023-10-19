/*
 * TcpServer.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_
#define TCP_COMP	"TCP_SERVER"

#include <boost/smart_ptr/shared_ptr.hpp>
#include <google/dense_hash_map>
#include <google/dense_hash_set>
#include <boost/thread/mutex.hpp>
#include "commons/ThreadBase.h"
#include "Component.h"
#include "Connection.h"
#include "logger/LogManager.h"

namespace core {
	class Engine;
	class Server;
}

namespace qr {
class QRcode
{
private:
    std::string tel;
    std::string device_name;
    std::string ip_address;
    std::string platform_name;
    std::string platform_version;
    std::string qrtoken;
    uint64_t time;
    tcp::connection_ptr connection_desktop;
public:
    QRcode(tcp::connection_ptr connection)
    {
        connection_desktop = connection;
        tel = "";
        device_name = "";
        ip_address = "";
        platform_name = "";
        time = 0;
        platform_version = "";
        qrtoken = "";
    }
    virtual ~QRcode(){};
    void set_tel(std::string tel_param) { tel = tel_param; }
    void set_ip_address(std::string ip_address_param) { ip_address = ip_address_param; }
    void set_device_name(std::string device_name_param) { device_name = device_name_param; }
    void set_platform_name(std::string platform_name_param) { platform_name = platform_name_param; }
    void set_platform_version(std::string platform_version_param) { platform_version = platform_version_param; }
    void set_time(uint64_t time_param) { time = time_param; }
    void set_qrtoken(std::string qrtoken_param) { qrtoken = qrtoken_param; }
    std::string get_tel()const { return tel; }
    std::string get_device_name() const { return device_name; }
    std::string get_ip_address() const { return ip_address; }
    std::string get_platform_name() const { return platform_name; }
    std::string get_platform_version() const { return platform_version; }
    std::string get_qrtoken() const { return qrtoken; }
    uint64_t get_time() const { return time; }
    tcp::connection_ptr get_connection() const { return connection_desktop; }
};
typedef boost::shared_ptr<QRcode> qrcode_ptr;
}

namespace tcp {
class TcpLauncher;
class TcpServer: public Component
{
public:
	TcpServer(Server* server);
	virtual ~TcpServer();

	bool watch(int fd);
	void main_loop();
	connection_ptr open_connection(std::string host, int port);
	connection_ptr add_connection(int fd);
	void close_connection(int fd);
	connection_ptr get_connection(int fd);
	int listen_connection(std::string host, int port);

    qr::qrcode_ptr add_qrtoken(std::string qrtoken, connection_ptr connection);
    qr::qrcode_ptr get_connection_from_qrtoken(std::string qrtoken);

    // Add logs
    int GetConCurrentUser();

	void initialize();
	void start();
	void stop();
	void join();

	void push_task(message_ptr message, int fd);
private:
	int epoll_fd;
	int max_event;
	google::dense_hash_set<int> fds;
    google::dense_hash_map<std::string, qr::qrcode_ptr> qr_tokens;
	google::dense_hash_map<int, connection_ptr> connections;
	boost::mutex mutex;
	bool running;
	core::Engine* engine;
	TcpLauncher* launcher;

    // Add logs
    std::set<int> sConCurrentUser;
    LogManager *m_pLogger;
};

class TcpLauncher: public ThreadBase
{
public:
	TcpLauncher(TcpServer* server): server(server)
	{
	}
	virtual ~TcpLauncher()
	{
	}
	void run()
	{
		server->main_loop();
	}
private:
	TcpServer* server;
};

}  // namespace tcp
#endif /* TCPSERVER_H_ */
