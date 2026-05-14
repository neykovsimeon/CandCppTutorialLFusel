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

	const char* iniContent =
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
/******************************************************************************/
void stripeBuffer(char* buffer)
{
	char* cursor;
	for (cursor = buffer; cursor[1] != '\0'; cursor++);
	while (*cursor == ' ' || *cursor == '\t')
	{
		*cursor = '\0';
		cursor--;
	}
}
/******************************************************************************/
void appendBuffer(char* buffer, char c)								// Buffer size (256) not checked !
{
	char* cursor;
	for (cursor = buffer; *cursor; cursor++);						// Cycling until '\0' is found
	*cursor = c;													// Equivalent to: cursor[0] = c;
	*(cursor + 1) = '\0';											// Equivalent to: cursor[1] = '\0';

	/*
	*  Implementation with buffer size check / buffer free space check
	* 
	* void appendBuffer(char* buffer, char c)
	* {
	*  char* cursor;
	*  for (cursor = buffer; *cursor; cursor++); // find the buffer's end and count bytes number
	*  long currentLenght = cursor - buffer;	 // The diff between the current address and the start address gives the length
	*  if (currentLength + 1 < 256)
    *  {
    *		cursor[0] = c;
    *		cursor[1] = '\0';
    *  }
	* }
	*/
}
/******************************************************************************/
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
		// Waiting for INI data
		if (state == 0)												// Ready for INI data
		{
				 if (*c == ';')	state = 1;							// go to Comment started
			else if (*c == '[')	state = 2;							// go to Section name started. 
																	// Space is not allowed in Section name
			else if (!(*c == ' ' || *c == '\t' || *c == '\n'))
			{
				 appendBuffer(buffer, *c);							// store already received first character
				 state = 3;
			}// go to Key Name started. '\t' - TAB check
		}
		// Reading comment
		else if (state == 1)										// Comment started
		{
			if (*c == '\n') state = 0;								// Comment ended here
		}
		// Section name started
		else if (state == 2)
		{
			if (*c == ']')											// Section name ended
			{
				memcpy(currentSection, buffer, 256 * sizeof(char));
				*buffer = '\0';										// Clear the buffer
				state = 0;
			}
			else if (*c == '\n')									// Invalid section name ! (Missing ']')
			{
				// Discard section name. Won't report any errors.
				*buffer = '\0';										// This 'clears' the buffer, means empty buffer is given
				state = 0;
			}
			else // if it's not end of line or invalid section, we append all characters in between
			{
				appendBuffer(buffer, *c);							// Add the current character to the buffer
			}
		}
		// Key name started. Space at the beginning of the key name is OK, but we discard it
		else if (state == 3)
		{
			if (*c == ' ' || *c == '\t')							// Key name is finished
			{
				memcpy(currentKeyName, buffer, 256 * sizeof(char));	// Clear the buffer
				*buffer = '\0';
				state = 4;											// Go to key value
			}
			else if (*c == '\n')									
			{
				state = 0;	// We have a key name defined, but it is not valid (only name, but not value)
			}
			else
			{
				appendBuffer(buffer, *c);						// Add the current character to the buffer
			}
		}
		// End of key name, take the key value
		else if (state == 4)
		{
				 if (*c == '=')  state = 5;						// Start of the key's value
			else if (*c == '\n') state = 0;						// Invalid key-name - key-value pair
			else if (!(*c == '\n' || *c == '\t')) state = 7;	// Invalid key-name - key-value pair, wait for next new line
		}
		// Ready for the key value
		else if (state == 5)
		{
				 if (*c == '\n') state = 0;						// Invalid key-name - key-value pair
			else if (!(*c == ' ' || *c == '\t'))
			{
				 appendBuffer(buffer, *c);
				 state = 6;	// Begin key value
			}
		}
		// Start of the key value
		else if (state == 6)
		{
			if (*c == '\n')
			{
				stripeBuffer(buffer); // Removes spaces at the end of the key-value - just before the new line \n
				memcpy(currentKeyValue, buffer, 256 * sizeof(char));
				*buffer = '\0';									// Clear the buffer
				state = 0;

				// Report the result
				printf("Propertie: \"%s/%s\": \"%s\"\n", currentSection, currentKeyName, currentKeyValue);
			}
			else 
			{
				appendBuffer(buffer, *c);						// Add the current character to the buffer
			}
		}
		else if (state == 7)
		{
			if (*c == '\n') state = 0;
		}
		//printf(" '%c' ", *c);
	}
}


