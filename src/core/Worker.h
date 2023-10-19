/*
 * Worker.h
 *
 *  Created on: Jan 9, 2015
 *      Author: hongsan
 */

#ifndef WORKER_H_
#define WORKER_H_

#include "commons/ThreadBase.h"

namespace core
{

class Engine;

class Worker: public ThreadBase
{
private:
	int _id;
	Engine* _engine;
public:
	Worker(int id, Engine* engine);
	virtual ~Worker();
	void run();
};

typedef boost::shared_ptr<Worker> worker_ptr;

}  // namespace core

#endif /* WORKER_H_ */
