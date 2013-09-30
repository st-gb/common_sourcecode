/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany
 * ("Trilobyte SE") 2010-at least 2012.
 * You are allowed to modify and use the source code from Trilobyte SE for free
 * if you are not making profit directly or indirectly with it or its adaption.
 * Else you may contact Trilobyte SE. */
/*
 * ILogFileWriter.cpp
 *
 *  Created on: 26.04.2012
 *      Author: Stefan
 */

#include "Controller/Logger/Formatter/I_LogFormatter.hpp"
//#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
#include <limits.h> //SHRT_MAX
//#include <Controller/Logger/Logger.hpp> //class Logger
#include <Controller/Logger/OutputHandler/I_LogEntryOutputter.hpp>
#include <Controller/Logger/Appender/FormattedLogEntryProcessor.hpp>

//I_LogFormatter::I_LogFormatter()
//{
//  // TODO Auto-generated constructor stub
//
//}
//e.g. { -> '{'
#define MAKE_ANSI_CHAR(x) ' ## x ## '

//32xxx = 5 characters
#define NUMBER_OF_CHARS_FOR_MAX_2_BYTE_VALUE_IN_DEC 5
#define PLACE_HOLDER_BEGIN_SIGN /*'%'*/ {
//#define PLACE_HOLDER_BEGIN_CHAR /*'%'*/ MAKE_ANSI_CHAR(PLACE_HOLDER_BEGIN_SIGN)
#define PLACE_HOLDER_BEGIN_CHAR /*'%'*/ '{'
#define PLACE_HOLDER_BEGIN_STRING /*'%'*/ "{"
#define PLACE_HOLDER_END_CHAR /*'%'*/ '}'
#define PLACE_HOLDER_END_STRING /*'%'*/ "}"

const std::string I_LogFormatter::s_std_strDefaultLinuxLogTimeFormatString =
  "{year}.{month}.{day} {hour}:{minute}:{second}s{millisecond}ms{microsecond}us";
const std::string I_LogFormatter::s_std_strDefaultWindowsLogTimeFormatString =
  "{year}.{month}.{day} {hour}:{minute}:{second}s{millisecond}ms";

I_LogFormatter::I_LogFormatter(//std::ofstream * p_std_ofstream
//  const I_LogEntryOutputter * outputhandler
  const FormattedLogEntryProcessor * p_formattedlogentryprocessor
  )
  :
//    m_p_outputhandler(outputhandler),
    m_p_formattedlogentryprocessor(p_formattedlogentryprocessor),
    m_p_chTimeString(NULL),
    m_nodetrieTimePlaceHolderToLogFileEntryMember(256, NULL)
{
  m_p_std_ostream = //p_std_ofstream;
    /*m_p_outputhandler*/ p_formattedlogentryprocessor->GetStdOstream();
  m_p_logfileentry = /* & m_p_outputhandler*/
    p_formattedlogentryprocessor->GetLogFileEntry();
  m_TimeFormatString =
    PLACE_HOLDER_BEGIN_STRING "year" PLACE_HOLDER_END_STRING
    "-" PLACE_HOLDER_BEGIN_STRING "month" PLACE_HOLDER_END_STRING "-"
    PLACE_HOLDER_BEGIN_STRING "day" PLACE_HOLDER_END_STRING "&nbsp;"
    PLACE_HOLDER_BEGIN_STRING "hour" PLACE_HOLDER_END_STRING ":"
    PLACE_HOLDER_BEGIN_STRING "minute" PLACE_HOLDER_END_STRING ":"
    PLACE_HOLDER_BEGIN_STRING "second" PLACE_HOLDER_END_STRING "s"
    PLACE_HOLDER_BEGIN_STRING "millisecond" PLACE_HOLDER_END_STRING "ms";
  m_p_chTimeString = (char *) m_TimeFormatString.c_str();
  CreateTimePlaceHolderToLogFileEntryMemberMapping();
}

I_LogFormatter::~I_LogFormatter()
{
//  if( m_p_chTimeString )
//    delete [] m_p_chTimeString;
//  DeleteTimePlaceHolderToLogFileEntryMemberNodeTrie();
  m_nodetrieTimePlaceHolderToLogFileEntryMember.DeleteWithMember();
//  LOGN_INFO("m_dwNumberOfNodes for PlaceHolderToLogFileEntryMember trie:"
//    << m_nodetrieTimePlaceHolderToLogFileEntryMember.getNumberOfNodes() )
}

