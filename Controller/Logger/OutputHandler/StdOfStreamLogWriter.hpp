/*
 * StdOfStreamLogWriter.hpp
 *
 *  Created on: 08.02.2013
 *      Author: Stefan
 */

#ifndef STDOFSTREAMLOGWRITER_HPP_
#define STDOFSTREAMLOGWRITER_HPP_

#include <fstream> //for class std::ofstream
//class I_LogEntryOutputter
#include <Controller/Logger/OutputHandler/I_LogEntryOutputter.hpp>

/** Actual/physical output of formatted log file entries via std::ofstream. */
class StdOfStreamLogWriter
  : public I_LogEntryOutputter
{
  private:
    std::ofstream * m_p_std_ofstream ;
public:
  StdOfStreamLogWriter();
  virtual
  ~StdOfStreamLogWriter();
  unsigned Close()
  {
#ifdef COMPILE_LOGGER_THREAD_SAFE
    m_critical_section.Enter();
#endif //COMPILE_LOGGER_THREAD_SAFE
    if( m_p_std_ofstream )
    {
      m_p_std_ofstream->close();
//      m_p_std_ofstream = NULL;
    }
    bool bBadOFstream = ! m_p_std_ofstream->good();
#ifdef COMPILE_LOGGER_THREAD_SAFE
    m_critical_section.Leave();
#endif //COMPILE_LOGGER_THREAD_SAFE
    return bBadOFstream;
  }
  bool IsOpen();
  bool OpenA( const std::string & c_r_stdstrFilePath);
  //"virtual" because: allow polymorphism: call function of the actual type
  // (may be a direct or indirect subclass of this class).
  std::ostream * GetStdOstream() const { return m_p_std_ofstream; }
  virtual unsigned DoOutput() { m_p_std_ofstream->flush(); return 0;}
//  bool SetStdOstream(const std::string & c_r_stdstrFilePath) {
//    m_p_std_ostream =
//  }
  int RenameFileThreadUnsafe(const std::string & cr_std_strFilePath
    /*, enum I_LogEntryOutputter::open_mode open_mode = I_LogEntryOutputter::Append*/ );
  bool SetStdOstream(const std::string & c_r_stdstrFilePath);
  void TruncateOutputSizeToZero()
  {
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//    //Sync with other code accessing the ofstream.
//    m_critical_section_typeLogging.Enter();
//#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
    if( m_p_std_ofstream )
    {
      m_p_std_ofstream->close();
      m_p_std_ofstream->open( m_std_strLogFilePath.c_str(), std::ios_base::trunc);
    }
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//    m_critical_section_typeLogging.Leave();
//#endif //#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
  }
};

#endif /* STDOFSTREAMLOGWRITER_HPP_ */
