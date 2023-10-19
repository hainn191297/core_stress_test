/*
 * Task.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef TASK_H_
#define TASK_H_

#include "Context.h"

namespace core {

class Task
{
public:
	Task(int type, context_ptr context): _type(type), _context(context)
	{
	}

	virtual ~Task()
	{
	}

	int type()
	{
		return _type;
	}

	context_ptr context()
	{
		return _context;
	}
private:
	int _type;
	context_ptr _context;
};

typedef Task* task_ptr;

}  // namespace core

#endif /* TASK_H_ */
