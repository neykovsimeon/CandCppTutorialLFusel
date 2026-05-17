#include "INIParser.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ini_parseINIFromFile(const char* filePath, const char* logfilePath, ini_callback callback)
{
	FILE* my_file = NULL;
	fopen_s(&my_file, filePath, "rb");				// Mode specified to read-binary
	if (my_file)
	{
		// Open file for reading
		// Use fseek and ftell for taking the file size uning file position indicator
		size_t fileSize = 0;
		fseek(my_file, 0, SEEK_END);				// Go to the file end
		fileSize = ftell(my_file);					// Tell what is the current position. Since we moved to the file end, it will represent the file size
		//fseek(my_file, 0, SEEK_SET);				// Return back to the beginning of the file to perform the actual read below
		rewind(my_file);							// Alternative method  to return back to the beginning of the file to perform the actual read below
		char* fileContent = malloc(fileSize + 1);	// Have to insert manualy and '\0' end of file terminator, this is why we extend the file size here
		if (fileContent)
		{
			// the whole file as one element, this one element contains the whole file in binary
			if (fread(fileContent, fileSize, 1, my_file) == 1)
			{
				// Read success
				fileContent[fileSize] = '\0';		// Insert the NULL terminator at the end of the buffer with the file content taken with fread()
				ini_parseINI(fileContent, logfilePath, callback);
			}
			free(fileContent);
		}
		fclose(my_file);
	}

}

/****************************************************************************************************************************/
void ini_parseINI(const char* iniData, const char* logfilePath, ini_callback callback)
{
	// Handle a parser-log file here
	FILE* my_parser_log = NULL;
	if (logfilePath)
	{
		fopen_s(&my_parser_log, logfilePath, "wb");  // Always will create it and if existed - with re-write 
	}
	


	// Working buffer to collect INI component data
	char buffer[256];
	*buffer = '\0';

	// Current section name
	char currentSection[256];
	*currentSection = '\0';

	// Current key name
	char currentKeyName[256];
	*currentKeyName = '\0';

	// Current key value
	char currentKeyValue[256];
	*currentKeyValue = '\0';

	/*
	*  0 - Ready for INI data
	*  1 - Comment started
	*  2 - Section name started
	*  3 - Key started
	*  4 - Key finished
	*  5 - Ready for value
	*  6 - Value started
	*  7 - Invalid data
	*/
	int32_t state = 0;
	// For actual use: based on pointers
	for (const char* c = iniData; *c; c++)
	{
		switch (state)
		{
		case 0:													// Waiting for INI data
			switch (*c)
			{
			case ';':	// Start comment
			case '#':
				state = 1;
				break;
			case '[':	// Start section name
				state = 2;
				break;
			case ' ':	// Valid spacing
			case '\t':
			case '\n':
				break;
			default:	// State key
				ini_appendBuffer(buffer, *c);						// store already received first character
				state = 3;										// go to Key Name started. '\t' - TAB check
				break;
			}
			break;
			/*******************************************/
		case 1:													// Reading comment, comment started
			if (*c == '\n') state = 0;							// Comment ended here
			break;
			/*******************************************/
		case 2:													// Section name started
			switch (*c)
			{
			case ']':
				strcpy_s(currentSection, 256, buffer);		// Max size is given, but copy what is needed only
				*buffer = '\0';								// Clear the buffer
				state = 0;
				break;
			case '\n':
				// Discard section name. Won't report any errors.
				*buffer = '\0';								// This 'clears' the buffer, means empty buffer is given
				state = 0;
				break;
			default:	 // if it's not end of line or invalid section, we append all characters in between
				ini_appendBuffer(buffer, *c);					// Add the current character to the buffer
				break;
			}
			break;
			/*********************************************/
		case 3:					// Key name started. Space at the beginning of the key name is OK, but we discard it
			switch (*c)
			{
			case ' ':										// Key name is finished
			case '\t':
				strcpy_s(currentKeyName, 256, buffer);		// Max size is given, but copy what is needed only
				*buffer = '\0';								// Clear the buffer
				state = 4;									// Go to key value
				break;
			case '\n':
				state = 0;									// We have a key name defined, but it is not valid (only name, but not value)
				break;
			default:
				ini_appendBuffer(buffer, *c);					// Add the current character to the buffer
				break;
			}
			break;
			/*********************************************/
		case 4:													// End of key name, take the key value
			switch (*c)
			{
			case '=':										// Start of the key's value
				state = 5;
				break;
			case '\n':										// Invalid key-name - key-value pair
				state = 0;
				break;
			case ' ':
			case '\t':
				break;
			default:
				state = 7;									// Invalid key-name - key-value pair, wait for next new line
				break;
			}
			break;
			/*********************************************/
		case 5:													// Ready for the key value
			switch (*c)
			{
			case '\n':										// Invalid key-name - key-value pair
				state = 0;
				break;
			case ' ':
			case '\t':
				break;
			default:
				ini_appendBuffer(buffer, *c);
				state = 6;	// Begin key value
				break;
			}
			break;
			/*********************************************/
		case 6:													// Start of the key value
			switch (*c)
			{
			case '\n':										// End of the key's value
				ini_stripeBuffer(buffer); // Removes spaces at the end of the key-value - just before the new line \n
				strcpy_s(currentKeyValue, 256, buffer);		// Max size is given, but copy what is needed only
				*buffer = '\0';								// Clear the buffer
				state = 0;

				// Report the result, introduce callback, define report format out-side of the parser itself
				callback(currentSection, currentKeyName, currentKeyValue);

				if (my_parser_log)
				{
					fprintf_s(my_parser_log, "Section = \"%s\"; KeyName = \"%s\"; KeyValue = \"%s\";\n", currentSection, currentKeyName, currentKeyValue);
				}

				break;
			default:
				ini_appendBuffer(buffer, *c);
				break;
			}
			break;
			/*********************************************/
		case 7:	// Invalid key
			if (*c == '\n') state = 0;
			break;
		}
	}

	if (my_parser_log)
	{
		fclose(my_parser_log);
	}

}
/***************************************************************************************************************************/
void ini_stripeBuffer(char* buffer)
{
	char* c = &buffer[strlen(buffer) - 1];							// Take and check the last character
	if (*c == ' ' || *c == '\t')									// If it is space or tab - replace with NULL
	{
		*c = '\0';
		ini_stripeBuffer(buffer);									// Recursive function call until *c is no longer space or tab
	}
}
/****************************************************************************************************************************/
void ini_appendBuffer(char* buffer, char c)							// Buffer size (256) not checked !
{
	if (!iscntrl(c))												// Windows control characters we don't want to append
	{
		char str[2] = { c, '\0' };
		strcat_s(buffer, 256, str);									// Concatenate: The max buffer size is yet hard coded
	}
}
