#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Introduced function pointer
typedef void(*ini_callback)(const char* section, const char* key_name, const char* key_value);

void ini_parseINIFromFile(const char* filePath, const char* logfilePath, ini_callback callback);
void ini_parseINI(const char* iniData, const char* logfilePath, ini_callback callback); 
void ini_appendBuffer(char* buffer, char c);
void ini_stripeBuffer(char* buffer);