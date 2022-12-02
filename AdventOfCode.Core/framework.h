#pragma once

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
#include <windows.h>

#ifdef ADVENT_CORE_EXPORT
#define ADVENT_CORE __declspec(dllexport)
#else
#define ADVENT_CORE __declspec(dllimport)
#endif