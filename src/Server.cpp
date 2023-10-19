/*
 * Server.cpp
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#include "Server.h"
#include "Component.h"
#include "core/Engine.h"
// #include "tcp/TcpServer.h"
#include "logger/LogManager.h"
#include <glog/logging.h>
#include <Utils.h>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cppcms/json.h>
#include <boost/algorithm/string/replace.hpp>

Server::Server(cppcms::json::value const &s): _config(s)
{
	_components.set_empty_key("");
	_components.set_deleted_key(" ");
}

Server::~Server()
{
}

void Server::register_component(component_ptr component)
{
	// _components[component->id()] = component;
}

void Server::register_components(cppcms::service &service)
{
	// auto log = boost::make_shared<LogManager>(this);
    // this->register_component(log);
	// auto engine = boost::make_shared<core::Engine>(this);
	// this->register_component(engine);

	// VTLOG2(vtlog::DEBUG, "Worker count: %d", _config.worker_count());
	// auto tcp =  boost::make_shared<tcp::TcpServer>(this);
	// this->register_component(tcp);
}


std::string Server::renew_swift_auth_token(bool is_admin, std::string& auth_token)
{
	// return Server::renew_swift_auth_token_ceph(is_admin,auth_token);
	//return Server::renew_swift_auth_token_openstack(is_admin,auth_token);
}

/*ceph
 * GET /auth HTTP/1.1
Host: swift.radosgwhost.com
X-Auth-User: johndoe
X-Auth-Key: R7UUOLFDI2ZI9PRCQ53K
 */
std::string Server::renew_swift_auth_token_ceph(bool is_admin, std::string& auth_token)
{
    // CURL *curl;
    // CURLcode res;
    // curl = curl_easy_init();
    // std::string s, new_auth_token, auth_user, auth_key;
    // std::map<std::string, std::string> mHeader;


    // if (curl)
    // {
    //     struct curl_slist *headers = NULL;

    //     curl_easy_setopt(curl, CURLOPT_URL, _config.keystone_auth_url().c_str());
    //     curl_easy_setopt(curl, CURLOPT_HTTPGET, true);

    //     curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Utils::curlWrite_CallbackFunc_StdString);
    //     curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Utils::header_callback);
    //     curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    //     curl_easy_setopt(curl, CURLOPT_HEADERDATA, &mHeader);
    //     /* Now specify the POST data */
    //     if (is_admin)
    //     {

    //         auth_user = "X-Auth-User: " + _config.swift_username_admin();
    //         auth_key = "X-Auth-Key: "  + _config.swift_password_admin();
    //     }
    //     else
    //     {

    //         auth_user = "X-Auth-User: " + _config.swift_username_client();
    //         auth_key = "X-Auth-Key: "  + _config.swift_password_client();
    //     }

    //     headers = curl_slist_append(headers, auth_user.c_str());
    //     headers = curl_slist_append(headers, auth_key.c_str());
    //     curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    //     curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    //     /* Perform the request, res will get the return code */
    //     res = curl_easy_perform(curl);
    //     /* Check for errors */
    //     if(res != CURLE_OK)
    //     {
    //         DLOG(ERROR)<< "curl_easy_perform() failed:" << curl_easy_strerror(res);
    //     }
    //     else
    //     {

    //         std::map<std::string, std::string>::const_iterator itt;
    //         for (itt = mHeader.begin(); itt != mHeader.end(); itt++)
    //         {
    //             if (itt->first == "X-Auth-Token")
    //             {
    //                 new_auth_token = itt->second;
    //                 break;
    //             }
    //         }

    //     }
    //     /* always cleanup */
    //     curl_easy_cleanup(curl);
    //     /* free the custom headers */
    //     curl_slist_free_all(headers);
    // }
	// if(new_auth_token.size() > 5)
	// {
	// 	auth_token = new_auth_token.substr(5);
	// }
	// VTLOG2(vtlog::DEBUG, "auth_token2 %s", auth_token.c_str());
    return auth_token;
}

