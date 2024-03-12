/**File name "fnSigNmsTestMain.c" comes from:
 * "Fn"=FuNction: http://www.allacronyms.com/function/abbreviated
 * "Sig"=SIGnature: http://www.abbreviations.com/abbreviation/signature
 * Nms=NaMeS: http://www.abbreviations.com/abbreviation/name
 * "Main": contains the "main" function (program entry point)*/
///(c)from 16Sep2023 by Stefan Gebauer(Computer Science Master from TU Berlin)
///@author Stefan Gebauer(TU Berlin:Comp.Sc.Master,matriculation number 361095)

///C(++) standard header files:
 #include <stdio.h>///printf(...)
 #include <stdlib.h>///malloc(...)
 #include <string.h>///strncpy(...)

///http://stackoverflow.com/questions/189972/argument-parsing-helpers-for-c-unix
//#include <argp.h>
///https://stackoverflow.com/questions/9642732/parsing-command-line-arguments-in-c
///https://www.gnu.org/software/libc/manual/html_node/Getopt.html
//#include <unistd.h>///getopt

///Stefan Gebauer's(TU Berlin matriculation number 361095) ~"cmnSrc"repository:
 #include "../../../currFuncSig.h"///TU_Bln361095progLangC_andCppCurrFnSig
 ///TU_Bln361095compilerC_andCppFnSigUse(GetFnNm)(...),
 ///TU_Bln361095compilerC_andCppFnSigUse(GetNmOfClAndOrNmSpc)(...)
 #include "../../../getFnSigNms.h"
/**TU_Bln361095disableUseSecC_RunTimeStrFnWarn,
 * TU_Bln361095enableUseSecC_RunTimeStrFnWarn */
 #include <compiler/C,C++/useSecureC_RunTimeStrFuncsWarn.h>
///TU_Bln361095castToCharPtr
 #include <compiler/GCC/avoid_write_strings_warning.h>
 #include <CstdLib/strcmpRtrnCds.h>///TU_Bln361095CstdLibStrcmpEqlStrs
 /**TU_Bln361095numBforANSIstrTerm0char, TU_Bln361095numBforANSIstrTerm0char
  * preprocessor macro */
 #include <dataType/charStr/strTermChar.h>
 #include <dataType/charStr/stringize.h>///TU_Bln361095expandAndStringize(...)
 #include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(FaststUint);
///TU_Bln361095OpSysProcessCmdLneArgsUse(FirstIdx)
 #include <OperatingSystem/Process/cmdLineArgs.h>

///chr=CHaRacter: http://www.abbreviations.com/abbreviation/character
///Ptr=PoinTeR: http://www.abbreviations.com/abbreviation/pointer
///Typ=TYPe: http://www.abbreviations.com/abbreviation/type
typedef char * chrPtrTyp;///CHaRacter PoinTeR TYPe

/**http://en.wikipedia.org/wiki/Static_variable#Scope :
 * "static":only visible in this compilation unit
 * ENglish EXIT CoDe ANSI*/
static const char * const
///http://en.wikipedia.org/wiki/Exit_status
  enExitCdANSI[]={
  "success:function/namespace/class names as expected",
  "failure:function/namespace/class names mismatch",
  "failed to allocate function name string array",
  "no expected function name given",
  "no expected namespace/class name given"
 };
/**NUMber of EXIT CoDe ARRay ELEmentS*/
#define numExitCdArrEles (sizeof(enExitCdANSI)/sizeof(enExitCdANSI[0]) )
///Exit CoDeS
enum exitCds{sccss=0,nmEqul=0,nmUnEqul=1,nmDiff=1,allocStrArrFaild, 
  noXptdFnNmGvn,///NO expected function name GiVeN
  noXptdNmSpcAndOrClssNmGvn,///no expected namespace/class name given
  unDef};

#define cllFnANSIlit "call function"///CaLL FuNction ANSI LITeral
#define dtSegANSIlit "data segment"///DaTa SEGment ANSI LITeral

/**FunctioN SIGnature AND NaMeS:
 * fn=FunctioN:http://www.allacronyms.com/function/abbreviated
 * Sig=SIGnature:http://www.abbreviations.com/abbreviation/signature
 * Nm=NaMe:http://www.abbreviations.com/abbreviation/name */
