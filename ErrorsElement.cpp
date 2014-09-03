#include "ErrorsElement.h"
#include "IOfunction.h"

using namespace std;


ErrorsElement::ErrorsElement(OperationType operation, std::String errorMessage, std::String elementPath, std::String optionalCopyPath)
{
	Operation = operation;
	ErrorMessage = errorMessage;
	ElementPath = elementPath;
	OptionalCopyPath = optionalCopyPath;
}

void ErrorsElement::Print()
{
	//wcerr.exceptions(iostream::failbit | iostream::badbit);

	wcerr << endl << endl << L"Error - ";
	switch (Operation)
	{
	case OperationType::FileCopy:
		wcerr << L"File copy: " << endl
			<< L"   from: " << ElementPath << endl
			<< L"     to: " << OptionalCopyPath;
		break;

	case OperationType::FileDelete:
		wcerr << L"File delete: " << endl
			<< ElementPath;
		break;

	case OperationType::FolderCreate:
		wcerr << L"Directory creation: " << endl
			<< OptionalCopyPath;
		break;

	case OperationType::FolderRemove:
		wcerr << L"Directory delete: " << endl
			<< ElementPath;
		break;
	}
	wcerr << endl << ErrorMessage;
}

void ErrorsElement::Fix()
{
	switch (Operation)
	{
	case OperationType::FileCopy:
		IOfunction::CopyFileByPath(ElementPath, OptionalCopyPath);
		break;

	case OperationType::FileDelete:
		IOfunction::DeleteFileByPath(ElementPath);
		break;

	case OperationType::FolderCreate:
		IOfunction::CreateDirectoryByPath(ElementPath, OptionalCopyPath);
		break;

	case OperationType::FolderRemove:
		IOfunction::DeleteFolderByPath(ElementPath);
		break;		
	}
}