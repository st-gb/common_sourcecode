#pragma once

namespace ModifiedUTF8
{
  /** http://en.wikipedia.org/wiki/UTF-8#Modified_UTF-8:
   *  "In Modified UTF-8,[21] the null character (U+0000) is encoded as 
   *  0xC0,0x80" */
  const int byteSizeOfTerminatingNullChar = 2;
  void AppendNullCharacter(char * const currendStringEnd )
  {
    currendStringEnd[0] = 0xC0;
    currendStringEnd[1] = 0x80;
  }
}
