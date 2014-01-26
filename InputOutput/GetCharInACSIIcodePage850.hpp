#pragma once

#include "ASCIIcodepage850.hpp" //ASCIIcodepage850

inline char GetCharInASCIIcodePage850(int ch)
{
  switch (ch)
  {
  //case 195: //11000011bin
  //  break;
  //see http://www.utf8-zeichentabelle.de/unicode-utf8-table.pl?number=1024&htmlent=1
  case 164: //10100100bin
    return ASCIIcodepage850::ae /*'�'*/;
  case 0xb6:
    return ASCIIcodepage850::oe ; //'�';
  case 0xbc:
    return ASCIIcodepage850::ue ;//'�';
  case 0x9f:
    return ASCIIcodepage850::sz ;//'�';
  case 0x84:
    return ASCIIcodepage850::Ae; //'�';
  case 0x96:
    return ASCIIcodepage850::Oe; //'�';
  case 0x9c:
    return ASCIIcodepage850::Ue; //'�';
  }
  return 0;
}
