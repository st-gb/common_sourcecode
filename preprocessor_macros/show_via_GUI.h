/*
 * show_via_GUI.h
 *
 *  Created on: 05.02.2011
 *      Author: Stefan
 */

#ifndef SHOW_VIA_GUI_H_
#define SHOW_VIA_GUI_H_

#include <winuser.h> //::MessageBox(...)

#ifdef _TEST_VERSION
  #define SHOW_VIA_GUI(string) \
    ::MessageBox( \
      NULL, \
      string, \
      _T("info"), \
      MB_OK \
      );
#else
  #define SHOW_VIA_GUI(string) {}
#endif

#endif /* SHOW_VIA_GUI_H_ */
