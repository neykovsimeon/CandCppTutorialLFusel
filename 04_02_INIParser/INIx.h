#pragma once

#include "INIParser_API.h"
#include "INIParser.h"

#include <stdlib.h>
#include <string.h>

/*
*	root: inix_data
*		---> inix_section (name1)
*		---> ---> inix_key (name11, value11)
*		---> ---> inix_key (name12, value12)
*		---> ---> inix_key (name13, value13)
*		---> inix_section (name2)
*		---> ---> inix_key (name21, value21)
*		---> ---> inix_key (name22, value22)
*		---> ---> inix_key (name23, value23)
*/
/********************* Describe first the most lower leaf of the tree ******************/
typedef struct __inix_key
{
	char* key_name;
	char* key_value;

	struct __inix_key* nextKey;
} inix_key;
/***************************************************************************************/
typedef struct __inix_section
{
	char* section_name;
	struct __inix_key* firstKey;

	struct __inix_section* nextSection;
} inix_section;
/**************************************************************************************/
typedef struct __inix_data
{
	struct __inix_section* firstSection;

} inix_data;
/**************************************************************************************/

// Public DOM API
INI_API inix_data* inix_parseINIFromFile(const char* filePath, const char* logfilePath);
INI_API inix_data* inix_parseINI(const char* iniData, const char* logfilePath);
INI_API void inix_close(inix_data* data);

INI_API int inix_section_exists(inix_data* data, const char* name);
INI_API int inix_key_exists(inix_data* data, const char* in_section_name, const char* exist_key_name);
INI_API const char* inix_get(inix_data* data, const char* in_section_name, const char* exist_key_name);

// Clasical SAX parsing
INI_API void inix_enumerate(inix_data* data, ini_callback callback, void* userdata);


// Internal helper functions
void inix_callback(inix_data* data, const char* section, const char* key_name, const char* key_value);

inix_data* inix_new();

inix_key* inix_new_key(const char* key_name, const char* key_value);
inix_key* inix_get_key(inix_key* root, const char* get_key_name);
// append new key (name & value) to the end of an existing keys' list (we know the root key, not the section
void inix_append_key(inix_key* root, const char* key_name, const char* key_value); 
void inix_close_key(inix_key* key);

inix_section* inix_new_section(const char* name);
inix_section* inix_append_section(inix_section* root, const char* append_section_name);
inix_section* inix_get_section(inix_section* root, const char* name);
// append new key (name & value) to the end of an existing section's list of keys (we know the section in which we append new key)
void inix_appen_key_to_section(inix_section* section, const char* append_key_name, const char* append_key_value);
void inix_close_section(inix_section* section);

inix_section* inix_ensure_section(inix_data* data, const char* name);
void inix_append_key_to_data(inix_data* data, const char* section_name, const char* key_name, const char* key_value);

