#include <INIParser.h>

#include <stdio.h>
#include <string.h>

void iniDataCallback1(const char* section, const char* key_name, const char* key_value);
void iniDataCallback2(const char* section, const char* key_name, const char* key_value);

/*******************************************************************************************************************************************************/
int main(int argc, char** argv)				// argc -> arguments count; argv -> arguments values: aray of count argc
{
	printf("\n==== Hello from INI parser! Cmd line arguments. Function pointer =====\n\n");

	if (argc < 2 || argc > 4)				// pass ini file name as an argument and <optional> report format and log file
	{
		printf_s("Usage: INIParser_C [PathToINIFile] <OPTIONLA:ReportFormat(1/2) <OPTIONAL:PathToLogFile>");
		return -1;
	}

	ini_callback callback = iniDataCallback1;			// Set a defualt output report format
	// Check Report format argument - simplified for example purpose
	if (argc >= 3 && strcmp(argv[2], "2") == 0)
	{
		callback = iniDataCallback2;					// Set an alternative output report format
	}

	// Check logfile path - simplified for example purpose
	const char* logfile = NULL;
	if (argc >= 4)
	{
		logfile = argv[3];
	}
	else if (argc >= 3)
	{
		logfile = argv[2];
	}
	else
	{
		printf_s("No INI log file argument specified!");
	}

	// Parse the ini file
	ini_parseINIFromFile(argv[1], logfile, callback); // Introduce function pointer

	return 0;
}
/******************************************************************************************************/
void iniDataCallback1(const char* section, const char* key_name, const char* key_value)
{
	printf_s("[%s]\n%s = %s\n\n", section, key_name, key_value);
}

void iniDataCallback2(const char* section, const char* key_name, const char* key_value)
{
	printf_s("%s\\%s is %s\n", section, key_name, key_value);
}

