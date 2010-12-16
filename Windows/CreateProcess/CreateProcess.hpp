/*
 * CreateProcess.hpp
 *
 *  Created on: May 22, 2010
 *      Author: Stefan
 */

#ifndef CREATEPROCESS_HPP_
#define CREATEPROCESS_HPP_

void InvokeApp(DWORD dwSessionID) ;

#include <string> //for std::wstring
#include <Controller/character_string/stdtstr.hpp> //class std::string

//class ServiceAttributes ;
class CreateProcessAsUserAttributes
{
  std::tstring m_stdtstrCommandLine ;
  std::tstring m_stdtstrCurrentDirectory ;
};

class CreateProcessAsUserAttributesW
{
public:
  std::wstring m_stdwstrCommandLine ;
  std::wstring m_stdwstrCurrentDirectory ;
};

namespace Windows_API
{
  //Using a class and store attributes that are are among functions is faster than
  // to copy them as parameters (global variables as alternative do not have the
  // encapsulation advantage)
  class CreateProcess
  {
  //  STARTUPINFO startupinfo;
    STARTUPINFOW startupinfo;
    PROCESS_INFORMATION process_information;
  //  ServiceAttributes & m_r_service_attrs ;
    CreateProcessAsUserAttributesW & m_r_createprocessasuserattributesw ;
  public:
    CreateProcess(//ServiceAttributes & r_service_attrs
      CreateProcessAsUserAttributesW & r_createprocessasuserattributesw )
  //    :
  //    m_r_service_attrs (r_service_attrs) {}
      ;
    BOOL CreateProcessAsNeeded(
      //Use param here for less error-prone change ( so the param value
      // can be switched easily)
      HANDLE handleToken
      ) ;
    void StartProcess(DWORD dwSessionID) ;
  };
}

#endif /* CREATEPROCESS_HPP_ */
