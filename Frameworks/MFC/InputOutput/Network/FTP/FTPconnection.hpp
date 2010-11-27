#pragma once

//#include "UserInterface/UserInterface.hpp"
//#include "Controller/I_FTPconnection.hpp"

//class UserInterface ;
class I_FTPconnection ;
//class SyncData ;
class CFtpConnection ;

class FTPconnection
  : public I_FTPconnection
{
  enum status_code
  {
    ErrorGettingStartingDir
  };
private:
  CFtpConnection ** ppftpconnection ;
//  SyncData * mp_syncdata ;
//  UserInterface * mp_userinterface ;
public:
  FTPconnection(  
    SyncData & mp_syncdata //,
//    UserInterface & p_userinterface
    ) ;
  void StartOrRestartFTPSession() ;
};
