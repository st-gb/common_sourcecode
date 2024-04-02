##(c) Stefan Gebauer(Computer Science Master from TU Berlin)
##@author Stefan Gebauer(TU Berlin matriculation number 361095)

include(${CMAKE_CURRENT_LIST_DIR}/Logger.cmake)
if(DEFINED TU_Bln361095cmnSrcLoggerDir)
  ##Set the default source files for Stefan Gebauer's logging here.
  set(
    ##cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
    ##Src=SouRCe: http://www.abbreviations.com/abbreviation/Source
    ##Dflt=DeFauLT: http://www.allacronyms.com/default/abbreviated
    TU_Bln361095cmnSrcDfltLoggerSrcFilePaths

    ${SG_BasicLoggerSrcFilePaths}
    ${TU_Bln361095cmnSrcLoggerDir}/Appender/RollingFileOutput.cpp
    #TODO HTML formatter really necessary?
    ${TU_Bln361095cmnSrcLoggerDir}/Formatter/HTMLlogFormatter.cpp
    ${TU_Bln361095cmnSrcLoggerDir}/Formatter/Log4jFormatter.cpp
    #TODO std::cout outputter really necessary?
    ${TU_Bln361095cmnSrcLoggerDir}/OutputHandler/StdCoutLogWriter.cpp
    ${TU_Bln361095cmnSrcLoggerDir}/OutputHandler/StdOfStreamLogWriter.cpp
    )
else()
  message("\"TU_Bln361095cmnSrcLogger\" not defined")
endif()
if(WIN32)
  if(DEFINED TU_Bln361095cmnSrcDir)
    set(TU_Bln361095cmnSrcDfltLoggerSrcFilePaths
      ${TU_Bln361095cmnSrcDfltLoggerSrcFilePaths}
      ${TU_Bln361095cmnSrcDir}/OperatingSystem/Windows/Logger/LogEntryOutputter.cpp
      )
  else()
    message("\"TU_Bln361095cmnSrcDir\" not defined=>can't set MicroSoft Windows"
      " outputter for logger")
  endif()
endif()