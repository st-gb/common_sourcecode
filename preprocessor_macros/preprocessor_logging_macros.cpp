/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * preprocessor_logging_macros.c
 *
 *  Created on: Aug 8, 2010
 *      Author: Stefan
 */

#include <string> //for std::string
#include <Controller/Logger/Logger.hpp> //class Logger

//LOGGING_CHARACTER_TYPE
#include <preprocessor_macros/logging_preprocessor_macros_definitions.h>

//Global variable that is used by logging macros-> needn't be created on stack
// each time -> should be faster.
//std::string g_stdstrLog ;
std::basic_string<LOGGING_CHARACTER_TYPE> g_std_basicstring_log_char_typeLog;
Logger g_logger ;