struct fnSigAndNms{
  char * fnSig;///FunctioN SIGnature
  char * fnNm;///"fn"=FunctioN "Nm"=NaMe
  char * nmOfNmSpcAndOrCl;///NaMe of NaMeSPaCe AND/OR CLass
};

/**http://en.wikipedia.org/wiki/Static_variable#Scope :
 * "static":only visible in this compilation unit
 * SIGnature AND eXPeCTeD NaMeS of FunctioNS in DATA SEGment*/
static const struct fnSigAndNms
  sigAndXpctdNmsOfFns_DataSeg [] = {
  {TU_Bln361095castToCharPtr
    "std::set<int> outrNmSpc::innrNmSpc::clss::fn(std::set<int> )",
  TU_Bln361095castToCharPtr "fn",
  TU_Bln361095castToCharPtr "outrNmSpc::innrNmSpc::clss"}
};

/**http://en.wikipedia.org/wiki/Static_variable#Scope :
 * "static":only visible in this compilation unit
 * FuNction SIGnature*/
static chrPtrTyp s_fnSig;

/**By making "static inline": avoid GNU (10.3.0) C compiler warning 
 * "warning: '[...]' is static but used in inline function '[...]'
 * which is not static"*/
TU_Bln361095frcSttcInln void printCompilerAndVersion()
{
  printf("Using ");
#ifdef _MSC_VER
  //printf("MicroSoft ")
#endif
#ifdef __GNUC__
  //printf("GNU ");
#endif
#ifdef __cplusplus
  #ifdef CppCompiler
  printf("%s",
    TU_Bln361095expandAndStringize(CppCompiler) );
    #ifdef CppCompilerVersion
  printf(" %s",
    TU_Bln361095expandAndStringize(CppCompilerVersion) );
    #endif
  #endif
  printf(" C++ compiler to get the current function signature from a function "
    "call.\n");
#else///#ifdef __cplusplus
  #ifdef C_compiler
  printf("%s",
    TU_Bln361095expandAndStringize(C_compiler) );
    #ifdef C_compilerVersion
  printf(" %s",
    TU_Bln361095expandAndStringize(C_compilerVersion) );
    #endif
  printf(" C compiler to get the current function signature from a function "
    "call.\n");
  #endif
#endif
}

void outputUsage()
{
  printf("Program to test getting names for function and namespace/class from "
    "function signatures.\n");
  printCompilerAndVersion();
  printf("Command line arguments:\n"
    "-[>>function signature<<"
#ifdef oneCmdLneArgForFn
    ";"
#else
    " "
#endif
    ">>expected function name"
#ifdef oneCmdLneArgForFn
    ";"
#else
    " "
#endif
    "<< [>>expected name(s) of namespace(s),class<<]];\n"
    "-\"" cllFnANSIlit "\":call function(s) for getting their signature(s) &"
     "names\n"
    "-\"" dtSegANSIlit "\":use function signature(s) & names from data segment"
     "\n");
  printf("Program exit/return codes/values:\n");
  for(TU_Bln361095CPUuse(FaststUint) exitCdIdx=0; exitCdIdx <numExitCdArrEles;
    exitCdIdx++)
  {
    printf("%u=%s\n", exitCdIdx, enExitCdANSI[exitCdIdx]);
  }
}

///@param ppStorage pointer to/address of pointer to/address of storage
TU_Bln361095frcInln void assignStr(
  chrPtrTyp * ppStorage,
  const char strToCopy[]
  //const TU_Bln361095CPUuse() numChars
  )
{
  if(*ppStorage !=NULL)
    free(*ppStorage);
  *ppStorage =
    /**Avoid MicroSoft Visual C++ compiler ~'error C2440: "=": "void *" can not
     * be converted to "char *"' by casting.*/
    (chrPtrTyp) malloc(strlen(strToCopy) +
    TU_Bln361095numBforANSIstrTerm0char
    //numChars
    );
  ///Disable warning because array size is safe.
  TU_Bln361095disableUseSecC_RunTimeStrFnWarn
  strcpy(*ppStorage, strToCopy);
  TU_Bln361095enableUseSecC_RunTimeStrFnWarn
}

#define nmSpcAndClBgn(a, b) a :: b

#define fnNmSpcAndClBgn nmSpcAndClBgn(nmSpcAndClBgn("outrNmSpc", "innrNmSpc"), "clss")
#define nmSpcAndCl()

/**Make identifier names as character pointer for dynamic memory allocation or
 * as array with maximum identifier length.*/
