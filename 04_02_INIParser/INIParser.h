#pragma once

#include "INIParser_API.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Introduced function pointer
typedef void(*ini_callback)(const char* section, const char* key_name, const char* key_value);

// First two functions we say to be exported into DLL. Other two aren't meant to be used publicly
void INI_API ini_parseINIFromFile(const char* filePath, const char* logfilePath, ini_callback callback);
void INI_API ini_parseINI(const char* iniData, const char* logfilePath, ini_callback callback);
void ini_appendBuffer(char* buffer, char c);
void ini_stripeBuffer(char* buffer);