/*
 * ILogEntryOutputter.cpp
 *
 *  Created on: 07.02.2013
 *      Author: Stefan
 */

#include "I_LogEntryOutputter.hpp"
#include <Controller/Logger/Logger.hpp> //class Logger
extern Logger g_logger;

I_LogEntryOutputter::I_LogEntryOutputter()
  : m_p_std_ostream(NULL)
{
  // TODO Auto-generated constructor stub

}

I_LogEntryOutputter::~I_LogEntryOutputter()
{
  // TODO Auto-generated destructor stub
}

int I_LogEntryOutputter::RenameThreadSafe(
  const std::string & cr_std_strFilePath
  /*, enum open_mode mode*/ )
{
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//  //Sync with other code accessing the ofstream.
////  g_logger.m_critical_section_typeLogging.Enter();
//  m_critical_section.Enter();
//#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  int i = RenameFileThreadUnsafe(cr_std_strFilePath/*, mode*/ );
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
////  g_logger.m_critical_section_typeLogging.Leave();
//  m_critical_section.Leave();
//#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  return i;
}

