#ifndef IOFUNCTION_H_
#define IOFUNCTION_H_

#include <string>

#include "SystemWraper.h"
#include "OneWaySync.h"



namespace IOfunction
{
	/*	Apply the function to every element of a folder, ptr is untouched
		returns 1 if the folder is empty, 0 otherwise */
	int FolderMap(
		std::String folderPath,
		void* ptrToPassInFunction,
		void(*function)(std::String path, std::String fileName, unsigned long long lastModifiedDate, unsigned long long fileSize, bool isDirectory, void* ptr)
		);

	 
	void CreateDirectoryByPath(std::String originalPath, std::String destinationPath);

	void DeleteFileByPath(std::String fileName);
	void DeleteFolderByPath(std::String path);

	void CopyFileByPath(std::String origin, std::String destination);
	void CopyFolderByPath(std::String origin, std::String destination);
}

#endif