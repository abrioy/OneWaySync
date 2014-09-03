#include "FolderPair.h"

using namespace std;

FolderPair::FolderPair(const String* leftFolderRootPath, const String* rightFolderRootPath, const String relativePath, const Filter conditions, const enum CompareMode mode)
{
	if (leftFolderRootPath->empty() || rightFolderRootPath->empty())
	{
		// At least one path is empty, invalid arguments
		return;
	}
	else
	{
		LeftPath = leftFolderRootPath;
		RightPath = rightFolderRootPath;
		RelativePath = relativePath;
		Conditions = conditions;
		Mode = mode;
	}
}


void FolderPair::Sync()
{
	IOfunction::CreateDirectoryByPath(EMPTYSTRING, *RightPath + RelativePath);

	DirectoryIndex leftFolder = DirectoryIndex((*LeftPath) + RelativePath);
	DirectoryIndex rightFolder = DirectoryIndex((*RightPath) + RelativePath);

	File currentLeftFile;
	File currentRightFile;
	bool LastFileInFolderLeft = leftFolder.FindNext(&currentLeftFile, Conditions) != 0;
	bool LastFileInFolderRight = rightFolder.FindNext(&currentRightFile) != 0;

	if (!LastFileInFolderLeft)
	{
		while (!LastFileInFolderRight)
		{
			if (currentLeftFile.IsDirectory != currentRightFile.IsDirectory)
			{
				// Only one file is directory
				currentRightFile.Delete();
				LastFileInFolderRight = rightFolder.FindNext(&currentRightFile) != 0;
			}
			else
			{
				switch (currentLeftFile.CompareName(currentRightFile))
				{
				case 0: // Files have the same name

					if (currentLeftFile.IsDirectory)
					{
						// Both files are directories with the same name
						FolderPair subfolderPair = FolderPair(LeftPath, RightPath, (RelativePath + BACKSLASH + currentLeftFile.Name), Conditions, Mode);
						subfolderPair.Sync();
					}
					else
					{

						if (currentLeftFile.CompareLastModificationDate(currentRightFile) != 0)
						{
							// Files have a different last modification date
							currentLeftFile.CopyToPath(&(rightFolder.GetPath()));
						}
						else
						{
							if (currentLeftFile.CompareSize(currentRightFile) != 0)
							{
								// Files have a different size
								currentLeftFile.CopyToPath(&(rightFolder.GetPath()));
							}
							else
							{
								// Files are supposed identical at this point because they have the same name/date/size
								if (Mode == CompareMode::Accurate)
								{
									if (currentLeftFile.CompareHash(currentRightFile) != 0)
									{
										// Files are different
										currentLeftFile.CopyToPath(&(rightFolder.GetPath()));
									}
									else
									{
										// The files are identical
									}

								}
							}
						}
						


					}
					// At this point both files are the same
					LastFileInFolderLeft = leftFolder.FindNext(&currentLeftFile, Conditions) != 0;
					LastFileInFolderRight = rightFolder.FindNext(&currentRightFile) != 0;
					break;


				case -1: // Left file is before right file in the sorting order
					// Left file has to be copied to the right
					currentLeftFile.CopyToPath(&(rightFolder.GetPath()));

					// At this point the current left file exists in both folders
					LastFileInFolderLeft = leftFolder.FindNext(&currentLeftFile, Conditions) != 0;
					break;


				case 1: // Right file is before left file in the sorting order
					// Right file does not exsists in the left folder and has to be deleted

					currentRightFile.Delete();

					LastFileInFolderRight = rightFolder.FindNext(&currentRightFile) != 0;
					break;
				}

				if (LastFileInFolderLeft)
				{
					// We finishing going throught the left folder before the right folder
					// Every file remaining in the right folder does not exists in the left

					while (!LastFileInFolderRight)
					{
						currentRightFile.Delete();
						LastFileInFolderRight = rightFolder.FindNext(&currentRightFile) != 0;
					}
					break; // Getting out of the while loop
				}
			}

		}// End while

		// At this point either we finished going through both folders of only the right one
		while (!LastFileInFolderLeft)
		{
			// The remaining files from the left folder are not present in the right so we copy them
			currentLeftFile.CopyToPath(&(rightFolder.GetPath()));
			LastFileInFolderLeft = leftFolder.FindNext(&currentLeftFile, Conditions) != 0;
		}

		// Both folder are identical (I hope) ! Yay !
			
	}
	else
	{
		// Left folder is empty we delete what is left in the right one
		while (!LastFileInFolderRight)
		{
			currentRightFile.Delete();
			LastFileInFolderRight = rightFolder.FindNext(&currentRightFile) != 0;
		}
	}
}