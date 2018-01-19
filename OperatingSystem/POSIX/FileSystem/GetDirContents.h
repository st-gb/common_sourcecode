/** GetDirContents.h
 *  Created on: 23.12.2015
 *      Author: s.gebauer  */

#ifndef GETDIRCONTENTS_H_
#define GETDIRCONTENTS_H_

#ifdef __cplusplus

extern "C" {
#endif

/*char * */ unsigned GetDirContents(
  const char * const dirToRetrieveContentsFrom,
  char * p_ch,
  unsigned * p_numFilesOrDirs);

#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif /* GETDIRCONTENTS_H_ */
