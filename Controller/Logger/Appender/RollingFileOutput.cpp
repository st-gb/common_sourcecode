/*
 * RollingFileOutput.cpp
 *
 *  Created on: 07.02.2013
 *      Author: Stefan
 */

#include "RollingFileOutput.hpp"

//RollingFileOutput::RollingFileOutput()
//{
//  // TODO Auto-generated constructor stub
//
//}
//
//RollingFileOutput::~RollingFileOutput()
//{
//  // TODO Auto-generated destructor stub
//}

  bool RollingFileOutput::GetActualFilePath(std::string & str)
  {
    static char ch;
    std::string::size_type lastDotCharIndex = m_filePath.rfind('.');
    if( lastDotCharIndex != std::string::npos )
    {
      if( lowerFileName )
        ch = '0';
      else
        ch = '1';
      str = m_filePath.substr(0, lastDotCharIndex) + ch +
        m_filePath.substr(lastDotCharIndex);
      lowerFileName = ! lowerFileName;
      return true;
    }
    return false;
  }

  bool RollingFileOutput::Open(std::string & actualFilePath)
  {
    bool bOpen = false;
    if( GetActualFilePath(actualFilePath) )
    {
      bOpen = m_p_outputhandler->OpenA(actualFilePath );
      if( bOpen )
      {
        m_p_std_ostream = m_p_outputhandler->GetStdOstream();
        if( m_p_log_formatter)
        {
          m_p_log_formatter->SetStdOstream(m_p_std_ostream);
        }
      }
    }
    return bOpen;
  }
