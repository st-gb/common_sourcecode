#pragma once //Include guard.

#include <windef.h> //for BYTE etc.

//other compilers than Microsoft's usually do not know the following.
#ifndef _MSC_VER //If not MicroSoft C compiler.
//#if __GNUC__ < 4 &&
  //Definitions from MSVCs Windows v7.0a winnt.h:
//  typedef enum _LOGICAL_PROCESSOR_RELATIONSHIP {
//      RelationProcessorCore,
//      RelationNumaNode,
//      RelationCache,
//      RelationProcessorPackage,
//      RelationGroup,
//      RelationAll = 0xffff
//  } LOGICAL_PROCESSOR_RELATIONSHIP;
//
//  typedef enum _PROCESSOR_CACHE_TYPE {
//      CacheUnified,
//      CacheInstruction,
//      CacheData,
//      CacheTrace
//  } PROCESSOR_CACHE_TYPE;
//
//  typedef struct _CACHE_DESCRIPTOR {
//      BYTE   Level;
//      BYTE   Associativity;
//      WORD   LineSize;
//      DWORD  Size;
//      PROCESSOR_CACHE_TYPE Type;
//  } CACHE_DESCRIPTOR, *PCACHE_DESCRIPTOR;
//
//  typedef struct _SYSTEM_LOGICAL_PROCESSOR_INFORMATION {
//      ULONG_PTR   ProcessorMask;
//      LOGICAL_PROCESSOR_RELATIONSHIP Relationship;
//      union {
//          struct {
//              BYTE  Flags;
//          } ProcessorCore;
//          struct {
//              DWORD NodeNumber;
//          } NumaNode;
//          CACHE_DESCRIPTOR Cache;
//          ULONGLONG  Reserved[2];
//      } DUMMYUNIONNAME;
//  } SYSTEM_LOGICAL_PROCESSOR_INFORMATION,
//    * PSYSTEM_LOGICAL_PROCESSOR_INFORMATION;
//#endif
#endif //#ifndef _MSC_VER

namespace Windows
{
//  enum error_codes{ no_GetLogicalProcessorInformation_fct = 60000};
  WORD GetNumberOfLogicalCPUcores() ;
};
