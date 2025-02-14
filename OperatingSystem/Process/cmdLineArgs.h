/**File name "cmdLneArgs" comes from:CoMmanD LiNE ARGumentS
 * (c) from 09.02.2013 by Stefan Gebauer(Computer Science Master from TU Berlin)
 * @author: Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
  /**Include guard supported by (nearly) all industry compilers:*/\
/**Bln=BerLiN:https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPeratingSYStem:
 *  http://www.abbreviations.com/abbreviation/operating%20system
 * cmd=CoMmanD: http://www.abbreviations.com/abbreviation/command
 * Lne=LiNE
 * Args=ARGUmentS: http://www.abbreviations.com/abbreviation/argument */\
 ! defined TU_Bln361095cmnSrc__OpSys__Process__cmdLneArgs_h
   #define TU_Bln361095cmnSrc__OpSys__Process__cmdLneArgs_h

///Stefan Gebauer's(TU Berlin matric. number 361095) ~"cmnSrc" repository files:
 /**TU_Bln361095OpSysProcessNmSpc, TU_Bln361095OpSysProcessNmSpcEnd,
  * TU_Bln361095OpSysProcessNmSpcBgn */
 #include <OperatingSystem/Process/OpSysProcess_ID_prefix.h>
 #include <compiler/force_inline.h>///TU_Bln361095frcInln
 #include <hardware/CPU/fastest_data_type.h>///TU_Bln361095CPUuse(FaststUint)

/**Use these preprocessor macros in source code for example to enable both C and
 * C++.*/
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysProcessCmdLneArgsDef(suffix) suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095OpSysProcessCmdLneArgsNmSpc\
    TU_Bln361095OpSysProcessNmSpc ::\
/**Do not append "::" right of the rightmost namespace name to enable
 * "using namespace >>this #define'd namespace<<" */\
    CmdLneArgs
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysProcessCmdLneArgsNmSpcBgn\
    TU_Bln361095OpSysProcessNmSpcBgn namespace CmdLneArgs{
  #define TU_Bln361095OpSysProcessCmdLneArgsNmSpcEnd\
      TU_Bln361095OpSysProcessNmSpcEnd }
  #define TU_Bln361095OpSysProcessCmdLneArgsUse(suffix)\
    TU_Bln361095OpSysProcessCmdLneArgsNmSpc :: suffix
