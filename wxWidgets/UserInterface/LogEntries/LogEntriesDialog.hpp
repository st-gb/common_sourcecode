/*
 * LogEntriesDialog.hpp
 *
 *  Created on: 02.04.2014
 *      Author: mr.sys
 */

#ifndef LOGENTRIESDIALOG_HPP_
#define LOGENTRIESDIALOG_HPP_

#include <wx/dialog.h> //Base class

/** Forward declarations */
namespace wxWidgets
{
  class LogEntriesListCtrl;
}
class Logger;
class wxTextCtrl;

namespace wxWidgets
{

  class LogEntriesDialog
    : public wxDialog
  {
    wxTextCtrl * m_p_messageToSearch;
    wxWidgets::LogEntriesListCtrl * m_p_logEntriesListCtrl;
  public:
    LogEntriesDialog(const Logger & logger);
    virtual
    ~LogEntriesDialog();

    void OnClose( wxCloseEvent & wxcmd );
    void OnGoToNextMatchButton(wxCommandEvent & evt);
    void OnClearLogEntriesButton(wxCommandEvent & evt);
    /** For receiving messages. */
    DECLARE_EVENT_TABLE()
  };

} /* namespace wxWidgets */

#endif /* LOGENTRIESDIALOG_HPP_ */
