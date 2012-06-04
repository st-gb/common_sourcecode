/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * log_logger_name_thread_unsafe.h
 *
 *  Created on: 07.05.2011
 *      Author: Stefan
 */

#ifndef LOG_LOGGER_NAME_THREAD_UNSAFE_H_
#define LOG_LOGGER_NAME_THREAD_UNSAFE_H_


  #define LOG_LOGGER_NAME_THREAD_UNSAFE(logger,to_ostream) \
  { \
    std::stringstream strstream ; \
    strstream << to_ostream; \
    /*/for g++ compiler:
    //Because I want to call Log( std::string & ) I have to create an object at
    //first*/ \
    /*std::string stdstr = strstream.str() ;*/ \
    g_std_basicstring_log_char_typeLog = strstream.str() ; \
    /*g_logger->Log(to_ostream) ; */ \
    /*g_logger.Log( stdstr ) ;*/ \
    POSSIBLY_LOG_TO_STDOUT(g_std_basicstring_log_char_typeLog) \
    OWN_LOGGER_LOG_LOGGER_NAME( logger ,/*stdstr*/ g_std_basicstring_log_char_typeLog ) \
    LOG4CPLUS_INFO(log4cplus_logger, /*stdstr*/ g_std_basicstring_log_char_typeLog ); \
    /*g_logger.Log("test ") ; */ \
  }

#endif /* LOG_LOGGER_NAME_THREAD_UNSAFE_H_ */
