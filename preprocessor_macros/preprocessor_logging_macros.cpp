/*
 * preprocessor_logging_macros.c
 *
 *  Created on: Aug 8, 2010
 *      Author: Stefan
 */

#include <string> //for std::string
#include <Controller/Logger/Logger.hpp> //class Logger

//Global var. that is used by logging macros-> needn't be created on stack
// each time -> should be faster.
std::string g_stdstrLog ;
Logger g_logger ;
