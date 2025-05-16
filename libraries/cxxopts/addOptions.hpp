#pragma once///Include guard

///Stefan Gebauer's(TU Berlin matriculation number 36095) ~"cmnSrc" files:
 #include <compiler/force_inline.h>///TU_Bln361095frcInln

namespace cxxopts{

template <typename optionType> TU_Bln361095freInln void addOptions(
  cxxopts::Options & cmdLineOpts,
  const char flagName[],
  const char description[])
{
  ///1. Calls OptionAdder Options::add_options(std::string group = "")
  cmdLineOpts.add_options()
    ///2. Calls class OptionAdder::operator()(...)
    (flagName, description, cxxopts::value<
    /**Causes a std::bad_cast exception if the data type here and in template
     * <typename T> cxxopts::OptionValue.as() / handleArg(...) differs.*/
	  optionType>()
    );
}

}///End namespace
