/*
 * Table.h
 *
 *  Created on: Jun 12, 2016
 *      Author: avs
 */

#ifndef TABLE_HPP_
#define TABLE_HPP_

#include <map>
#include "Common.h"

namespace Core {

class Table {
public:
	explicit
	Table();
	virtual
	~Table();

//	virtual void add (std::string);
protected:
	std::map<std::string, std::string> table;
	std::map<std::string, double> values;
};

} /* namespace Core */

#endif /* TABLE_HPP_ */
