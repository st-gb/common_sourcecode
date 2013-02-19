/*
 * StdCoutLogWriter.hpp
 *
 *  Created on: 17.02.2013
 *      Author: Stefan
 */

#ifndef STDCOUTLOGWRITER_HPP_
#define STDCOUTLOGWRITER_HPP_

#include <Controller/Logger/OutputHandler/I_LogEntryOutputter.hpp>
#include <iostream>

//namespace Logger
//{

  class StdCoutLogWriter
    : public I_LogEntryOutputter
  {
  public:
    StdCoutLogWriter();
    virtual
    ~StdCoutLogWriter();
    unsigned Close() { m_p_std_ostream = NULL; return 0; }
    unsigned DoOutput() { //m_p_std_ostream->flush();
      return ! m_p_std_ostream->good(); } //all done by formatter via std::ostream
//    std::ostream * GetStdOstream() const { return m_p_std_ostream; }
    bool IsOpen() { bool isOpen = m_p_std_ostream //!= NULL
        && m_p_std_ostream->good() ;
      return isOpen;
    }
    bool OpenA( const std::string & c_r_stdstrFilePath) {
      m_p_std_ostream = & std::cout;
      return m_p_std_ostream->good();
    }
    /** E.g. set file size to 0 / remote file size to 0.
     * "virtual" because: allow polymorphism: call subclasses' function */
    void TruncateOutputSizeToZero() { /*m_p_std_ostream->flush();*/ }
    bool SetStdOstream(const std::string & c_r_stdstrFilePath) { return true; }
    //"virtual" because: allow polymorphism
    int RenameFileThreadUnsafe(const std::string & r_stdstrFilePath
      //,enum I_LogEntryOutputter::open_mode = I_LogEntryOutputter::Append
      ) { return 0; }
  };

//} /* namespace Logger */
#endif /* STDCOUTLOGWRITER_HPP_ */
