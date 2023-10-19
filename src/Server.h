/*
 * Server.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <boost/shared_ptr.hpp>
#include <google/dense_hash_map>
#include <cppcms/json.h>
#include <cppcms/service.h>
#include <string>
#include <boost/thread/mutex.hpp>
#include "logger/LogManager.h"
#include <unordered_map>
#include <set>

class Component;
typedef boost::shared_ptr<Component> component_ptr;

class ServerConfig
{
public:
	explicit ServerConfig(const cppcms::json::value &s);
	virtual ~ServerConfig();

	// core
	std::string host() const;
    std::string bind_host() const;
    int port_server() const;
    int port_client() const;
	int queue_size() const;
	int worker_count() const;

	int media_queue_size() const;
	int media_worker_count() const;

	int push_queue_size() const;
	int push_worker_count() const;

	std::string udp_host() const;
	int udp_port() const;

	// settings
	bool show_review_ios() const;
	bool show_review_android() const;
	bool init_fake_db() const;
    bool run_load_test() const;
	bool production_mode() const;
	std::string swift_container() const;
	std::string swift_username_admin() const;
	std::string swift_password_admin() const;
	std::string swift_tenantname_admin() const;
	std::string swift_username_client() const;
	std::string swift_password_client() const;
	std::string swift_tenantname_client() const;
	std::string swift_host() const;
	std::string swift_client() const;
	std::string keystone_auth_url() const;
    int qrtoken_expired() const;
    const cppcms::json::array GetDefaultSticker() const;
    std::string GetStickerVersion() const;
    const cppcms::json::array GetStickerData() const;
	/*setting for mynumber*/
	std::string mynumber_url() const;
	// Setting host of redis client
	// std::string db_host() const;
	// Setting port of redis client
	// int db_port() const;
	// Setting for node
	std::string node_channel() const;
	std::string node_id() const;
	std::string channel_master() const;
	// Setting for epoll_max_event
	int epoll_max_event() const;
	void SetAuthenApiConfig(const cppcms::json::value &jConfig);
	std::string GetAuthenPubKey() const;
	std::string GetAuthenPubKeyVNPT() const;
	void SetAuthenPubKey(const std::string &strKey);
	void SetAuthenPubKeyVNPT(const std::string &strKey);
	uint64_t GetTimeExp() const;
	void SetTimeExp(const uint64_t &uTimeExp);
	const std::unordered_map<std::string, std::unordered_map<std::string, std::string> >& GetDatabaseConfig() const;
	const int32_t &GetAppVersionStatus() const;
	const std::set<std::string> &GetAppVersionBlacklist() const;
	const std::set<std::string> &GetAppVersionWhitelist() const;
	const std::unordered_map<std::string, std::string> &GetAppVersionMin() const;
	const std::unordered_map<std::string, std::string> &GetAppVersionMax() const;
    const std::unordered_map<std::string, std::string> &GetAppVersionNew() const;
	int GetSwApiHttpRemoveAllContact() const;
	void SetSwApiHttpRemoveAllContact(const int &iSwitchRemove);
	
private:
	cppcms::json::value const &_settings;
	cppcms::json::value m_settingAuthenKey;
    cppcms::json::value m_jStickerSetting;
	ServerConfig(const ServerConfig&);
	ServerConfig& operator=(const ServerConfig&);
	std::string m_strAuthenPubKey;
	std::string m_strAuthenPubKeyVNPT;
	uint64_t m_uSessionExpTime;
	int m_iSwApiHttpRemoveAllContact;

	// Map to store database config
	// Key : string - name of database (or config name)
	// Value : Map attribute config with sub-keys, sub-values
	// sub-key : attribute name (ex: user, pass,...)
	// sub-value : attribute value (ex: name of user, value of pass,...)
	std::unordered_map<std::string, std::unordered_map<std::string, std::string> > m_hmDatabaseConfig;
	std::unordered_map<std::string, std::string> m_hmAppVersionMin;	// Min version server support
	std::unordered_map<std::string, std::string> m_hmAppVersionMax;	// Max version server support
    std::unordered_map<std::string, std::string> m_hmAppVersionNew;	// New version server support new API
	std::set<std::string> m_setAppVersionWhiteList;	// Whitelist version
	std::set<std::string> m_setAppVersionBlackList;	// Blacklist version
	int32_t m_iAppVersionStatus; // 0 - OFF, 1 - ON
};

class Server
{
public:
	Server(cppcms::json::value const &s);
	virtual ~Server();

	void init();
	void start();
	void stop();

	void register_components(cppcms::service &service);
	
	std::string renew_swift_auth_token(bool is_admin, std::string& auth_token);
	std::string renew_swift_auth_token_ceph(bool is_admin, std::string& auth_token);
	std::string renew_swift_auth_token_openstack(bool is_admin, std::string& auth_token);

	component_ptr component(std::string id);
	const ServerConfig &settings();
	void set_swift_api_url(std::string swift_api_url);
	void set_swift_auth_token(std::string swift_auth_token);
	void set_swift_client_url(std::string swift_client_url);
	void set_swift_apps_url(std::string swift_apps_url);
	std::string swift_api_url() const;
	std::string swift_auth_token() const;
	std::string swift_client_url() const;
	std::string swift_apps_url() const;
private:
	void register_component(component_ptr component);
	google::dense_hash_map<std::string, component_ptr> _components;
	ServerConfig _config;
	std::string m_swift_api_url;
	std::string m_swift_auth_token;
	std::string m_swift_client_url;
	std::string m_swift_apps_url;
	boost::mutex _mutex;
};

#endif /* SERVER_H_ */
