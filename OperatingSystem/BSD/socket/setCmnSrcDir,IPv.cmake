##(c)2022 Stefan Gebauer,Computer Science Master,TU Berlin matricul. no. 361095
##Can/should be used for many tests for BSD sockets.

macro(TU_Bln361095setCmnSrcDirAndIPv subDir)
if(DEFINED TU_Bln361095cmnSrcDir)##For example defined in "cmake" command line
  message("\"TU_Bln361095cmnSrcDir\" defined for CMake:\""
    "${TU_Bln361095cmnSrcDir}\"")
else()
  #For "include_directories(...)" and "include(...)"
  set(TU_Bln361095cmnSrcDir ../../../../../${subDir})
endif()
#Get away/resolve ".." etc. in file system path.
get_filename_component(TU_Bln361095cmnSrcDir "${TU_Bln361095cmnSrcDir}"
  ABSOLUTE)

include(${TU_Bln361095cmnSrcDir}/CMake/SGR_terminalColours.cmake)
##May have been defined before. In this case do not override its value.
if(NOT DEFINED SGRattrNm)
 set(SGRattrNm ${SGR_Magenta})
endif()
##May have been defined before. In this case do not override its value.
if(NOT DEFINED SGRattrVal)
 set(SGRattrVal ${SGR_Blue})
endif()
message("Resolved ${SGRattrNm}cmnSrcDir${SGR_ColourReset}:\"${SGRattrVal}"
 "${TU_Bln361095cmnSrcDir}${SGR_ColourReset}\"")
#To set the IP version via CMake/compiler macro definition.
include(${TU_Bln361095cmnSrcDir}/OperatingSystem/BSD/socket/set_IPv.cmake)
endmacro()
