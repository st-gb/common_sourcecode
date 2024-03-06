/**File name "getFnSigNms" comes from:
 * -Fn=FuNction: http://www.allacronyms.com/function/abbreviated
 * -Sig=SIGnature: http://www.abbreviations.com/abbreviation/signature
 * -Nms=NaMeS: http://www.abbreviations.com/abbreviation/name
 * Do not put these file's functions into "currFnSig.h" because _here_ also
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
 !defined TU_Bln361095compiler__C_andCpp__getFnSigNms_h
  #define TU_Bln361095compiler__C_andCpp__getFnSigNms_h

///C(++) standard library header files:
 #include <assert.h>//assert(...)

///Stefan Gebauer's(TU Berlin matriculation number 361095) ~"cmnSrc" repo files:
 /**TU_Bln361095compilerC_andCppNmSpc, TU_Bln361095compilerC_andCppNmSpcBgn,
  * TU_Bln361095compilerC_andCppNmSpcEnd */
 #include<compiler/C,C++/C,C++ID_prfx.h>
 #include<compiler/force_inline.h>///TU_Bln361095frcInln
 ///TU_Bln361095numBforANSIstrTerm0char preprocessor macro
 #include<dataType/charStr/strTermChar.h>

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

//means : global scope (no namespame names)
static const char TU_Bln361095progLangCandCppGlobSculpOper []= "::";

TU_Bln361095frcSttcInln const char * useSculpOperator(
  char ** const pp_nmOfClAndOrNmSpcEnd)
{
  ///Derefer to store pointer to/address of character string end.
  *pp_nmOfClAndOrNmSpcEnd = 
    /**Cast to "char *" to avoid MicroSoft Visual Studio "warning C4090: "=":
     * Different "const" qualifiers"*/
    (char*)
    TU_Bln361095progLangCandCppGlobSculpOper + //(char *)
    (///<=>number of characters
    (sizeof(TU_Bln361095progLangCandCppGlobSculpOper)///"sizeof"=number of bytes
      - TU_Bln361095numBforANSIstrTerm0char) /
    sizeof(char)
    )
    ;
  return TU_Bln361095progLangCandCppGlobSculpOper;
}

/**@brief Gets the whole namespace&class name within function signature.
 *  This may be the _current_ function signature (GNU C Compilers's
 *  "__PRETTY_FUNCTION__", MicroSoft Visual C++'s "__FUNCSIG__", ...) or another
 *  /previous function signature. See file ~"compiler/C,C++/currFuncSig.h" for
 *  the format of "__PRETTY_FUNCTION__" and "__FUNCSIG__".
 * @param fnNmBgn [in] pointer to begin(1st character) of function name
 * @param nmOfClAndOrNmSpcEnd [out] address of pointer to end (last/rightmost
 *  character) of class/namespace name
 *  If for example "AAAA" is the address of the character string end and "BBBB"
 *  is the address where "AAAA" should be stored, then "BBBB" is passed as value
 *  here and dereferenced later for storing "AAAA" in it.
 * @return pointer to 1st/leftmost character of class/namespace name */
//TODO can't distiguish between class and namespace name only by signature
// because all may be namespace names and classes may have inner classes.

TU_Bln361095frcSttcInln const char * const
 TU_Bln361095compilerC_andCppFnSigDef(/*GetClOrNmSpcNm*/
/**Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Cl=CLass: http://www.abbreviations.com/abbreviation/class
 * Spc=SPaCe: http://www.abbreviations.com/abbreviation/space */
   GetNmOfClAndOrNmSpc)(
  const char * const fnNmBgn,
  char ** const nmOfClAndOrNmSpcEnd
  )
{
#if defined __cplusplus
/**Search backwards from the first/leftmost function name character because:
 * -searching from the function signature begin is more difficult for Microsoft
 *  Visual C++'s "__FUNCSIG__" preprocessor macro (see file
 *  ~"compiler/C,C++/currFuncSig.h") because class constructors have no return
 *  type so only a character string comparison can determine if the first " "-
 *  delimited string is the return type or the calling convention(
 *  http://en.wikipedia.org/wiki/Calling_convention) in order to skip them.
 * -the return type may have namespace/class names/sculp operators */
  const char * spcChr1BfrFnNmBgn = fnNmBgn;
  while(*--spcChr1BfrFnNmBgn != ' ');
  if(spcChr1BfrFnNmBgn == fnNmBgn - 1)///<=>No class/namespace name before.
  {
    return useSculpOperator(nmOfClAndOrNmSpcEnd);
  }
  *nmOfClAndOrNmSpcEnd =
    /**Cast to "char *" to avoid MicroSoft Visual Studio "warning C4090: "=":
     * Different "const" qualifiers"*/
    (char * const)
    fnNmBgn - 2;
  return spcChr1BfrFnNmBgn+1;
#else///No namespace or class names because "C" programming language.
  return useSculpOperator(nmOfClAndOrNmSpcEnd);
#endif
}