std::string Server::renew_swift_auth_token_openstack(bool is_admin, std::string& auth_token)
{
	// CURL *curl;
	// CURLcode res;
	// curl = curl_easy_init();
    std::string s, new_auth_token;
    // std::map<std::string, std::string> mHeader;

	// if (curl)
	// {
	// 	struct curl_slist *headers = NULL;
    //     headers = curl_slist_append(headers, "Accept: application/json");
    //     headers = curl_slist_append(headers, "Content-Type: application/json");
	// 	headers = curl_slist_append(headers, "charsets: utf-8");
	// 	curl_easy_setopt(curl, CURLOPT_URL, _config.keystone_auth_url().c_str());
	// 	curl_easy_setopt(curl, CURLOPT_POST, true);
	// 	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	// 	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Utils::curlWrite_CallbackFunc_StdString);
    //     curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, Utils::header_callback);
	// 	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
    //     curl_easy_setopt(curl, CURLOPT_HEADERDATA, &mHeader);
    //     /* Now specify the POST data */
	// 	std::string swift_username, swift_password, swift_tenantname;
	// 	if (is_admin)
	// 	{
	// 		swift_username = _config.swift_username_admin();
	// 		swift_tenantname = _config.swift_tenantname_admin();
	// 		swift_password = _config.swift_password_admin();
	// 	}
	// 	else
	// 	{
	// 		swift_username = _config.swift_username_client();
	// 		swift_tenantname = _config.swift_tenantname_client();
	// 		swift_password = _config.swift_password_client();
	// 	}

    //     std::string jsonstr = "{ \"auth\": {\"identity\": {\"methods\": [\"password\"], \"password\": {\"user\": { \"name\": \"" + swift_username + "\", \"domain\": { \"id\": \"default\" }, \"password\": \"" +
    //     						swift_password + "\" }}}, \"scope\": { \"project\": { \"name\": \"service\", \"domain\": { \"id\": \"default\" }}}}}";

    //     DLOG(INFO) << "jsonstr : " << jsonstr;
    //     DLOG(INFO) << " keystone URL: " << _config.keystone_auth_url();

    //     curl_easy_setopt(curl, CURLOPT_POSTFIELDS, (void*)jsonstr.c_str());
    //     curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, jsonstr.length());
	// 	/* Perform the request, res will get the return code */
	// 	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
    //     /* Perform the request, res will get the return code */
	// 	res = curl_easy_perform(curl);
	// 	/* Check for errors */
	// 	if(res != CURLE_OK)
	// 	{
	// 		DLOG(ERROR)<< "curl_easy_perform() failed:" << curl_easy_strerror(res);
	// 	}
	// 	else
    //     {
    //         DLOG(INFO)<<"result: "<<s.c_str();
	// 		stringstream ss;
	// 		ss << s;
	// 		cppcms::json::value json_read;
	// 		if (!json_read.load(ss, true))
	// 		{
	// 			DLOG(ERROR) << "parse json error!";

	// 		}
	// 		else
	// 		{
    //             std::map<std::string, std::string>::const_iterator itt;
    //             for (itt = mHeader.begin(); itt != mHeader.end(); itt++)
    //             {
    //                 if (itt->first == "X-Subject-Token")
    //                 {
    //                     auth_token = itt->second;
    //                     break;
    //                 }
    //             }
    //         	try
    //         	{
    //         		new_auth_token = json_read.get<string>("token.project.id");
    //         		DLOG(INFO) << "new_auth_token:" << new_auth_token << " ID: " << auth_token;
    //         	}
    //         	catch (std::exception const &e)
    //         	{
    //         		DLOG(ERROR)<< "can not parse json:" << e.what();
    //         		new_auth_token = "";
    //         		DLOG(ERROR) << "new_auth_token:" << new_auth_token << " ID: " << auth_token;
    //         	}
	// 		}
	// 	}
	// 	/* always cleanup */
	// 	curl_easy_cleanup(curl);
	// 	/* free the custom headers */
	// 	curl_slist_free_all(headers);
	// }
	return new_auth_token;
}


component_ptr Server::component(std::string id)
{
	// auto it = _components.find(id);
	// if (it != _components.end()) return it->second;
	// return component_ptr();
}

void Server::init()
{
	// for (auto& c : _components)
	// {
	// 	c.second->initialize();
	// }
}

