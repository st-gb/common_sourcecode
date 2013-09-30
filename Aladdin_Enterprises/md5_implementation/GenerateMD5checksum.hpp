/*
 * GenerateMD5checksum.hpp
 *
 *  Created on: Sep 19, 2013
 *      Author: stefan
 */

#ifndef GENERATEMD5CHECKSUM_HPP_
#define GENERATEMD5CHECKSUM_HPP_

#include "md5.h"

#define NUM_MD5_BYTES 16

namespace Aladdin_Enterprises
{
  namespace md5_implementation
  {
    /** TODO do an (md5) chechsum over the model data that with the same members
    * as in the dyn lib.
    * -Prevent changing the model data by this executable (e.g. via GUI or via getting
    * data from service)
    * compare with the md5 sum done in the DLL */
    inline void GenerateMD5checkSum_inline(const void * const data, unsigned len,
      unsigned char md5 [])
    {
      md5_state_t state;
    //  md5_byte_t digest[16];
    //  char hex_output[16*2 + 1];
    //  int di;

      md5_init(&state);
      md5_append(&state, (const md5_byte_t *)data, len);
      md5_finish(&state, /*digest*/ md5);
    }
    void GenerateMD5checkSum(const void * const data, unsigned len,
      unsigned char md5 []);
  }
}

#endif /* GENERATEMD5CHECKSUM_HPP_ */
