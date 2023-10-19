//
// Created by SonNT on 4/27/2020.
//

#ifndef VIETTALK_SERVER_LOGGER_H
#define VIETTALK_SERVER_LOGGER_H
#include <stdarg.h>
#include <stdio.h>
#include <string>
#include <iostream>

#define DEFAULT_LOGGER_NAME "VT"
#define DEFAULT_LOG "./comm-server.log"
#define  MAX_LOG_SIZE 2048

#define SUCCESS_LOG 0

namespace vtlog {

    enum LOG_LEVEL
    {
        DEBUG,
        INFO,
        WARNING,
        ERROR,
        FATAL
    };

    class Logger {
    public:
        virtual int InitLog() = 0;
        virtual int Log(const int logLevel, const std::string &strMessage) = 0;
        virtual int Log(const int logLevel, const char *pzsFormat, ...) = 0;
        Logger &operator<<(const std::string &strMessage);
    };
}
#endif //VIETTALK_SERVER_LOGGER_H