void Server::start()
{
	// TNVN1.0.x # SonTV # 2020-12-17 # Priority start component -> tcp server -> http server
	// component_ptr pTCPComp = NULL;

	// for (auto& c : _components)
	// {
	// 	// Skip starting tcp component
	// 	if (c.first == TCP_COMP)
	// 	{
	// 		pTCPComp = c.second;
	// 		continue;
	// 	}

	// 	c.second->start();
	// }
    auto engine = _components.find(ENGINE_COMP);
    if (engine != _components.end())
    {
        VTLOG(vtlog::DEBUG, "[Core] Start engine");
        engine->second->start();
    }
    else
    {
        VTLOG(vtlog::DEBUG, "[Core] Engine not found");
    }
	// for (auto& c : _components)
	// {
	// 	if (c.first == TCP_COMP)
	// 	{
	// 		continue;
	// 	}

	// 	c.second->join();
	// }

	// Post start tcp and http server
	// if (pTCPComp)
	// {
	// 	pTCPComp->start();
	// 	pTCPComp->join();
	// }
}

void Server::stop()
{
	// for (auto& c : _components)
	// {
	// 	c.second->stop();
	// }
}

std::string Server::swift_api_url() const
{
	return m_swift_api_url;
}

std::string Server::swift_auth_token() const
{
	return m_swift_auth_token;
}

std::string Server::swift_client_url() const
{
	return m_swift_client_url;
}

std::string Server::swift_apps_url() const
{
	return m_swift_apps_url;
}

void Server::set_swift_api_url(std::string swift_api_url)
{
	boost::mutex::scoped_lock scoped_lock(_mutex);
	m_swift_api_url = swift_api_url;
}

void Server::set_swift_auth_token(std::string swift_auth_token)
{
	boost::mutex::scoped_lock scoped_lock(_mutex);
	m_swift_auth_token = swift_auth_token;
}

void Server::set_swift_client_url(std::string swift_client_url)
{
	boost::mutex::scoped_lock scoped_lock(_mutex);
	m_swift_client_url = swift_client_url;
}

void Server::set_swift_apps_url(std::string swift_apps_url)
{
	boost::mutex::scoped_lock scoped_lock(_mutex);
	m_swift_apps_url = swift_apps_url;
}

const ServerConfig& Server::settings()
{
	return _config;
}

