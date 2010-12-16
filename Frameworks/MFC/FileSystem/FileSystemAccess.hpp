#pragma once

#include <string>
#include <afx.h> //for class CFile
#include "Controller/I_FileSystemAccess.hpp"

class UserInterface ;
class ProtocolFileData ;

class FileSystemAccess
{
private:
  CFile m_fileFileAndDirChangeProtocol ;
  ProtocolFileData * mp_protocolfiledata ;
  UserInterface * mp_userinterface ;
public:
  FileSystemAccess(
    ProtocolFileData & r_protocolfiledata ,
    UserInterface & r_userinterface
    );
  {
     mp_protocolfiledata = & r_protocolfiledata ;
     mp_userinterface = & r_userinterface
  }

  bool LoadProtocol(//const CString & rcstrFilePath
      const std::string & rcstdstrFilePath)
  void WriteAndFlushProtocolFile() ;
};
