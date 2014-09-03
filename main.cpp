#include <iostream>

#include "OneWaySync.h"
#include "FolderPair.h"

using namespace std;

/*
	TODO :
		catch erreur regex
*/

void printHelp()
{
	wcout << "OneWaySync" << endl
		<< "   -h - help" << endl
		<< "         Display this help" << endl
		<< endl
		<< "   -s -source  'Path'" << endl
		<< "         Path of the left folder" << endl
		<< endl
		<< "   -t - target  'Path'" << endl
		<< "         Path of the right folder" << endl
		<< endl
		<< "   -m -mode  fast/accurate" << endl
		<< "         fast     : Compare the name, last modification date, and size of the files" << endl
		<< "         accurate : Compare the md8 hash of the files" << endl
		<< endl
		<< "   -f -filter 'Regex1' 'Regex2' 'RegexN'" << endl
		<< "         Filter out every file and folder matching the regexes" << endl
		<< endl
		<< "   -e -errorfix  n t" << endl
		<< "         Retry every action that failed after t seconds n times" << endl
		<< endl
		<< "   -v -verbose  1/2/3" << endl
		<< "         1 : Errors only" << endl
		<< "         2 : Output every IO" << endl
		<< "         3 : Debug output" << endl
		<< endl;
}


int wmain(int argc, wchar_t* argv[])
{
	String source = L"";
	String target = L"";
	int errorNumberOfRetries = 0;
	int errorTimeout = 0;
	enum CompareMode mode = CompareMode::Fast;
	Filter filter = Filter();


	if (argc < 5)
	{
		wcout << L"Error: not enough arguments." << endl << endl;
		printHelp();
		return 0;
	}

	int i = 1;
	while (i+1 < argc)
	{
		if (wcscmp(argv[i], L"-h") == 0 || wcscmp(argv[i], L"-help") == 0)
		{
			printHelp();
		}
		else if (wcscmp(argv[i], L"-s") == 0 || wcscmp(argv[i], L"-source") == 0)
		{
			++i;
			source = String(argv[i]);
			wcout << endl << L"Source Path: " << source;
			++i;
		}
		else if (wcscmp(argv[i], L"-t") == 0 || wcscmp(argv[i], L"-target") == 0)
		{
			++i;
			target = String(argv[i]);
			wcout << endl << L"Target Path: " << target;
			++i;
		}
		else if (wcscmp(argv[i], L"-m") == 0 || wcscmp(argv[i], L"-mode") == 0)
		{
			++i;
			if (wcscmp(argv[i], L"fast") == 0)
			{
				mode = CompareMode::Fast;
				wcout << endl << L"Mode: fast";
			}
			else if (wcscmp(argv[i], L"accurate") == 0)
			{
				mode = CompareMode::Accurate;
				wcout << endl << L"Mode: accurate";
			}
			else
			{
				wcout << endl << L"Error: unknown mode \"" << argv[i] << "\".";
			}
			++i;
		}
		else if (wcscmp(argv[i], L"-f") == 0 || wcscmp(argv[i], L"-filter") == 0)
		{
			++i;
			wcout << endl << L"Filter(s): ";
			while (i < argc && argv[i][0] != '-')
			{
				filter.AddCondition(argv[i]);
				wcout << endl << L"     " << argv[i];
				++i;
			}
		}
		else if (wcscmp(argv[i], L"-e") == 0 || wcscmp(argv[i], L"-errorfix") == 0)
		{
			++i;
			errorNumberOfRetries = wcstol(argv[i], NULL, 10);
			++i;
			if (i < argc)
			{
				errorTimeout = wcstol(argv[i], NULL, 10)*1000;
				++i;
			}
			wcout << endl << L"Fix Error: " << errorNumberOfRetries << L" tries with " << (errorTimeout/1000) << L"s between each try.";
		}
		else if (wcscmp(argv[i], L"-v") == 0 || wcscmp(argv[i], L"-verbose") == 0)
		{
			++i;
			auto verbose = wcstol(argv[i], NULL, 10);
			ErrorsHandler::GetInstance().VerboseLevel = verbose;
			wcout << endl << L"Verbose level: " << verbose;
			++i;
		}
		else
		{
			wcout << endl << L"Error: unknown argument \"" << argv[i] << L"\".";
			++i;
		}

	}


	if (source.empty() || target.empty())
	{
		wcout << endl << L"Error: source and target are not optional." << endl << endl;
		printHelp();
		return 0;
	}

	wcout << endl << endl << endl << L"Sync in progress ..." << endl;




	// Do the actual syncing

	FolderPair syncPair = FolderPair(&source, &target, L"", filter, mode);
	syncPair.Sync();


	wcout << endl << L"Syncing is over.";


	// Error retrying

	for (int i = 0; i < errorNumberOfRetries; i++)
	{
		wcout << endl << L"Waiting " << (errorTimeout / 1000) << L"s" << endl;
		Sleep(errorTimeout);
		wcout << endl << L"Attempt " << i << L" out of " << errorNumberOfRetries << L"." << endl;
		if (ErrorsHandler::GetInstance().FixAllErrors() == 0)
			break;
	}
	






	/*
	filter.AddCondition(L".*F[1-3]");

	FolderPair Test1 = FolderPair(new String(L"C:\\_FOLDER1"), new String(L"C:\\_FOLDER2"), L"", filter);
	FolderPair Test2 = FolderPair(new String(L"C:\\_FOLDER11"), new String(L"C:\\_FOLDER2"), L"", filter);
	Test1.Sync();
	wcout << endl << endl << endl;
	Sleep(1000);
	Test2.Sync();
	wcout << endl << endl << endl;
	Sleep(1000);
	Test1.Sync();
	Sleep(1000);

	

	FolderPair Test3 = FolderPair(new String(L"C:\\Users\\Miow\\AppData"), new String(L"H:\\BACKUP\\AppData"), L"", filter);
	//Test3.Sync();
	


	wcout << endl << endl << L"###################" << endl << endl;
	Sleep(5000);
	ErrorsHandler::GetInstance().VerboseLevel = 2;
	ErrorsHandler::GetInstance().FixAllErrors();

	Sleep(10000);
	*/

	wcout << endl << endl << L"All done !" << endl;

	return 1;

}


