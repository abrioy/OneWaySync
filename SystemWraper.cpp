#include "SystemWraper.h"

using namespace std;

String PrintLastError()
{
	DWORD dLastError = GetLastError();
	LPCTSTR strErrorMessage = NULL;

	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS |
		FORMAT_MESSAGE_ARGUMENT_ARRAY | FORMAT_MESSAGE_ALLOCATE_BUFFER,
		NULL,
		dLastError,
		0,
		(LPWSTR)&strErrorMessage,
		0,
		NULL);

	return strErrorMessage;
}


int SystemWraper::SysCreateDirectory(String optionalOriginalPath, String newPath)
{
	
	// Handling the copy of the security descriptor
	LPSECURITY_ATTRIBUTES securityAttributesPointer = NULL;
	SECURITY_ATTRIBUTES securityAttributes;

	if (!optionalOriginalPath.empty())
	{
		securityAttributes.nLength = sizeof(securityAttributes);
		securityAttributes.bInheritHandle = false;

		securityAttributesPointer = &securityAttributes;

		// retrieving the security attributes of the original folder
		if (GetNamedSecurityInfo(
				// In
				optionalOriginalPath.c_str(),	// Path
				SE_FILE_OBJECT,					// Means that we look for a file/directory
				ATTRIBUTE_SECURITY_INFORMATION, // http://msdn.microsoft.com/en-us/library/windows/desktop/aa379573%28v=vs.85%29.aspx
				// Out
				NULL,	// Owner sid
				NULL,	// Group sid
				NULL,	// DACL 
				NULL,	// SACL
				(PSECURITY_DESCRIPTOR*)&securityAttributes.lpSecurityDescriptor
			) == 0)
		{
			//failed to retrieve security attributes
			securityAttributesPointer = NULL;
		}

	}

	int isSuccess = 0;

	if (CreateDirectory(newPath.c_str(), securityAttributesPointer) == 0)
	{
		if (GetLastError() != ERROR_ALREADY_EXISTS)
		{
			ErrorsHandler::GetInstance().Add(FolderCreate, PrintLastError(), optionalOriginalPath, newPath);
			isSuccess = 1;
		}
	}
	else
	{
		if (ErrorsHandler::GetInstance().VerboseLevel >= 2)
			wcout << endl << L"NEW DIR   : " << newPath << endl;
	}



	// Free what windows has allocated for us
	if (securityAttributesPointer != NULL)
	{
		LocalFree(securityAttributes.lpSecurityDescriptor);
	}


	return isSuccess;
}

int SystemWraper::SysRemoveDirectory(String path)
{
	if (RemoveDirectory(path.c_str()) == 0)
	{
		ErrorsHandler::GetInstance().Add(FolderRemove, PrintLastError(), path, EMPTYSTRING);
		return 1;
	}
	else
	{
		if (ErrorsHandler::GetInstance().VerboseLevel >= 2)
			wcout << endl << L"DELETE DIR: " << path << endl;

		return 0;
	}	
}

int SystemWraper::SysCopyFile(String origin, String target)
{
	if (CopyFile(origin.c_str(), target.c_str(), false) == 0)
	{
		ErrorsHandler::GetInstance().Add(FileCopy, PrintLastError(), origin, target);
		return 1;
	}
	else
	{
		if (ErrorsHandler::GetInstance().VerboseLevel >= 2)
		{
			wcout << endl 
				<< L"COPY  From: " << origin << endl
				<< L"      To  : " << target << endl;
		}
		return 0;
	}
}

int SystemWraper::SysDeleteFile(String path)
{
	if (DeleteFile(path.c_str()) == 0)
	{
		ErrorsHandler::GetInstance().Add(FileDelete, PrintLastError(), path, EMPTYSTRING);
		return 1;
	}
	else
	{
		if (ErrorsHandler::GetInstance().VerboseLevel >= 2)
			wcout << endl << L"DELETE    : " << path << endl;

		return 0;
	}
}