static chrPtrTyp
///xpcdFnNm=eXPeCteD FuNction NaMe
  s_xpcdFnNm = NULL;
///xpcdFnNm=eXPeCteD NaMe SPaCe AND OR CLass NaMe
static chrPtrTyp s_xpcdNmSpcNmAndOrClNm = NULL;

#ifdef __cplusplus///If this file is included by a C++(.cpp,.cxx etc.) file.
#include <set>///class std::set
namespace outrNmSpc{namespace innrNmSpc{class clss{
public:
static std::set<int> fn(const std::set<int> & ints)
{
  assignStr(& s_fnSig, TU_Bln361095progLangC_andCppCurrFnSig);
  assignStr(& s_xpcdFnNm, "fn");
  assignStr(& s_xpcdNmSpcNmAndOrClNm, "outrNmSpc::innrNmSpc::clss");
  return ints;
}
};/**class end*/
}}
#endif
void * fn(void * p)
{
  assignStr(& s_fnSig,
    /**avoid "warning: assignment discards 'const' qualifier from pointer target
     * type [-Wdiscarded-qualifiers]*/
    (char*) TU_Bln361095progLangC_andCppCurrFnSig);
  /**Can't use function parameter of this function because it must have at least
   * 2 pointers(for address of a pointer--for example "char **").
   * So use a static or global variable here.*/
  assignStr(& s_xpcdFnNm, "fn");
  assignStr(& s_xpcdNmSpcNmAndOrClNm, "::");
  return NULL;
}

/**@brief Compares function/namespace&class names
 * @param nmTyp function or class/namespace name
 * @param xpctdNm expected name
 * @param nmBgn name begin(1st character)*/
/**Make as "static" function to avoid GNU (version 10.3.0) C compiler warning
 * "warning: '[...]' is static but used in inline function '[...]' which is not
 *  static" */
TU_Bln361095frcSttcInln TU_Bln361095CPUuse(faststUint)
/**"cmp"=CoMPare
 * "Nms"=NaMeS */
  cmpNms(
  const char nmTyp[],
  const char xpctdNm[],
  const char * const nmBgn,
  const char * const nmEnd)
{
  /**Allocate array because for comparing with expected character string there
   * is no character string terminating '\0' character in function signature and
   * it can't be inserted.*/
  const TU_Bln361095CPUuse(FaststUint) numBtoCpy = (TU_Bln361095CPUuse(
    FaststUint))(nmEnd-nmBgn) + TU_Bln361095numBforANSIstrTerm0char;
  char * p_nm = (char*)malloc(numBtoCpy);
  if(! p_nm)
    return allocStrArrFaild;
  ///Disable warning because array size is safe.
  TU_Bln361095disableUseSecC_RunTimeStrFnWarn
  ///http://pubs.opengroup.org/onlinepubs/9699919799/functions/strncpy.html
  strncpy(p_nm, nmBgn, numBtoCpy);
  TU_Bln361095enableUseSecC_RunTimeStrFnWarn
  p_nm[numBtoCpy-1] = '\0';///Set character string terminating value.

  int strcmpRslt;
  strcmpRslt = strcmp(p_nm, xpctdNm);
  if(strcmpRslt == TU_Bln361095CstdLibStrcmpUse(EqlStrs) )
    printf("%s name=\"%s\" matches expected %s name\n", nmTyp, p_nm, nmTyp);
  else
    printf("%s name=\"%s\" mismatches expected %s name \"%s\"\n", nmTyp, p_nm,
      nmTyp, xpctdNm);
  free(p_nm);
  if(strcmpRslt == TU_Bln361095CstdLibStrcmpUse(EqlStrs) )
    return nmEqul;
  return nmUnEqul;
}

/**@brief extracts names from the function signature:
 *  -function name
 *  -class/namespace name(s)
 * @param fnSigOrignStr origin of function signature character string (command
 *  line, function call, data segment)
 *  FunctioN NaMe
 * @return name is expected or not */
/**Make as "static" function to avoid GNU (version 10.3.0) C compiler warning
 * "warning: '[...]' is static but used in inline function '[...]' which is not
 *  static"*/
