#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

void parseIni(const char* iniData);
void appendBuffer(char* buffer, char c);
void stripeBuffer(char* buffer);

int main()
{
	printf("\n==== Hello from strings concept! Parsing String with state machine. =====\n\n");

	const char* iniContent =								//  Source:  https://en.wikipedia.org/wiki/INI_file
		"; last modified 1 April 2001 by John Doe \n"
		"[owner]\n"
		"	name = John Doe\n"
		"	organization = Acme Widgets Inc. \n"
		"\n"
		"[database]\n"
		"; use IP address in case network name resolution is not working\n"
		"	server = 192.0.2.62 \n"
		"	port = 143\n"
		"	file = \"payroll.dat\"\n";

	printf("======= Raw INI File =======\n%s\n", iniContent);

	printf("\n======= Parsed Data =======\n");
	parseIni(iniContent);

	return 0;
}
/***************************************************************************************************************************/
void stripeBuffer(char* buffer)
{
	//size_t len = strlen(buffer);						// Take the length of the buffer string
	char* c = &buffer[strlen(buffer) - 1];				// Take and check the last character
	if (*c == ' ' || *c == '\t')						// If it is space or tab - replace with NULL
	{
		*c = '\0';
		stripeBuffer(buffer);							// Recursive function call until *c is no longer space or tab
	}
}
/***************************************************************************************************************************/
//void appendBuffer(char* buffer, char c)							// Buffer size (256) not checked !
//{
//	char* cursor;
//	for (cursor = buffer; *cursor; cursor++);						// Cycling until '\0' is found
//	*cursor = c;													// Equivalent to: cursor[0] = c;
//	*(cursor + 1) = '\0';											// Equivalent to: cursor[1] = '\0';
//}
/****************************************************************************************************************************/
void appendBuffer(char* buffer, char c)								// Buffer size (256) not checked !
{
	char str[2] = { c, '\0' };
	strcat_s(buffer, 256, str);										// Concatenate: The max buffer size is yet hard coded
}
/****************************************************************************************************************************/
void parseIni(const char* iniData)
{
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
					appendBuffer(buffer, *c);						// store already received first character
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
						appendBuffer(buffer, *c);					// Add the current character to the buffer
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
						appendBuffer(buffer, *c);					// Add the current character to the buffer
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
						appendBuffer(buffer, *c);
						state = 6;	// Begin key value
						break;
				}
				break;
				/*********************************************/
			case 6:													// Start of the key value
				switch (*c)
				{
					case '\n':										// End of the key's value
						stripeBuffer(buffer); // Removes spaces at the end of the key-value - just before the new line \n
						strcpy_s(currentKeyValue, 256, buffer);		// Max size is given, but copy what is needed only
						*buffer = '\0';								// Clear the buffer
						state = 0;

						// Report the result
						printf("Propertie: \"%s/%s\": \"%s\"\n", currentSection, currentKeyName, currentKeyValue);
						break;
					default:
						appendBuffer(buffer, *c);
						break;
				}
				break;
				/*********************************************/
			case 7:	// Invalid key
				if (*c == '\n') state = 0;
				break;
		}
	}
}


