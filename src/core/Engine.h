/*
 * TaskQueue.h
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#ifndef TASKQUEUE_H_
#define TASKQUEUE_H_

#define ENGINE_COMP	"ENGINE"

#include <boost/thread/mutex.hpp>
#include <boost/thread/condition.hpp>
#include <google/dense_hash_map>

#include "Worker.h"
#include "Task.h"
#include "Component.h"
#include "Service.h"

class Server;
namespace core
{

class Engine: public Component
{
private:
	task_ptr* data;
	task_ptr* first;
	task_ptr* last;
	task_ptr* next;
	task_ptr* end_of_data;
	int size;

	boost::mutex read_mutex;
	boost::mutex write_mutex;
	boost::condition empty_cond;
	boost::condition full_cond;
	bool end;

	std::vector<worker_ptr> workers;
	google::dense_hash_map<int, service_ptr> services;
	int worker_count;
   	// std::atomic_int m_iCurrentQueueSize;
public:
	Engine(Server* server);
	void initialize();
	virtual ~Engine();
	void enqueue(task_ptr task);
	task_ptr dequeue();
	bool empty();
	void start();
	void stop();
	bool running();
	void process_task(int &iWokerID);
	void register_service(service_ptr service);

	int GetQueueSize();
};

}  // namespace core

#endif /* ENGINE_H_ */
