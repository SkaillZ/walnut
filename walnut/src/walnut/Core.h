#pragma once

#ifdef WN_PLATFORM_WINDOWS
  // This project is currently untested on Windows, so this is for future compatibility only.
  #ifdef WN_BUILD_DLL
    #define WN_API __declspec(dllexport)
  #else
    #define WN_API __declspec(dllimport)
  #endif
#else
  // The #define can be empty on other platforms since __declspec() is not needed
  #define WN_API
#endif