ServerConfig::ServerConfig(const cppcms::json::value &s): _settings(s), m_uSessionExpTime(0), m_iAppVersionStatus(0), m_iSwApiHttpRemoveAllContact(0)
{
	cppcms::json::value jConfig;
	std::string strConfigFilePath = "config/database.json";
	string strPathAuthenticateApi = "config/authenticate_api.json";
	string strAppVersionValidationConfig = "config/app_version.json";
	std::string strStickerConfigFile = "config/stickers.json";

	cppcms::json::value jJsonReadPathKey;
	std::ifstream ifFile(strPathAuthenticateApi.c_str());
	if (!jJsonReadPathKey.load(ifFile, true))
	{
		VTLOG2(vtlog::DEBUG, "Error in load file: %s", strPathAuthenticateApi.c_str());
	}
	else
	{
		try
		{
			SetAuthenApiConfig(jJsonReadPathKey);
			SetAuthenPubKey(Utils::ParseKeyFromPem(jJsonReadPathKey.get<std::string>("rsa_pub_key")));
			SetAuthenPubKeyVNPT(Utils::ParseKeyFromPem(jJsonReadPathKey.get<std::string>("rsa_pub_key_vnpt")));
		}
		catch(...)
		{
			VTLOG(vtlog::ERROR, "can not parser");
		}
	}
	ifFile.close();

	cppcms::json::value root;
	string path = "config/session.json";
	std::ifstream file(path.c_str());
	if (!root.load(file, true))
	{
		VTLOG2(vtlog::ERROR, "Error in load file: %s", path.c_str());
	}
	else
	{
		try
		{
			SetTimeExp(root.get<uint64_t>("session_exp_time"));
		}
		catch(...)
		{
			VTLOG(vtlog::ERROR, "can not parser");
		}
	}
	file.close();

	cppcms::json::value jReadRemoveContact;
	string strPathRemoveContactApi = "config/remove_all_contact_api.json";
	std::ifstream ifFileRmContact(strPathRemoveContactApi.c_str());
	// if (!jReadRemoveContact.load(file, true))
	if (Utils::LoadJsonFromFile(strPathRemoveContactApi, jReadRemoveContact) != 0)
	{
		VTLOG2(vtlog::ERROR, "Error in load file: %s", strPathRemoveContactApi.c_str());
	}
	else
	{
		try
		{
			SetSwApiHttpRemoveAllContact(jReadRemoveContact.get<int>("Switch_Api_Remove_All_Contact"));
		}
		catch(...)
		{
			VTLOG(vtlog::ERROR, "can not parser");
		}
	}
	ifFileRmContact.close();
	// Loading database config
	if (Utils::LoadJsonFromFile(strConfigFilePath, jConfig) != 0)
	{
		VTLOG2(vtlog::ERROR, "Error in load file: %s", strConfigFilePath.c_str());
	}
	else
	{
		for (auto const &jItem : jConfig.object())
		{
			try
			{
				std::unordered_map<std::string, std::string> hmConfig;
				for (auto const &jObject : jItem.second.array())
				{
					for (auto const &jAttribute : jObject.object())
					{
						hmConfig[jAttribute.first.str()] = jAttribute.second.str();
					}
				}
				m_hmDatabaseConfig[jItem.first] = hmConfig;
			}
			catch (...)
			{
				VTLOG2(vtlog::ERROR, "[ServerConfig] Cannot parse json: %s", strConfigFilePath.c_str());
			}
		}
	}

	// Loading app version config
	if (Utils::LoadJsonFromFile(strAppVersionValidationConfig, jConfig) != 0)
	{
		VTLOG2(vtlog::ERROR, "Error in load file: %s", strAppVersionValidationConfig.c_str());
		m_iAppVersionStatus = 0;
	}
	else
	{
		try
		{
			cppcms::json::array jArray = jConfig.get<cppcms::json::array>("min_version");
			// Get enable / disable check app version feature
			m_iAppVersionStatus = jConfig.get<int32_t>("enable");
			
			// Get min version
			for (auto const &jItem : jArray)
			{
				for (auto const &jPair : jItem.object())
				{
					std::vector<std::string> vTmp;
					int32_t iResult = Utils::VerifyVersion(jPair.second.str(), vTmp);
					if (iResult == 1 || iResult == 3)
					{
						VTLOG2(vtlog::ERROR, "[Login] Config app version min format not correct: %s", jPair.second.str().c_str());
						continue;
					}
					else if (iResult == 2)
					{
						VTLOG2(vtlog::ERROR, "[Login] App version min unsupported: %s", jPair.second.str().c_str());
						continue;
					}
					m_hmAppVersionMin[jPair.first.str()] = jPair.second.str();
				}
			}

			jArray = jConfig.get<cppcms::json::array>("max_version");
			// Get max version
			for (auto const &jItem : jArray)
			{
				for (auto const &jPair : jItem.object())
				{
					std::vector<std::string> vTmp;
					if (!jPair.second.str().empty())
					{
						int32_t iResult = Utils::VerifyVersion(jPair.second.str(), vTmp);
						if (iResult == 1 || iResult == 3)
						{
							VTLOG2(vtlog::ERROR, "[Login] Config app version max format not correct: %s", jPair.second.str().c_str());
							continue;
						}
						else if (iResult == 2)
						{
							VTLOG2(vtlog::ERROR, "[Login] App version max unsupported: %s", jPair.second.str().c_str());
							continue;
						}
					}
					m_hmAppVersionMax[jPair.first.str()] = jPair.second.str();
				}
			}

			// Get whitelist version
			jArray = jConfig.get<cppcms::json::array>("whitelist_version");
			for (auto const &jItem : jArray)
			{
				m_setAppVersionWhiteList.insert(jItem.str());
			}

			// Get blacklist version
			jArray = jConfig.get<cppcms::json::array>("blacklist_version");
			for (auto const &jItem : jArray)
			{
				m_setAppVersionBlackList.insert(jItem.str());
			}

			// Get new version
            jArray = jConfig.get<cppcms::json::array>("new_version");
			for (auto const &jItem : jArray)
			{
				for (auto const &jPair : jItem.object())
				{
					std::vector<std::string> vTmp;
					if (!jPair.second.str().empty())
					{
						int32_t iResult = Utils::VerifyVersion(jPair.second.str(), vTmp);
						if (iResult == 1 || iResult == 3)
						{
							VTLOG2(vtlog::ERROR, "[Login] Config app version new format not correct: %s", jPair.second.str().c_str());
							continue;
						}
						else if (iResult == 2)
						{
							VTLOG2(vtlog::ERROR, "[Login] App version new unsupported: %s", jPair.second.str().c_str());
							continue;
						}
					}
					m_hmAppVersionNew[jPair.first.str()] = jPair.second.str();
				}
			}
		}
		catch (...)
		{
			VTLOG2(vtlog::ERROR, "[ServerConfig] Cannot parse json: %s", strAppVersionValidationConfig.c_str());
		}
	}

    // Loading json sticker config
	if (Utils::LoadJsonFromFile(strStickerConfigFile, m_jStickerSetting) != 0)
	{
		VTLOG2(vtlog::ERROR, "[Server] Error in load file: %s", strStickerConfigFile.c_str());
	}
}

