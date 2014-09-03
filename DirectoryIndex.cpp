#include "DirectoryIndex.h"

using namespace std;

DirectoryIndex::DirectoryIndex(const String pathToIndex)
{
	Path = pathToIndex;
	GenerateIndex();
}

String DirectoryIndex::GetPath()
{
	return Path;
}

void DirectoryIndex::GenerateIndex()
{
	IOfunction::FolderMap(
		GetPath(),
		(void*)&Index,
		[](String path, String fileName, unsigned long long lastModifiedDate, unsigned long long fileSize, bool isDirectory, void* ptr)
		{
		priority_queue<File>* index = ((priority_queue<File>*)ptr);

		// Pushing at the end of the index every file from the folder
		index->emplace(File(path, fileName, lastModifiedDate, fileSize, isDirectory));
		}
		);
}


int DirectoryIndex::FindNext(File* resultFile)
{
	if (Index.size() == 0)
	{
		return 1;
	}

	*resultFile = Index.top();
	Index.pop();
	return 0;
}


int DirectoryIndex::FindNext(File* resultFile, Filter condition)
{
	if (Index.size() == 0)
	{
		return 1;
	}

	File indexTop = Index.top();
	Index.pop();

	if (!condition.TestString(indexTop.Path + BACKSLASH + indexTop.Name))
	{
		// File is ignored
		FindNext(resultFile, condition);
	}
	else
	{
		*resultFile = indexTop;
	}
	return 0;
}