TU_Bln361095frcSttcInln TU_Bln361095CPUuse(faststUint) extractFnSigNms(
  const char * fnSigOrignStr,///FuNction SIGnature ORIGiN STRing
  const struct fnSigAndNms *
    ///SIGnature AND eXPeCTeD NaMeS of FunctioN
    sigAndXpctdNmsOfFn
  )
{
  char * fnNmEnd;
  printf("function signature from %s:\"%s\"\n", fnSigOrignStr,
    sigAndXpctdNmsOfFn->fnSig);
  const char * const fnNmBgn = TU_Bln361095compilerC_andCppFnSigUse(
    GetFnNm)(
    sigAndXpctdNmsOfFn->fnSig,
    /**Avoid "warning: passing argument [...] of [...] from incompatible
     * pointer type [-Wincompatible-pointer-types]"*/
    (const char **) & fnNmEnd);
  const int cmpFnNmRslt = cmpNms("function", sigAndXpctdNmsOfFn->fnNm, fnNmBgn,
    fnNmEnd);

  char * nmOfClAndOrNmSpcEnd;// = NULL;
  const char * const nmOfClAndOrNmSpcBgn =
    TU_Bln361095compilerC_andCppFnSigUse(GetNmOfClAndOrNmSpc)(fnNmBgn,
    & nmOfClAndOrNmSpcEnd);
  const int cmpFnNmOfClAndOrNmSpcRslt = cmpNms("namespace/class",
    sigAndXpctdNmsOfFn->nmOfNmSpcAndOrCl, nmOfClAndOrNmSpcBgn,
    nmOfClAndOrNmSpcEnd);
  if(cmpFnNmRslt == nmUnEqul || cmpFnNmOfClAndOrNmSpcRslt == nmUnEqul)
    nmUnEqul;
  return nmEqul;
}

///FuNction SIGnature AND NaMeS ORIGiN
enum fnSigAndNmsOrign{
  /**Gets FuNction SIGnature and NaMeS from CoMmanD LiNE.*/
  fnSigAndNmsOrignCmdLne = 0,
  /**Gets FuNction SIGnature and NaMeS from DATA SEGment.*/
  fnSigAndNmsOrignDataSeg,
  /**Gets FuNction SIGnature AND NaMeS via C(++) compiler preprocessor macro
   * from called function.*/
  fnSigAndNmsOrignFnCll,
  /**FuNction SIGnature AND NaMeS not Set yet.*/
  fnSigAndNmsOrignUnset};
///FuNction SIGnature ORIGiN STRingS
static ///lit=LITeral: http://www.allacronyms.com/literal/abbreviated
  const char * fnSigOrignStrs[] = {///CoMmanD LiNE LITeral
   /*cmdLneLit = */"command line",
   ///INTERNal SToRaGE LITeral
   /*internStrgeLit = */"data segment",
/*const char fnCllLit[] = */"function call"};

///@brief Gets FuNction SIGnature AND NaMeS FROM DATA SEGment
/**Make as "static" function to avoid GNU (version 10.3.0) C compiler warning
 * "warning: '[...]' is static but used in inline function '[...]' which is not
 * static"*/
TU_Bln361095frcSttcInln /*enum exitCds*/TU_Bln361095CPUuse(faststUint)
 getFnSigAndNmsFromDataSeg(
  const char strFnSigOrign[],
  const TU_Bln361095CPUuse(faststUint) numFn
  )
{
  for(TU_Bln361095CPUuse(faststUint) fnIdx=0; fnIdx < numFn; fnIdx++)
  {
    TU_Bln361095CPUuse(faststUint) getFnSigNmsRslt = extractFnSigNms(
      strFnSigOrign,
      & sigAndXpctdNmsOfFns_DataSeg[fnIdx]
      );
    if(getFnSigNmsRslt != nmUnEqul)
      return getFnSigNmsRslt;
  }
  return nmEqul;
}

/**Make as "static" function to avoid GNU (version 10.3.0) C compiler warning
 * "warning: '[...]' is static but used in inline function '[...]' which is not
 * static"*/
TU_Bln361095frcSttcInln void assignPtrs(
  struct fnSigAndNms * p_fnSigAndNms)
{
  p_fnSigAndNms->fnSig = s_fnSig;
  p_fnSigAndNms->fnNm = s_xpcdFnNm;
  p_fnSigAndNms->nmOfNmSpcAndOrCl = s_xpcdNmSpcNmAndOrClNm;
}

/**Make as "static" function to avoid GNU (version 10.3.0) C compiler warning
 * "warning: '[...]' is static but used in inline function '[...]' which is not
 * static"*/
