/*
 * no_op_debug_output_macros.h
 *
 *  Created on: 15.09.2012
 *      Author: Stefan
 */

#ifndef NO_OP_DEBUG_OUTPUT_MACROS_H_
#define NO_OP_DEBUG_OUTPUT_MACROS_H_

  //The following macros compile to do no logging
  //Following macros: because of ";": block can be used after "if"/"else":
  // else DEBUG...(...)" -> "else ;"
  #define DEBUG(to_ostream) ;/*empty->do not log;can be used after "if"/"else"*/
  #define DEBUG_SPRINTF(...) ;/*do not log; can be used after "if"/"else"*/
  #define DEBUGN_LOGGER_NAME(logger_name,to_ostream) \
    ;/*do not log;can be used after "if"/"else"*/
  #define DEBUGN(to_ostream) ;/*do not log;can be used after "if"/"else"*/
  #define DEBUGWN(to_ostream) ;/*do not log;can be used after "if"/"else"*/
  #define DEBUGWN_WSPRINTF(...) ;/*do not log; can be used after "if"/"else"*/

#endif /* NO_OP_DEBUG_OUTPUT_MACROS_H_ */
