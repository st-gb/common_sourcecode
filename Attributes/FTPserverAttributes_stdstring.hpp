#pragma once //include guard
#include <string> //class std::sting

class CFTPServerAttributes
{
public:
  bool m_bPassiveMode;
  //volatile bool m_vbFTPOperationInProgress;
  volatile BYTE m_vbyNumberOfFTPOperationsInProgress;
  std::string m_strServerName;
  std::string m_strPassword;
  std::string m_strUserName;
  std::string m_strFullDirPathBelowServerPathRootDir;
  unsigned short m_wPortNumber;

  CFTPServerAttributes(
    const std::string & rcstrServer,
    const std::string & rcstrUserName,
    const std::string & rcstrPassword,
    const std::string & rcstrObject,
    unsigned short nPort
    );
  static std::string GetPathOptimizedForProcessingChanges(
    const std::string & rcstrOriginalPath
    );
  //ChangeAttributes(rcstrServer,
  //    rcstrPassword,rcstrUserName,rcstrObject,nPort);
public:
  //The dir where it starts after the connection may be another
  //than the root dir("/"). This can be configured/specified on
  //the FTP SERVER side.
  //This is the topmost directory. This directory may not be shown with
  //browsers and may not be accessible due to limitation of (for example: "CDUP")
  //rights.
  std::string m_strStartingDir;
};
