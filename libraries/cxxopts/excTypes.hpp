///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Bln=BerLiN
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/Guard*/
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#else
///Include guard supported by (nearly) all industry compilers:
  #ifndef TU_Bln361095cmnSrc_cxxopts_excTypes_hpp
  #define TU_Bln361095cmnSrc_cxxopts_excTypes_hpp
#endif

namespace TU_Bln360195{namespace cxxopts{
#if CXXOPTS__VERSION_MAJOR > 2
/**Exception names changed from cxxopts::argument_incorrect_type at 12 Jul 2022
 * (see git history) Unfortunately the cxxopts version did not change at this
 * time.*/
  typedef cxxopts::exceptions::incorrect_argument_type incorrArgTypeExc;
  typedef cxxopts::exceptions::exception mostGenericExc;
#else
  typedef cxxopts::argument_incorrect_type incorrArgTypeExc;
  typedef cxxopts::OptionException mostGenericExc;
#endif
}}

#ifndef TU_Bln361095usePrgmInclGrd
#endif///#ifndef TU_Bln361095cmnSrc_cxxopts_excTypes_hpp
#endi