/**@brief Gets the begin of the function name.
 * @param p_fnNmEnd pointer to the last/rightmost character of function name
 *   within function signature.
 *  May be the _current_ function signature (GNU C Compilers's
 *  "__PRETTY_FUNCTION__", MicroSoft Visual C++'s "__FUNCSIG__", ...) or another
 *  /previous function signature. See file ~"compiler/C,C++/currFuncSig.h" for
 *  the format of "__PRETTY_FUNCTION__" and "__FUNCSIG__".
 * @return pointer to function name begin */
TU_Bln361095frcInln const char *
/**Fn=FuNction: http://www.abbreviations.com/abbreviation/function
 * Nm=NaMe: http://www.abbreviations.com/abbreviation/name
 * Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated */
  getFnNmBgn(
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
    case ':':///sculp operator ("::") of class or namespace name
    case ' ':
      p_fnNmBgn = p_fnNmBgn + 1;
      return p_fnNmBgn;
    }
  }
  return p_fnNmBgn;
}

//TODO the identifier before a function name may also be a namespace name?!
/**@brief gets the function via pointers to its 1st and last character
 * @param fnSig : function signature. May be the _current_ function signature
 *  (GNU C Compilers's "__PRETTY_FUNCTION__", MicroSoft Visual C++'s
 *  "__FUNCSIG__", ...) or another/previous function signature. See file
 *  ~"compiler/C,C++/currFuncSig.h" for the format of "__PRETTY_FUNCTION__" and
 *  "__FUNCSIG__".
 * @param p_fnNmEnd
 *  [out] address of/pointer to a pointer to the last/rightmost character of
 *   function name. The address of the pointer to this character is changed
 *   inside this function
 *  A pointer to the last function name character needs to be provided to get
 *   the end of function name because the character right of it can't be set to
 *   '\0' to signalize string end (then pogram crash?) if for example \p fnSig
 *   is "__FUNCSIG__" from Microsoft Visual C++.
 * @return pointer to the 1st character of the function name inside \p fnSig */
TU_Bln361095frcInln const char * const TU_Bln361095compilerC_andCppFnSigDef(
  /**Fn=FuNction: http://www.abbreviations.com/abbreviation/function
   * Nm=NaMe: http://www.abbreviations.com/abbreviation/name */
  GetFnNm)(
  const char fnSig[],
  const char ** p_fnNmEnd)
{
#if defined __cplusplus
  #define TU_Bln361095compilerFnSigSearchForBracket
#else
  #ifndef __GNUC__
    #define TU_Bln361095compilerFnSigSearchForBracket
  #endif
#endif
#if defined TU_Bln361095compilerFnSigSearchForBracket
  *p_fnNmEnd =
/**http://pubs.opengroup.org/onlinepubs/9699919799.orig/functions/strchr.html
 * "The strchr() function shall locate the first occurrence of c (converted to
 * a char) in the string pointed to by s. The terminating NUL character is
 * considered to be part of the string.
 * RETURN VALUE : "Upon completion, strchr() shall return a pointer to the byte,
 * or a null pointer if the byte was not found."*/
    strchr(fnSig,'(');///Search for 1st/leftmost '('
  assert(*p_fnNmEnd != NULL);
  const char * p_fnNmBgn = getFnNmBgn(*p_fnNmEnd);
#else///In GNU C the function signature is the same as the function name.
  *p_fnNmEnd = fnSig + strlen(fnSig);
  const char * p_fnNmBgn = fnSig;
#endif
  return p_fnNmBgn;
}

TU_Bln361095compilerC_andCppFnSigNmSpcEnd

#endif///include guard
