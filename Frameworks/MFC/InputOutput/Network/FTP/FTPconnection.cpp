#include "stdafx.h" //for "NULL" etc.
#include "FTPconnection.hpp"
#include <afxinet.h> //CFtpConnection, CInternetException
#include "UserInterface/UserInterface.hpp"

FTPconnection::FTPconnection(
  SyncData & r_syncdata //,
//  UserInterface & r_userinterface
  )
{
  mp_syncdata = & r_syncdata ;
//  mp_userinterface = & r_userinterface ;
}

//#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION
//To always restart a connection has the following reason: 
//If one started one for a destination FTP server, a timeout
//may happen(the duration until the timeout occurs can be set
//on the side of the server). And when the timeout happens 
//the connection is closed/invalid.
//CFtpConnection * 
void FTPconnection::StartOrRestartFTPSession
  (
  //CFtpConnection ** ppftpconnection////=NULL
  std::tstring & r_stdtstr
  )
{
  ASSERT(mp_ftpserverattributes != NULL);
  CFtpConnection * pftpconnection;
  ////If NULL.
  if( ! ppftpconnection)
  {
    pftpconnection = m_pFTPServerAttributes->m_pFtpConnection;
    ppftpconnection = & m_pFTPServerAttributes->m_pFtpConnection;
  }
  else
    pftpconnection = * ppftpconnection;
  ////It may happen that 2 or more threads try to (re)start the FTP connection.
  ////Protect against this case.
  //CSingleLock slCFtpConnection(&m_pFTPServerAttributes->m_csCFtpConnection,
  //  //BOOL bInitialLock 
  //  TRUE);
  ////If there currently is another operation (at another thread) 
  ////with this CFTPConnection, 
  ////restarting the FTP session may cause an error because the used
  ////connection is closed and deleted while the other thread works with it.
  //if(!m_pFTPServerAttributes->m_vwNumberOfFTPOperationsInProgress)
  {
    try
    {
      //INTERNET_OPTION_CONNECTED_STATE 
      //if(this->m_pFTPServerAttributes->m_pFtpConnection->QueryOption(
      //The following from MFC Library Reference: 
      //If the connection is open, close it.
      //I think/believe that m_pFTPServerAttributes->m_pFtpConnection
      //can be not NULL although one cancelled the connection
      //(by Sysinternals/Microsoft TCPView).
      if(//m_pFTPServerAttributes->m_pFtpConnection
        pftpconnection)
      {
        //I guess that even CFtpConnection::Close can raise an
        //exception.
        //m_pFTPServerAttributes->m_pFtpConnection->Close();
        pftpconnection->Close();
        //delete m_pFTPServerAttributes->m_pFtpConnection;
        delete pftpconnection;
      }
      //m_pFTPServerAttributes->m_pFtpConnection=
      * ppftpconnection =
        m_pFTPServerAttributes->m_internetSession.GetFtpConnection(
        m_pFTPServerAttributes->m_strServerName,
        m_pFTPServerAttributes->m_strUserName,
        m_pFTPServerAttributes->m_strPassword//,
        //nPort = INTERNET_INVALID_PORT_NUMBER//,
        ,m_pFTPServerAttributes->m_nPort,
        //BOOL bPassive = FALSE 
        m_pFTPServerAttributes->m_bPassiveMode
        );
    }
    catch (//must be a pointer, else the exceptions is not catched!
      CInternetException * pEx)
    {
      CString strPortNumber;
      strPortNumber.Format("%u",m_pFTPServerAttributes->m_nPort);
      TCHAR sz[1024];
      if( pEx->GetErrorMessage(sz, 1024) )
        //Nonzero if the function is successful.
      {
        TRACE("ERROR!  %s\n", sz);
        //theApp.WriteToMessagesWindow(
//        mp_userinterface->Message("Es konnte keine FTP-Verbindung "
//          "hergestellt werden zu " +
//          //m_strUserName+":"+m_strPassword+"@"+m_strServerName+
//          //m_strFullDirPathBelowServerPathRootDir+":"+strPortNumber
//          Synchronize::PossiblyHidePassword(
//            this->m_strUserInputDestinationDirToReceiveChanges) +
//            ":" + CString(sz)
//          );
        r_stdtstr = std::tstring(sz) ;
      }
      pEx->Delete();
      //m_pFTPServerAttributes->m_pFtpConnection=NULL;
      * ppftpconnection = NULL;
      pftpconnection = NULL;
    }
    if(//m_pFTPServerAttributes->m_pFtpConnection
      * ppftpconnection)
    {
      try
      {
        pftpconnection = * ppftpconnection;
        //The dir where it starts after the connection may be another
        //than the root dir("/"). This can be configured/specified on
        //the FTP SERVER side.
        if(//!m_pFTPServerAttributes->m_pFtpConnection->GetCurrentDirectory(
          ! pftpconnection->GetCurrentDirectory(
            m_pFTPServerAttributes->m_strStartingDir)
          )
          //Nonzero if successful; otherwise 0.
          //theApp.WriteToMessagesWindow(
//            mp_userinterface->Message(
//            "Es trat ein Fehler auf beim Abfragen des Startverzeichnis bei " +
//            Synchronize::PossiblyHidePassword( this->
//              m_strUserInputDestinationDirToReceiveChanges)
//            );
          return ErrorGettingStartingDir ;
      }
      catch(CInternetException * pie)
      {
        //theApp.
//          mp_userinterface->WriteToMessagesWindow(
//            "Es trat ein Fehler auf beim Abfragen des Startverzeichnis bei " +
//          Synchronize::PossiblyHidePassword( this->
//            m_strUserInputDestinationDirToReceiveChanges)
//          );
        pie->Delete();
        return ErrorGettingStartingDir ;
      }
    }
  }
  return //m_pFTPServerAttributes->m_pFtpConnection;
    pftpconnection;
}
//#endif //#ifndef COMPILE_FOR_NON_COMPLETE_MFC_VERSION

void FTPconnection::DeleFileOrDir()
{
  
};
