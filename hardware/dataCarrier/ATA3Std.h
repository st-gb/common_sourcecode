///(c)from 2020:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
///Created ca.01.7.2020 by Stefan Gebauer(TU Berlin matriculation number 361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
///Include guard supported by (nearly) all industry compilers:
#ifndef TU_Berlin361095cmnSrcATA3Std_h
#define TU_Berlin361095cmnSrcATA3Std_h

///Standard C header files:
#include <stdint.h>///uint8_t

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
#include <hardware/CPU/atomic/AtomicExchange.h>///AtmcXchgTyp

///see http://www.t13.org/ ATA attachment
/**see http://www.scs.stanford.edu/11wi-cs140/pintos/specs/ata-3-std.pdf
 * -"7.7.13 Word 23-26: Firmware revision"
 + -"The contents of this field is an ASCII character string of eight bytes."*/
#define TU_Bln361095hardwareSMARTnumFWbytes 8///words 23-26 = 4 words each 2 bytes, p.53
/**see http://www.scs.stanford.edu/11wi-cs140/pintos/specs/ata-3-std.pdf
 * -"7.7.14 Words 27-46: Model number"
 * -"The contents of this field is an ASCII character string of forty bytes."*/
#define TU_Bln361095hardwareSMARTnumModelBytes 40///27-46 = 20 words each 2 bytes
/**see http://www.scs.stanford.edu/11wi-cs140/pintos/specs/ata-3-std.pdf
 * -"7.7.9 Words 10-19: Serial number"
 * -"The contents of this field is an ASCII character string of twenty bytes."*/
#define TU_Bln361095hardwareSMARTnumSNbytes 20///words 10-19 = 20 bytes

///https://en.wikipedia.org/wiki/S.M.A.R.T.#Known_ATA_S.M.A.R.T._attributes :
/// v. 23:34, 1. Jun. 2020 : "raw value [...] has 48 bits"
#define TU_Bln361095hardwareATA_SMARTnumSMARTrawValB 6
///https://en.wikipedia.org/wiki/S.M.A.R.T. :1 till 254 = 254 different
#define TU_Bln361095dataCarrierNumSATA_SMARTattrIDs 254
/**see
http://en.wikipedia.org/wiki/Self-Monitoring,_Analysis_and_Reporting_Technology
 * #Known_NVMe_S.M.A.R.T._attributes : 1 till 15=15*/
#define TU_Bln361095dataCarrierNumNVMeSMARTattrIDs 15
/** http://en.wikipedia.org/wiki/S.M.A.R.T.#ATA_S.M.A.R.T._attributes
 * "The initial default value of attributes is 100 but can vary between
 * manufacturer.[17]" Default normalized value is 100:*/
#define ATA3Std_DfltNrmlzdVal 100
/**For 40 GB HDD model "WDC WD400EB-00CPF0", firmware "06.04G06" (,serial number
 * "WD-WCAAT4328734" at Power-On Time raw value "5667") for S.M.A.R.T. attribute
 * IDs 1, 5, 7, 196-200 the normalized current value was 200. So the maximum
 * current value >= 200.*/
#define ATA3Std_GtrDfltNrmlzdVal 200

/** http://en.wikipedia.org/wiki/S.M.A.R.T.#ATA_S.M.A.R.T._attributes : "[...]
 * normalized value, which ranges from 1 to 253"-> 1 byte is sufficient*/
typedef /*AtmcXchgTyp*/uint8_t ATA3Std_NrmlzdValTyp;

#endif///#ifndef TU_Berlin361095cmnSrcATA3Std_h