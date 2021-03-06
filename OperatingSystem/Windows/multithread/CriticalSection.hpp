/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * I_CriticalSection.hpp
 *
 *  Created on: 06.02.2011
 *      Author: Stefan
 */

#ifndef I_CRITICALSECTION_HPP_
#define I_CRITICALSECTION_HPP_

#include <windows.h> //CRITICAL_SECTION, ::EnterCriticalSection(...)

namespace OperatingSystem
{
  namespace Windows
  {
    class CriticalSection
    {
      CRITICAL_SECTION m_critical_section;
    public:
      CriticalSection()
      {
        //http://msdn.microsoft.com/en-us/library/ms682530%28v=vs.85%29.aspx:
        //"Before the threads of the process can use it, initialize the
        //critical section by using the InitializeCriticalSection"
        ::InitializeCriticalSection(& m_critical_section);
      }
      ~CriticalSection()
      {
        ::DeleteCriticalSection(& m_critical_section);
      }
      void Enter()
      {
        ::EnterCriticalSection(& m_critical_section);
      }
      void Leave()
      {
        ::LeaveCriticalSection(& m_critical_section);
      }
    };
  }
}

#endif /* I_CRITICALSECTION_HPP_ */
