/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * show_via_GUI.h
 *
 *  Created on: 05.02.2011
 *      Author: Stefan
 */

#ifndef SHOW_VIA_GUI_H_
#define SHOW_VIA_GUI_H_

#ifdef _TEST_VERSION
  #ifdef _WIN32
  #include <winuser.h> //::MessageBox(...)

    #define SHOW_VIA_GUI(string) \
      ::MessageBox( \
        NULL, \
        string, \
        _T("info"), \
        MB_OK \
        );
  #endif //#ifdef _WIN32
#else
  #define SHOW_VIA_GUI(string) {}
#endif

#endif /* SHOW_VIA_GUI_H_ */
