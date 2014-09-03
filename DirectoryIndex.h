#ifndef DIRECTORYINDEX_H_
#define DIRECTORYINDEX_H_


#include <String>
#include <queue>

#include "OneWaySync.h"
#include "IOfunction.h"
#include "File.h"
#include "Filter.h"


// The index is suuposed sorted at the end of the generation
class DirectoryIndex
{
private:
	std::priority_queue<File> Index;
	std::String Path;

	DirectoryIndex();
public:
	DirectoryIndex(const std::String pathToOpen);
	std::String GetPath();
	// Populate the index with the content of the folder (sub folders included)
	void GenerateIndex();
	
	// Return the next element of the index 
	int FindNext(File* resultFile);
	// Return the next element of the index which respects the condition
	int FindNext(File* resultFile, Filter condition);
	
};


#endif