#include "LogManager.h"
#include "Server.h"
#include <glog/logging.h>
#include "Utils.h"
#include <cppcms/json.h>
#include <unistd.h>
#include <fstream>

VTLogger *LogManager::m_pVTLogger = NULL;
VTLogger *LogManager::m_pVTLoggerUSER_REGISTER = NULL;
VTLogger *LogManager::m_pVTLoggerUSER_LOGIN = NULL;
VTLogger *LogManager::m_pVTLoggerCALL = NULL;
VTLogger *LogManager::m_pVTLoggerSMS = NULL;
VTLogger *LogManager::m_pVTLoggerDEVICE = NULL;
VTLogger *LogManager::m_pVTLoggerGEO = NULL;
VTLogger *LogManager::m_pVTLoggerMESSAGE = NULL;

// HaiNN 07-01-2021 Add 4 logs 
VTLogger *LogManager::m_pVTLoggerCALL_OUT = NULL;
VTLogger *LogManager::m_pVTLoggerCALL_FREE = NULL;
VTLogger *LogManager::m_pVTLoggerSMS_OUT = NULL;
VTLogger *LogManager::m_pVTLoggerCON_CURRENT = NULL;

// HAINN Add logs
// #if (REDIS_CHANGE)
VTLogger *LogManager::m_pVTLoggerUSER_CHANGE = NULL;
VTLogger *LogManager::m_pVTLoggerRELATION_CHANGE = NULL;

// HaiNN # Add log check queue size
VTLogger *LogManager::m_pVTLoggerQUEUE_SIZE = NULL;
// #endif

LogManager::LogManager(Server* server) : Component(server, LOG_MANGER_COMP)
{
    /*read file configure*/
	cppcms::json::value root;
	string path = "config/logmanager.json";
	std::ifstream file(path.c_str());

    std::string strSystemLog, strUserRegisterLog, strUserLoginLog;
    std::string strCallLog, strSmsLog, strDeviceLog, strGeoLog, strMessageLog;

    std::string strUserChangeLog , strRelationChange;
    std::string strQueueSizeLog;
     // Add logs
    std::string strCallOutLog, strCallFreeLog, strSmsOutLog, strConCurrentLog;
	if (!root.load(file, true))
	{
		file.close();
		//DLOG(INFO)<<"Error in load file:" << path;
		return;
	}
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    strSystemLog = root.get<std::string>("log_system");
    if(strSystemLog.size() == 0) strSystemLog = DEFAULT_LOG_SYSTEM_PATH;

    strUserRegisterLog = root.get<std::string>("log_user_register");
    if(strUserRegisterLog.size() == 0) strUserRegisterLog = DEFAULT_LOG_USER_REGISTER_PATH;

    strUserLoginLog = root.get<std::string>("log_user_login");
    if(strUserLoginLog.size() == 0) strUserLoginLog = DEFAULT_LOG_USER_LOGIN_PATH;

    strCallLog = root.get<std::string>("log_call");
    if(strCallLog.size() == 0) strCallLog = DEFAULT_LOG_CALL_PATH;

    strSmsLog = root.get<std::string>("log_sms");
    if(strSmsLog.size() == 0) strSmsLog = DEFAULT_LOG_SMS_PATH;

    strDeviceLog = root.get<std::string>("log_device");
    if(strDeviceLog.size() == 0) strDeviceLog = DEFAULT_LOG_DEVICE_PATH;
    
    strGeoLog = root.get<std::string>("log_geo");
    if(strGeoLog.size() == 0) strGeoLog = DEFAULT_LOG_GEO_PATH;

    strMessageLog = root.get<std::string>("log_message");
    if(strMessageLog.size() == 0) strMessageLog = DEFAULT_LOG_MESSAGE_PATH;

     // Add logs
    strCallOutLog = root.get<std::string>("log_call_out");
    if(strCallOutLog.size() == 0) strCallOutLog = DEFAULT_LOG_CALL_OUT_PATH;

    strCallFreeLog = root.get<std::string>("log_call_free");
    if(strCallFreeLog.size() == 0) strCallFreeLog = DEFAULT_LOG_CALL_FREE_PATH;

    strSmsOutLog = root.get<std::string>("log_sms_out");
    if(strSmsOutLog.size() == 0) strSmsOutLog = DEFAULT_LOG_SMS_OUT_PATH;

    strConCurrentLog = root.get<std::string>("log_con_current");
    if(strConCurrentLog.size() == 0) strConCurrentLog = DEFAULT_LOG_CON_CURRENT_PATH;

    strUserChangeLog = root.get<std::string>("log_user_change");
    if(strUserChangeLog.size() == 0) strUserChangeLog = DEFAULT_LOG_USER_CHANGE_PATH;

    strRelationChange = root.get<std::string>("log_relation_change");
    if(strRelationChange.size() == 0) strRelationChange = DEFAULT_LOG_RELATION_CHANGE_PATH;

    strQueueSizeLog = root.get<std::string>("log_queue_size");
    if(strQueueSizeLog.size() == 0) strQueueSizeLog = DEFAULT_LOG_QUEUE_SIZE_PATH;
    // init normal logger for system log
    // #define LOG_FILE    1
    INIT_LOGGER2(strSystemLog);
    // m_vtLogger = new VTLogger(DEFAULT_LOGGER_NAME, strSystemLog);
    // #undef LOG_FILE 
    // init service log file
    // #define LOG_FILE    1
    INIT_SERVICE_LOGGER2(USER_REGISTER, strUserRegisterLog);
    INIT_SERVICE_LOGGER2(USER_LOGIN, strUserLoginLog);
    INIT_SERVICE_LOGGER2(CALL, strCallLog);
    INIT_SERVICE_LOGGER2(SMS, strSmsLog);
    INIT_SERVICE_LOGGER2(DEVICE, strDeviceLog);
    INIT_SERVICE_LOGGER2(GEO, strGeoLog);
    INIT_SERVICE_LOGGER2(MESSAGE, strMessageLog);

    // Add logs
    INIT_SERVICE_LOGGER2(CALL_OUT, strCallOutLog);
    INIT_SERVICE_LOGGER2(CALL_FREE, strCallFreeLog);
    INIT_SERVICE_LOGGER2(SMS_OUT, strSmsOutLog);
    INIT_SERVICE_LOGGER2(CON_CURRENT, strConCurrentLog);

    // HAINN
    INIT_SERVICE_LOGGER2(USER_CHANGE, strUserChangeLog);
    INIT_SERVICE_LOGGER2(RELATION_CHANGE, strRelationChange);

    INIT_SERVICE_LOGGER2(QUEUE_SIZE, strQueueSizeLog)
    // #undef LOG_FILE 


//VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // url_elastic = root.get<std::string>("elastic_url");
    // tp::ThreadPoolOptions tp_option;
    // if (root.get<unsigned int>("worker_count") > tp_option.threadCount())
	// {
	// 	tp_option.setThreadCount(root.get<unsigned int>("worker_count"));
	// }
    // tp_option.setQueueSize(root.get<unsigned int>("queue_size"));
    // pool = new tp::ThreadPool(tp_option);




}

