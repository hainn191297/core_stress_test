//
// Created by SonNT on 4/27/2020.
//

#ifndef VIETTALK_SERVER_VTSPDLOG_H
#define VIETTALK_SERVER_VTSPDLOG_H

#include "../Logger.h"

#include <memory>


namespace spdlog
{
    class logger;
}

namespace vtlog
{
    class VTSpdLog : public Logger
    {
    public:
        VTSpdLog(const std::string strLoggerName, const std::string strLogpath);
        VTSpdLog();
        int InitLog();
        //int Log(const int logLevel, const std::string &strMessage);
        int Log(const int logLevel, const std::string &strMessage);
        int Log(const int logLevel, const char *pzsFormat, ...);
        VTSpdLog &operator<<(const std::string &strMessage);

    private:
        std::shared_ptr<spdlog::logger> m_pSpdLog;
    };

#endif //VIETTALK_SERVER_VTSPDLOG_H

};