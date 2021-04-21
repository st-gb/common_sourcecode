this file is based on
https://gist.github.com/PurpleBooth/109311bb0361f32d87a2#file-readme-template-md

# common_sourcecode: sourcecode for multiple projects

Cross-platform (Windows/Linux/Android/POSIX) C++98/03 (kind of) library.

Some paths don't seem be senseful and so may need to change.

## Highest Quality Source Code

Not all of the source code is on a high standard (from point of view of a 
quality-aware long-year software engineer with an Master of Science in Computer Science).

the highest level code (Apr 2021) is:

* multithread-safe logger (/Controller/Logger)
* Trie data structure (/data_structures/Trie)
* BSD sockets and concrete implementations in
  - /OperatingSystem/BSD/socket
  - /OperatingSystem/Windows/BSD_sockets
  - /OperatingSystem/POSIX/BSD_sockets
* multithreading and synchronization
  - /OperatingSystem/mutithread
  - /OperatingSystem/POSIX/mutithread
  - /OperatingSystem/Windows/mutithread
* CPU core usage via Performance Data Helper
  (/OperatingSystem/Windows/GetCPUusage/PerformanceDataHelper)
* Windows power profile access
  (/OperatingSystem/Windows/PowerProfAccess)
* Apache Xerces (/Xerces)

## Authors

[Stefan Gebauer, M.Sc. Comp. Sc.](https://github.com/st-gb)

## License

Copyright by Stefan Gebauer, no commercial use without grant