/** Data structure filled is used in "GetNeededArraySizeForTimeString()" */
void I_LogFormatter::CreateTimePlaceHolderToLogFileEntryMemberMapping()
{
  std::string str = "year";
  //for initalizing a struct:
  //http://stackoverflow.com/questions/330793/how-to-initialize-a-struct-in-ansi-c99
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    //(PointerToLogFileEntryMemberAndNumFormatChars)
    new PointerToLogFileEntryMemberAndNumFormatChars(4,& m_p_logfileentry->year) );
  str = "month";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(2,& m_p_logfileentry->month) );
  str = "day";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(2,& m_p_logfileentry->day) );
  str = "hour";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(2,& m_p_logfileentry->hour) );
  str = "minute";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(2,& m_p_logfileentry->minute) );
  str = "second";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(2,& m_p_logfileentry->second) );
  str = "millisecond";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(3,
      & m_p_logfileentry->millisecond) );
  str = "microsecond";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(3,
      & m_p_logfileentry->microsecond) );
  str = "nanosecond";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    new PointerToLogFileEntryMemberAndNumFormatChars(3,
      & m_p_logfileentry->nanosecond) );
}

/** Before formatting the numbers to string the maximum size of the resulting
 * time format strings needs to be known else the array could be either
 * -to small->needs to be enlarged -> costs CPU time
 * -too large: wastes memory */
uint16_t I_LogFormatter::GetNeededArraySizeForTimeString(
  const std::string & timeFormatString)
{
//  NodeTrieNode<const uint16_t *> * p_ntn;
  NodeTrieNode<PointerToLogFileEntryMemberAndNumFormatChars *> * p_ntn;
  uint16_t currentCharIndex = 0;
  uint16_t charIndexOfPlaceholderBeginChar = SHRT_MAX;
  uint16_t arraySizeForTimeString = 0;
  unsigned numCharsBetweenPlaceholderChars;
  int charIndexOfPlaceholderEndChar = 0;
  BYTE numCharsInBetween;
  BYTE percentPairIndex = 0;
  const char * const c_p_chTimeFormatStringBegin = timeFormatString.c_str();
  const char * c_p_chTimeFormatStringCurrentChar = timeFormatString.c_str();

  //Important, because it may be filled from a call from before.
  m_vecPointerToTimeElementFromLogFileEntry.clear();

  while( * c_p_chTimeFormatStringCurrentChar )
  {
    if( * c_p_chTimeFormatStringCurrentChar == PLACE_HOLDER_BEGIN_CHAR )
    {
//      if( IndexOfLeftPercentSign == SHRT_MAX ) // left "%"
//      {
        charIndexOfPlaceholderBeginChar = currentCharIndex;
        // "begin...%placeholder%" and "%placeholder%...%placeholder%"
        numCharsBetweenPlaceholderChars = charIndexOfPlaceholderBeginChar -
          charIndexOfPlaceholderEndChar - 1;
        arraySizeForTimeString += numCharsBetweenPlaceholderChars;
    }
//      bPercentSignFound = true;
//      else //-> right "%" belonging to left "%"
    else if( * c_p_chTimeFormatStringCurrentChar == PLACE_HOLDER_END_CHAR )
    {
      //chars between left "%" and right "%" from %placeholder%"
      numCharsInBetween = currentCharIndex - charIndexOfPlaceholderBeginChar - 1;
      charIndexOfPlaceholderEndChar = currentCharIndex;

      p_ntn = m_nodetrieTimePlaceHolderToLogFileEntryMember.contains_inline(
        (BYTE *) (c_p_chTimeFormatStringBegin + charIndexOfPlaceholderBeginChar + 1),
        numCharsInBetween,
        true);
      if( p_ntn //&& p_ntn->m_member
          )
      {
        const uint16_tPointerAndBYTE logFilePlaceHolder(
          p_ntn->m_member,
          numCharsInBetween + 2,
//              percentPairIndex
          charIndexOfPlaceholderBeginChar//,
          );
        m_vecPointerToTimeElementFromLogFileEntry.push_back(
          logFilePlaceHolder
          );
        arraySizeForTimeString +=
          NUMBER_OF_CHARS_FOR_MAX_2_BYTE_VALUE_IN_DEC;
      }
      else
        arraySizeForTimeString += numCharsInBetween;
      charIndexOfPlaceholderBeginChar = SHRT_MAX;
      ++ percentPairIndex;
    }
//    }
    ++ currentCharIndex;
    ++ c_p_chTimeFormatStringCurrentChar;
  }
//  if( IndexOfLeftPercentSign != SHRT_MAX )
  //-> placeholder end char or any placeholder char in string
  if( charIndexOfPlaceholderBeginChar == SHRT_MAX )
  {
    //either:
    // - # of chars of "..." in "%placeholder%"...end"
    // - if no "%" in whole string: # of chars of whole string
    arraySizeForTimeString += timeFormatString.length() -
      //# chars right of "%"
      charIndexOfPlaceholderEndChar - 1;
  }
  else //left "%"
//    if( IndexOfRightPercentSign > IndexOfLeftPercentSign)
      // # of chars of "..." in "%xxx"...end"
    arraySizeForTimeString += timeFormatString.length() -
        //# chars right of "%" plus 1 char for "%"
      charIndexOfPlaceholderBeginChar;
  return arraySizeForTimeString;
}

