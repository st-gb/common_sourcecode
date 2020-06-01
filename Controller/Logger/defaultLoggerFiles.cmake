include(${CMAKE_CURRENT_LIST_DIR}/Logger.cmake)
set(defaultLoggerSrcFilePaths
  ${SG_BasicLoggerSrcFilePaths}
  ${CmnSrcLogger}/Appender/RollingFileOutput.cpp
  #TODO HTML formatter really necessary?
  ${CmnSrcLogger}/Formatter/HTMLlogFormatter.cpp
  ${CmnSrcLogger}/Formatter/Log4jFormatter.cpp
  #TODO std::cout outputter really necessary?
  ${CmnSrcLogger}/OutputHandler/StdCoutLogWriter.cpp
  ${CmnSrcLogger}/OutputHandler/StdOfStreamLogWriter.cpp
)
