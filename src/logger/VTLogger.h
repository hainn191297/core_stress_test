//
// Created by SonNT on 4/27/2020.
//

#ifndef VIETTALK_SERVER_VTLOG_H
#define VIETTALK_SERVER_VTLOG_H

#include "vt-glog/VTGlog.h"
#include "spdlog/VTSpdLog.h"

#define LOG_FILE 1
#define LOG_DEBUG 1
#define _DEBUG

#ifdef _DEBUG
static inline void LogBuilder(std::string &strOut, const char *pzsFormat, ...)
{
	char szBuffer[MAX_LOG_SIZE];
    va_list args;

    va_start (args, pzsFormat);
    vsnprintf (szBuffer,MAX_LOG_SIZE,pzsFormat, args);
	strOut = szBuffer;
}
#endif // _DEBUG

class VTLogger {
public:
    VTLogger();
    ~VTLogger();
    VTLogger(std::string strLoggerName, std::string strLogPath);
    int InitLog();
    int Log(const int logLevel, const std::string &strMessage);
   // int Log(const int logLevel, const std::string strMessage);
    int Log(const int logLevel, const char *pzsFormat, ...);
    VTLogger &operator<<(const std::string &strMessage);

private:
    vtlog::Logger *m_pLogDebug;
    vtlog::Logger *m_pLogFile;
};

#define CREATE_LOGGER\
            static VTLogger *m_pVTLogger;

#define INIT_LOGGER \
            m_pVTLogger = new VTLogger();

#define INIT_LOGGER2(logPath) \
            m_pVTLogger = new VTLogger(DEFAULT_LOGGER_NAME, logPath);

#ifdef _DEBUG
#define VTLOG(loglevel, message)\
	{\
		DLOG(INFO) << (message);\
	}
#else
#define VTLOG(loglevel, message)\
	do\
	{\
		LogManager::m_pVTLogger->Log(loglevel, message);\
	} while (0);
#endif

		/*char szBuffer[MAX_LOG_SIZE];\*/
#ifdef _DEBUG
#define VTLOG2(loglevel, format, ...)\
	{\
		std::string strOutLog;\
		LogBuilder(strOutLog, format, ##__VA_ARGS__);\
		DLOG(INFO) << strOutLog;\
	}
#else
#define VTLOG2(loglevel, format, ...)\
	do\
	{\
		LogManager::m_pVTLogger->Log(loglevel, format,  ##__VA_ARGS__);\
	} while (0);
#endif

#define CREATE_SERVICE_LOGGER(name) \
            static VTLogger *m_pVTLogger ## name;

#define INIT_SERVICE_LOGGER(name) \
            m_pVTLogger ## name = new VTLogger();

#define INIT_SERVICE_LOGGER2(name, logPath) \
            m_pVTLogger ## name = new VTLogger(#name, logPath);

#define VTSLOG(name, loglevel, message)\
                do {\
                LogManager::m_pVTLogger ## name->Log(loglevel, message);\
                } while (0);

#define VTSLOG2(name, loglevel, format, ...)\
                do {\
                LogManager::m_pVTLogger  ## name->Log(loglevel, format,  ##__VA_ARGS__);\
                } while (0);



#endif //VIETTALK_SERVER_VTLOG_Hs
