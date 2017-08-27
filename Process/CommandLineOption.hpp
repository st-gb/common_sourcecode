/** File:   CommandLineOption.hpp
 * Author: sg
 * Created on 26. Juni 2017, 00:43  */

#ifndef COMMANDLINEOPTION_HPP
#define COMMANDLINEOPTION_HPP

/** @param charType: e.g. char or wchar_t */
/*template<typename charType>*/ struct CommandLineOption
{
  typedef char charType;
  const charType * optionName;
  const charType * possibleOptionValue;
  void (*pfn )(const char []);
};

#endif /* COMMANDLINEOPTION_HPP */