void LogManager::initialize()
{
}

void LogManager::start()
{
//  NOTE: this comment code is for debug
//    log_message(LOG_MESSAGE_TYPE_SMSOUT, "id_1");
//    sleep(1);
//    log_message(LOG_MESSAGE_TYPE_SMSOUT, "id_2");
//    sleep(2);
//    log_message(LOG_MESSAGE_TYPE_SMSOUT, "id_3");
//    sleep(4);
//    log_message(LOG_MESSAGE_TYPE_SMSOUT, "id_4");
//    sleep(5);
//    log_message(LOG_MESSAGE_TYPE_NORMAL, "id_5");
//    sleep(6);
//    log_message(LOG_MESSAGE_TYPE_NORMAL, "id_6");
//    sleep(10);
//    log_message(LOG_MESSAGE_TYPE_NORMAL, "id_7");

//    log_user_register("abc_1", "841698174847", 0);
//    sleep(2);

//    log_user_register("abc_2", "84169viettel", 0);
//    sleep(2);

//    log_user_register("abc_3", "84126vina", 2);
//    sleep(2);

//    log_user_register("abc_4", "84124vina", 2);
//    sleep(2);

//    log_user_register("abc_5", "8498viettel", 3);
//    sleep(2);

//    log_user_register("abc_6", "84188vietnammobile", 7);
//    sleep(2);

//    log_user_login("a1", "841698174847");
//    sleep(2);
//    log_user_login("a1", "841698174847");
//    sleep(2);
//    log_user_login("a1", "841698174847");
//    sleep(2);
//    log_user_login("a4", "841698174847");
//    sleep(2);
//    log_user_login("a5", "841698174847");
//    sleep(2);
//    log_user_login("a6", "841698174847");
//    sleep(2);
//    log_user_login("a7", "841698174847");
//    sleep(2);
//    log_user_login("a8", "841698174847");
//    sleep(2);
//    log_user_login("a9", "841698174847");
}
void LogManager::stop()
{
}

