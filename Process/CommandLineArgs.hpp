/*
 * CommandLineArgs.hpp
 *
 *  Created on: 09.02.2013
 *      Author: Stefan
 */

#ifndef COMMANDLINEARGS_HPP_
#define COMMANDLINEARGS_HPP_

#include <limits.h> //UINT_MAX

template<typename charType> class CommandLineArgs
{
  unsigned m_argumentCount;
  charType ** m_stringArray; //array (1st "*") of strings (2nd "*")
  charType * fullProgramPath;
public:
  enum ArgIndices { FullProgramPathArgIndex = 0};
  CommandLineArgs() {};
  CommandLineArgs(int argc, charType ** stringArray)
    : m_argumentCount(argc), m_stringArray(stringArray)
  {
    fullProgramPath = stringArray[FullProgramPathArgIndex];
  }
  charType * GetFullProgramPath()
  {
    return fullProgramPath;
  }
  charType ** const GetStringArray() const { return m_stringArray; }
  void Set(int argc, charType * stringArray[])
  {
    m_argumentCount = argc;
    m_stringArray = stringArray;
    fullProgramPath = stringArray[FullProgramPathArgIndex];
  }
  /** @return UINT_MAX for inequality */
  unsigned contains(charType * compareString)
  {
    charType * string;
    unsigned charIndex;
    for(unsigned stringIndex = 0; stringIndex < m_argumentCount; ++ stringIndex)
    {
      string = m_stringArray[stringIndex];
//      if( _tcscmp( ) == 0
      charIndex = 0;
      while( string[charIndex] != 0 && string[charIndex] ==
          compareString[charIndex] )
      {
        ++ charIndex;
      }
//      if( charIndex > 0)
//      {
//        -- charIndex;
        //If last characters are equal
        if( string[charIndex] == compareString[charIndex] )
          return stringIndex;
//      }
    }
    return UINT_MAX;
  }
};

#endif /* COMMANDLINEARGS_HPP_ */