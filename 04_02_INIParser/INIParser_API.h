#pragma once

#ifdef INI_BUILD_DLL			// we define this in IDE's configurations, Project's properties
#define INI_API __declspec(dllexport)
#else
#define INI_API __declspec(dllimport)
#endif