TU_Bln361095frcSttcInln void freeMemForAll()
{
  free(s_fnSig);
  free(s_xpcdFnNm);
  free(s_xpcdNmSpcNmAndOrClNm);
}

///@brief Gets FuNction SIGnature AND NaMeS FROM FuNction CALL
/**Make as "static" function to avoid GNU (version 10.3.0) C compiler warning
 * "warning: '[...]' is static but used in inline function '[...]' which is not
 * static"*/
TU_Bln361095frcSttcInln /*enum exitCds*/TU_Bln361095CPUuse(faststUint)
 getFnSigAndNmsFromFnCall(
  const char strFnSigOrign[])
{
  struct fnSigAndNms sigAndXpctdNmsOfFns;
  TU_Bln361095CPUuse(faststUint) getFnSigNmsRslt;
#ifdef __cplusplus
  std::set<int> set;
  set.insert(0);
  outrNmSpc::innrNmSpc::clss::fn(set);
  assignPtrs(& sigAndXpctdNmsOfFns);
/**Alternative to call each function in a loop: use static function in classes
 * and the same parameter lists in every function, make as function pointer
 * array and then iterate over it.*/
  getFnSigNmsRslt = extractFnSigNms(
    strFnSigOrign,
    & sigAndXpctdNmsOfFns);
  if(getFnSigNmsRslt != nmEqul)///Break on first error.
    return getFnSigNmsRslt;
#endif
  fn(0);
  assignPtrs(& sigAndXpctdNmsOfFns);
  getFnSigNmsRslt = extractFnSigNms(
    strFnSigOrign,
    & sigAndXpctdNmsOfFns);
  freeMemForAll();
  return getFnSigNmsRslt;
  //assignFnSigAndTest();
}

typedef const char * cmdLneArgTyp;
/**Avoid GCC "warning: passing argument 2 of 'getFnSigAndNmsFromCmdLne' from
 * incompatible pointer type [-Wincompatible-pointer-types]"*/
#define castToCmdLneArgsTyp (cmdLneArgTyp*)

/**2 more command line arguments:
 * -expected function name
 * -expected namespace/class name*/
#define numAdditionalCmdLneArgs 2

///@brief GETs FuNction SIGnature AND NaMeS FROM CoMmanD LiNE
/**Make as "static" function to avoid GNU (version 10.3.0) C compiler warning
 * "warning: '[...]' is static but used in inline function '[...]' which is not
 *  static"*/
TU_Bln361095frcSttcInln TU_Bln361095CPUuse(faststUint) /*enum exitCds*/
  getFnSigAndNmsFromCmdLne(
  const int cmdLneArgsCnt,
  cmdLneArgTyp cmdLneArgs[],
  const char strFnSigOrign[]
  )
{
  struct fnSigAndNms sigAndXpctdNmsOfFns;
  /**Possibilities for passing function signatures and expected function/
   * namepace&class name:
   * -For every part 1 command line argument
   * -1 command line argument for all, separated by ";" for example */
  for(TU_Bln361095CPUuse(FaststUint) cmdLneArgIdx =
    /**Start at 2nd command line argument because the 1st is the path to
      _this_ program.*/
    1; cmdLneArgIdx
#ifdef oneCmdLneArgForFn
      + numAdditionalCmdLneArgs
#endif
      < (TU_Bln361095CPUuse(FaststUint) )cmdLneArgsCnt;
    cmdLneArgIdx++
    )
  {
#ifdef oneCmdLneArgForFn
    const size_t numChrs = strlen(cmdLneArgs[cmdLneArgIdx]) +
      TU_Bln361095numBforANSIstrTerm0char;
/**Work with copy of command line argument, don't write to it directly because
 * it is in the program environment/(constant) data segment.*/
    char * const fnSigAndXpctdNms = malloc(numChrs);
    if(fnSigAndXpctdNms == NULL)
      return allocStrArrFaild;
    memcpy(fnSigAndXpctdNms, cmdLneArgs[cmdLneArgIdx], numChrs);
    ///Pointer to SEParator CHaRacter
    char * p_sepChr = strchr(fnSigAndXpctdNms, ';');
    if(p_sepChr == NULL)///<=>No semicolon found
      return noXptdFnNmGvn;
    ///Write terminating character to fnSigAndXpctdNms.
    *p_sepChr = TU_Bln361095ANSIstrTerm0char;///function signature end
    sigAndXpctdNmsOfFns.fnSig = fnSigAndXpctdNms;
    sigAndXpctdNmsOfFns.fnNm = p_sepChr + 1;

    p_sepChr = strchr(sigAndXpctdNmsOfFns.fnNm, ';');
    if(p_sepChr == NULL)///<=>No semicolon found
      return noXptdNmSpcAndOrClssNmGvn;
    ///Write terminating character to fnSigAndXpctdNms.
    *p_sepChr = TU_Bln361095ANSIstrTerm0char;///(Expected) function name end
    sigAndXpctdNmsOfFns.nmOfNmSpcAndOrCl = p_sepChr + 1;
#else
    sigAndXpctdNmsOfFns.fnSig = (char *) cmdLneArgs[cmdLneArgIdx++];
    sigAndXpctdNmsOfFns.fnNm = (char *) cmdLneArgs[cmdLneArgIdx++];
    sigAndXpctdNmsOfFns.nmOfNmSpcAndOrCl = (char *) cmdLneArgs[cmdLneArgIdx];
#endif
    int rslt = extractFnSigNms(
      strFnSigOrign,
      & sigAndXpctdNmsOfFns
      );
#ifdef oneCmdLneArgForFn
    free(fnSigAndXpctdNms);
#endif
    if(rslt != nmEqul)///Break loop on first error.
      return rslt;
  }
  return nmEqul;
}

