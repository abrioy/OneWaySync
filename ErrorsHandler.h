#ifndef ERRORSHANDLER_H_
#define ERRORSHANDLER_H_

#include <string>
#include <iostream>
#include <queue>
#include <iterator>


#include "OneWaySync.h"
#include "ErrorsElement.h"

class ErrorsHandler
{
private:
	ErrorsHandler() {}
	ErrorsHandler(ErrorsHandler const&);  // Don't Implement.
	void operator=(ErrorsHandler const&); // Don't implement


	std::queue<ErrorsElement> ErrorsContainer;

public:
	static ErrorsHandler& GetInstance();
	int VerboseLevel = 1;

	// Add a new error to the list, strings must include the file name and optional strings can be empty
	void Add(OperationType operation, std::String errorMessage, std::String elementPath, std::String optionalCopyPath);

	size_t GetErrorCount();
	void Recap();
	// Returns 0 if there is no errors left
	int FixAllErrors();
};



#endif
