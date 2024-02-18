/**Do not put these file's functions into "currFnSig.h" because _here_ also
 * function and class/namespace name from non-current function signatures should
 * be able to be exctracted.
 * Created on: 19.12.2012 */
/**(c)from 2023:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)
 * @author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard
/**Define on compiler command line,for example for GCC:
 * (see http://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html :)
 * "gcc -D TU_Bln361095UsePrgmInclGuard"*/
/**Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude: http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD: http://www.abbreviations.com/abbreviation/Guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**TU=Technical University
 * Bln=BerLiN: http://www.acronymfinder.com/Berlin-(Bln).html
 * Fn/Fun/Func=FUNCtion: http://www.allacronyms.com/function/abbreviated
 * Sig=SIGnature: http://www.abbreviations.com/abbreviation/signature */\
 !defined TU_Bln361095compiler__C_andCpp__fnSig__getNames_h
  #define TU_Bln361095compiler__C_andCpp__fnSig__getNames_h

///C(++) standard library header files:
 #include <assert.h>//assert(...)

///Stefan Gebauer's(TU Berlin matriculation number 361095) ~"cmnSrc" repo files:
 /**TU_Bln361095compilerC_andCppNmSpc, TU_Bln361095compilerC_andCppNmSpcBgn,
  * TU_Bln361095compilerC_andCppNmSpcEnd */
 #include<compiler/C,C++/C,C++ID_prfx.h>
 ///TU_Bln361095numBforANSIstrTerm0char preprocessor macro
 #include<dataType/charStr/numBforStrTerm0char.h>

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095compilerC_andCppFnSigDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095compilerC_andCppFnSigNmSpc\
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace >>this #define'd namespace<<" */\
    TU_Bln361095compilerC_andCppNmSpc :: FnSig
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095compilerC_andCppFnSigNmSpcBgn\
    TU_Bln361095compilerC_andCppNmSpcBgn namespace FnSig{
  #define TU_Bln361095compilerC_andCppFnSigNmSpcEnd\
      TU_Bln361095compilerC_andCppNmSpcEnd }
  #define TU_Bln361095compilerC_andCppFnSigUse(suffix)\
    TU_Bln361095compilerC_andCppFnSigNmSpc :: suffix
#else///C compiler
  #define TU_Bln361095compilerC_andCppFnSigDef(suffix)\
    TU_Bln361095compilerC_andCppFnSig##suffix
  #define TU_Bln361095compilerC_andCppFnSigNmSpcBgn
  #define TU_Bln361095compilerC_andCppFnSigNmSpcEnd
  #define TU_Bln361095compilerC_andCppFnSigUse(suffix)\
    TU_Bln361095compilerC_andCppFnSigDef(suffix)
#endif

TU_Bln361095compilerC_andCppFnSigNmSpcBgn
{
  {
  }


//means : global scope (no namespame names)
static const char TU_Bln361095progLangCandCppGlobSculpOper []= "::";

/** GCC's __PRETTY_FUNCTION__ format is:
 * >>return type<< [namespace::]>>class name<< "::"
 * >>function name<< >>parameters list (only data type, no identifiers )<<
 * Works with GCC ("__PRETTY_FUNCTION__") and maybe with MSVC ("__FUNCSIG__").
 * @param fnNmBgn begin of function name
 * @param nmOfClAndOrNmSpcEnd end of class/namespace name
 * @return begin of class/namespace name
 Cl=CLass: http://www.allacronyms.com/class/abbreviated */
//TODO can't distiguish between class and namespace name only by signature
// because all may be namespace names and classes may have inner classes.
inline const char * const
 TU_Bln361095compilerC_andCppFnSigDef(/*GetClOrNmSpcNm*/GetNmOfClAndOrNmSpc)(
  const char * const fnNmBgn,
  char ** const nmOfClAndOrNmSpcEnd
  )
{
  /**Search backwards from the function name begin because searching from the begin
   * is more difficult for __FUNCSIG__ because class constructors have no return type
   * so only a character string comparison can determine if the first " "-delimited 
   * string is the return type or the calling convention
   * (http://en.wikipedia.org/wiki/Calling_convention). */
  const char * spcChr1BfrFnNmBgn = fnNmBgn;
  while(*--spcChr1BfrFnNmBgn != ' ');
  if(spcChr1BfrFnNmBgn == fnNmBgn - 1)
  {
    *nmOfClAndOrNmSpcEnd = 
      /**Cast to "char *" to avoid MicroSoft Visual Studio "warning C4090: "=":
       * Different "const" qualifiers"*/
      (char*)
      TU_Bln361095progLangCandCppGlobSculpOper + //(char *)
      (
      (sizeof(TU_Bln361095progLangCandCppGlobSculpOper)-
        TU_Bln361095numBforANSIstrTerm0char) /
      sizeof(char)
      )
      ;
    return TU_Bln361095progLangCandCppGlobSculpOper;
  }
  *nmOfClAndOrNmSpcEnd =
    /**Cast to "char *" to avoid MicroSoft Visual Studio "warning C4090: "=":
     * Different "const" qualifiers"*/
    (char * const)
    fnNmBgn - 2;
  return spcChr1BfrFnNmBgn+1;

/**@brief Gets the begin of the function name.
 * @param p_fnNmEnd pointer to end of function name within function signature
 *  (via __FUNCSIG__ or __PRETTY_FUNCTION__ see file "currFuncSig.h"
 * @return pointer to function name begin */
inline const char * getFnNmBgn(
  const char * const p_fnNmEnd)
{
  const char * p_fnNmBgn = p_fnNmEnd - 1;
  ///Search backwards for begin of leftmost name of class/namespace/function
  /**Assumes that before the function name there is always a space
   * character(" ") or colon(":") */
  for(; /*p_fnNmBgn > currFnSig*/; --p_fnNmBgn)
  {
    switch(*p_fnNmBgn)
    {
    case ':':
    case ' ':
      p_fnNmBgn = p_fnNmBgn + 1;
      return p_fnNmBgn;
    }
  }
  return p_fnNmBgn;
}

/**@param fnSig : function signature. Works with GCC's __PRETTY_FUNCTION__ format:
 * >>return type<< [namespace::]>>class name<< "::"
 * >>function name<< >>parameters list (only data type, no identifiers )<<
 * Works with GCC ("__PRETTY_FUNCTION__") and with MSVC ("__FUNCSIG__").
 * @param p_fnNmEnd
 *  out:address of/pointer to a pointer to the function name end
 *  character. The address of the pointer is changed inside this function
 * @return pointer to the 1st character of the function name inside \p fnSig */
inline const char * const TU_Bln361095compilerC_andCppFnSigDef(GetFnNm)(
  const char fnSig[],
  const char ** p_fnNmEnd)
{
  *p_fnNmEnd = strchr(fnSig,'(');///Search for 1st/leftmost '('
  assert(*p_fnNmEnd != NULL);
  const char * p_fnNmBgn = getFnNmBgn(*p_fnNmEnd);
  return p_fnNmBgn;
}

TU_Bln361095compilerC_andCppFnSigNmSpcEnd

#endif///include guard