/**@param cmdLneArgs command line arguments from operating system/execution
 *  environment */
int main(
  ///CoMmanD LiNE ARGumentS CouNT
  int cmdLneArgsCnt,
  ///CoMmanD LiNE ARGumentS
  char * cmdLneArgs[])
{
  outputUsage();
  char * strFnSigAndNmsOrign;
  enum fnSigAndNmsOrign fnSigAndNmsOrign =
/**By default solely call the functions and do not get name from command line or
 * data segment because GCC C compiler can't get function name for C++ function
 * signature in ~"TU_Bln361095compilerC_andCppFnSigUse(GetFnNm)(...)" because
 * with GCC's C compiler "the "__PRETTY_FUNCTION__" does not have return value
 * left of function name.*/
    fnSigAndNmsOrignFnCll;
  TU_Bln361095CPUuse(FaststUint) numFn;///NUMber of FuNctions
  if(cmdLneArgsCnt > 1)
  {
    numFn = cmdLneArgsCnt - 1;
    if(strcmp(cmdLneArgs[TU_Bln361095OpSysProcessCmdLneArgsUse(FirstIdx)],
      cllFnANSIlit) == TU_Bln361095CstdLibStrcmpUse(EqlStrs) )
      fnSigAndNmsOrign = fnSigAndNmsOrignFnCll;
    else if(strcmp(cmdLneArgs[TU_Bln361095OpSysProcessCmdLneArgsUse(FirstIdx)],
      dtSegANSIlit) == TU_Bln361095CstdLibStrcmpUse(EqlStrs) )
      fnSigAndNmsOrign = fnSigAndNmsOrignDataSeg;
    else
      fnSigAndNmsOrign = fnSigAndNmsOrignCmdLne;
  }
  if(fnSigAndNmsOrign == fnSigAndNmsOrignUnset)
  {
#ifdef __cplusplus
    fnSigAndNmsOrign = fnSigAndNmsOrignFnCll;
#else
    /**C++ code can't be executed by a C compiler, so use the function signature
     * from data segment/internal storage.*/
    fnSigAndNmsOrign = fnSigAndNmsOrignDataSeg;
    numFn = sizeof(sigAndXpctdNmsOfFns_DataSeg)/sizeof(
      sigAndXpctdNmsOfFns_DataSeg[0]);
#endif
  }
  strFnSigAndNmsOrign = (char *)fnSigOrignStrs[fnSigAndNmsOrign];
  switch(fnSigAndNmsOrign)
  {
  case fnSigAndNmsOrignFnCll:
    return getFnSigAndNmsFromFnCall(strFnSigAndNmsOrign);
  case fnSigAndNmsOrignDataSeg:
    return getFnSigAndNmsFromDataSeg(strFnSigAndNmsOrign, numFn);
  case fnSigAndNmsOrignCmdLne:
    return getFnSigAndNmsFromCmdLne(cmdLneArgsCnt,
      castToCmdLneArgsTyp cmdLneArgs,
      strFnSigAndNmsOrign);
  }
  return unDef;
}
