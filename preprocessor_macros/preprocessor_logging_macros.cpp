/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * preprocessor_logging_macros.c
 *
 *  Created on: Aug 8, 2010
 *      Author: Stefan
 */

#include <string> //for std::string

//LOGGING_CHARACTER_TYPE
#include <preprocessor_macros/logging_preprocessor_macros_definitions.h>

//Global variable that is used by logging macros-> needn't be created on stack
// each time -> should be faster.
//std::string g_stdstrLog ;
std::basic_string<LOGGING_CHARACTER_TYPE> g_std_basicstring_log_char_typeLog;

#include <preprocessor_macros/global_logger_object.hpp>
//DEFINE_GLOBAL_LOGGER_OBJECT
#include <Controller/Logger/Logger.hpp> //class Logger
//#ifdef _WIN32
//  #include <Windows/Logger/Logger.hpp> //class Windows_API::Logger
//#endif
//#ifdef USE_OWN_LOGGER
//#ifdef GLOBAL_LOGGER_FULLY_QUALIFIED_CLASS_NAME
  //#define DEFINE_GLOBAL_LOGGER_OBJECT_ Logger g_logger ;
  ::Logger g_logger;
//  GLOBAL_LOGGER_FULLY_QUALIFIED_CLASS_NAME g_logger;
//#endif
