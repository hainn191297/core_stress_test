/*
 * TcpService.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef TCPSERVICE_H_
#define TCPSERVICE_H_

#include <glog/logging.h>
#include "core/Service.h"
#include "TcpContext.h"
#include "Connection.h"
#include "logger/LogManager.h"
#include "Utils.h"
#include <sstream>

#define TCP_SERVICE_BEGIN(name) \
class name##Service: public tcp::TcpService<name> \
{\
public:\
	name##Service(Server* server) : TcpService(comm::name::kIDFieldNumber, server)\
	{\
	}\
	virtual ~name##Service()\
	{\
	}\
	int execute(tcp::connection_ptr connection,comm::name::Request& request, comm::name::Reply& reply, db::VTDatabase *m_vtDatabase, int iWorkNumber);

#define TCP_SERVICE_END };

#define SERVICE_ROUTINE(name, routine) \
public:\
	int routine(session::Session* session, comm::name::Request& request, comm::name::Reply& reply);

#define SERVICE_ROUTINE_DEF(name, routine) \
		int name##Service::routine(session::Session* session, comm::name::Request& request, comm::name::Reply& reply)

#define SERVICE_PARAM session_, request, reply
#define MAX_LIST_CALL_COUNT		10000000
#define MAX_LIST_MESSAGE_COUNT	10000000
#define MAX_LIST_MESSAGE_GET	20
#ifndef CALL_INDEX_VALUE_ALL_CALL
#define CALL_INDEX_VALUE_ALL_CALL "ALL_CALL"
#endif

#define TCP_SERVICE(name) \
class name##Service: public tcp::TcpService<name> \
{\
public:\
	name##Service(Server* server) : TcpService(comm::name::kIDFieldNumber, server)\
	{\
	}\
	virtual ~name##Service()\
	{\
	}\
	int execute(tcp::connection_ptr connection,comm::name::Request& request, comm::name::Reply& reply, db::VTDatabase *m_vtDatabase, std::string strWorkerID) override;\
};

#define TCP_EXECUTE(name) int name##Service::execute(tcp::connection_ptr connection, comm::name::Request& request, comm::name::Reply& reply, db::VTDatabase *m_vtDatabase, std::string strWorkerID)

namespace tcp
{

template<class S>
class TcpService: public core::Service
{
protected:
	// db::Database* db;
	session::UserManager* user_manager;
	node::PresenceUserManager* presence_user_mng;
    LogManager* logger;
	// db::VTDatabase *m_vtDatabase;
public:
	TcpService(int type, Server* server) :
			core::Service(type, server)
	{
		// db = (db::Database*) server->component(DATABASE_COMP).get();
		user_manager = (session::UserManager*) server->component(USER_COMP).get();
		presence_user_mng = (node::PresenceUserManager*) server->component(PRESENCE_COMP).get();
        logger = (LogManager*) server->component(LOG_MANGER_COMP).get();
		// m_vtDatabase = (db::VTDatabase*) server->component(VT_DATABASE_COMP + to_string(server->settings().worker_count())).get();
	}

	virtual ~TcpService()
	{

	}

	virtual bool process(core::context_ptr context) final
	{
		typename S::Request request;
		typename S::Reply reply;
		comm::Reply r;
        //uint64_t start_time = Utils::time_t();

		auto tc = dynamic_cast<TcpContext*>(context.get());
		if (tc == nullptr) return true;
		auto con = tc->get_connection();
		auto msg = tc->get_message();
		std::string strWorkerID = Utils::NumberToString(tc->m_iWokerID);
		
		VTLOG2(vtlog::DEBUG, "Process connection: %d", con->get_socket());
		db::VTDatabase* pDatabase = (db::VTDatabase*) _server->component(VT_DATABASE_COMP + strWorkerID).get();

		if (!request.ParseFromArray(msg->get_content_data(), msg->get_content_size())) r.set_type(comm::ResultType::REQUEST_INVALID);
		else
		{
			try
			{
				uint64_t uTimeEnd = 0;
				int ret = execute(con, request, reply, pDatabase, strWorkerID);
				uTimeEnd = Utils::time_t();
				r.set_type(ret);
				r.set_time(uTimeEnd);
				if ((r.type()==0 || r.type() == comm::DATA_ERROR) && reply.IsInitialized()) r.MutableExtension(S::ID)->CopyFrom(reply);
				else VTLOG(vtlog::DEBUG, "Not Initialize");
			}
			catch (std::exception const &e)
			{
				VTLOG2(vtlog::ERROR, "Tcpservice err: %s", e.what());
				return true;
			}
			catch (...)
			{
				VTLOG(vtlog::INFO, "Problem in service implementation");
				return true;
			}
		}

		// MyVNPT # SONTV # 28-05-20 # Move attach presence from 
		// attach presence
		if (r.type() == 0) attach_present(con, r);

		// send
		auto rep = Message::encode(r.SerializeAsString(), 0, msg->id);
		con->send_message(rep);
        // calculate time run this service
        /*if (type() == comm::Login::kIDFieldNumber || type() == comm::ListChats::kIDFieldNumber ||
                type() == comm::ListMessage::kIDFieldNumber || type() == comm::ListContacts::kIDFieldNumber ||
                type() == comm::ImportContacts::kIDFieldNumber)
        {
            uint64_t end_time = Utils::time_t();
            if (end_time > start_time)
            {
                uint64_t duration = end_time - start_time;
                // logger->log_time_run_service(type(), duration);
            }
        }*/
		return true;
	}

	void attach_present(connection_ptr connection, comm::Reply& rep)
	{
		// uint64_t current_time = Utils::time_t();
		// if (connection->data==nullptr) return ;
		// session::Session* session = static_cast<session::Session*>(connection->data);
		// if (session == nullptr) return;
		// if (type() == comm::Logout::kIDFieldNumber) return;//if logout then not attach present
		// /*Check to append present: after 30s then check or after login*/
		// if ((current_time - session->last_sent_presence()) > 30 * 1000 || type() == comm::Login::kIDFieldNumber
		// 		|| type() == comm::GetPresentContact::kIDFieldNumber)
		// {
			// boost::shared_ptr<session::User> user = session->user();
			// if (user)
			// {
				// const std::list<string>& friends = user->friends();
				// for (std::list<string>::const_iterator iter = friends.begin(); iter != friends.end(); iter++)
				// {
				// 	auto friend_user = user_manager->get(*iter);
				// 	if (friend_user != nullptr && friend_user->last_active() != 0)
				// 	{
						// uint64_t last_active = friend_user->last_active();
						// uint64_t time_now = Utils::time_t();
						// uint64_t diff_time = time_now - last_active;
						// comm::Presence *presence = rep.add_presences();
						// presence->set_user_id(*iter);
						// presence->set_active_time(diff_time);
					// }
				// }
			// }

			// if(session) session->set_last_sent_presence(current_time);
		// }
	}
	virtual int execute(connection_ptr connection, typename S::Request& request, typename S::Reply& reply, db::VTDatabase *m_vtDatabase, std::string strWorkerID) = 0;

	/*static bool isBlocked(const uint64_t& index_type, const std::string& user1, const std::string& user2, db::Database* db, std::string& key_blocked)
	{
		bool b_check = false;
		db::index_iter_ptr it_block = db->index_last(index_type, user1);
		while (it_block->prev())
		{
			string eid = it_block->get_key();
			if (eid.find(user1) == string::npos) break;

			model::Entity contact_entity;
			if (db->index_get(index_type, eid, contact_entity) == db::OK )
			{
				if (contact_entity.id() == user2)
				{
					b_check = true;
					key_blocked = eid;
					break;
				}
			}
		}
		return b_check;
	}*/

	static bool isOwnerMessage(vt::Message& msg, std::string& uid)
	{
		// for (int index = 0; index < msg.uids_size(); index++)
		// {
		// 	if (msg.uids(index) == uid)
		// 	{
		// 		return true;
		// 	}
		// }
		// return false;
		// return (std::find(msg.uids().begin(), msg.uids().end(), uid) != msg.uids().end());
		return true;
	}

	// static std::string getAliasName(const std::string& user_id, const std::string& contact_id, db::Database* db)
	// {
	// 	if (user_id == contact_id) return "";
	// 	model::Relation rel_entity;
	// 	/*find alias name of 2 users*/
	// 	if (db->rel_get(user_id, vt::RelationType::RELATE_TO, contact_id, rel_entity) == db::OK)
	// 	{
	// 		vt::RelateTo rel_user_contact = rel_entity.GetExtension(vt::RelateTo::RELATE_TO);
	// 		if (rel_user_contact.has_alias()) return rel_user_contact.alias();
	// 	}
	// 	return "";
	// }
};

}  // namespace tcp
#endif /* TCPSERVICE_H_ */
