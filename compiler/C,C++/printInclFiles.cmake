##(c) from 2024 by Stefan Gebauer(Computer Science Master from TU Berlin)
##@author Stefan Gebauer:Technical University Berlin matriculation number 361095
##File name "printInclFiles" comes from:
## "Incl"=INCLude: http://www.abbreviations.com/abbreviation/include

#message("CMAKE_C_COMPILER_ID: ${CMAKE_C_COMPILER_ID}")
##http://cmake.org/cmake/help/latest/variable/CMAKE_LANG_COMPILER_ID.html
if(CMAKE_C_COMPILER_ID STREQUAL "GNU")
  #message("GNU compiler")
  set(COMPILE_DEFINITIONS
	${COMPILE_DEFINITIONS}
##http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html :
## "-H
##
##  Print the name of each header file used, in addition to other normal
##  activities. Each name is indented to show how deep in the ‘#include’ stack
##  it is. Precompiled header files are also printed, even if they are found to
##  be invalid; an invalid precompiled header file is printed with ‘...x’ and a
##  valid one with ‘...!’ ."
    -H
    )
  #message("\"COMPILE_DEFINITIONS\" after adding preprocessor option for "
  #  "printing include files:${COMPILE_DEFINITIONS}")
endif()
