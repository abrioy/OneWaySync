#ifndef FILE_H_
#define FILE_H_

#include <String>

#include "OneWaySync.h"

class File
{
private:
	unsigned long long LastModificationDate;
	unsigned long long FileSize;

public:
	std::String Name;
	bool IsDirectory;
	std::String Path;
	

	File();
	File(const std::String path, std::String name, unsigned long long lastModificationDate, unsigned long long fileSize, bool isDirectory);

	bool File::operator<(const File& comparedFile) const;

	// Compare the name of the two files, returns 0 if they have the same name, -1 if the file beeing compared if before in alphabetical order, 1 otherwise
	int CompareName(File otherFile);
	// Compare the date of last access of two files, returns 0 if they are the same, -1 if the compared file has been modified first, 1 otherwise
	int CompareLastModificationDate(File otherFile);
	// Compare the size of two files, returns 0 if they are the same, -1 if the compared file is smaller, 1 otherwise
	int CompareSize(File otherFile);

	// Compare the hash of two files, returns 0 if they are the same
	int CompareHash(File otherFile);


	// This function only delete the physical this associated to this object
	void Delete();
	// Copy the physical file to the specified path
	void CopyToPath(const std::String* destinationPath);


	
};


#endif