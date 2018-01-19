/** GetDirContents.h
 *  Created on: 17.01.2018
 *      Author: s.gebauer  */

#ifndef GETDIRCONTENTS_HPP_
#define GETDIRCONTENTS_HPP_

#include <vector> //class std::vector
#include <string> //class std::string

namespace FileSystem {

unsigned GetDirContents(
  const char * const dirToRetrieveContentsFrom,
  std::vector<std::string> & );

}

#endif /* GETDIRCONTENTS_HPP_ */

