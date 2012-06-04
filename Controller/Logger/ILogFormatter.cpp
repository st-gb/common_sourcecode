/*
 * ILogFileWriter.cpp
 *
 *  Created on: 26.04.2012
 *      Author: Stefan
 */

#include "Controller/Logger/ILogFormatter.hpp"
#include <limits.h> //SHRT_MAX
#include <Controller/Logger/Logger.hpp> //class Logger

//I_LogFormatter::I_LogFormatter()
//{
//  // TODO Auto-generated constructor stub
//
//}

//32xxx = 5 characters
#define NUMBER_OF_CHARS_FOR_MAX_2_BYTE_VALUE_IN_DEC 5

uint16_t I_LogFormatter::GetNeededArraySizeForTimeString(std::string timeFormatString)
{
  NodeTrieNode<const uint16_t *> * p_ntn;
  uint16_t currentCharIndex = 0;
  uint16_t IndexOfLeftPercentSign = SHRT_MAX;
  uint16_t ArraySizeForTimeString = 0;
  int IndexOfRightPercentSign = 0;
  BYTE numCharsInBetween;
  BYTE percentPairIndex = 0;
  const char * const c_p_chTimeFormatStringBegin = timeFormatString.c_str();
  const char * c_p_chTimeFormatStringCurrentChar = timeFormatString.c_str();

  //Important, because it may be filled from a call from before.
  m_vecPointerToTimeElementFromLogFileEntry.clear();

  while( * c_p_chTimeFormatStringCurrentChar )
  {
    if( * c_p_chTimeFormatStringCurrentChar == '%' )
    {
      if( IndexOfLeftPercentSign == SHRT_MAX ) // left "%"
      {
        IndexOfLeftPercentSign = currentCharIndex;
        // "begin...%placeholder%" and "%placeholder%...%placeholder%"
        ArraySizeForTimeString += IndexOfLeftPercentSign -
          IndexOfRightPercentSign;
      }
//      bPercentSignFound = true;
      else //-> right "%" belonging to left "%"
      {
        //chars between left "%" and right "%" from %placeholder%"
        numCharsInBetween = currentCharIndex - IndexOfLeftPercentSign - 1;
        IndexOfRightPercentSign = currentCharIndex;

        p_ntn = m_nodetrieTimePlaceHolderToLogFileEntryMember.contains_inline(
          (BYTE *) (c_p_chTimeFormatStringBegin + IndexOfLeftPercentSign + 1),
          numCharsInBetween,
          true);
        if( p_ntn && p_ntn->m_member)
        {
          const uint16_tPointerAndBYTE logFilePlaceHolder(
            p_ntn->m_member,
            numCharsInBetween + 2,
//              percentPairIndex
            IndexOfLeftPercentSign
            );
          m_vecPointerToTimeElementFromLogFileEntry.push_back(
            logFilePlaceHolder
            );
          ArraySizeForTimeString +=
            NUMBER_OF_CHARS_FOR_MAX_2_BYTE_VALUE_IN_DEC;
        }
        else
          ArraySizeForTimeString += numCharsInBetween;
        IndexOfLeftPercentSign = SHRT_MAX;
        ++ percentPairIndex;
      }
    }
    ++ currentCharIndex;
    ++ c_p_chTimeFormatStringCurrentChar;
  }
//  if( IndexOfLeftPercentSign != SHRT_MAX )
  if( IndexOfLeftPercentSign == SHRT_MAX ) //-> right "%" or any "%" in string
  {
    //either:
    // - # of chars of "..." in "%placeholder%"...end"
    // - if no "%" in whole string: # of chars of whole string
    ArraySizeForTimeString += timeFormatString.length() -
      //# chars right of "%"
      IndexOfRightPercentSign - 1;
  }
  else //left "%"
//    if( IndexOfRightPercentSign > IndexOfLeftPercentSign)
      // # of chars of "..." in "%xxx"...end"
      ArraySizeForTimeString += timeFormatString.length() -
        //# chars right of "%" plus 1 char for "%"
        IndexOfLeftPercentSign;
  return ArraySizeForTimeString;
}

