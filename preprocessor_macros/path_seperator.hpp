/*
 * path_seperator.hpp
 *
 *  Created on: Nov 8, 2012
 *      Author: sgebauer
 */

#ifndef PATH_SEPERATOR_HPP_
#define PATH_SEPERATOR_HPP_

#ifdef _WIN32
  #define PATH_SEPERATOR_CHAR '\\'
//#endif
#else
//#ifndef __linux__
  #define PATH_SEPERATOR_CHAR '/'
#endif

#endif /* PATH_SEPERATOR_HPP_ */
