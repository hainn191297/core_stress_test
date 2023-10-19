//
// Created by SonNT on 4/27/2020.
//

#ifndef VIETTALK_SERVER_VTGLOG_H
#define VIETTALK_SERVER_VTGLOG_H

#include "../Logger.h"

namespace vtlog
{
    class VTGlog : public Logger
    {
    public:
        VTGlog();
        int InitLog();
       // int Log(const int logLevel, const std::string &strMessage);
        int Log(const int logLevel, const std::string &strMessage);
        int Log(const int logLevel, const char *pzsFormat, ...);
        VTGlog &operator<<(const std::string &strMessage);
    };

}


#endif //VIETTALK_SERVER_VTGLOG_H
