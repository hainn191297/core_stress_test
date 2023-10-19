#ifndef COMMON_UTIL_H_
#define COMMON_UTIL_H_

class SocketUtils
{
public:
    static int create_and_bind(const char* addr, const char* port);
	static int make_socket_non_blocking(int fd);
	static int disable_nagle(int fd);
	static int socket_connection_new(const char *host, const char *port, int timeout);
};

#endif
