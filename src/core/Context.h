/*
 * Context.h
 *
 *  Created on: May 22, 2015
 *      Author: nguyenhongsan
 */

#ifndef CONTEXT_H_
#define CONTEXT_H_

#include <boost/shared_ptr.hpp>

namespace core {

class Context;
typedef boost::shared_ptr<Context> context_ptr;

class Context
{
public:
	Context():m_iWokerID(-1)
	{
	}
	virtual ~Context()
	{
	}

	int m_iWokerID;
};

}  // namespace core

#endif /* CONTEXT_H_ */
