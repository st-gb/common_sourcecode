/*
 * SynchronizeFileStatus.hpp
 *
 *  Created on: Nov 17, 2010
 *      Author: Stefan
 */

#ifndef SYNCHRONIZEFILESTATUS_HPP_
#define SYNCHRONIZEFILESTATUS_HPP_

namespace MFC
{
  void SynchronizeFilesStatus(
    const CFileStatus & fileStatusSource,
    CFileStatus & fileStatusDestination,
    bool & bFilePropertiesAreDifferent,
    bool & bFileContentMayBeModified
    ) ;
}
#endif /* SYNCHRONIZEFILESTATUS_HPP_ */
