#ifndef LOG_MANAGER_H_
#define LOG_MANAGER_H_

#include "Component.h"
#include <time.h>
#include <stdio.h>
#include "thread_pool.hpp"
#include <math.h>
#include "logger/VTLogger.h"

#define LOG_MANGER_COMP "LOG_MANAGER_COMP"

#define DEFAULT_LOG_SYSTEM_PATH             "./comm_server.log"    
#define DEFAULT_LOG_USER_REGISTER_PATH      "./user_register.log"
#define DEFAULT_LOG_USER_LOGIN_PATH         "./user_login.log"
#define DEFAULT_LOG_CALL_PATH               "./call.log"
#define DEFAULT_LOG_SMS_PATH                "./sms.log"
#define DEFAULT_LOG_DEVICE_PATH             "./device.log"
#define DEFAULT_LOG_GEO_PATH                "./geo.log"
#define DEFAULT_LOG_MESSAGE_PATH            "./message.log"
#define DEFAULT_LOG_SMS_OUT_PATH            "./sms_out.log"
#define DEFAULT_LOG_CALL_OUT_PATH           "./call_out.log"
#define DEFAULT_LOG_CALL_FREE_PATH          "./call_free.log"
#define DEFAULT_LOG_CON_CURRENT_PATH        "./con_current.log"

#define DEFAULT_LOG_USER_CHANGE_PATH        "./user_change.log"
#define DEFAULT_LOG_RELATION_CHANGE_PATH    "./relation_change.log"
#define DEFAULT_LOG_QUEUE_SIZE_PATH    "./queue_size.log"
//create obj
// CREATE_LOGGER;


/*  We define some index
 *  - message (for statistic message chat, message sms ...)
 *  - user    (for statistic user register, user login ..)
 *	- call	(for statistic callin, callout, callfree...)
 *	- sms (for statistic smsin, smsout)
 *	- device info
 *  For index 'message' we have 2 type
 *  - normal  (for tracking normal message text, photo, sticker ...)
 *  - smsout  (for tracking smsout message)
 *  For index 'user'
 *  - register (for tracking user register)
 *  - login     (for tracking user login)
 *  For index 'call' we have 3 type
 *  - callin
 *  - callout
 *  - callfree
 *	For index 'sms' we have 2 type
 *	- smsin
 *	- smsout
 *	For index 'device' we have some type
 *	- android
 *	- ios
 *	- window
 * For index 'service' we have some service
 *  - authenticate_service
 *  - checkaccount_service
 *  - login_service
 *  - listchats_service
 *  - listcontacts_service
 *  - listmessages_service
 */



class Server;
class LogManager : public Component
{
public:
    explicit LogManager(Server* server);
    virtual ~LogManager();

	void initialize() override;
	void start() override;
	void stop() override;

    enum log_message_type {
        LOG_MESSAGE_TYPE_NORMAL = 0,
        LOG_MESSAGE_TYPE_SMSOUT = 1
    };

    void log_user_register(std::string id, std::string tel, std::string &strLogMsg);// id - user_id
    void log_user_login(std::string id, std::string tel, std::string &strLogMsg);// id - user_id
    void log_call(int type, int duration, std::string id, std::string &strLogMsg);// id - call_id
    void log_sms(int type, std::string id, std::string &strLogMsg);// id - message_id
    void log_device(int type, std::string platform_version, std::string id, std::string &strLogMsg);// id - session_id
    void log_geo(double lat, double lon, std::string id, std::string &strLogMsg);// id - session_id
    // void log_message(log_message_type type, std::string id, std::string &strLogMsg);// id - message_id
    void log_time_run_service(int type_service, uint64_t duration_ms, std::string &strLogMsg);

    void log_message(log_message_type type, std::string SenderID, std::string id, std::string &strLogMsg); // id - messageid - sender id
    void log_call(int type, int duration,std::string strCallerID, std::string strCalleeID, std::string id, std::string &strLogMsg); // id - call_id - caller_id - callee_id
    void log_concurrent(int fd, std::string &strLogMsg); // fd - number of connection

    void log_userchange(std::string strType, std::string strUserID, uint64_t uTime, std::string &strLogMsg);
    void log_relationchange(std::string strType, std::string strOwnerID, std::string strFriendID, uint64_t uTime, std::string &strLogMsg);

    void log_size(int queue_size, std::string &strLogMsg);

    std::string convert_call_type_to_string(int type);
    static std::string getCurrentTimeYYYYMMddHHmmss()
    {
        char buffer[80];
        time_t t1 = time(NULL);   // get time now
        struct tm* now = gmtime(&t1);
        strftime(buffer,80,"%Y%m%d%H%M%S",now);
        std::string current_time(buffer, 14);
        return current_time;
    }
    // static VTLogger *m_vtLogger;
    CREATE_LOGGER;
    CREATE_SERVICE_LOGGER(USER_REGISTER);
    CREATE_SERVICE_LOGGER(USER_LOGIN);
    CREATE_SERVICE_LOGGER(CALL);
    CREATE_SERVICE_LOGGER(SMS);
    CREATE_SERVICE_LOGGER(DEVICE);
    CREATE_SERVICE_LOGGER(GEO);
    CREATE_SERVICE_LOGGER(MESSAGE);

    // Add Logs
    CREATE_SERVICE_LOGGER(CALL_OUT);
    CREATE_SERVICE_LOGGER(CALL_FREE);
    CREATE_SERVICE_LOGGER(SMS_OUT);
    CREATE_SERVICE_LOGGER(CON_CURRENT);

    CREATE_SERVICE_LOGGER(USER_CHANGE);
    CREATE_SERVICE_LOGGER(RELATION_CHANGE);

    CREATE_SERVICE_LOGGER(QUEUE_SIZE);
private:
    /// send to elastichsearch
    void _send(const std::string& path, const std::string& data);

    /// helper
    std::string convert_log_message_type_to_string(log_message_type type);
    std::string convert_os_to_string(int type);
    std::string convert_sms_type_to_string(int type);
    std::string convert_log_type_service_to_string(int type_service);
    std::string current_time();
    time_t current_time_t();
    ///
    tp::ThreadPool *pool;
    std::string url_elastic;
};

#endif /* LOG_MANAGER_H_ */
