/*
 * TaskQueue.cpp
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#include "Engine.h"
#include "Server.h"
#include <glog/logging.h>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "logger/LogManager.h"
#include <boost/chrono/duration.hpp>

namespace core
{

Engine::Engine(Server* server) : Component(server, ENGINE_COMP)
{
	end = true;
	this->size = _server->settings().queue_size();
	services.set_deleted_key(-1);
	services.set_empty_key(-2);
    // m_iCurrentQueueSize = 0;
}

void Engine::initialize()
{
	data = (task_ptr*) malloc(size * sizeof(task_ptr));
	first = data;
	last = first;
	next = last + 1;
	end_of_data = data + size;

	this->worker_count = _server->settings().worker_count();

	for (int i = 0; i < worker_count; i++)
	{
		auto tmp = boost::make_shared<Worker>(i, this);
		workers.push_back(tmp);
	}
}

Engine::~Engine()
{
	if (data) free(data);
}

void Engine::enqueue(task_ptr task)
{
	boost::mutex::scoped_lock wlock(write_mutex);
	while (next == first) //full
	{
        full_cond.wait(wlock);
		if (end) return;
	}

	*last = task;
	last = next;
	next++;
	if (next == end_of_data) next = data;
    VTLOG2(vtlog::DEBUG, "[Core] Engine enqueue notify one task: %d", task->type());
	empty_cond.notify_one();
    // m_iCurrentQueueSize++;
    // VTLOG2(vtlog::DEBUG, "[Core] Current queue size %d", m_iCurrentQueueSize);
}

void Engine::start()
{
	end = false;
	for (auto& w : workers)
	{
		w->start();
	}
}

void Engine::stop()
{
	end = true;
	empty_cond.notify_all();
	full_cond.notify_all();
	for (auto& w : workers)
	{
		w->join();
	}
}

task_ptr Engine::dequeue()
{
	bool full = false;
	task_ptr ret = NULL;

	boost::mutex::scoped_lock rlock(read_mutex);
	while (last == first) //empty
	{
		empty_cond.wait(rlock); //wait until queue is not empty
		if (end) return NULL;
	}

	if (next == first) full = true;
	ret = *first;
	first++;
	if (first == end_of_data) first = data;
	if (full) full_cond.notify_one();
    VTLOG2(vtlog::DEBUG, "[Core] Engine dequeue task: %d", ret->type());
    // if (m_iCurrentQueueSize > 0)
	// {
		// m_iCurrentQueueSize--;
    	// VTLOG2(vtlog::DEBUG, "[Core] Current queue size %d", m_iCurrentQueueSize);
	// }

	return ret;
}

bool Engine::empty()
{
	return (last == first);
}

bool Engine::running()
{
	return (!end);
}

void Engine::register_service(service_ptr service)
{
	services[service->type()] = service;
}

void Engine::process_task(int &iWokerID)
{
	auto task = dequeue();
	if (task == nullptr)
	{
		VTLOG(vtlog::ERROR, "Task is null");
		return;
	}
	auto it = services.find(task->type());
	if (it != services.end())
	{
		auto context = task->context();
		context->m_iWokerID = iWokerID;
		if (it->second->process(context))
		{
			delete task;
			task = nullptr;
		}
	}
	else
	{
		VTLOG2(vtlog::DEBUG, "Strange request: %d", task->type());
		delete task;
		task = nullptr;
	}
}

// int Engine::GetQueueSize()
// {
// 	return m_iCurrentQueueSize;
// }
}  // namespace core
