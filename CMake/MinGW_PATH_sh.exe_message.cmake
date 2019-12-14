#Must be executed before a CMake "project(...)" definition

#https://cmake.org/cmake/help/v3.0/variable/CMAKE_GENERATOR.html
message("CMake build system generator: ${CMAKE_GENERATOR}")
if("${CMAKE_GENERATOR}" STREQUAL "MinGW Makefiles")#MINGW)#WIN32)
  #https://stackoverflow.com/questions/41333215/mingw-sh-exe-must-not-be-in-your-path
  message("if error \"sh.exe was found in your PATH, here:\" execute \"where sh.exe\"")
  #https://cmake.org/cmake/help/latest/command/execute_process.html#execute-process
  execute_process(COMMAND where sh.exe OUTPUT_VARIABLE where_sh.exe)
  message("result of \"where sh.exe\": ${where_sh.exe}")
  message("PATH may have been set by an Integrated Development Environment ")
  message("(IDE) when this script is processed from with an IDE.")
  #message("PATH: $ENV{PATH}")
endif()