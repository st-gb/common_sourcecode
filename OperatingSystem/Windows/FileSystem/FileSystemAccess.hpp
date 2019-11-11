#pragma once

class I_UserInterface ;

#define COMPILE_AS_STATIC_CLASS_ELEMENTS static

namespace Windows_API
{
  class FileSystemAccess
  {
  private:
    COMPILE_AS_STATIC_CLASS_ELEMENTS I_UserInterface * mp_userinterface ;
  public:
    //Static has a little performance gain of member function: no
    //"this"-pointer is IMPLICITELY passed as a parameter
    //static
    COMPILE_AS_STATIC_CLASS_ELEMENTS
      DWORD 
  //#ifdef USE_NAMESPACES_INSTEAD_OF_MVC_PREFIXES
  //#endif // #ifdef USE_NAMESPACES_INSTEAD_OF_MVC_PREFIXES
      CreateMissingDirLevelsOfDirPath(
      const std::string & strFullDirPath
      , int & nIndexOfBackslashWhereErrorOccured
      ) ;
  };
};
