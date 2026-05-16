#pragma once

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void ini_parseINIFromFile(const char* filePath, const char* logfilePath);
void ini_parseINI(const char* iniData, const char* logfilePath);
void ini_appendBuffer(char* buffer, char c);
void ini_stripeBuffer(char* buffer);