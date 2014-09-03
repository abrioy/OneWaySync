#include "Filter.h"

using namespace std;



void Filter::AddCondition(String conditionString)
{
	wregex newCondition = wregex(conditionString);
	ConditionsList.push_back(newCondition);
}


bool Filter::TestString(std::String inputString)
{
	if (!ConditionsList.empty())
	{
		// Iterate on the regex list to find out if the string match any of them
		for (auto it = ConditionsList.begin(); it != ConditionsList.end(); it++)
		{
			bool isConditionMatched = regex_match(inputString, *it, regex_constants::match_default);
			if (isConditionMatched)
				return false;
		}
	}
	return true;
}


