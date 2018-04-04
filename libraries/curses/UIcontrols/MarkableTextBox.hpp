/** File:   MarkableTextBox.hpp
 * Author: sg
 * Created on 27. März 2018, 16:38 */

#ifndef MARKABLETEXTBOX_HPP
#define MARKABLETEXTBOX_HPP

#include "TextBox.hpp"
#include <vector> //class std::vector

namespace curses {
class MarkableTextBox
  : public curses::TextBox 
{
public:
    class Mark {
      public:
        int begin;
        int length;
        bool operator < (const Mark & rhs) const
        {
            if(begin < rhs.begin)
                return true;
            return false;
        }
        unsigned getMarkEnd() const
        {
            return begin + length;
        }
    };
    MarkableTextBox(chtype colorPair, chtype markColorPair);
    virtual ~MarkableTextBox() {}
    typedef std::set<MarkableTextBox::Mark> markPositionsType;
    void SetMark(const markPositionsType & markPositions) {
      m_markPositions = markPositions;
    }
    void HandleCurrentLine(
      const HandleCurrentLineParams & handleCurrentLineParams);
private:
  chtype m_markColorPair;
  markPositionsType m_markPositions;
};
}

#endif /* MARKABLETEXTBOX_HPP */

