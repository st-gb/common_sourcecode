#pragma once///Include guard

/** To avoid GCC (and "clang"?) compiler warning  "warning: ISO C++ forbids 
 * converting a string constant to ‘char*’ [-Wwrite-strings]" by casting to a
 * "char" pointer */
#define CAST_TO_CHAR_POINTER (char *)
#define TU_Bln361095castToCharPtr (char *)

/**To avoid GCC (and "clang"?) compiler warning ~"deprecated conversion from
 * string constant to 'wchar_t*' [-Wwrite-strings]" by casting to a wchar_t 
 * pointer.*/
#define TU_Bln361095castToWchar_tPtr (wchar_t *)