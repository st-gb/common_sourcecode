/*
 * HideMinGWconsoleWindow.h
 *
 *  Created on: Sep 8, 2010
 *      Author: Stefan
 */

#ifndef HIDEMINGWCONSOLEWINDOW_H_
#define HIDEMINGWCONSOLEWINDOW_H_

  #if ! defined(_DEBUG) && defined(__MINGW32__)
    #include <winuser.h> //ShowWindow(...)
    //see http://www.gamedev.net/community/forums/topic.asp?topic_id=209528:
    //You may also pass "-mwindows" to gcc/ g++.
    void HideMinGWconsoleWindow()
    {
      //from Florian Doersch:
      //Hide the MinGW console window (was not necessary if compiled with MSVC/
      // under Linux)
      ShowWindow( GetConsoleWindow(), SW_HIDE);
    }
  #else
    inline void HideMinGWconsoleWindow() {}
  #endif

#endif /* HIDEMINGWCONSOLEWINDOW_H_ */
