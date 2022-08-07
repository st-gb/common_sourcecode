##(c)2022 Stefan Gebauer,Computer Science Master,TU Berlin matricul. no. 361095
##Can/should be used for many tests for BSD sockets.

macro(setCmnSrcDirAndIPv subDir)
if(DEFINED cmnSrcDir)##For example defined in "cmake" command line
  message("\"cmnSrcDir\" defined for CMake:\"${cmnSrcDir}\"")
else()
  #For "include_directories(...)" and "include(...)"
  set(cmnSrcDir ../../../../../${subDir})
endif()
#Get away/resolve ".." etc. in file system path.
get_filename_component(cmnSrcDir "${cmnSrcDir}" ABSOLUTE)

include(${cmnSrcDir}/CMake/SGR_terminalColours.cmake)
##May have been defined before. In this case do not override its value.
if(NOT DEFINED SGRattrNm)
 set(SGRattrNm ${SGR_Magenta})
endif()
##May have been defined before. In this case do not override its value.
if(NOT DEFINED SGRattrVal)
 set(SGRattrVal ${SGR_Blue})
endif()
message("Resolved ${SGRattrNm}cmnSrcDir${SGR_ColourReset}:\"${SGRattrVal}"
 "${cmnSrcDir}${SGR_ColourReset}\"")
#To set the IP version via CMake/compiler macro definition.
include(${cmnSrcDir}/OperatingSystem/BSD/socket/set_IPv.cmake)
endmacro()
