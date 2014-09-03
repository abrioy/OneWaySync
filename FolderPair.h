#ifndef FOLDERPAIR_H_
#define FOLDERPAIR_H_

#include <String>

#include "OneWaySync.h"
#include "DirectoryIndex.h"

const enum CompareMode{
	Fast,
	Accurate,
};


class FolderPair
{
private:
	Filter Conditions;
	CompareMode Mode;
	const std::String* LeftPath;
	const std::String* RightPath;
	std::String RelativePath;

	FolderPair();
public:
	FolderPair(const std::String* leftFolderRootPath, const std::String* rightFolderRootPath, const std::String relativePath, const Filter conditions, const enum CompareMode mode);
	void Sync();

};


#endif