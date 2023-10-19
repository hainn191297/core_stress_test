/*
 * Worker.cpp
 *
 *  Created on: Jan 16, 2015
 *      Author: hongsan
 */

#include "Worker.h"
#include "Engine.h"
#include <glog/logging.h>
#include "logger/LogManager.h"

namespace core
{

Worker::Worker(int id, Engine* engine): _id(id), _engine(engine)
{
}

Worker::~Worker()
{
}

void Worker::run()
{
	VTLOG2(vtlog::DEBUG, "Worker: %d has started", _id);
	while (_engine->running())
	{
		_engine->process_task(_id);
		VTLOG2(vtlog::DEBUG, "Worker: %d", _id);

	}
	VTLOG2(vtlog::DEBUG, "Worker: %s is stopped", _id);
}

}
  // namespace core
