#pragma once

#ifdef __04_02_INIParser_BUILD_DLL			// we define this in IDE's configurations, Project's properties
#define INI_API __declspec(dllexport)
#else
#define INI_API __declspec(dllimport)
#endif