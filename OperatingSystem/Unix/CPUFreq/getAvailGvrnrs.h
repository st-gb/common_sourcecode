///(c)from 2022 Stefan Gebauer,Computer Science Master(TU Berlin matr.no.361095)
/**@author Stefan Gebauer(TU Berlin matriculation number 361095)*/

///Include guard,see http://en.wikipedia.org/wiki/Include_guard :

/**Bln=BerLiN:http://www.acronymfinder.com/Berlin-(Bln).html
 * Prgm=PRaGMa:
 * Incl=INCLude:http://www.abbreviations.com/abbreviation/include
 * Grd=GuaRD:http://www.abbreviations.com/abbreviation/guard */
#ifdef TU_Bln361095usePrgmInclGrd
/**Non-standard include guard:supported by many, but not all industry compilers:
 * see http://en.wikipedia.org/wiki/Pragma_once#Portability */
  #pragma once
#endif
#if defined TU_Bln361095usePrgmInclGrd ||\
/**Include guard supported by (nearly) all industry compilers:*/\
/**cmn=CoMmoN:http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe:http://www.abbreviations.com/abbreviation/Source
 * OpSys=OPerating SYStem:http://www.abbreviations.com/OPSYS
 * Avail=AVAILable:http://www.abbreviations.com/abbreviation/Available
 * Gvrnrs=GoVeRNoRS*/\
 ! defined TU_Bln361095cmnSrc_OpSys_Unix_CPUFreq_getAvailGvrnrs_h
   #define TU_Bln361095cmnSrc_OpSys_Unix_CPUFreq_getAvailGvrnrs_h

///C standard library header files:
#include <stdio.h>///sprintf(...),fopen(...),fread(...)
#include <stdlib.h>///malloc(...)
#include <string.h>///strcpy(...)

///Stefan Gebauer's(TU Berlin matr.#361095)"common_sourcecode" repository files:
///TU_Bln361095Cstdlib_fseekRtrnCodeUse(success)
#include <C_standard_library/fseek.h>
///TU_Bln361095FlSysUse(GetFileSizeInB)(...)
#include <FileSystem/File/getFileSizeInB.h>
///TU_Bln361095CPUuse(FaststUint)
#include <hardware/CPU/fastest_data_type.h>
///enum TU_Bln361095hardwareDVFSu(DVFS),TU_Bln361095hardwareDVFSd()
//#include <hardware/DVFS.h>
/**availGvrnrsAbsFilePathFmtStr,TU_Bln361095OpSysUnixCPUFreqDef,
 * TU_Bln361095OpSysUnixCPUFreqUse */
#include <OperatingSystem/Unix/CPUFreq/CPUFreq.h>
#include <OperatingSystem/GetLastErrorCode.hpp>///

#define maxNumDecDigitsFor16BitInt 5///2^16=65536
#define maxNumDecDigitsFor16BitIntPlusTerm0Char (maxNumDecDigitsFor16BitInt + \
  /**1 character string terminating 0 ('\0') character*/1)

/**Use these preprocessor macros in source code for example to enable both C and
 * C++. */
#ifdef __cplusplus
/**Def=definition: http://www.abbreviations.com/abbreviation/definition
 * Put definition between "[...]NmSpcBgn" and "[...]NmSpcEnd" #define'd below.*/
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(suffix)\
    suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space*/
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpc\
    TU_Bln361095OpSysUnixCPUFreqNmSpc :: GetAvailGvrnrs :: Rslt
///Bgn=BeGiN: http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpcBgn\
    TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpcBgn namespace\
     GetAvailGvrnrsRslt{
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpcEnd\
    /** "}" times >>number of namespaces<< */\
    TU_Bln361095OpSysUnixCPUFreqNmSpcEnd }}
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(suffix)\
    TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpc :: suffix
