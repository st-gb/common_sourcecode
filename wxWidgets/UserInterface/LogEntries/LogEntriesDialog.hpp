/*
 * LogEntriesDialog.hpp
 *
 *  Created on: 02.04.2014
 *      Author: mr.sys
 */

#ifndef LOGENTRIESDIALOG_HPP_
#define LOGENTRIESDIALOG_HPP_

#include <wx/dialog.h> //Base class

class Logger;

namespace wxWidgets
{

  class LogEntriesDialog
    : public wxDialog
  {
  public:
    LogEntriesDialog(const Logger & logger);
    virtual
    ~LogEntriesDialog();
  };

} /* namespace wxWidgets */

#endif /* LOGENTRIESDIALOG_HPP_ */
