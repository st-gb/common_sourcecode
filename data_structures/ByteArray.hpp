#pragma once

#include <string.h> //::strlen(...)

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

  unsigned char * GetArray() const { return m_pchArray; }

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
    const unsigned size = ::strlen(string);
    add( (const unsigned char *) string, size);
  }
};
