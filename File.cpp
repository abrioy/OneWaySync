#include "File.h"
#include "IOfunction.h"


using namespace std;

File::File()
{

}
 
File::File(const String path, String name, unsigned long long lastModificationDate, unsigned long long fileSize, bool isDirectory)
{
	Path = path;
	Name = name;
	FileSize = fileSize;
	LastModificationDate = lastModificationDate;
	IsDirectory = isDirectory;
}



bool File::operator<(const File& comparedFile) const
{
	return Name.compare(comparedFile.Name) != -1;
}


int File::CompareName(File otherFile)
{
	return Name.compare(otherFile.Name);
}


int File::CompareLastModificationDate(File otherFile)
{
	if (LastModificationDate == otherFile.LastModificationDate)
	{
		return 0;
	}
	else if (LastModificationDate > otherFile.LastModificationDate)
	{
		return -1;
	}

	return 1;
}

int File::CompareSize(File otherFile)
{
	if (FileSize == otherFile.FileSize)
	{
		return 0;
	}
	else if (FileSize > otherFile.FileSize)
	{
		return -1;
	}

	return 1;
}

int File::CompareHash(File otherFile)
{
	
	return 1;
}



void File::Delete()
{
	if (IsDirectory)
	{
		IOfunction::DeleteFolderByPath(Path + BACKSLASH + Name);
	}
	else
	{
		IOfunction::DeleteFileByPath(Path + BACKSLASH + Name);
	}
}

void File::CopyToPath(const String* destinationPath)
{

	if (IsDirectory)
	{
		IOfunction::CopyFolderByPath(Path + BACKSLASH + Name, *destinationPath + BACKSLASH + Name);
	}
	else
	{
		IOfunction::CopyFileByPath(Path + BACKSLASH + Name, *destinationPath + BACKSLASH + Name);
	}

}