#include "INIParser.h"

#include <stdio.h>

/*******************************************************************************************************************************************************/
int main()
{
	printf("\n==== Hello from INI parser! Read INI from a file. =====\n\n");


	
	
	printf("\n======= Parsed Data =======\n");

	ini_parseINIFromFile("./my_config.ini");								// Relative path 

	return 0;
}


