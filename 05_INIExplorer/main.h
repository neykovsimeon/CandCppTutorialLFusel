#pragma once

#include <INIParser.h>

#include <stdio.h>
#include <string.h>

void iniDataCallback1(void* userdata, const char* section, const char* key_name, const char* key_value);
void iniDataCallback2(void* userdata, const char* section, const char* key_name, const char* key_value);
