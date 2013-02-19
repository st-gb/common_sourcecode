/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
//This file must be processed for every built event, so 

//see http://gcc.gnu.org/onlinedocs/cpp/Stringification.html#Stringification:
// "If you want to stringify the result of expansion of a macro argument, you
//have to use two levels of macros. "
// -> the 1st expands the expression, the 2nd stringifies
//#define STRINGIFY(str) " ## str ## "
#define MAKE_MINGW32_VERSION(str) MAKE_MINGW32_VERSION_2(str)
#define MAKE_MINGW32_VERSION_2(str) str ## EXPAND_AND_STRINGIFY( __GNUC__ ))

#define EXPAND_AND_STRINGIFY(str) STRINGIFY(str)
#define EXPAND_AND_STRINGIFY_2(str1,str2) STRINGIFY_2(str2)


#define STRINGIFY(str) #str
#define STRINGIFY_2(str1, str2) CONCATENATE(str1 , STRINGIFY(str2) )

#define CONCATENATE(str, str2) str ## str2
#define EXPAND(str) str
#define AFTERX(x) "\"" ## x ## "\""
#define XAFTERX(x) AFTERX(x)
#ifdef __CYGWIN__
    #define BUILT_TIME "Build: " __DATE__" " __TIME__ " GMT + 1\n\n"
#endif
#ifdef __GNUC__
  //We need a _T() macro (wide char-> L"", char->"") for EACH 
  //line to make it compatible between char and wide char.
  //#define BUILT_TIME _T("Build: ") ## __DATE__ ## _T(" ") ## __TIME__ ## _T(" GMT + 1\n\n")
  //#define BUILT_TIME _T("Build: ")__DATE__ _T(" ") __TIME__ _T(" GMT + 1\n\n")
  //MSVC 2005 and gcc can compile this, but not MSVC 2010 as far as I remember.
  #define BUILT_TIME _T("Build: ")_T(__DATE__) _T(" ") _T(__TIME__) _T(" GMT + 1")
  #define BUILT_DATE_AND_TIME EXPAND_AND_STRINGIFY(__DATE__) ## EXPAND_AND_STRINGIFY(__TIME__)
  #define BUILT_DATE_AND_TIME_STRING /*EXPAND_AND_STRINGIFY(BUILT_DATE_AND_TIME)*/ \
    STRINGIFY( EXPAND(__DATE__) EXPAND(__TIME__) )
  //"Build: " __DATE__ " " __TIME__ " GMT\n\n"
  //
  #define GCC_VERSION __GNUC__.__GNUC_MINOR__.__GNUC_PATCHLEVEL__
  #define GCC_VERSION_T _T(__GNUC__) _T(".") _T(__GNUC_MINOR__) _T(".") \
    _T(__GNUC_PATCHLEVEL__)
  #ifdef __MINGW32__
    //gcc.gnu.org/onlinedocs/cpp/Stringification.html#Stringification:
    //"If you want to stringify the result of expansion of a macro argument,
    //you have to use two levels of macros. "
//#define COMPILER_VERSION "MinGW32 GCC " ## EXPAND(__GNUC__)
    //#define COMPILER_VERSION \ /*"MinGW32 GCC " ## EXPAND_AND_STRINGIFY( __GNUC__ )*/
      /*MAKE_MINGW32_VERSION("hh") */
    //#define COMPILER_VERSION  "MinGW32 GCC " ## EXPAND_AND_STRINGIFY(GCC_VERSION)
    #define COMPILER_VERSION_NUMBER EXPAND_AND_STRINGIFY(GCC_VERSION)
    #define COMPILER_VERSION _T("MinGW32 GCC ")_T(__GNUC__) _T(".") _T(__GNUC_MINOR__) _T(".") \
    _T(__GNUC_PATCHLEVEL__)
    //#define COMPILER_VERSION STRINGIFY( CONCATENATE(MinGW32 GCC , GCC_VERSION))
    //#define COMPILER_VERSION EXPAND_AND_STRINGIFY( GCC_VERSION )
    //#define COMPILER_VERSION EXPAND_AND_STRINGIFY( "M", GCC_VERSION )
    //#define COMPILER_VERSION EXPAND_AND_STRINGIFY_2( "M", GCC_VERSION )
  #else //#ifdef __MINGW32__
    #define COMPILER_VERSION _T("")__GNUC__ __GNUC_MINOR__ __GNUC_PATCHLEVEL__ T("")
  #define COMPILER_VERSION_NUMBER EXPAND_AND_STRINGIFY(GCC_VERSION)
  #endif //#ifdef __MINGW32__
#endif //#ifdef __GNUC__
