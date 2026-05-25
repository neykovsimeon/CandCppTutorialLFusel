#include "INIx.h"

void inix_parseINIFromFile(inix_data* data, const char* filePath, const char* logfilePath)
{
    ini_parseINIFromFile(filePath, logfilePath, inix_appendKeyToData, data);
}

void inix_parseINI(inix_data* data, const char* iniData, const char* logfilePath)
{
    ini_parseINI(iniData, logfilePath, inix_appendKeyToData, data);
}

void inix_close(inix_data* data)
{
    if (data)
    {
        // TODO: Cleanup
        if (data->firstSection)
        {
            inix_closeSection(data->firstSection);
        }
        free(data);
    }

}

int inix_sectionExists(inix_data* data, const char* name)
{
    // boolean expresion works from left to right.
    return data->firstSection && inix_getSection(data->firstSection, name);
}

int inix_keyExists(inix_data* data, const char* in_section_name, const char* exist_key_name)
{
    if (data->firstSection)
    {
        inix_section* section = inix_getSection(data->firstSection, in_section_name);
        if (section)                                                    // If section with the requested name has been found
        {
            if (section->firstKey)                                      // Check this section has keys/root/firstKey
            {
                return 1 && inix_getKey(section->firstKey, exist_key_name); // Return 1 (true) if a key with the requested name exists
            }
        }
    }

    return 0;                                                           // Return false if data->firstSection dsoesn't exists
}

const char* inix_get(inix_data* data, const char* in_section_name, const char* exist_key_name)
{
    if (data->firstSection)
    {
        inix_section* section = inix_getSection(data->firstSection, in_section_name);
        if (section && section->firstKey)
        {
            inix_key* key = inix_getKey(section->firstKey, exist_key_name);
            if (key)
            {
                return key->key_value;
            }
        }
    }
    
    return NULL;
}

void inix_enumerate(inix_data* data, ini_callback callback, void* userdata)
{
    for (inix_section* section = data->firstSection; section; section = section->nextSection)
    {
        for (inix_key* key = section->firstKey; key; key = key->nextKey)
        {
            callback(userdata, section->section_name, key->key_name, key->key_value);
        }
    }
}

inix_data* inix_new()
{
    inix_data* data = malloc(sizeof(inix_data));
    // TODO: Init data
    if (data)
    {
        data->firstSection = NULL;
    }
    return data;
}

void inix_callback(inix_data* data, const char* section, const char* key_name, const char* key_value)
{


}

inix_key* inix_newKey(const char* new_key_name, const char* new_key_value)
{
    inix_key* new_key = malloc(sizeof(inix_key));
    if (new_key)
    {
        new_key->key_name = _strdup(new_key_name);
        new_key->key_value = _strdup(new_key_value);
        new_key->nextKey = NULL;
    }

    return new_key;
}

inix_key* inix_getKey(inix_key* root, const char* get_key_name)
{
    if (strcmp(root->key_name, get_key_name) == 0)
    {
        return root;
    }
    if (root->nextKey)
    {
        return inix_getKey(root->nextKey, get_key_name);
    }

    return NULL; // by defult and when we didn't found the requested (get) key name
}

void inix_appendKey(inix_key* root, const char* key_name, const char* key_value)
{
    while (root->nextKey) // This will end-up at the end of the key's list.
    {
        root = root->nextKey;
    }
    // When we are at the end of the list - assign to its next key given name and value
    root->nextKey = inix_newKey(key_name, key_value);
}

void inix_closeKey(inix_key* key)
{
    if (key)
    {
        if (key->nextKey)
        {
            inix_closeKey(key->nextKey);
        }
        
        if(key->key_name) free(key->key_name);
        if(key->key_value) free(key->key_value);
        
        free(key);
    }
}

inix_section* inix_newSection(const char* name)
{
    inix_section* new_section = malloc(sizeof(inix_section));
    if (new_section)
    {
        new_section->section_name = _strdup(name);

        new_section->firstKey = NULL;
        new_section->nextSection = NULL;
    }

    return new_section;
}

inix_section* inix_appendSection(inix_section* root, const char* append_section_name)
{
    while (root->nextSection) // This will end-up at the end of the senctions' list.
    {
        root = root->nextSection;
    }
    root->nextSection = inix_newSection(append_section_name);

    return root->nextSection;
}

inix_section* inix_getSection(inix_section* root, const char* name)
{
    // Check if section exists
    inix_section* foundSection = NULL;
    for (inix_section* section = root; section; section = section->nextSection)
    {
        if (strcmp(section->section_name, name) == 0)
        {
            foundSection = section;
            break;
        }
    }
    return foundSection;
}

void inix_appendKeyToSection(inix_section* section, const char* append_key_name, const char* append_key_value)
{
    if (section->firstKey) // if we already have keys list -> we append new one at the end
    {
        inix_appendKey(section->firstKey, append_key_name, append_key_value);
    }
    else // if we don't yet have any keys (firstKey = NULL), we create new key, it becomes the root/first key in this section
    {
        section->firstKey = inix_newKey(append_key_name, append_key_value);
    }
}

void inix_closeSection(inix_section* section)
{
    if (section)
    {
        if (section->nextSection)
        {
            inix_closeSection(section->nextSection);
        }
        if (section->firstKey)
        {
            inix_closeKey(section->firstKey);
        }
        if(section->section_name) free(section->section_name);
        free(section);
    }
}

inix_section* inix_ensureSection(inix_data* data, const char* name)
{
    // Check if section exists
    //int sectionExists = 0; // false by defualt
    inix_section* foundSection = NULL;
    if (data->firstSection)
    {
        foundSection = inix_getSection(data->firstSection, name);
    }

    // Insert section if not existed
    if (!foundSection)
    {
        if (data->firstSection)
        {
            foundSection = inix_appendSection(data->firstSection, name);
        }
        else
        {
            // valid assignment, works from right to left
            foundSection = data->firstSection = inix_newSection(name);
        }
    }

    return foundSection;
}

void inix_appendKeyToData(inix_data* data, const char* section_name, const char* append_key_name, const char* append_key_value)
{
    inix_section* section = inix_ensureSection(data, section_name);
    if (section)
    {
        if (section->firstKey)
        {
            inix_key* key_found = inix_getKey(section->firstKey, append_key_name);
            if (key_found) // if existed  - we replace its value with the requested one
            {
                if (key_found->key_value) free(key_found->key_value);
                key_found->key_value = _strdup(append_key_value);
            }
            else // if not existed  - we append the requested one
            {
                inix_appendKey(section->firstKey, append_key_name, append_key_value);
            }
            
        }
        else
        {
            section->firstKey = inix_newKey(append_key_name, append_key_value);
        }
    }
}

