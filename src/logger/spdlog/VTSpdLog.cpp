//
// Created by SonNT on 4/27/2020.
//

#include "VTSpdLog.h"
#include "spdlog/spdlog.h"
//#include "spdlog/cfg/env.h" // for loading levels from the environment variable
#include "spdlog/async.h"
#include "spdlog/sinks/basic_file_sink.h"

vtlog::VTSpdLog::VTSpdLog()
{

}
vtlog::VTSpdLog::VTSpdLog(const std::string strLoggerName, const std::string strLogpath)
{
    m_pSpdLog =  spdlog::basic_logger_mt<spdlog::async_factory>(strLoggerName, strLogpath);
    spdlog::set_level(spdlog::level::debug);
	spdlog::flush_every(std::chrono::seconds(2));

}
int vtlog::VTSpdLog::InitLog()
{
    return 0;
}

//int vtlog::VTSpdLog::Log(const int logLevel, const std::string &strMessage)
//{
//    if(logLevel == vtlog::INFO) m_pSpdLog->info(strMessage);
//    else if (logLevel == vtlog::ERROR) m_pSpdLog->error(strMessage);
//    else if (logLevel == vtlog::WARNING) m_pSpdLog->warn(strMessage);
//    else if (logLevel == vtlog::DEBUG) m_pSpdLog->debug(strMessage);
//    else if(logLevel == vtlog::FATAL) m_pSpdLog->error(strMessage);
//
//    return SUCCESS_LOG;
//}

int vtlog::VTSpdLog::Log(const int logLevel, const std::string &strMessage)
{
    if(logLevel == vtlog::INFO) m_pSpdLog->info(strMessage);
    else if (logLevel == vtlog::ERROR) m_pSpdLog->error(strMessage);
    else if (logLevel == vtlog::WARNING) m_pSpdLog->warn(strMessage);
    else if (logLevel == vtlog::DEBUG) m_pSpdLog->debug(strMessage);
    else if(logLevel == vtlog::FATAL) m_pSpdLog->error(strMessage);

    return SUCCESS_LOG;
}

int vtlog::VTSpdLog::Log(const int logLevel, const char *pzsFormat, ...)
{
    char szBuffer[MAX_LOG_SIZE];
    va_list args;

    va_start(args, pzsFormat);
    vsnprintf(szBuffer,MAX_LOG_SIZE,pzsFormat, args);

    if(logLevel == vtlog::INFO) m_pSpdLog->info(szBuffer);
    else if (logLevel == vtlog::ERROR) m_pSpdLog->error(szBuffer);
    else if (logLevel == vtlog::WARNING) m_pSpdLog->warn(szBuffer);
    else if (logLevel == vtlog::DEBUG) m_pSpdLog->debug(szBuffer);
    else if(logLevel == vtlog::FATAL) m_pSpdLog->error(szBuffer);

    va_end(args);

    return SUCCESS_LOG;
}

vtlog::VTSpdLog &vtlog::VTSpdLog::operator<<(const std::string &strMessage)
{

}