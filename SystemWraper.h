#ifndef SYSTEMWRAPER_H_
#define SYSTEMWRAPER_H_

#include <String>
#include <iostream>

#include <Aclapi.h>
#include <AccCtrl.h>
#include <Windows.h>


#include "OneWaySync.h"
#include "ErrorsHandler.h"

namespace SystemWraper
{
	// Create a directory with the same security descriptor as the original, return 0 on success
	int SysCreateDirectory(std::String optionalOriginalPath, std::String newPath);

	// Remove a directory, return 0 on success
	int SysRemoveDirectory(std::String path); 
	
	// Copy a file to the specified path with the same name, return 0 on success
	int SysCopyFile(std::String origin, std::String targets);

	// Delete a file, return 0 on success
	int SysDeleteFile(std::String filePath);

}


#endif