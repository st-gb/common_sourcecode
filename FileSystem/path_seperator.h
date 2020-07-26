#pragma once

#ifndef PATH_SEPERATOR_H
#define PATH_SEPERATOR_H

#if defined(__linux__)
  #define PATH_SEPERATOR_CHAR '/'
  #define PATH_SEPERATOR_WCHAR L'/'
  #define PATH_SEPERATOR_CHAR_STRING "/"
#elif defined(_WIN32) //Windows 32 or 64 bit
  #define PATH_SEPERATOR_CHAR '\\'
#endif

#endif //#ifndef PATH_SEPERATOR_H