LogManager::~LogManager()
{
    if (pool) delete pool;
}

// NOTE: write_json treat all type of data is string ???
// Ref: http://stackoverflow.com/questions/2855741/why-boost-property-tree-write-json-saves-everything-as-string-is-it-possible-to
void LogManager::log_user_register(std::string id, std::string tel, std::string &strLogMsg)
{
    std::string path = url_elastic + "user/register/" + Utils::uuid_encode(id) + "?pretty";
    cppcms::json::value data;
    data.set("user_id", Utils::uuid_encode(id));
    data.set("time", current_time());
    data.set("time_t", current_time_t());
    data.set("type", "register");
    data.set("tel", tel);
   
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_user_login(std::string id, std::string tel, std::string &strLogMsg)
{
    std::string path = url_elastic + "user/login/" + std::to_string(current_time_t()) + "?pretty";
    cppcms::json::value data;
    data.set("id", Utils::uuid_encode(id));
    data.set("time", current_time());
    data.set("time_t", current_time_t());
    data.set("type", "login");
    data.set("tel", tel);

    //_send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(USER_LOGIN, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_call(int type, int duration, std::string id, std::string &strLogMsg)
{
    //std::string path = url_elastic + "call/" + convert_call_type_to_string(type) + "/" + Utils::uuid_encode(id) + "?pretty";
    std::string call_type = convert_call_type_to_string(type);
    std::string path = url_elastic + call_type + "/" + call_type + "/" + Utils::uuid_encode(id) + "?pretty";
	cppcms::json::value data;
	data.set("id", Utils::uuid_encode(id));
	data.set("time", current_time());
	data.set("time_t", current_time_t());
    data.set("type", call_type);
	data.set("duration", duration);
	
//	_send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(CALL, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

// log call add CallerID and CalleeID
void LogManager::log_call(int type, int duration,std::string strCallerID, std::string strCalleeID, std::string id, std::string &strLogMsg)
{
    //std::string path = url_elastic + "call/" + convert_call_type_to_string(type) + "/" + Utils::uuid_encode(id) + "?pretty";
    std::string call_type = convert_call_type_to_string(type);
    std::string path = url_elastic + call_type + "/" + call_type + "/" + Utils::uuid_encode(id) + "?pretty";
	cppcms::json::value data;
	data.set("id", Utils::uuid_encode(id));
	data.set("time", current_time());
	data.set("time_t", current_time_t());
    data.set("type", call_type);
	data.set("duration", duration);
    data.set("caller_id", Utils::uuid_encode(strCallerID));
    data.set("callee_id",Utils::uuid_encode(strCalleeID));
	
//	_send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(CALL, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_sms(int type, std::string id, std::string &strLogMsg)
{
    //std::string path = url_elastic + "sms/" + convert_sms_type_to_string(type) + "/" + Utils::uuid_encode(id) + "?pretty";
    std::string type_sms = convert_sms_type_to_string(type);
    std::string path = url_elastic + type_sms + "/" + type_sms + "/" + Utils::uuid_encode(id) + "?pretty";
	cppcms::json::value data;
	data.set("id", Utils::uuid_encode(id));
	data.set("time", current_time());
	data.set("time_t", current_time_t());
    data.set("type", type_sms);

	// _send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(SMS, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_device(int type, std::string platform_version, std::string id, std::string &strLogMsg)
{
    //std::string path = url_elastic + "device/" + convert_os_to_string(type) + "/" + Utils::uuid_encode(id) + "?pretty";
    std::string type_device = convert_os_to_string(type);
    std::string id_index = Utils::uuid_encode(id) + std::to_string(current_time_t());
    std::string path = url_elastic + type_device + "/" + type_device + "/" + id_index + "?pretty";
	cppcms::json::value data;
    //data.set("id", Utils::uuid_encode(id));
	data.set("time", current_time());
	data.set("time_t", current_time_t());
    data.set("type", type_device);
	data.set("platform_version", platform_version);
	
   
	//_send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(DEVICE, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_geo(double lat, double lon, std::string id, std::string &strLogMsg)
{
	std::string path = url_elastic + "geo/" + Utils::uuid_encode(id) + "?pretty";
	cppcms::json::value data;
	data.set("id", Utils::uuid_encode(id));
	data.set("time", current_time());
	data.set("time_t", current_time_t());
	data.set("lat", lat);
	data.set("lon", lon);
	
	//_send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(GEO, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

// log message add sender
void LogManager::log_message(log_message_type type, std::string SenderID, std::string id, std::string &strLogMsg)
{
    //std::string path = url_elastic + "message/" + convert_log_message_type_to_string(type) + "/" + Utils::uuid_encode(id) + "?pretty";
    std::string type_message = convert_log_message_type_to_string(type);
    std::string path = url_elastic + type_message + "/" + type_message + "/" + Utils::uuid_encode(id) + "?pretty";
    cppcms::json::value data;
    data.set("id", Utils::uuid_encode(id));
    data.set("time", current_time());
    data.set("time_t", current_time_t());
    data.set("type", type_message);
    data.set("sender_id", Utils::uuid_encode(SenderID));

    //_send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(MESSAGE, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}
void LogManager::log_concurrent(int fd, std::string &strLogMsg)
{
    //std::string path = url_elastic + "message/" + convert_log_message_type_to_string(type) + "/" + Utils::uuid_encode(id) + "?pretty";

    cppcms::json::value data;
    data.set("fd", fd);
    data.set("time", current_time());
    data.set("time_t", current_time_t());

    //_send(path, data.save(cppcms::json::readable));
    //VT2.5.0 # SONNT # 05-05-2020 # upgrade new logger
    // VTSLOG(MESSAGE, vtlog::INFO,  data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_time_run_service(int type_service, uint64_t duration_ms, std::string &strLogMsg)
{
    std::string type_service_name = convert_log_type_service_to_string(type_service);
    std::string id = Utils::generate_text_uuid() + "_" + type_service_name;
    std::string path = url_elastic + type_service_name + "/" + type_service_name + "/" + id + "?pretty";
    cppcms::json::value data;
    data.set("time", current_time());
    data.set("time_t", current_time_t());
    data.set("type", type_service_name);
    data.set("duration", duration_ms);
    // send
    //_send(path, data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_userchange(std::string strType, std::string strUserID, uint64_t uTime, std::string &strLogMsg)
{
    cppcms::json::value data;
    data.set("time", uTime);
    data.set("type", strType);
    data.set("UserID", strUserID);
    // send
    //_send(path, data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

void LogManager::log_relationchange(std::string strType, std::string strOwnerID, std::string strFriendID, uint64_t uTime, std::string &strLogMsg)
{
    cppcms::json::value data;
    data.set("time: ", uTime);
    data.set("type: ", strType);
    data.set("OwnerID: ", strOwnerID);
    data.set("FriendID: ", strFriendID);
    // send
    //_send(path, data.save(cppcms::json::readable));
    strLogMsg = data.save(cppcms::json::compact);
}

std::string LogManager::convert_log_message_type_to_string(log_message_type type)
{
    if(type == LOG_MESSAGE_TYPE_NORMAL) return "message_normal";
    if(type == LOG_MESSAGE_TYPE_SMSOUT) return "message_smsout";
    return "message_normal";
}

void LogManager::log_size(int queue_size, std::string &strLogMsg)
{
    cppcms::json::value data;

    data.set("queue_size", queue_size);
    data.set("time", current_time());
    data.set("time_t", current_time_t());
    strLogMsg = data.save(cppcms::json::compact);
}

std::string LogManager::convert_os_to_string(int type)
{
    switch (type) {
    case 0:
        return "os_blackberry";
    case 1:
        return "os_ios";
    case 2:
        return "os_android";
    case 3:
        return "os_winphone";
    case 4:
        return "os_macx";
    case 5:
        return "os_windows";
    case 6:
        return "os_linux";
    default:
        return "os_other";
    }
}

std::string LogManager::convert_call_type_to_string(int type)
{
	switch (type)
	{
		case 0:
			return "callfree";
		case 1:
			return "callout";
		case 2:
			return "callin";
		case 3:
			return "callgroup";
		default:
			return "callother";
	}
}

std::string LogManager::convert_sms_type_to_string(int type)
{
	switch (type)
	{
		case 0:
			return "smsin";
		case 1:
			return "smsout";
		default:
			return "";
	}
}

std::string LogManager::convert_log_type_service_to_string(int type_service)
{

}

/// Ref: http://www.epochconverter.com/programming/c
std::string LogManager::current_time()
{
    time_t now;
    time(&now);
    struct tm  ts;
    char       buf[80];
    // { "date": "2015-01-01T12:10:30Z" }
    // https://www.w3.org/TR/1998/NOTE-datetime-19980827
    ts = *gmtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%dT%H:%M:%SZ", &ts);
    // printf("%s\n", buf);
    std::string ret(buf);
    return ret;
}

time_t LogManager::current_time_t()
{
    time_t now;
    time(&now);
    return now * 1000;
}
