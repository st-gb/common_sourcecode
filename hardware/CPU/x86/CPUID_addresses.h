#ifndef CPUID_SPECS
#define CPUID_SPECS

#define VENDOR_ID_INDEX 0x0
//http://en.wikipedia.org/wiki/CPUID#EAX.3D1:_Processor_Info_and_Feature_Bits:
#define PROCESSOR_INFO_AND_FEATURE_BITS 0x1
/** 4 byte per CPUID register * 4 CPUID registers (EAX,EBX,ECX,EDX) */
#define NUMBER_OF_CPUID_REGISTER_BYTES 16
//http://en.wikipedia.org/wiki/CPUID
// #EAX.3D80000002h.2C80000003h.2C80000004h:_Processor_Brand_String:
//"48-byte null-terminated ASCII processor brand string."
// 4 byte per CPUID register * 4 CPUID registers (EAX,EBX,ECX,EDX) * 3 CPUID
//  functions/ addresses = 4*4*3=16*3=48 byte
#define CPUID_PROCESSOR_NAME_CHAR_NUMBER 48
#define GET_HIGHEST_EXTENDED_FUNCTION_SUPPORTED 0x80000000
#define EXTENDED_L2_CACHE_FEATURES 0x80000006
#define FIRST_PROCESSOR_BRAND_STRING_INDEX 0x80000002
#define LAST_PROCESSOR_BRAND_STRING_INDEX 0x80000004

#endif //#ifndef CPUID_SPECS
