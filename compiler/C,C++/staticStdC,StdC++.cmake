if(WIN32)##Microsoft Windows operating system(also 64 bit)
 if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
##https://stackoverflow.com/questions/16141451/the-procedure-entry-point-gxx-personality-v0-could-not-be-located-in-the-dynam
## if contains "__gxx_personality_v0" : "nm libstdc++-6.dll | grep personality"
## linker flags: "-static-libgcc -static-libstdc++"
##
##If not added then runtime error message "The procedure entry point
## __gxx_personality_v0 could not be located in the dynamic link library 
## libstdc++-6.dll" may show up.
##https://stackoverflow.com/questions/11783932/how-do-i-add-a-linker-or-compile-flag-in-a-cmake-file
  SET(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++")
 endif()
endif()
