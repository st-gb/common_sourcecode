
namespace FileSystem
{
#if defined(__linux__)
  const seperatorChar = '/';  
#elif defined(_WIN32) //Windows 32 or 64 bit
  const seperatorChar = '\\';
#endif
};