I_LogFormatter::I_LogFormatter(//std::ofstream * p_std_ofstream
  const Logger * p_logger)
  :
    m_p_logger(p_logger),
    m_p_chTimeString(NULL),
    m_nodetrieTimePlaceHolderToLogFileEntryMember(256)
{
  m_p_std_ofstream = //p_std_ofstream;
    p_logger->m_p_std_ofstream;
  m_p_logfileentry = & p_logger->m_logfileentry;
  m_TimeFormatString =
    "%year%-%month%-%day%&nbsp;%hour%:%minute%:%second%s%millisecond%ms";
  CreateTimePlaceHolderToLogFileEntryMemberMapping();
}

I_LogFormatter::~I_LogFormatter()
{
  if( m_p_chTimeString )
    delete [] m_p_chTimeString;
}

void I_LogFormatter::CreateTimePlaceHolderToLogFileEntryMemberMapping()
{
  std::string str = "year";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    & m_p_logfileentry->year);
  str = "month";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    & m_p_logfileentry->month);
  str = "day";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    & m_p_logfileentry->day);
  str = "hour";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    & m_p_logfileentry->hour);
  str = "minute";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    & m_p_logfileentry->minute);
  str = "second";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    & m_p_logfileentry->second);
  str = "millisecond";
  m_nodetrieTimePlaceHolderToLogFileEntryMember.insert_inline(
    (BYTE *) str.c_str(), str.size(), //(const void *)
    & m_p_logfileentry->millisecond);
}

//void I_LogFormatter::CreateTimeStringArray()
//{
//}

inline void I_LogFormatter::Replace(
  const std::string & std_strToReplace,
  const std::string & std_strFromLogFileEntry
  )
{
  static std::string::size_type posOfOccurence;
  posOfOccurence = m_TimeFormatString.find(std_strToReplace);
  if( posOfOccurence != std::string::npos )
    m_TimeFormatString.replace(posOfOccurence, std_strToReplace.length(),
      std_strFromLogFileEntry);
}

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

BYTE I_LogFormatter::Replace(
  uint16_t IndexOf1stChar,
  uint16_t IndexOfLastChar
  , //std::string & std_strTime
  char * & p_chTimeString
  )
{
  static const char * pchStringBegin;
  static NodeTrieNode<const uint16_t *> * p_ntn;
  static uint16_t ui16Number;
//  static char ar_ch[6];
  static int stringSize;

  pchStringBegin = m_TimeFormatString.c_str();
//  pchStringBegin = m_TimeFormatString.at(IndexOf1stChar)
  p_ntn = m_nodetrieTimePlaceHolderToLogFileEntryMember.contains_inline(
    (BYTE *) (pchStringBegin + IndexOf1stChar),
    IndexOfLastChar - IndexOf1stChar,
    true);
  if( p_ntn && p_ntn->m_member)
  {
    ui16Number = * ( (uint16_t *) p_ntn->m_member);
//    ui16Number = m_p_logfileentry->minute;
//    ui16Number = IndexOf1stChar;
    stringSize = uint16tToCharArray(ui16Number, //ar_ch
      p_chTimeString);
//    std_strTime.replace(//IndexOf1stChar, IndexOfLastChar - IndexOf1stChar,
//      1, 2,
//      ar_ch
////      "hh"
//      );
//    ui16Number = IndexOfLastChar;
//    uint16tToCharArray(ui16Number, ar_ch);
    //TODO string::replace always creates a new buffer?
//    std_strTime.replace(//IndexOf1stChar, IndexOfLastChar - IndexOf1stChar,
//      10, 2,
//      ar_ch
//      );
//    memcpy(p_chTimeString, ar_ch, stringSize );
    p_chTimeString += stringSize;

//    memcpy(p_chTimeString, "23", 2 );
//    p_chTimeString += 2;
    return stringSize;
  }
  return 0;
}

void I_LogFormatter::SetTimeFormat(const std::string & TimeFormatString)
{
  m_TimeFormatString = TimeFormatString;
  if( m_p_chTimeString)
    delete [] m_p_chTimeString;
  //  CreateTimeStringArray();
  //  BYTE NumberOfPlaceHolders =
  uint16_t arraySize = GetNeededArraySizeForTimeString(m_TimeFormatString);
  //= m_TimeFormatString.size() + NumberOfPlaceHolders * 5 + 1;
  m_p_chTimeString = new char[ arraySize + 1];
}
//void I_LogFormatter::Append()
//{
//
//}

