/**(c) Stefan Gebauer,Computer Science Master(TU Berlin,matric.number 361095)
 * @author Stefan Gebauer:TU Berlin matriculation number 361095*/

///Include guard, see http://en.wikipedia.org/wiki/Include_guard :

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
/**Bln=BerLiN: https://www.acronymfinder.com/Berlin-(Bln).html
 * cmn=CoMmoN: http://www.abbreviations.com/abbreviation/common
 * Src=SouRCe: http://www.abbreviations.com/abbreviation/Source */\
 ! defined TU_Bln361095cmnSrc__data_structures__ByteArray_hpp
   #define TU_Bln361095cmnSrc__data_structures__ByteArray_hpp

///C(++) standard header files:
 #include <string.h>///strlen(),memcpy(...)

///Stefan Gebauer's(TU Berlin matricul. num. 361095) ~"cmnSrc" repository files:
 ///TU_Bln361095dataStructuresNmSpcBgn, TU_Bln361095dataStructuresNmSpcEnd
 #include <data_structures/dataStructs_ID_prefix.h>
 #include <hardware/CPU/fastest_data_type.h>///TU_Bln361095::CPU::faststUint

/** This class may e.g. hold the bytes of an UTF-8 string. */
class ByteArray
{
  /** The actual number of bytes used. */
  unsigned m_size;
  /** The number of bytes allocated for the array. 
   *  It is doubled if the array needs to be enlarged. */
  unsigned m_capacity;
  unsigned char * m_pchArray;
public:
  ByteArray()
    :
      m_size(0),
      m_capacity(512)//,
//      m_pchArray(0)
  {
    m_pchArray = new unsigned char[m_capacity];
  }

  ByteArray(const unsigned capacity)
    :
      m_size(0),
      m_capacity(capacity)//,
//      m_pchArray(0)
  {
    m_pchArray = new unsigned char[capacity];
  }

  /** Copy constructor. */
  ByteArray(const ByteArray & orig)
    :
      m_size(orig.GetSize() ),
      m_capacity(orig.GetCapacity() )//,
//      m_pchArray(0)
  {
    m_pchArray = new unsigned char[m_capacity];
    ::memcpy(m_pchArray, orig.GetArray(), m_size);
  }

  ~ByteArray()
  {
    delete [] m_pchArray;
    m_pchArray = NULL;
  }

  unsigned GetCapacity() const
  {
    return m_capacity;
  }

  unsigned GetSize() const
  {
    return m_size;
  }

  void setSize(unsigned newSizeInBytes) { m_size = newSizeInBytes; }

  unsigned char * GetArray() const { return m_pchArray; }
  
  void SetCapacity(const fastestUnsignedDataType newCapacity)
  {
    unsigned char * newArray = new unsigned char[newCapacity];
    ::memcpy(newArray, m_pchArray, m_size);
    delete [] m_pchArray; /** Free memory for current array*/
    m_pchArray = newArray;
    m_capacity = newCapacity;
    m_size = newCapacity;
  }

  void add(const unsigned char * arrayToAdd, const unsigned size)
  {
    const unsigned minSize = m_size + size;
    if( minSize > m_capacity )
    {
      do
      {
        m_capacity *= 2;
      }while( minSize > m_capacity );

      unsigned char * newArray = new unsigned char[m_capacity];
      ::memcpy(newArray, m_pchArray, m_size);
      delete [] m_pchArray;
      m_pchArray = newArray;
    }
    ::memcpy( (m_pchArray + m_size), arrayToAdd, size);
    m_size += size;
  }

  void add(const char * const string)
  {
    const /*unsigned*/
      ///Use the same return data type as in "strlen" to avoid compiler warning.
      size_t numStrChars = ::strlen(string);
    add( (const unsigned char *) string, numStrChars);
  }
};
