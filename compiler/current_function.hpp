/*
 * current_function.hpp
 *
 *  Created on: 19.12.2012
 *      Author: Stefan
 */

#ifndef CURRENT_FUNCTION_HPP_
#define CURRENT_FUNCTION_HPP_

namespace PrettyFunctionFormattedFunctionSignature
{
  /** @brief Get 1st namespace, class or function name character
   *  can e.g. be "inline virtual void FuncName(" 
   * Works with GCC ("__PRETTY_FUNCTION__") and maybe with MSVC ("__FUNCSIG__").
   */
  inline const char * Get1stIdentifierChar(
    const char * prettyFunctionFormattedFunctionName,
    const char * endOfFunctionName)
  {
    char * string = (char *) prettyFunctionFormattedFunctionName,
      * firstIdentifierChar = NULL;
    /** A space character separates the return type from the 
     *  function/class/namespace name*/
    string = strchr(string,' ') + 1;
    /** Get the space character directly before the function name. */
    while( string !=
      //by "(const char *)" : avoid g++ error "ISO C++ forbids comparison
      // between pointer and integer"
      (const char *)1 && string < endOfFunctionName )
    {
      firstIdentifierChar = string;
      //http://pubs.opengroup.org/onlinepubs/009695399/functions/strchr.html:
      //"null pointer if the byte was not found"
      string = strchr(string,' ') + 1;
    }
    /** Constructors don't have return types.-> no space before class name */
    if( firstIdentifierChar == NULL //(const char *)1
        )
      firstIdentifierChar = (char *) prettyFunctionFormattedFunctionName;
    return firstIdentifierChar;
  }

  /** GCC's __PRETTY_FUNCTION__ format is:
   * >>return type<< [namespace::]>>class name<< "::"
  * >>function name<< >>parameters list (only data type, no identifiers )<<
  * Works with GCC ("__PRETTY_FUNCTION__") and maybe with MSVC ("__FUNCSIG__").
  */
  inline std::string GetClassName(const char * prettyFunctionFormattedFunctionName)
  {
    char * string = (char *) prettyFunctionFormattedFunctionName,
      * firstOccurenceOfSculpRightOfFunctionName, * lastOccurenceOfSculp = NULL,
      * endOfFunctionName;
    const char * beginOfClassOrNamespaceName;/*, * endOfClassOrNamespaceName = NULL*/;

    /** The function name ends exactly left of the first "(" character. */
    endOfFunctionName = strchr(string,'(');
    beginOfClassOrNamespaceName = Get1stIdentifierChar(string,
      endOfFunctionName);
    /** It is important that the sculp does NOT belong to the return type which
        is before/left of the function sculp o*/
    firstOccurenceOfSculpRightOfFunctionName = strstr(endOfFunctionName,"::");
    //pass by all namespaces
    while(firstOccurenceOfSculpRightOfFunctionName &&
      //param may be "std::set"
      firstOccurenceOfSculpRightOfFunctionName < endOfFunctionName)
    {
      string = firstOccurenceOfSculpRightOfFunctionName + 2;
      lastOccurenceOfSculp = firstOccurenceOfSculpRightOfFunctionName;
      firstOccurenceOfSculpRightOfFunctionName = strstr(string,"::");
    }

//        if( ! beginOfClassOrNamespaceName )
    if( beginOfClassOrNamespaceName && lastOccurenceOfSculp )
    {
      std::string std_strClassName = std::string(
        beginOfClassOrNamespaceName,
        lastOccurenceOfSculp - beginOfClassOrNamespaceName);
      return //std::string(beginOfClassOrNamespaceName + 1,
//            beginOfClassOrNamespaceName - lastOccurenceOfSculp + 1);
        std_strClassName;
    }
    //->No class or namespace name existent: just a global function
    return "::"; //means : global scope
  }

  //TODO the identifier before a function name may also be a namespace name?!
  /** GCC's __PRETTY_FUNCTION__ format is:
   * >>return type<< [namespace::]>>class name<< "::"
  * >>function name<< >>parameters list (only data type, no identifiers )<<
  * Works with GCC ("__PRETTY_FUNCTION__") and maybe with MSVC ("__FUNCSIG__").
  */
  inline std::string GetFunctionName(
    const char * const prettyFunctionFormattedFunctionName)
  {
    const char * beginOfFunctionName;
    char * string = (char *) prettyFunctionFormattedFunctionName,
      * firstOccurenceOfSculp, * endOfFunctionName,
      * lastOccurenceOfSculp = NULL;
    endOfFunctionName = strchr(string,'(');

    firstOccurenceOfSculp = strstr(string,"::");
    //pass by all namespaces
    while(firstOccurenceOfSculp &&
        //param may be "std::set"
        firstOccurenceOfSculp < endOfFunctionName)
    {
      string = firstOccurenceOfSculp + 2;
      lastOccurenceOfSculp = firstOccurenceOfSculp;
      firstOccurenceOfSculp = strstr(string,"::");
    }
    if(lastOccurenceOfSculp)
    {
      beginOfFunctionName = lastOccurenceOfSculp + 2;
    }
    else
//          beginOfFunctionName = strchr(prettyFunctionFormattedFunctionName,
//            ' ') + 1;
      beginOfFunctionName = Get1stIdentifierChar(string, endOfFunctionName);
    return std::string(beginOfFunctionName,
      endOfFunctionName - beginOfFunctionName);
  }
} // namespace PrettyFunctionFormattedFunctionSignature


#endif /* CURRENT_FUNCTION_HPP_ */
