#include "ErrorsHandler.h"

using namespace std;


ErrorsHandler& ErrorsHandler::GetInstance()
{
	static ErrorsHandler instance;
	return instance;
}

void ErrorsHandler::Add(OperationType operation, std::String errorMessage, std::String elementPath, std::String optionalCopyPath)
{
	ErrorsElement error = ErrorsElement(operation, errorMessage, elementPath, optionalCopyPath);
	ErrorsContainer.push(error);

	if (VerboseLevel >= 1){
		error.Print();
	}
}


size_t ErrorsHandler::GetErrorCount()
{
	return ErrorsContainer.size();
}

void ErrorsHandler::Recap()
{
	if (ErrorsContainer.size() > 0)
	{
		wcout << endl << endl << ErrorsContainer.size() << L" errors encountered" << endl << flush;
	}
	else
	{
		wcout << endl << endl << L"No errors." << endl << flush;
	}
}

int ErrorsHandler::FixAllErrors()
{
	size_t countBeforeFix = ErrorsContainer.size();
	for (size_t i = 0; i < countBeforeFix; i++)
	{
		ErrorsElement error = ErrorsContainer.front();
		error.Fix();
		ErrorsContainer.pop();
	}
	
	wcout << endl << endl << countBeforeFix - ErrorsContainer.size() << L" errors fixed, " << ErrorsContainer.size() << L" remaining" << endl << flush;

	return (int) ErrorsContainer.size();
}