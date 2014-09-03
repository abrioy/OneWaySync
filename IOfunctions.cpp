#include "IOfunction.h"

using namespace std;


int IOfunction::FolderMap(
	String folderPath,
	void* ptrToPassInFunction,
	void(*function)(String path, String fileName, unsigned long long lastModifiedDate, unsigned long long fileSize, bool isDirectory, void* ptr)
	)
{

	WIN32_FIND_DATA file_data;

	HANDLE Win_DirHandle = FindFirstFile(String(folderPath + L"\\*").c_str(), &file_data);
	if (Win_DirHandle == INVALID_HANDLE_VALUE)
		// Folder is empty
		return 1;

	if (file_data.cFileName[0] == '.')
		FindNextFile(Win_DirHandle, &file_data);
	if (file_data.cFileName[0] == '.' && file_data.cFileName[1] == '.')
	{
		if (FindNextFile(Win_DirHandle, &file_data) == 0)
		{
			// Folder is empty
			FindClose(Win_DirHandle);
			return 1;
		}
	}


	do{
		ULARGE_INTEGER convertDate;
		convertDate.LowPart = file_data.ftLastWriteTime.dwLowDateTime;
		convertDate.HighPart = file_data.ftLastWriteTime.dwHighDateTime;

		ULARGE_INTEGER convertSize;
		convertSize.LowPart = file_data.nFileSizeLow;
		convertSize.HighPart = file_data.nFileSizeHigh;
		
		(*function)(
			folderPath,
			String(file_data.cFileName),
			(unsigned long long)convertDate.QuadPart,
			(unsigned long long)convertSize.QuadPart,
			(file_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) != 0,
			ptrToPassInFunction
			);

	} while (FindNextFile(Win_DirHandle, &file_data) != 0);



	// Close the directory
	if (FindClose(Win_DirHandle) != 0)
	{
		return 0;
	}

	return 0;
}



void IOfunction::CreateDirectoryByPath(String originalPath, String destinationPath)
{
	SystemWraper::SysCreateDirectory(originalPath, destinationPath);
}



void IOfunction::DeleteFileByPath(String fileName)
{
	SystemWraper::SysDeleteFile(fileName);
}


void IOfunction::DeleteFolderByPath(String path)
{
	IOfunction::FolderMap(
		path,
		NULL,
		[](String path, String fileName, unsigned long long lastModifiedDate, unsigned long long fileSize, bool isDirectory, void* ptr)
	{
		if (isDirectory)
		{
			IOfunction::DeleteFolderByPath(path + BACKSLASH + fileName);
		}
		else
		{
			IOfunction::DeleteFileByPath(path + BACKSLASH + fileName);
		}
	}
	);
	

	SystemWraper::SysRemoveDirectory(path);
}




void IOfunction::CopyFileByPath(String origin, String destination)
{
	SystemWraper::SysCopyFile(origin, destination);
}

void IOfunction::CopyFolderByPath(String origin, String destination)
{

	CreateDirectoryByPath(origin, destination);

	IOfunction::FolderMap(
		origin, 
		(void*)&destination,
		[](String path, String fileName, unsigned long long lastModifiedDate, unsigned long long fileSize, bool isDirectory, void* ptr)
		{
			if (isDirectory)
			{
				IOfunction::CopyFolderByPath(path + BACKSLASH + fileName, *(String*)ptr + BACKSLASH + fileName);
			}
			else
			{
				IOfunction::CopyFileByPath(path + BACKSLASH + fileName, *(String*)ptr + BACKSLASH + fileName);
			}
		}
		);
}

