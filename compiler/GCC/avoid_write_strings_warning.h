#pragma once///Include guard

///To avoid GCC (and "clang"?) compiler warning  "warning: ISO C++ forbids 
///converting a string constant to ‘char*’ [-Wwrite-strings" by converting to a
///"char" pointer
#define CAST_TO_CHAR_POINTER (char *)

