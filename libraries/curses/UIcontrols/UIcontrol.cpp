#include "UIcontrol.hpp"

std::set<int> curses::UIcontrol::s_colorPairIndices;

namespace curses { 
  void UIcontrol::SetFocus(bool focus) { 
    m_hasFocus = focus;
    if(focus == true)
      m_colorPair = /*s_colorPairIndices.at(activated) activated */ 6;
    else
      m_colorPair = /*s_colorPairIndices.at(deactivated) deactivated*/ 7;
    /** Update new color visually. */
    show();
  }
}
