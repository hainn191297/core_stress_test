//
// Created by SonNT on 4/27/2020.
//

#include "VTLogger.h"
#include "Utils.h"

VTLogger::VTLogger()
{
#ifdef LOG_FILE
    m_pLogFile = new vtlog::VTSpdLog(DEFAULT_LOGGER_NAME, DEFAULT_LOG);
#endif

#ifdef LOG_DEBUG
    m_pLogDebug = new vtlog::VTGlog();
#endif

}

VTLogger::VTLogger(std::string strLoggerName, std::string strLogPath)
{
#ifdef LOG_FILE
    m_pLogFile = new vtlog::VTSpdLog(strLoggerName, strLogPath);
#endif

#ifdef LOG_DEBUG
    m_pLogDebug = new vtlog::VTGlog();
#endif
}

VTLogger::~VTLogger()
{
    SAFE_DEL(m_pLogFile);
    SAFE_DEL(m_pLogDebug);
}

int VTLogger::InitLog()
{
    return 0;
}

int VTLogger::Log(const int logLevel, const std::string &strMessage)
{
#ifdef LOG_FILE
    m_pLogFile->Log(logLevel, strMessage);
#endif

#ifdef LOG_DEBUG
   m_pLogDebug->Log(logLevel, strMessage);
#endif

return SUCCESS_LOG;
}

int VTLogger::Log(const int logLevel, const char *pzsFormat, ...)
{
    char szBuffer[MAX_LOG_SIZE];
    va_list args;

    va_start (args, pzsFormat);
    vsnprintf (szBuffer,MAX_LOG_SIZE,pzsFormat, args);
#ifdef LOG_FILE
    m_pLogFile->Log(logLevel,  std::string(szBuffer));
#endif

#ifdef LOG_DEBUG
    m_pLogDebug->Log(logLevel,  std::string(szBuffer));
#endif

    va_end (args);

    return SUCCESS_LOG;
}

VTLogger &VTLogger::operator<<(const std::string &strMessage)
{
    VTLogger vtLogger;
    return vtLogger;
}