ServerConfig::~ServerConfig()
{
}

std::string ServerConfig::host() const
{
	return _settings["core"]["host"].str();
}

std::string ServerConfig::bind_host() const
{
    return _settings["core"]["bind_host"].str();
}

int ServerConfig::port_server() const
{
    return _settings["core"]["port_server"].number();
}
int ServerConfig::port_client() const
{
    return _settings["core"]["port_client"].number();
}

bool ServerConfig::init_fake_db() const
{
	return _settings["settings"]["init_fake_db"].boolean();
}
bool ServerConfig::run_load_test() const
{
    return _settings["settings"]["run_load_test"].boolean();
}

bool ServerConfig::show_review_ios() const
{
	return _settings["settings"]["show_review_ios"].boolean();
}
bool ServerConfig::show_review_android() const
{
	return _settings["settings"]["show_review_android"].boolean();
}
bool ServerConfig::production_mode() const
{
	return _settings["settings"]["production_mode"].boolean();
}

int ServerConfig::queue_size() const
{
	return _settings["core"]["queue_size"].number();
}

int ServerConfig::worker_count() const
{
    return _settings["core"]["worker_count"].number();
}

int ServerConfig::media_queue_size() const
{
	return _settings["core"]["media_queue_size"].number();
}

int ServerConfig::media_worker_count() const
{
	return _settings["core"]["media_worker_count"].number();
}

int ServerConfig::push_queue_size() const
{
    return _settings["core"]["push_queue_size"].number();
}

int ServerConfig::push_worker_count() const
{
	return _settings["core"]["push_worker_count"].number();
}

std::string ServerConfig::udp_host() const
{
	return _settings["core"]["udp_host"].str();
}

int ServerConfig::udp_port() const
{
	return _settings["core"]["udp_port"].number();
}

std::string ServerConfig::swift_container() const
{
	return _settings["settings"]["swift_container"].str();
}

std::string ServerConfig::swift_host() const
{
	return _settings["settings"]["swift_host"].str();
}

std::string ServerConfig::swift_client() const
{
	return _settings["settings"]["swift_client"].str();
}

std::string ServerConfig::swift_username_admin() const
{
	return _settings["settings"]["swift_username_admin"].str();
}
std::string ServerConfig::swift_password_admin() const
{
	return _settings["settings"]["swift_password_admin"].str();
}
std::string ServerConfig::swift_tenantname_admin() const
{
	return _settings["settings"]["swift_tenantname_admin"].str();
}
std::string ServerConfig::swift_username_client() const
{
	return _settings["settings"]["swift_username_client"].str();
}
std::string ServerConfig::swift_password_client() const
{
	return _settings["settings"]["swift_password_client"].str();
}
std::string ServerConfig::swift_tenantname_client() const
{
	return _settings["settings"]["swift_tenantname_client"].str();
}
std::string ServerConfig::keystone_auth_url() const
{
	return _settings["settings"]["keystone_auth_url"].str();
}
int ServerConfig::qrtoken_expired() const
{
    return _settings["settings"]["qrtoken_expired"].number();
}

