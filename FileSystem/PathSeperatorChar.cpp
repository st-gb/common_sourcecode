
namespace FileSystem
{
#if defined(__linux__)
  const char dirSeperatorChar = '/';  
#elif defined(_WIN32) //Windows 32 or 64 bit
  const char dirSeperatorChar = '\\';
#endif
};
