#include "INIParser.h"

#include <stdio.h>

/*******************************************************************************************************************************************************/
int main(int argc, char** argv)				// argc -> arguments count; argv -> arguments values: aray of count argc
{
	printf("\n==== Hello from INI parser! Read INI from a file. Cmd line arguments =====\n\n");

	// Example variant for getting file name from an user input.
	//char fileName[256];
	//printf_s("Please enter the file: ");
	//scanf_s("%s", fileName, 256);
	
	// Command line argument preferred
	//for (int i = 0; i < argc; i++)
	//{
	//	printf_s("%i: %s\n", i, argv[i]);
	//}

	if (argc < 2 || argc > 3) // pass ini file name as an argument and <optional> log file
	{
		printf_s("Usage: INIParser_C [PathToINIFile] <OPTIONAL:PathToLogFile>");
		return -1;
	}

	// Check logfile path
	const char* logfile = NULL;
	if (argc >= 3)
	{
		logfile = argv[2];
	}

	// Parse the ini file
	ini_parseINIFromFile(argv[1], logfile);				// Relative path 

	return 0;
}


