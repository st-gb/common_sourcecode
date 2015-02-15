#pragma once

#ifdef __cplusplus
namespace C_standard_library
{
  namespace strcmp
  {
    /*** http://pubs.opengroup.org/onlinepubs/009695399/functions/strcmp.html :
     * Upon completion, strcmp() shall return an integer greater than, equal to,
     * or less than 0, if the string pointed to by s1 is greater than, equal to,
     * or less than the string pointed to by s2, respectively.*/
    enum { firstStringIsLess = -1 , stringsAreEqual, firstStringIsGreater};
  }
};
#endif
