#pragma once  //include guard

#include <attributes/disassemble/Operand.hpp>

/** https://en.wikipedia.org/wiki/Data_structure_alignment#x86
 * "Typical alignment of C structs on x86" :
 * struct MyData {
    short Data1;
    short Data2;
    short Data3; };
 *  "Data1 would be at offset 0, Data2 at offset 2, and Data3 at offset 4." */
  #pragma pack(push)  /* push current alignment to stack */
  /** Set alignment to 1 byte boundary (default: size of CPU archictecture?)
   * This is important for reading a struct from a (device) file. */
  #pragma pack(1)

  struct low2Byte{
    uint8_t highByte;
    uint8_t lowByte;
  };
  union _16bitRegister {
    uint16_t high2Bytes;
    struct low2Byte _low2Byte;
  };

  struct FourByte{
    _16bitRegister __16bitRegister;
    uint16_t highBytes;
  };

  /** see http://www.cs.virginia.edu/~evans/cs216/guides/x86.html */
  union _32bitRegister
  {
    struct FourByte fourByte;
    uint32_t _32bitValue;
  } ;
#pragma pack(pop) /** restore original alignment from stack */

/** The class models a CPU and can e.g. be used to */
class CPUregisters
{
public:
  unsigned ZeroFlag;
//  EAX, EBX, ECX, EDX;  AX, BX, CX, DX
  _32bitRegister ExtendedAccumulator, EBX, ECX, EDX, m_ExtendedStackPointer,
    m_ExtendedSourceIndex;
  /** see http://www.tenouk.com/Bufferoverflowc/Bufferoverflow1a.html
   *  segment reigsters have a size of 16 bit */
  uint16_t m_CodeSegment, m_DataSegment, m_StackSegment;

//  uint8_t AH, AL, BH, BL, CH, CL, DH, DL;

  CPUregisters()
    //: ExtendedAccumulator(0), EBX(0), ECX(0), EDX(0)
    : m_DataSegment(0)
  {
    ExtendedAccumulator._32bitValue = 0;
    EBX._32bitValue = 0;
    ECX._32bitValue = 0;
    EDX._32bitValue = 0;
    m_ExtendedSourceIndex._32bitValue = 0;
    ZeroFlag = 0;
  }

  inline void CoMPare(void * p_leftOperandRegisterAddress,
    unsigned registerByteWidth, uint32_t data)
  {
    switch( registerByteWidth)
    {
      case 1 :
        * ( (uint8_t *) p_leftOperandRegisterAddress) -= data;
        /** https://www.hellboundhackers.org/articles/read-article.php?article_id=729:
         * "The zero flag is set whenever the result of the subtraction is
         *  equal to zero." */
        if( *( (uint8_t *) p_leftOperandRegisterAddress) == 0 )
          ZeroFlag = 1;
        //"The sign flag is set when the result of the subtraction is negative."
        break;
    }
  }

  inline unsigned getRegisterByteWidth(const std::string & registerName) const {
    const unsigned registerNameLength = registerName.length();
    if( registerNameLength > 1 )
    {
      const char lastChar = registerName.substr(registerNameLength - 1, 1).c_str()[0];
      const char secondFromLastChar = registerName.substr(
        registerNameLength - 1, 1).c_str()[0];
      switch( lastChar )
      {
        case 'l' : // "l" = "Low Byte",
        case 'h' : // 'h'=High Byte
          return 1;
        case 'i' : /** si=Stack Index */
          return 2;
        case 's' : /** ds=Data segment, cs=Code segment, ... */
          return 2;
        case 'x' : // eax, ax
          if( registerNameLength == 2) //ax, bx, cx, dx
            return 2;
          else if ( registerNameLength == 3) // eax, edx, ecx, edx
            return 4;
        case 'p' : //(e)bp, (e)sp
          switch( secondFromLastChar )
          {
            case 's' : // esp, sp
              if(registerNameLength == 2)
                return 2;
              else
                return 4;
          }
      }
    }
    return 0;
  }

  inline void * getRegisterAddressFromName(const std::string & registerName) const {
    unsigned numChars = registerName.length();
    if( numChars > 1 )
    {
      const char secondFromLastChar = registerName.substr(numChars - 2, 1)[0];
      const char lastChar = registerName.substr(numChars - 1, 1)[0];
      const _32bitRegister * p_32bitRegister;
      const unsigned registerByteWidth = getRegisterByteWidth(registerName);
      /** e.g. "aL", "aH", "eaX" */
      if( lastChar == 'h' || lastChar == 'l' || lastChar == 'x' )
        switch( secondFromLastChar)
        {
          case 'a' :
            p_32bitRegister = & ExtendedAccumulator;
            break;
          case 'b' :
            p_32bitRegister = & EBX;
            break;
          case 'c' :
            p_32bitRegister = & ECX;
            break;
          case 'd' :
            p_32bitRegister = & EDX;
            break;
        }
      else
      {
        if(registerName == "ds" )
          return (void *) & m_DataSegment;
        if(registerName == "ss" )
          return (void *) & m_StackSegment;
        if( registerName == "esi" || registerName == "si" )
          p_32bitRegister = & m_ExtendedSourceIndex;
      }
      if( p_32bitRegister )
      {
        switch( registerByteWidth )
        {
          case 4 :
            return (void *) & p_32bitRegister->_32bitValue;
            break;
          case 2 :
            return (void *) & p_32bitRegister->fourByte.__16bitRegister.high2Bytes;
          case 1 :
            const char lastChar = registerName.substr(numChars - 1, 1)[0];
            switch(lastChar)
            {
              case 'l' :
                return (void *) & p_32bitRegister->fourByte.__16bitRegister.
                  _low2Byte.lowByte;
              case 'h' :
                return (void *) & p_32bitRegister->fourByte.__16bitRegister.
                  _low2Byte.highByte;
            }
        }
      }
//      if( registerName == "dl" )
//        return .__16bitRegister._low2Byte.lowByte;
    }
    return NULL;
  }

  inline unsigned getValue(char * registerName ) const
  {
    uint32_t * p = (uint32_t *) getRegisterAddressFromName(registerName);
    if( p)
      return *p;
    return 0xFFFF;
  }

  inline void test(
    signed leftValue, signed rightValue//,
  //  x86_op_t & op1, x86_op_t & op2,
//    CPUregisters & _CPUregisters
    )
  {
    /** https://en.wikipedia.org/wiki/TEST_%28x86_instruction%29 :
     * "performs a bitwise AND on two operands. The flags SF, ZF, PF
     * are modified while the result of the AND is discarded. The
     * OF and CF flags are set to 0, while AF flag is undefined." */
  //  signed leftValue = getValue(op1);
  //  signed rightValue = getValue(op2);

    /** "If the result of the AND is 0, the ZF is set to 1" */
    signed result = leftValue & rightValue;
    ZeroFlag = result == 0;
  }
};

