this file is based on
https://gist.github.com/PurpleBooth/109311bb0361f32d87a2#file-readme-template-md

# common_sourcecode: sourcecode for multiple projects

Cross-platform (Windows/Linux/Android/POSIX) C++98/03 (kind of) library.

Some paths to source and header files don't seem be senseful and so may need to
change.

## Highest Quality Source Code

Not all of the source code is on a high standard (from point of view of a 
quality-aware long-year software engineer with an Master of Science in Computer
Science).

the highest level code (Apr 2021) is:

* multithread-safe logger (/Controller/Logger)
  - able store file formats:
    * log4j
    * HTML
    * txt
  - able to output the following attributes in log entries:
    * function name where the log output happens. Therefore it uses GCC's
      "\__PRETTY_FUNCTION__"
    * thread name (must be set via I_Thread::SetThreadName(...) from
      "OperatingSystem/multithread/I\_Thread.hpp" from the thread whose name is
      to set before)
    * thread ID
    * date and time of log output
    * log level
  - configurable time format string with place holders/variables/fields like
    {year},{month},{day},{hour},{minute},{second},{millisecond} that are
    preprocessed in I_LogFormatter::GetNeededArraySizeForTimeString(const
    std::string &) to save time when logging
* [iterable](http://en.wikipedia.org/wiki/Iterator)
  [trie](http://en.wikipedia.org/wiki/Trie) data structure with template as
  member
 
  (/data_structures/Trie)

  Uses a template instead of "void \*" for information on nodes so e.g. a member
  function pointer (needs more than "sizeof(void *)" bytes?!) may be stored
  there.
* [BSD sockets](http://en.wikipedia.org/wiki/Berkeley_sockets) : ease of use of/
  unified (cross-OS) access to its functions:
  - /OperatingSystem/BSD/socket
  - /OperatingSystem/Windows/BSD_sockets
  - /OperatingSystem/POSIX/BSD_sockets
* multithreading and synchronization
  - /OperatingSystem/mutithread
  - /OperatingSystem/POSIX/mutithread
  - /OperatingSystem/Windows/mutithread
* CPU core usage via
  [Performance Data Helper](
   http://docs.microsoft.com/en-us/windows/win32/perfctrs/performance-counters-functions)
  in MS Windows

  (/OperatingSystem/Windows/GetCPUusage/PerformanceDataHelper)

  This is the least CPU-time consuming way to get the CPU core usage via MS
  Windows known by the author.
* [Windows power profile](
   http://docs.microsoft.com/en-us/windows/win32/power/power-management-functions)
   access

  (/OperatingSystem/Windows/PowerProfAccess)

  Is able to access (unified) via 2 (dynamically linked at runtime to enable
  both APIs with the same executable) power profile APIs:
  - API for access up to Windows XP/Server 2003
  - API for access beginnung from Windows v.6/Vista
* Apache Xerces (/Xerces)

## Authors

[Stefan Gebauer, M.Sc. Comp. Sc.](https://github.com/st-gb)

## License

Copyright by Stefan Gebauer, no commercial use without grant.
If you want to use the code in a commercial product then contact the author.

You may use the code free of charge

- to study the implementation and quality (of one of the authour's software
  products) so bugs can be reported.
- in a non-commercial product if it is not in competition with an author's
  software product.
  
  If in doubt which applications this affects then ask the author.

It is appreciated to reference the author (e.g. in the "about" dialog or
README.txt) if using this code. Therefore please refer to this github user page
and/or to "it-gebauer.de".
