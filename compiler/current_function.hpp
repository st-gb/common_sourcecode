/*
 * current_function.hpp
 *
 *  Created on: 19.12.2012
 *      Author: Stefan
 */

#ifndef CURRENT_FUNCTION_HPP_
#define CURRENT_FUNCTION_HPP_

  /** Get 1st namespace, class or function name character
   *  can e.g. be "inline virtual void FuncName(" */
  inline const char * Get1stIdentifierChar(
    const char * prettyFunctionFormattedFunctionName,
    const char * endOfFunctionName)
  {
    char * string = (char *) prettyFunctionFormattedFunctionName,
      * firstIdentifierChar = NULL;
    string = strchr(string,' ') + 1;
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
    //C'tors don't have return types.-> no space before class name
    if( firstIdentifierChar == NULL //(const char *)1
        )
      firstIdentifierChar = (char *) prettyFunctionFormattedFunctionName;
    return firstIdentifierChar;
  }

  /** GCC's __PRETTY_FUNCTION__ format is:
   * >>return type<< [namespace::]>>class name<< "::"
* >>function name<< >>parameters list (only data type, no identifiers )<<*/
  inline std::string GetClassName(const char * prettyFunctionFormattedFunctionName)
  {
    char * string = (char *) prettyFunctionFormattedFunctionName,
      * firstOccurenceOfSculp, * lastOccurenceOfSculp = NULL,
      * endOfFunctionName;
    const char * beginOfClassOrNamespaceName;/*, * endOfClassOrNamespaceName = NULL*/;

    endOfFunctionName = strchr(string,'(');
    beginOfClassOrNamespaceName = Get1stIdentifierChar(string,
      endOfFunctionName);
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

  /** GCC's __PRETTY_FUNCTION__ format is:
   * >>return type<< [namespace::]>>class name<< "::"
* >>function name<< >>parameters list (only data type, no identifiers )<<*/
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


#endif /* CURRENT_FUNCTION_HPP_ */
