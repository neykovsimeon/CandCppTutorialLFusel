#include <INIParser.h>

#include <stdio.h>
#include <string.h>

#if defined(INIEXPLORER_DEFAULT_FORMAT1) && !defined(INIEXPLORER_DEFAULT_FORMAT2)
#define INIEXPLORER_FORMAT_CALLBACK iniDataCallback1
#elif defined(INIEXPLORER_DEFAULT_FORMAT2) && !defined(INIEXPLORER_DEFAULT_FORMAT1)
#define INIEXPLORER_FORMAT_CALLBACK iniDataCallback2
#else
#error Please define ONLY one default format!
#endif


void iniDataCallback1(const char* section, const char* key_name, const char* key_value);
void iniDataCallback2(const char* section, const char* key_name, const char* key_value);

/*******************************************************************************************************************************************************/
int main(int argc, char** argv)				// argc -> arguments count; argv -> arguments values: aray of count argc
{
	printf("\n=== Hello from INI parser! DLL intro - windows specific ===\n\n");

	// Example use of preprocessor directives
	//myGreet(MY_NAME);
	//debugOnly(printf_s("Test debug print 1234...\n\n"));

	if (argc < 2 || argc > 3)				// pass ini file name as an argument and <optional> report format and log file
	{
		printf_s("Usage: INIParser_C [PathToINIFile] <OPTIONAL:PathToLogFile>");
		return -1;
	}

	// Set a defualt output report format, use it within the IDE (MS VS)
	ini_callback callback = INIEXPLORER_FORMAT_CALLBACK;	

	// Check the actual user input given in the command line
	if (argc >= 3)
	{
		switch (*argv[2])
		{
			case '1':
				callback = iniDataCallback1;
				break;
			case '2':
				callback = iniDataCallback2;
				break;
			default:
				printf_s("\nInvalid output report format!");
				return -1;
		}
	}

	// Check logfile path - simplified for example purpose
	const char* logfile = NULL;
	if (argc >= 3)
	{
		logfile = argv[2];
	}
	else
	{
		printf_s("\nNo INI log file argument specified!\n\n");
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