void GetTimeAsStringViaStringReplacement(
  const LogFileEntry & logfileentry,
  std::string & std_strTime )
{
  //  static std::string std_strToReplace;
  //  static std::string std_strFromLogFileEntry;
  //
  //  std_strToReplace = "%year%";
  //  std_strFromLogFileEntry = logfileentry.year;
  //  convertToStdString(logfileentry.year);
  //  Replace( std_strToReplace, std_strFromLogFileEntry);
  //
  //  std_strToReplace = "%month%";
  //  std_strFromLogFileEntry = logfileentry.month;
  //  Replace( std_strToReplace, std_strFromLogFileEntry);
  //
  //  std_strToReplace = "%day%";
  //  std_strFromLogFileEntry = logfileentry.day;
  //  Replace( std_strToReplace, std_strFromLogFileEntry);
  //
  //  std_strToReplace = "%hour%";
  //  std_strFromLogFileEntry = logfileentry.hour;
  //  Replace( std_strToReplace, std_strFromLogFileEntry);
  //
  //  std_strToReplace = "%minute%";
  //  std_strFromLogFileEntry = logfileentry.minute;
  //  Replace( std_strToReplace, std_strFromLogFileEntry);
  //
  //  std_strToReplace = "%second%";
  //  std_strFromLogFileEntry = logfileentry.second;
  //  Replace( std_strToReplace, std_strFromLogFileEntry);
  //
  //  std_strToReplace = "%millisecond%";
  //  std_strFromLogFileEntry = logfileentry.millisecond;
  //  Replace( std_strToReplace, std_strFromLogFileEntry);
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

void ReplaceViaReadingTimeFormatString()
{
//  if( c_iterTimeElementFromLogFileEntry != m_vecPointerToTimeElementFromLogFileEntry.end() )
//  {
//    c_p_chCurrentCharOfTimeFormatString = //std_strTime.c_str();
//      m_TimeFormatString.c_str();
//  //  bPercentSignFound = false;
//    currentCharIndex = 0;
//    percentPairIndex = 0;
//    IndexOfLeftPercentSign = SHRT_MAX;
//    IndexOfCharRightOfRightPercentSign = 0;
//    bInsertedReplacement = false;
//    while( * c_p_chCurrentCharOfTimeFormatString )
//    {
//      if( * c_p_chCurrentCharOfTimeFormatString == '%' )
//      {
//        if( IndexOfLeftPercentSign == SHRT_MAX ) // left "%"
//        {
//          numCharsToCopy = currentCharIndex -
//            IndexOfCharRightOfRightPercentSign;
//          memcpy( p_chCurrentCharInFormattedTimeString,
//            c_p_chIndexOf1stCharOfTimeFormatString +
//              IndexOfCharRightOfRightPercentSign,
//            numCharsToCopy);
//          p_chCurrentCharInFormattedTimeString += numCharsToCopy;
//
//          if( c_iterTimeElementFromLogFileEntry != m_vecPointerToTimeElementFromLogFileEntry.end() &&
//              currentCharIndex == c_iterTimeElementFromLogFileEntry->m_percentPairIndex )
//          {
//            stringSize = uint16tToCharArray( * c_iterTimeElementFromLogFileEntry->m_p_uint16_t, //ar_ch
//              p_chCurrentCharInFormattedTimeString);
//            p_chCurrentCharInFormattedTimeString += stringSize;
//
//            //skip bytes for placeholder
//            currentCharIndex += c_iterTimeElementFromLogFileEntry->m_byte;
//            c_p_chCurrentCharOfTimeFormatString += c_iterTimeElementFromLogFileEntry->m_byte;
//            IndexOfLeftPercentSign = SHRT_MAX;
//            IndexOfCharRightOfRightPercentSign = currentCharIndex;
//            bInsertedReplacement = true;
//
//            ++ c_iterTimeElementFromLogFileEntry;
//            continue; //Skip the increment at end of this while loop.
//          }
//          else
//          {
//            bInsertedReplacement = false;
//            IndexOfLeftPercentSign = currentCharIndex;
//          }
//        }
//  //      bPercentSignFound = true;
//        else //-> right "%" belonging to left "%"
//        {
//  //        if( ! Replace( IndexOfLeftPercentSign + 1, currentCharIndex, //std_strTime
//  //            p_chCurrentCharInFormattedTimeString)
//  //          )
//  //          if( percentPairIndex == c_iterTimeElementFromLogFileEntry->m_percentPairIndex )
//  //          {
//  //            stringSize = uint16tToCharArray( * c_iterTimeElementFromLogFileEntry->m_p_uint16_t, //ar_ch
//  //              p_chCurrentCharInFormattedTimeString);
//  //            p_chCurrentCharInFormattedTimeString += stringSize;
//  //            ++ c_iterTimeElementFromLogFileEntry;
//  //          }
//  //          else
//          if( //currentCharIndex != c_iterTimeElementFromLogFileEntry->m_percentPairIndex
//              ! bInsertedReplacement )
//            Insert(p_chCurrentCharInFormattedTimeString,
//              c_p_chIndexOf1stCharOfTimeFormatString + IndexOfLeftPercentSign,
//              currentCharIndex - IndexOfLeftPercentSign + 1);
//          IndexOfLeftPercentSign = SHRT_MAX;
//          IndexOfCharRightOfRightPercentSign = currentCharIndex + 1;
//  //          ++ percentPairIndex;
//        }
//      }
//      ++ currentCharIndex;
//      ++ c_p_chCurrentCharOfTimeFormatString;
//    }
//      if( IndexOfLeftPercentSign == SHRT_MAX ) //-> right "%" or any "%" in string
//      {
//        //either:
//        // - # of chars of "..." in "%placeholder%"...end"
//        // - if no "%" in whole string: # of chars of whole string
//        numCharsToCopy = m_TimeFormatString.length() -
//          //# chars right of "%"
//          IndexOfCharRightOfRightPercentSign;
//        memcpy( p_chCurrentCharInFormattedTimeString,
//          c_p_chIndexOf1stCharOfTimeFormatString +
//            IndexOfCharRightOfRightPercentSign,
//          numCharsToCopy);
//      }
  //    else //left "%"
  //    {
  //  //    if( IndexOfRightPercentSign > IndexOfLeftPercentSign)
  //        // # of chars of "..." in "%xxx"...end"
  //      numCharsToCopy = m_TimeFormatString.length() -
  //        //# chars right of "%" plus 1 char for "%"
  //        IndexOfLeftPercentSign;
  //      memcpy( p_chCurrentCharInFormattedTimeString,
  //        c_p_chIndexOf1stCharOfTimeFormatString +
  //          IndexOfLeftPercentSign,
  //        numCharsToCopy);
  //    }
//      p_chCurrentCharInFormattedTimeString += numCharsToCopy;
  //  }
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
  static const char * c_p_chCurrentCharOfTimeFormatString;
  static const char * c_p_chIndexOf1stCharOfTimeFormatString = //std_strTime.c_str();
    m_TimeFormatString.c_str();
//  static bool bPercentSignFound;
  static uint16_t currentCharIndex;
  static uint16_t IndexOfLeftPercentSign;
  static uint16_t IndexOfCharRightOfRightPercentSign;
  static uint16_t numCharsToCopy;
  static BYTE stringSize;
  static BYTE percentPairIndex;
  static std::vector<uint16_tPointerAndBYTE>::const_iterator
    c_iterTimeElementFromLogFileEntry;
  static bool bInsertedReplacement;

  c_iterTimeElementFromLogFileEntry = m_vecPointerToTimeElementFromLogFileEntry.begin();
  //Init here and not in declaration because else the init. is only done once
  //for static variables.
  IndexOfCharRightOfRightPercentSign = 0;

  while(c_iterTimeElementFromLogFileEntry != m_vecPointerToTimeElementFromLogFileEntry.end())
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

    stringSize = uint16tToCharArray(
      * c_iterTimeElementFromLogFileEntry->m_p_uint16_t, //ar_ch
      p_chCurrentCharInFormattedTimeString);
    p_chCurrentCharInFormattedTimeString += stringSize;

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

//  Replace( 0, 2, //std_strTime
//    p_chCurrentCharInFormattedTimeString);
//  memcpy( p_chCurrentCharInFormattedTimeString,
//    "88",
//    2);
//  p_chCurrentCharInFormattedTimeString += 2;
  * p_chCurrentCharInFormattedTimeString = '\0';
}
