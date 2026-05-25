#pragma once

#include "INIParser_API.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Introduced function pointer
typedef void(*ini_callback)(void* userdata, const char* section, const char* key_name, const char* key_value);

// SAX Api (SAX -> Simple Api for Xml) -> take the concept, use it for INI (Simple Api for INI)
// First two functions we say to be exported into DLL. Other two aren't meant to be used publicly
void INI_API ini_parseINIFromFile(const char* filePath, const char* logfilePath, ini_callback callback, void* userdata);
void INI_API ini_parseINI(const char* iniData, const char* logfilePath, ini_callback callback, void* userdata);
void ini_appendBuffer(char* buffer, char c);
void ini_stripeBuffer(char* buffer);