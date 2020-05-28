#ifdef _WIN32///if compiling for Microsoft Windows (also 64 bit).
 #include "../Windows/time/GetUptime.h"
#endif

#ifdef __linux__
 #include "../Linux/time/GetUptime.h"
#endif
