/*
 * GnuPG.hpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */

#ifndef GNUPG_HPP_
#define GNUPG_HPP_

namespace GnuPG
{
  enum retval
  {
    STARTING_ECRYPTION_PROCESS_SUCCEEDED ,
    ERROR_STARTING_ECRYPTION_PROCESS
  };
  enum eCreateFileNameWithAppendedTimeFirst
  {
    ONLY_IF_NOT_EXISTANT ,
    ALWAYS
  };
}

#endif /* GNUPG_HPP_ */
