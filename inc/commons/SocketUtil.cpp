/*
* SocketUtil.cpp
*
*  Created on: Jul 21, 2016
*      Author: manh
*/

#include "SocketUtil.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <stdint.h>
#include <arpa/inet.h>
#include <glog/logging.h>
#include "logger/LogManager.h"

int SocketUtils::create_and_bind(const char *addr, const char *port)
{
    //    struct addrinfo *result;
    //    int s, sfd;
    //    int yes = 1;

    //    s = getaddrinfo(addr, port, NULL, &result);

    //    if (s != 0)
    //    {
    //        DLOG(ERROR) << "No interfaces to bind";
    //        return -1;
    //    }

    //    if (result) {
    //        struct sockaddr_in* saddr = (struct sockaddr_in*)result->ai_addr;
    //        const char* ip = inet_ntoa(saddr->sin_addr);
    //        DLOG(INFO) << "Address IP: " << ip;
    //        sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    //        if (sfd == -1)
    //            return -1;

    //        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    //            return -1;

    //        s = bind(sfd, result->ai_addr, result->ai_addrlen);
    //        if (s != 0) {
    //            DLOG(ERROR) << "Failed to bind " << ip << ':' << port;
    //            close(sfd);
    //        }
    //    } else {
    //        DLOG(ERROR) << "Failed to get bind address info";
    //        return -1;
    //    }

    //    freeaddrinfo(result);
    //    return sfd;

	/*binhdc*/

//    struct addrinfo hints;
//    struct addrinfo *result, *rp;
//    int s, sfd;
//    int yes = 1;
//
//    memset (&hints, 0, sizeof (struct addrinfo));
//    hints.ai_family = AF_UNSPEC;     /* Return IPv4 and IPv6 choices */
//    hints.ai_socktype = SOCK_STREAM; /* We want a TCP socket */
//    hints.ai_flags = AI_PASSIVE;     /* All interfaces */
//
//    s = getaddrinfo (addr, port, &hints, &result);
//    if (s != 0)
//    {
//        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror (s));
//        return -1;
//    }
//
//    for (rp = result; rp != NULL; rp = rp->ai_next)
//    {
//        sfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
//        if (sfd == -1)
//            continue;
//
////        if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
////        {
////        	fprintf (stderr, "setsockopt(SO_REUSEADDR) failed\n");
////            return -1;
////        }
//
//        s = bind(sfd, rp->ai_addr, rp->ai_addrlen);
//        if (s == 0)
//        {
//            /* We managed to bind successfully! */
//            break;
//        }
//
//        close (sfd);
//    }
//
//    if (rp == NULL)
//    {
//        fprintf (stderr, "Could not bind\n");
//        return -1;
//    }
//
//    freeaddrinfo(result);
//
//    return sfd;

        /*binhdc end*/

    /**bienvv*/
//	int s, sfd;
//	int yes = 1;
//	struct addrinfo hints;
//	memset(&hints, 0, sizeof(hints));
//	hints.ai_family = AF_UNSPEC;
//	hints.ai_socktype = SOCK_STREAM;
//	hints.ai_protocol = 0;
//	hints.ai_flags = AI_PASSIVE|AI_ADDRCONFIG;
//	struct addrinfo* result = 0;
//    s = getaddrinfo(addr, port, &hints, &result);
//	if (s != 0)
//	{
//		DLOG(ERROR) << "No interfaces to bind";
//		return -1;
//	}
//	if (result)
//	{
//		struct sockaddr_in* saddr = (struct sockaddr_in*)result->ai_addr;
//		const char* ip = inet_ntoa(saddr->sin_addr);
//		DLOG(INFO) << "Address IP: " << ip;
//		sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
//		if (sfd == -1) return -1;
//
//		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
//			return -1;
//
//		s = bind(sfd, result->ai_addr, result->ai_addrlen);
//		if (s != 0) {
//			DLOG(ERROR) << "Failed to bind " << ip << ':' << port;
//			close(sfd);
//		}
//	}
//	else
//	{
//		DLOG(ERROR) << "Failed to get bind address info";
//		return -1;
//	}
//
//	freeaddrinfo(result);
//	return sfd;

	/*ipv6 bienvv */
	int s, sfd;
	int yes = 1;
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET6;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	hints.ai_flags = AI_PASSIVE|AI_ADDRCONFIG;
	struct addrinfo* result = 0;
	s = getaddrinfo(addr, port, &hints, &result);
	if (s != 0)
	{
        VTLOG(vtlog::ERROR, "No interfaces to bind");
		return -1;
	}
	if (result)
	{
		struct sockaddr_in6* saddr = (struct sockaddr_in6*)result->ai_addr;
		sfd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
		if (sfd == -1)
		{
            VTLOG(vtlog::ERROR, "socket error!");
			return -1;
		}

		if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
			return -1;
		saddr->sin6_addr = in6addr_any;
		s = bind(sfd, (struct sockaddr *)saddr, result->ai_addrlen);
		if (s != 0) {
            VTLOG(vtlog::ERROR, "Failed to bind ");
			close(sfd);
		}
	}
	else
	{
        VTLOG(vtlog::ERROR, "Failed to get bind address info");
		return -1;
	}

	freeaddrinfo(result);
	return sfd;
}

/*
 * Make a socket non blocking.
 * Return -1 on error.
 */
int SocketUtils::make_socket_non_blocking(int fd)
{
    int flags, s;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1)
    {
        return -1;
    }

    flags |= O_NONBLOCK;
    s = fcntl(fd, F_SETFL, flags);
    if (s == -1)
    {
        return -1;
    }

    return 0;
}

/*
 * Use TCP_NODELAY
 */
int SocketUtils::disable_nagle(int fd)
{
    int flag = 1;
    if (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (char *) &flag, sizeof(int)) < 0)
    {
        return -1;
    }
    return 0;
}

/*
 * Connect to a server.
 * Return the socket file descriptor
 */
int SocketUtils::socket_connection_new(const char *host, const char *port, int timeout)
{
    int status, socketfd;
    struct addrinfo hints;
    struct addrinfo *servinfo;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    //Get host info
    if ((status = getaddrinfo(host, port, &hints, &servinfo)) != 0)
    {
        return -1;
    }

    //Opening socket
    socketfd = socket(servinfo->ai_family, servinfo->ai_socktype, servinfo->ai_protocol);
    if (socketfd == -1)
    {
        freeaddrinfo(servinfo);
        return -1;
    }

    int yes = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
    {
        freeaddrinfo(servinfo);
        return -1;
    }

    //Set timeout
    if (timeout > 0)
    {
        struct timeval t;
        t.tv_sec = timeout;
        t.tv_usec = 0;
        if (setsockopt(socketfd, SOL_SOCKET, SO_RCVTIMEO, (void *) &t, sizeof(t)) < 0)
        {
            freeaddrinfo(servinfo);
            return -1;
        }

        if (setsockopt(socketfd, SOL_SOCKET, SO_SNDTIMEO, (void *) &t, sizeof(t)) < 0)
        {
            freeaddrinfo(servinfo);
            return -1;
        }
    }

    //Connect
    if (connect(socketfd, servinfo->ai_addr, servinfo->ai_addrlen) == -1)
    {
        return -1;
    }

    freeaddrinfo(servinfo);
    return socketfd;
}