const cppcms::json::array ServerConfig::GetDefaultSticker() const
{    
    // return _settings["settings"]["sticker_default_id"];
    cppcms::json::array jArrayDefaultSticker;
    try
    {
        jArrayDefaultSticker = m_jStickerSetting.get<cppcms::json::array>("default_sticker");
    }
    catch (...)
    {
        // DLOG(INTO) << "[ServerConfig] Cannot parse json \"default"\" sticker";
    }
    return jArrayDefaultSticker;
}
/*setting for mynumber*/
std::string ServerConfig::mynumber_url() const
{
	return _settings["settings"]["mynumber_url"].str();
}

// Setting for node id
std::string ServerConfig::node_id() const
{
	return _settings["node_setting"]["node_id"].str();
}

// Setting for node channel
std::string ServerConfig::node_channel() const
{
	return _settings["node_setting"]["node_channel"].str();
}

// Setting for channel master
std::string ServerConfig::channel_master() const
{
	return _settings["node_setting"]["channel_master"].str();
}

// Setting for max_event
int ServerConfig::epoll_max_event() const
{
	return _settings["settings"]["epoll_max_event"].number();
}

void ServerConfig::SetAuthenApiConfig(const cppcms::json::value &jConfig) 
{
	m_settingAuthenKey = jConfig;
}

void ServerConfig::SetAuthenPubKey(const std::string &strKey)
{
	m_strAuthenPubKey = strKey;
}

void ServerConfig::SetAuthenPubKeyVNPT(const std::string &strKey)
{
	m_strAuthenPubKeyVNPT = strKey;
}

std::string ServerConfig::GetAuthenPubKey()  const
{
	return m_strAuthenPubKey;
}

std::string ServerConfig::GetAuthenPubKeyVNPT()  const
{
	return m_strAuthenPubKeyVNPT;
}

uint64_t ServerConfig::GetTimeExp()	const
{
	return m_uSessionExpTime;
}

void ServerConfig::SetTimeExp(const uint64_t &uTimeExp)  
{
	m_uSessionExpTime = uTimeExp;
}

const std::unordered_map<std::string, std::unordered_map<std::string, std::string> >& ServerConfig::GetDatabaseConfig() const
{
	return m_hmDatabaseConfig;
}

const int32_t &ServerConfig::GetAppVersionStatus() const
{
	return m_iAppVersionStatus;
}

const std::set<std::string> &ServerConfig::GetAppVersionBlacklist() const
{
	return m_setAppVersionBlackList;
}

const std::set<std::string> &ServerConfig::GetAppVersionWhitelist() const
{
	return m_setAppVersionWhiteList;
}

const std::unordered_map<std::string, std::string> &ServerConfig::GetAppVersionMin() const
{
	return m_hmAppVersionMin;
}

const std::unordered_map<std::string, std::string> &ServerConfig::GetAppVersionMax() const
{
	return m_hmAppVersionMax;
}

const std::unordered_map<std::string, std::string> &ServerConfig::GetAppVersionNew() const
{
	return m_hmAppVersionNew;
}

int ServerConfig::GetSwApiHttpRemoveAllContact()	const
{
	return m_iSwApiHttpRemoveAllContact;
}

void ServerConfig::SetSwApiHttpRemoveAllContact(const int &iSwitchRemove)  
{
	m_iSwApiHttpRemoveAllContact = iSwitchRemove;
}

std::string ServerConfig::GetStickerVersion() const
{
    std::string strStickerVersion = "";
    try
    {
        strStickerVersion = m_jStickerSetting.get<std::string>("version");
    }
    catch(...)
    {
        // Log sticker version not found
    }
    return strStickerVersion;
}

const cppcms::json::array ServerConfig::GetStickerData() const
{
    cppcms::json::array jStickerData;
    try
    {
        jStickerData = m_jStickerSetting.get<cppcms::json::array>("sticker_data");
    }
    catch(...)
    {
        // Log sticker data not found
    }
    
    return jStickerData;
}