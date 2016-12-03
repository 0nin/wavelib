/*
 * CfgTable.h
 *
 *  Created on: Jun 12, 2016
 *      Author: avs
 */

#ifndef CFGTABLE_HPP_
#define CFGTABLE_HPP_

#include "Common.h"
#include "Table.hpp"

namespace Core {

class CfgTable {
public:
	CfgTable(void);
	virtual
	~CfgTable(void);
	static CfgTable*
	getSingletonPtr(void);
};

} /* namespace Core */

#endif /* CFGTABLE_HPP_ */
