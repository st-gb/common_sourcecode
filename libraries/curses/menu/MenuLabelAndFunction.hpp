#pragma once

namespace curses {

typedef void (*FUNC)(void);

struct MenuLabelAndFunction
{
  std::string m_label;
  curses::FUNC m_function;
};

}
