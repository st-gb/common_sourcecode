#pragma once///Include guard

/**see http://gcc.gnu.org/onlinedocs/cpp/Stringizing.html
 * Macro-expands the formal parametr "s" and quotes it afterwards. */
#define stringize(s) quote(s)
/// "#" quotes
#define quote(s) #s