#else
///Def=definition: http://www.abbreviations.com/abbreviation/definition
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(suffix)\
    TU_Bln361095cmnSrcOpSysUnixCPUFreqDef(GetAvailGvrnrsRslt##suffix)
//    TU_Bln361095cmnSrcOpSysUnixCPUFreqGetAvailGvrnrsRslt ## suffix
/**Nm=name: http://www.abbreviations.com/abbreviation/name
 * Spc=space: http://www.abbreviations.com/abbreviation/Space */
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpc /**->empty*/
///Bgn=BeGiN :http://www.allacronyms.com/begin/abbreviated
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpcBgn /**->empty*/
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpcEnd /**->empty*/
  #define TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(suffix)\
   TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(suffix)
#endif

TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpcBgn

enum TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(E){
  ///SuCCeSS
  TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(Sccss),
  ///OPeN FiLe FAILeD
  TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(OpnFlFaild),
  ///GET FiLe SiZe FAILeD
  TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(GetFlSzFaild),
  ///ReaD FiLe FAILeD
  TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(RdFlFaild),
  ///ALLOCating MEMory FAILeD
  TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(AllocMemFaild),
  ///SeeK FiLe FAILeD
  TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltDef(SkFlFaild)
};

///English message for getting available governors result, ANSI version
//extern char * TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltEnMsgsA[];
extern char * TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(EnMsgsA)[];

TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltNmSpcEnd

TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcBgn

/**@brief gets available CPUFreq governors (Dynamic voltage and frequency
 *  scaling types).
 * 
 *  Must be declared "static inline" to avoid:
 *  -multiple definitions of this fuction
 *  -"undefined reference" to this fuction
 * @param p_numGvrnrs number of governors=number of elements in array \ref
 *  p_availGvrnrsArr
 * @param p_availGvrnrsArr address of character string array to fill inside this
 *   function
 * //return array of governor name character strings 
 * @return result (success or error code) */
static inline /*char ** */enum
  TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(E)
//  TU_Bln361095CPUuse(FaststUint)
  TU_Bln361095cmnSrcOpSysUnixCPUFreqDef(GetAvailGvrnrs)(
  const TU_Bln361095CPUuse(FaststUint) CPUcoreID,
  TU_Bln361095CPUuse(FaststUint) * const p_numGvrnrs,
//  enum TU_Bln361095OpSysUnixCPUFreqUse(GetAvailGvrnrsRslt) *
//    p_getAvailGvrnrsRslt
  char *** p_availGvrnrsArr//,
//  int * p_errorCode
  )
{
  ///fl=file Nm=name
  char availGvrnrsAbsFilePath[/*sizeof*/strlen(
    TU_Bln361095cmnSrcOpSysUnixCPUFreqUse(availGvrnrsAbsFilePathFmtStr) ) +
    maxNumDecDigitsFor16BitIntPlusTerm0Char];
  sprintf(availGvrnrsAbsFilePath, TU_Bln361095cmnSrcOpSysUnixCPUFreqUse(
    availGvrnrsAbsFilePathFmtStr),CPUcoreID);
  FILE * p_availGvrnrsFile =
  /** http://pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html :
   * "Upon successful completion, [...]  Otherwise, a null pointer shall be
   * returned." */
    fopen(availGvrnrsAbsFilePath,
    ///gnu.org/software/gnulib/manual/html_node/fopen.html
/** pubs.opengroup.org/onlinepubs/9699919799/functions/fopen.html :
 * "r or rb Open file for reading."*/
    "r");
  if(p_availGvrnrsFile == NULL)
    return TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(OpnFlFaild);

  long int numBtoRead;
  //TODO lock file before to avoid changing file contents before getting file
  // size and reading?:
//  const int availGvrnrsFileDesc = fileno(p_availGvrnrsFile);
//  (TU_Bln361095FlSysUse(FlLckWrt)(availGvrnrsFileDesc);

  if(TU_Bln361095cmnSrcFlSysUse(GetFileSizeInB)(p_availGvrnrsFile, &numBtoRead)
    != TU_Bln361095cmnSrcFlSysGetFlSzUse(Success) )
  {
    fclose(p_availGvrnrsFile);
    return TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(GetFlSzFaild);
  }
  char flBuf[numBtoRead];
  ///Set to "success" to ensure an error code comes from "fread" function.
//    TU_Bln361095OpSys(SetLastErrorCode)(TU_Bln361095OpSysErrorCode(Success) );
  const size_t numReadB =
/** http://pubs.opengroup.org/onlinepubs/007904975/functions/fread.html :
 * section "RETURN VALUE":
 * "Upon successful completion, fread() shall return the number of elements
 * successfully read which is less than nitems only if a read error or
 * end-of-file is encountered. If size or nitems is 0, fread() shall return 0
 * and the contents of the array and the state of the stream remain unchanged.
 * Otherwise, if a read error occurs, the error indicator for the stream shall
 * be set, [...]  and errno shall be set to indicate the error. [...]" */
    fread(flBuf, 1/**element size*/,/*fileSizeInB+1*/
    numBtoRead/**count*/, p_availGvrnrsFile);
  TU_Bln361095CPUuse(FaststUint) lastOSerrorCd = TU_Bln361095cmnSrcOpSysUse(
    GetLastErrorCode)();
  if(numReadB < numBtoRead && lastOSerrorCd != 0
    //TU_Bln361095OpSysErrorCodes(Success)
    )
  {
    fclose(p_availGvrnrsFile);
    return TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(RdFlFaild);
  }
  //TODO may have read too few bytes
  // (numReadB < numBtoRead && lastOSerrorCd == 0).
  TU_Bln361095CPUuse(FaststUint) numGvrnrs = 0;
  for(TU_Bln361095CPUuse(FaststUint) chrIdx = 0; chrIdx < /*numBtoRead*/
    numReadB; chrIdx++)
  {
    if(flBuf[chrIdx] == ' '){
      numGvrnrs++;
/**Set to character string terminating NULL character for strlen(...) to detect
 * the character string end.*/
      flBuf[chrIdx] = '\0';
    }
  }
  if(flBuf[numReadB - 1] == '\n'){
    numGvrnrs++;
/**Set to character string terminating NULL character for strlen(...) to detect
 * the character string end.*/
    flBuf[numReadB - 1] = '\0';
  }
  *p_numGvrnrs = numGvrnrs;
  char ** availGvrnrsArr = (char **) malloc(numGvrnrs +
    /**1 element for NULL entry*/1);
  if(availGvrnrsArr == NULL)///Allocating memory failed.
  {
    fclose(p_availGvrnrsFile);
    return TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(AllocMemFaild);
  }
  availGvrnrsArr[numGvrnrs] = NULL;///Mark array end.
  char * currChrIdx = flBuf;
  for(TU_Bln361095CPUuse(FaststUint) gvrnrIdx = 0; gvrnrIdx < numGvrnrs;
    gvrnrIdx++)
  {
    TU_Bln361095CPUuse(FaststUint) numGvrnrChrs = strlen(currChrIdx);
    availGvrnrsArr[gvrnrIdx] = (char*) malloc(numGvrnrChrs +
      /**1 character string terminating 0 ('\0') character*/1);
    if(availGvrnrsArr[gvrnrIdx] == NULL)///Allocating memory failed.
    {
      free(availGvrnrsArr);
      for(TU_Bln361095CPUuse(FaststUint) gvrnrIdx2 = 0; gvrnrIdx2 < gvrnrIdx;
        gvrnrIdx2++)
        free(availGvrnrsArr[gvrnrIdx2]);
      fclose(p_availGvrnrsFile);
      return TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(AllocMemFaild);
    }
    strcpy(availGvrnrsArr[gvrnrIdx], currChrIdx);
    currChrIdx += numGvrnrChrs + 1;
  }
  * p_availGvrnrsArr = availGvrnrsArr;
///Seek file to begin afterwards for the next time to read from file begin.
  if(fseek(p_availGvrnrsFile, 0, SEEK_SET) !=
    TU_Bln361095CstdLib_fseekRtrnCodeUse(Success) ){
//    p_errorCode = errno;
    fclose(p_availGvrnrsFile);
    return TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(SkFlFaild);
  }
  ///fclose(p_availGvrnrsFile);
  return TU_Bln361095OpSysUnixCPUFreqGetAvailGvrnrsRsltUse(Sccss);
}

TU_Bln361095cmnSrcOpSysUnixCPUFreqNmSpcEnd

#endif///Include guard