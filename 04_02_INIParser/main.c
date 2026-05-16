#include "INIParser.h"

#include <stdio.h>

/*******************************************************************************************************************************************************/
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
	ini_parseIni(iniContent);

	return 0;
}


