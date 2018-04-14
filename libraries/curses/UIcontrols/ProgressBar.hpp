/** File:   ProgressBar.h
 * Author: root
 * Created on 7. April 2018, 12:42  */

#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "UIcontrol.hpp" //base class curses::UIcontrol

namespace curses {
class ProgressBar
  : public curses::UIcontrol
{
public:
    ProgressBar(chtype colorPair) 
      : m_colorPair(colorPair),
        m_progress(0) 
        { }
//    ProgressBar(const ProgressBar& orig);
    virtual ~ProgressBar() {}
    
    void show();
    void SetProgress(unsigned progress) { }
private:
   chtype m_colorPair;
   signed m_progress;
};
} //namespace end

#endif /* PROGRESSBAR_H */

