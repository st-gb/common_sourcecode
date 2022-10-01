#pragma once///Include guard

/**see http://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
 * Macro-expands the formal parametr "s" and quotes it afterwards. */
#define stringize(s) quote(s)
/// "#" quotes
#define quote(s) #s

/**Adapted from:
* http://stackoverflow.com/questions/56103136/create-string-and-wide-string-literals-from-a-single-definition
* */
#define MakeWcharStr_Expand1st(x) L##x
#define MakeWcharStr(x) MakeWcharStr_Expand1st(x)
