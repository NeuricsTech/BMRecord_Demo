#pragma once

#ifdef _BMR_PLATFORM_WINDOWS_
#ifdef _BMR_DYNAMIC_LINK_
#ifdef _BMR_BUILD_DLL_
#define _BMR_API_ __declspec(dllexport)
#else
#define _BMR_API_ __declspec(dllimport)
#endif
#else
#define _BMR_API_
#endif
#else
#error The system must run on the Windows platform
#endif