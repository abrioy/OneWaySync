#ifndef FILTER_H_
#define FILTER_H_

#include <string>
#include <regex>
#include <list>
#include <iterator>

#include "OneWaySync.h"

class Filter
{
private:
	std::list<std::wregex> ConditionsList;

public:
	// Returns false if the string is to be filtered out
	bool TestString(const std::String inputString);

	void AddCondition(const std::String conditionString);

};


#endif