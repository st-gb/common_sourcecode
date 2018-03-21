/** File:   Label.hpp
 * Author: sg
 * Created on 10. März 2018, 20:50 */

#ifndef LABEL_HPP
#define LABEL_HPP

#include <libraries/curses/UIcontrols/UIcontrol.hpp> //base class UIcontrol
#include <string> //class std::string

namespace curses {
class Label
  : public curses::UIcontrol
{
  std::string m_label;
public:
  Label();
  virtual ~Label();
  
  void SetLabel(const char * const label) { m_label = label; }
  std::string GetLabel() const { return m_label;}
  void show();
  void GetMinimalSize(int & width, int & height);
private:

};
}

#endif /* LABEL_HPP */