#else///C compiler
  #define TU_Bln361095OpSysProcessCmdLneArgsDef(suffix)\
    TU_Bln361095OpSysProcessDef(CmdLneArgs##suffix)
  #define TU_Bln361095OpSysProcessCmdLneArgsNmSpc/**empty*/
  #define TU_Bln361095OpSysProcessCmdLneArgsNmSpcBgn/**empty*/
  #define TU_Bln361095OpSysProcessCmdLneArgsNmSpcEnd/**empty*/
  #define TU_Bln361095OpSysProcessCmdLneArgsUse(suffix)\
    TU_Bln361095OpSysProcessCmdLneArgsDef(suffix)
#endif

TU_Bln361095OpSysProcessCmdLneArgsNmSpcBgn

enum TU_Bln361095OpSysProcessCmdLneArgsDef(Idxs){
/**Not necessarily the absolute/full path: may also be a relative path.*/
  TU_Bln361095OpSysProcessCmdLneArgsDef(ProgPathIdx) = 0,
  /**When equal to this value: only program path(not process arguments)*/
	TU_Bln361095OpSysProcessCmdLneArgsDef(FirstIdx) = 1,
	TU_Bln361095OpSysProcessCmdLneArgsDef(NoProcessArgs) = 1
  };

TU_Bln361095OpSysProcessCmdLneArgsNmSpcEnd

#ifdef __cplusplus
///C(++) standard library header files:
 #include <limits.h>///UINT_MAX http://pubs.opengroup.org/onlinepubs/9699919799/
//#include <>
 #include <stddef.h>///NULL

TU_Bln361095OpSysProcessNmSpcBgn

///@tparam charType may be "char" or "wchar_t" for example
template<typename charType> class CmdLineArgs
{
private:
  TU_Bln361095CPUuse(FaststUint) m_argCnt;
  charType ** m_cmdLneArgs;///array (1st "*") of strings (2nd "*")
  //TODO Always the full program path or also relative program path(s)?
  charType * m_fullProgPath;
public:
  typedef std::basic_string<charType> string_type;

  CmdLineArgs() {};
  /**@param argCnt number of command line arguments
   * @param cmdLneArgs as array(first "*") of character string(second "*") */
  CmdLineArgs(const int argCnt, const charType ** const cmdLneArgs)
    : m_argCnt(argCnt), m_cmdLneArgs(cmdLneArgs)
  {
    m_fullProgPath = m_cmdLneArgs[TU_Bln361095OpSysProcessCmdLneArgsUse(
      ProgPathIdx)];
  }

  ///@return the number of command line arguments
  TU_Bln361095frcInln TU_Bln361095CPUuse(FaststUint) getArgCnt() const{
    return m_argCnt;}
  
  //TODO if a std::basicstream would be returned then an empty string could
  //  determine an error as command line args always consist of at least 1
  //  character
  /** @return
   *   -NULL: array index out of range
   *   -else command line argument at index \p argIdx */
  TU_Bln361095frcInln const charType * /*string_type*/ getArg(
    const TU_Bln361095CPUuse(FaststUint) argIdx) const
  {
//	  string_type string;
    if(argIdx < m_argCnt )
    {
      return m_cmdLneArgs[argIdx];
    }
    return NULL;
  }

  TU_Bln361095frcInln charType * getProgPath() const
  {
    return m_fullProgPath;
  }
//  charType * GetExeFileName()
//  {
//    string_type strfullProgramPath(fullProgramPath);
//    strfullProgramPath.rfind()
//    return fullProgramPath;
//  }
  TU_Bln361095frcInln charType ** const getCmdLneArgs() const {return
    m_cmdLneArgs;}

  TU_Bln361095frcInln void set(const int argCnt,
    const charType * const cmdLneArgs[])
  {
    m_argCnt = argCnt;
    m_cmdLneArgs = cmdLneArgs;
    m_fullProgPath = cmdLneArgs[TU_Bln361095OpSysProcessCmdLneArgsUse(
      ProgPathIdx)];
  }

  /**@strToCmp character string to look for within command line arguments
   *  member variable
   * @return command line argument index of \p strToCmp or UINT_MAX if \p
   *  strToCmp is not within command line arguments.*/
  TU_Bln361095frcInln TU_Bln361095CPUuse(FaststUint) getCmdLneArgIdx(
    const charType * const strToCmp
    ) const
  {
    charType * cmdLneArg;
    ///Idx=InDeX: http://www.abbreviations.com/abbreviation/index
    TU_Bln361095CPUuse(FaststUint) charIdx;
    for(TU_Bln361095CPUuse(FaststUint) argIdx = 0; argIdx < m_argCnt; ++ argIdx)
    {
      cmdLneArg = m_cmdLneArgs[argIdx];
//      if( _tcscmp( ) == 0
      for(charIdx = 0; cmdLneArg[charIdx] == strToCmp[charIdx]; ++ charIdx)
      {
        /**If 0-terminating character (character string end).
         * <=>Character strings are equal.*/
        if(cmdLneArg[charIdx] == '\0')
          return argIdx;
      }
    }
    return UINT_MAX;
  }

  TU_Bln361095frcInln bool contains(
    const charType * const strToSearch)
    const
  {
    return getCmdLneArgIdx(strToSearch) != UINT_MAX;
  }
};

TU_Bln361095OpSysProcessNmSpcEnd

#endif///#ifdef __cplusplus

#endif///include guard
