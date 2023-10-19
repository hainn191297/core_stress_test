//
// Created by SonNT on 4/27/2020.
//

#include "VTGlog.h"
#include <glog/logging.h>

vtlog::VTGlog::VTGlog()
{
//    google::InitGoogleLogging(".");
//    google::SetLogDestination(google::GLOG_INFO, "logs");
//    google::SetStderrLogging(google::NUM_SEVERITIES);
//    google::SetLogFilenameExtension(".log_");
}

int vtlog::VTGlog::InitLog()
{

}

//int vtlog::VTGlog::Log(const int logLevel, const std::string &strMessage)
//{
//    if(logLevel == INFO) DLOG(INFO)<< strMessage;
//    else if(logLevel == DEBUG) DLOG(INFO)<< strMessage;
//    else if(logLevel == WARNING) DLOG(WARNING)<< strMessage;
//    else if(logLevel == ERROR) DLOG(ERROR)<< strMessage;
//    else if(logLevel == FATAL) DLOG(WARNING)<< strMessage;
//
//    return SUCCESS_LOG;
//}


int vtlog::VTGlog::Log(const int logLevel, const std::string &strMessage)
{
    if(logLevel == INFO) DLOG(INFO)<< strMessage;
    else if(logLevel == DEBUG) DLOG(INFO)<< strMessage;
    else if(logLevel == WARNING) DLOG(WARNING)<< strMessage;
    else if(logLevel == ERROR) DLOG(ERROR)<< strMessage;
    else if(logLevel == FATAL) DLOG(WARNING)<< strMessage;

    return SUCCESS_LOG;
}

int vtlog::VTGlog::Log(const int logLevel, const char *pzsFormat, ...)
{
    char szBuffer[MAX_LOG_SIZE];
    va_list args;

    va_start (args, pzsFormat);
    vsnprintf (szBuffer,MAX_LOG_SIZE,pzsFormat, args);


    if(logLevel == INFO) DLOG(INFO)<< szBuffer;
    else if(logLevel == DEBUG) DLOG(INFO)<< szBuffer;
    else if(logLevel == WARNING) DLOG(WARNING)<< szBuffer;
    else if(logLevel == ERROR) DLOG(ERROR)<< szBuffer;
    else if(logLevel == FATAL) DLOG(WARNING)<< szBuffer;

    va_end (args);

    return SUCCESS_LOG;
}

vtlog::VTGlog &vtlog::VTGlog::operator<<(const std::string &strMessage)
{

}