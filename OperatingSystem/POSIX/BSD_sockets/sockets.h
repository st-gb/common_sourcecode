///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
///Elementary BSD sockets stuff goes into this file.*/

///Include guard, see http://en.wikipedia.org/wiki/Include_guard
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
//#pragma once
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Bln361095cmnSrcOpSysPOSIX_BSDskt_skt_h
#define TU_Bln361095cmnSrcOpSysPOSIX_BSDskt_skt_h

///Stefan Gebauer's(TU Berlin matr.no.361095)common_sourcecode repository files:
#include <compiler/force_inline.h>///TU_Bln361095frcInln
///TU_Bln361095BSDsktDef,TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd
#include <socket.h>

TU_Bln361095BSDsktNmSpcBgn

/**Force inlining to avoid multiple definitions of the same function if included
 * more than once for the same link target.*/
TU_Bln361095frcInln int TU_Bln361095BSDsktDef(
  ///bgn=begin:http://www.allacronyms.com/begin/abbreviated
  Bgn)(){return 0;}
/**Force inlining to avoid multiple definitions of the same function if included
 * more than once for the same link target.*/
TU_Bln361095frcInln void TU_Bln361095BSDsktDef(End)(){}

TU_Bln361095BSDsktNmSpcEnd

#endif///#define TU_Bln361095cmnSrcOpSysPOSIX_BSDskt_skt_h
