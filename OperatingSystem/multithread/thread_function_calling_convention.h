#pragma once

//Built-in preprocessor macro for MSVC, MinGW (also for 64 bit)
#ifdef _WIN32 //under Linux g++ error if "__stdcall"
  #define THREAD_FUNCTION_CALLING_CONVENTION __stdcall
#else
  #define THREAD_FUNCTION_CALLING_CONVENTION //-> empty
#endif