/** Defined because it should be faster
 * -e.g. by "inline"
 * -not setting a string terminating '\0'
 * than a call to a string formatting function.
 * @return # of chars written*/
inline uint16_t uint16tToCharArray(uint16_t ui16Number, //char ar_ch[6]
  char * ar_ch)
{
  static BYTE index;
  static BYTE digit;
  static uint16_t divisor;
  static bool bAtLeast1DigitWritten;
  static const char digitCharacters[] =
    { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };

  index = 0;
  if( ! ui16Number )
    ar_ch[index ++] = '0';
  else
  {
    divisor = 10000;
    bAtLeast1DigitWritten = false;
    while(divisor )
    {
      digit = ui16Number / divisor;
      if( digit ) // <> 0
      {
        ar_ch[index ++] = digitCharacters[digit];
        ui16Number -= digit * divisor;
        bAtLeast1DigitWritten = true;
      }
      else // 0
        //e.g. if a zero after a non-zero left from it like "30", "305"
        if( bAtLeast1DigitWritten
          //! ui16Number
          )
          ar_ch[index ++] = '0';
      divisor /= 10;
    }
  }
//  ar_ch[index ] = '\0'; //string terminating 0 char.
  return index;
}

/** Writes header for file format and creates char array for formatting the time string. */
void I_LogFormatter::Init(std::ostream /*&*/ * p_std_ostream /*= NULL*/,
  const std::string * p_std_strLogTimeFormatString //= NULL
  )
{
  if( p_std_ostream)
    //The std::ostream must be set every time the formatter changes.
    SetStdOstream( p_std_ostream );
  WriteHeader();
  if( ! p_std_strLogTimeFormatString)
  {
#ifdef _WIN32
    p_std_strLogTimeFormatString = & s_std_strDefaultWindowsLogTimeFormatString;
#endif
#ifdef __linux__
    p_std_strLogTimeFormatString = & s_std_strDefaultLinuxLogTimeFormatString;
#endif
  }
  SetTimeFormat( * p_std_strLogTimeFormatString);
}

/** Create array for formatting the time string into.
 *  Call when initializing or changing the time format.*/
void I_LogFormatter::SetTimeFormat(const std::string & TimeFormatString)
{
  m_TimeFormatString = TimeFormatString;
//  if( m_p_chTimeString)
//    //points to m_TimeFormatString.c_str()
//    delete [] m_p_chTimeString;
  //  CreateTimeStringArray();
  //  BYTE NumberOfPlaceHolders =
  uint16_t arraySize = GetNeededArraySizeForTimeString(m_TimeFormatString);
  //= m_TimeFormatString.size() + NumberOfPlaceHolders * 5 + 1;
  m_p_chTimeString = new char[ arraySize + 1];
}

void Insert(char * & p_chDestination,
  const char * c_p_chIndexOf1stCharOfTimeFormatString,
  BYTE numCharsToCopy )
{
  memcpy( p_chDestination,
    c_p_chIndexOf1stCharOfTimeFormatString,
    numCharsToCopy);
  p_chDestination += numCharsToCopy;
}

/** Format a number as string prepending zeros if too few digits. */
inline void FormatAsString(
  const PointerToLogFileEntryMemberAndNumFormatChars *
    p_p_logfileentrymember_and_num_formatchars,
  char ar_chFormatString[5],
  char *& p_chCurrentCharInFormattedTimeString
    )
{
  //    char ar_chNumCharsToFormat[2];
  //    itoa(p_p_logfileentrymember_and_num_formatchars->m_numCharsToFormat,
  //      ar_chNumCharsToFormat, 10);
  //TODO SIGSEV here sometimes?! (because of multithreaded logging wout crit sec?)
  sprintf(ar_chFormatString,
    //padding with "0": http://www.cplusplus.com/reference/cstdio/printf/
    // "%%"->"%", "%d"->number      entirely: ->"%0>>number<<d"
    "%%0%dd",
    p_p_logfileentrymember_and_num_formatchars->m_numCharsToFormat);
  if( p_p_logfileentrymember_and_num_formatchars->m_numCharsToFormat < 3)
    //see http://stackoverflow.com/questions/804288/creating-c-formatted-strings-not-printing-them
    p_chCurrentCharInFormattedTimeString += sprintf(
      p_chCurrentCharInFormattedTimeString, //"%2d",
      ar_chFormatString,
      * (uint8_t *) p_p_logfileentrymember_and_num_formatchars->
      m_p_logfileentrymember);
  else
    //see http://stackoverflow.com/questions/804288/creating-c-formatted-strings-not-printing-them
    p_chCurrentCharInFormattedTimeString += sprintf(
      p_chCurrentCharInFormattedTimeString, //"%2d",
      ar_chFormatString,
      * (uint16_t *) p_p_logfileentrymember_and_num_formatchars->
        m_p_logfileentrymember);
}

