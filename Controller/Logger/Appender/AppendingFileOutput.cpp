/*
 * AppendingFileOutput.cpp
 *
 *  Created on: 08.02.2013
 *      Author: Stefan
 */

#include "AppendingFileOutput.hpp"
#include "../OutputHandler/I_LogEntryOutputter.hpp"

//AppendingFileOutput::AppendingFileOutput()
//{
//  // TODO Auto-generated constructor stub
//
//}
//
//AppendingFileOutput::~AppendingFileOutput()
//{
//  // TODO Auto-generated destructor stub
//}

  bool AppendingFileOutput::Open()
  {
    bool bIsOpen = m_p_outputhandler->OpenA(m_filePath);
    if( bIsOpen)
      m_p_std_ostream = m_p_outputhandler->GetStdOstream();
    return bIsOpen;
  }
