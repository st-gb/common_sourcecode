#CMAKE_CURRENT_LIST_DIR if this file is included
set(SG_BasicLoggerSrcFilePaths
  ${CMAKE_CURRENT_LIST_DIR}/preprocessor_logging_macros.cpp#::Logger g_logger
  ${CMAKE_CURRENT_LIST_DIR}/Logger.cpp#class Logger
  #LogLevel::CreateLogLevelStringToNumberMapping()
  ${CMAKE_CURRENT_LIST_DIR}/LogLevel.cpp
  #Appender base class
  ${CMAKE_CURRENT_LIST_DIR}/Appender/FormattedLogEntryProcessor.cpp
  ${CMAKE_CURRENT_LIST_DIR}/Formatter/I_LogFormatter.cpp
  ${CMAKE_CURRENT_LIST_DIR}/OutputHandler/I_LogEntryOutputter.cpp
  )
