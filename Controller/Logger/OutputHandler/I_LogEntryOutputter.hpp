/*
 * ILogEntryOutputter.hpp
 *
 *  Created on: 07.02.2013
 *      Author: Stefan
 */

#ifndef ILOGENTRYOUTPUTTER_HPP_
#define ILOGENTRYOUTPUTTER_HPP_

#include <string> //class std::string
#include <Controller/multithread/nativeCriticalSectionType.hpp>

class OpeningLogFileException
{
  std::string m_errorMessage;
public:
  OpeningLogFileException(const char * const pch)
  {
    m_errorMessage = pch;
  }

  const std::string & GetErrorMessage() const
  {
    return m_errorMessage;
  }
};

/** @brief Base class for all classes that DO the actual / physical output.
 * So e.g. following outputs are possible:
 * -output to a file via:
 *  -std::ofstream (via "<<" operator )
 *  -Windows API ( via "WriteFile(...)" )
 * -to a socket
 * */
class I_LogEntryOutputter
{
protected:
  std::ostream * m_p_std_ostream ;
  std::string m_std_strLogFilePath;
//#ifdef COMPILE_LOGGER_MULTITHREAD_SAFE
//  typedef nativeCriticalSection critical_section_type;
//  critical_section_type m_critical_section;
//#endif
public:
  enum open_mode {truncateToSize0, Append};
  I_LogEntryOutputter();
  virtual
  ~I_LogEntryOutputter();

  virtual unsigned Close() = 0;
  /** "virtual" because: allow polymorphism: call function of the actual type
  * (may be a direct or indirect subclass of this class).
  * @brief this does the actual output to the underlying file etc.
  * @return 0: success  */
  virtual unsigned DoOutput() = 0;
  virtual std::ostream * GetStdOstream() const { return m_p_std_ostream; }
  //"virtual" because: allow polymorphism: call function of the actual type
  // (may be a direct or indirect subclass of this class).
  virtual bool IsOpen() = 0;
  /** @param c_r_stdstrFilePath needs to be passed because it may vary if
   *  e.g. rolling file appender: "[...]log0.txt", "[...]log1.txt" */
  virtual bool OpenA( const std::string & c_r_stdstrFilePath) = 0;
  /** E.g. set file size to 0 / remote file size to 0.
   * "virtual" because: allow polymorphism: call subclasses' function */
  virtual void TruncateOutputSizeToZero() = 0;
  int RenameFile(const std::string & cr_std_strFilePath)
  {
    return RenameThreadSafe(cr_std_strFilePath);
  }
  int RenameThreadSafe(const std::string & cr_std_strFilePath
    /*, enum open_mode mode = Append*/ /*truncateToSize0*/ );
  virtual bool SetStdOstream(const std::string & c_r_stdstrFilePath) = 0;
  //"virtual" because: allow polymorphism
  virtual int RenameFileThreadUnsafe(const std::string & r_stdstrFilePath
    //,enum I_LogEntryOutputter::open_mode = I_LogEntryOutputter::Append
    ) = 0;
  void TruncateFileToZeroAndRewrite() ;
};

#endif /* ILOGENTRYOUTPUTTER_HPP_ */
