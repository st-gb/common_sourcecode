##(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

## http://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
## http://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html
  if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(cmplrDbgOpts
## http://gcc.gnu.org/onlinedocs/gcc/Debugging-Options.html :
## "-glevel" : "Level 3 includes extra information, such as all the macro
##  definitions present in the program. Some debuggers support macro expansion
##  when you use -g3."
## "-ggdb" : "Produce debugging information for use by GDB. This means to use
##  the most expressive format available (DWARF, stabs, or the native format if
##  neither of those are supported), including GDB extensions if at all
##  possible."
## "-gdwarf-version" : "Produce debugging information in DWARF format (if that
##  is supported)."
## "-Og may result in a better debugging experience."
## http://gcc.gnu.org/onlinedocs/gcc/Optimize-Options.html#Optimize-Options :
## "-O0" : "Most optimizations are completely disabled at -O0"
##  "Reduce compilation time and make debugging produce the expected results.
##   This is the default."
## "-Og" : "It is a better choice than -O0 for producing debuggable code because
##  some compiler passes that collect debug information are disabled at -O0."
      "-g3 -Og -gdwarf-2")
    SET(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} ${cmplrDbgOpts}")
    SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${cmplrDbgOpts}")
  endif()
endif()

