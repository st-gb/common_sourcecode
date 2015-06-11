/*
 * LogEntriesDialog.hpp
 *
 *  Created on: 02.04.2014
 *      Author: mr.sys
 */

#ifndef LOGENTRIESDIALOG_HPP_
#define LOGENTRIESDIALOG_HPP_

#include <wx/dialog.h> //Base class
#include "SearchParams.hpp"

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
    SearchParams m_searchParams;
    wxTextCtrl * m_p_messageToSearch, * m_p_functionNameToSearch;
    wxWidgets::LogEntriesListCtrl * m_p_logEntriesListCtrl;
  public:
    enum winIDs { ClearLogEntriesButton, goToPreviousMatchButton,
      goToNextMatchButton, logEntriesListCtrl};

    LogEntriesDialog(const Logger & logger, const unsigned GUIthreadID);
    virtual
    ~LogEntriesDialog();

    void OnContextMenuMouseButtonDown(wxMouseEvent & evt);
    void OnPopupClick(wxCommandEvent & evt);
    void OnClose( wxCloseEvent & wxcmd );
    void OnGoToNextMatchButton(wxCommandEvent & evt);
    void OnGoToPreviousMatchButton(wxCommandEvent & evt);
    void OnClearLogEntriesButton(wxCommandEvent & evt);
    /** For receiving messages. */
    DECLARE_EVENT_TABLE()
  };

} /* namespace wxWidgets */

#endif /* LOGENTRIESDIALOG_HPP_ */
