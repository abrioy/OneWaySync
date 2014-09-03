#ifndef ERRORSELEMENT_H_
#define ERRORSELEMENT_H_

#include <string>

#include "OneWaySync.h"


const enum OperationType
{
	FileCopy,
	FileDelete,
	FolderCreate,
	FolderRemove,
};


class ErrorsElement
{
private:
	OperationType Operation;
	std::String ErrorMessage;
	std::String ElementPath;
	std::String OptionalCopyPath;
public:
	ErrorsElement(OperationType operation, std::String errorMessage, std::String elementPath, std::String optionalCopyPath);

	void Print();
	void Fix();
};

#endif