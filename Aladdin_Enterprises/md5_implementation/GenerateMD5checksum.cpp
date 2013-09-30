/*
 * GenerateMD5checksum.cpp
 *
 *  Created on: Sep 19, 2013
 *      Author: stefan
 */
#include "GenerateMD5checksum.hpp" //GenerateMD5checkSum_inline(...)

namespace Aladdin_Enterprises
{
  namespace md5_implementation
  {
    void GenerateMD5checkSum(const void * const data, unsigned len,
      unsigned char md5 [])
    {
      GenerateMD5checkSum_inline(data, len, md5);
    }
  }
}