//virtual void WriteTimeStamp(const std::ofstream & std::ofstream) {}
void I_LogFormatter::GetTimeAsString(const LogFileEntry & logfileentry//,
//  std::string & std_strTime
  )
{
  char * p_chCurrentCharInFormattedTimeString = m_p_chTimeString;

//  std_strTime = m_TimeFormatString;
  //Use static variables because they are global and aren't created on the
  //stack for each call to this function.
//  static const char * c_p_chCurrentCharOfTimeFormatString;
  static const char * c_p_chIndexOf1stCharOfTimeFormatString;// = //std_strTime.c_str();
    //m_TimeFormatString.c_str();
  //Must be assigned for each call to this function because the time format
  //string may change.
  c_p_chIndexOf1stCharOfTimeFormatString = m_TimeFormatString.c_str();
//  static bool bPercentSignFound;
//  static uint16_t currentCharIndex;
//  static uint16_t IndexOfLeftPercentSign;
  static uint16_t IndexOfCharRightOfRightPercentSign;
  static uint16_t numCharsToCopy;
//  static BYTE stringSize;
//  static BYTE percentPairIndex;
  static std::vector<uint16_tPointerAndBYTE>::const_iterator
    c_iterTimeElementFromLogFileEntry;
//  static bool bInsertedReplacement;

  c_iterTimeElementFromLogFileEntry = m_vecPointerToTimeElementFromLogFileEntry.begin();
  //Init here and not in declaration because else the init. is only done once
  //for static variables.
  IndexOfCharRightOfRightPercentSign = 0;

  char ar_chFormatString[5]; // '%','0',number,'d','\0' = 5 chars
  while(c_iterTimeElementFromLogFileEntry !=
      m_vecPointerToTimeElementFromLogFileEntry.end())
  {
    //Insert left from place holder until either
    // -right "%" of previous place holder: "place_holder%..%place_holder%"
    // -begin of time format string: "^..%place_holder%"
    Insert(
      p_chCurrentCharInFormattedTimeString, //destination string
      //source string
      (c_p_chIndexOf1stCharOfTimeFormatString +
        IndexOfCharRightOfRightPercentSign
        ),
      //c_iterTimeElementFromLogFileEntry->m_numCharsToSkip
      c_iterTimeElementFromLogFileEntry->m_charIndexOfLeftPercentSign -
      IndexOfCharRightOfRightPercentSign
      );

    IndexOfCharRightOfRightPercentSign = c_iterTimeElementFromLogFileEntry->
      m_charIndexOfLeftPercentSign + c_iterTimeElementFromLogFileEntry->
      m_numCharsToSkip;

//    stringSize = uint16tToCharArray(
//      * c_iterTimeElementFromLogFileEntry->m_p_uint16_t, //ar_ch
//      p_chCurrentCharInFormattedTimeString);
//    p_chCurrentCharInFormattedTimeString += stringSize;
    const PointerToLogFileEntryMemberAndNumFormatChars *
      p_p_logfileentrymember_and_num_formatchars =
      c_iterTimeElementFromLogFileEntry->
      m_p_p_logfileentrymember_and_num_formatchars;
    FormatAsString(
      p_p_logfileentrymember_and_num_formatchars,
      ar_chFormatString,
      p_chCurrentCharInFormattedTimeString
      );
    ++ c_iterTimeElementFromLogFileEntry;
  }
//  ReplaceViaReadingTimeFormatString();
  numCharsToCopy = m_TimeFormatString.length() -
    //# chars right of "%"
    IndexOfCharRightOfRightPercentSign;
  Insert( p_chCurrentCharInFormattedTimeString,
    c_p_chIndexOf1stCharOfTimeFormatString +
      IndexOfCharRightOfRightPercentSign,
    numCharsToCopy);

  * p_chCurrentCharInFormattedTimeString = '\0';
}
