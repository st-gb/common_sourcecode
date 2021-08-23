# Functionality of this Repository's BSD sockets Files

Ease of use of/unified ([cross-Operating System](
http://en.wikipedia.org/wiki/Cross-platform_software#Software), currently
[Linux](
http://en.wikipedia.org/wiki/Linux)/[POSIX](http://en.wikipedia.org/wiki/POSIX)
and [Microsoft Windows](http://en.wikipedia.org/wiki/Microsoft_Windows)) access
to [BSD sockets](http://en.wikipedia.org/wiki/Berkeley_sockets) functions. If
these files are included into a [C++](http://en.wikipedia.org/wiki/C%2B%2B)
source file then often the file content (functions, enums, ...) is enclosed into
the [namespace](http://en.wikipedia.org/wiki/Namespace#Use_in_common_languages) "OperatingSystem::BSD::sockets" as [conditional compilation](
http://en.wikipedia.org/wiki/Conditional_compilation) ("#ifdef __cplusplus").\
(State: 08 Aug 2021):

- [/OperatingSystem/BSD/socket/](/OperatingSystem/BSD/socket) :
  - [**blckngCnnctErrMsg**.hpp](
    OperatingSystem/BSD/socket/blckngCnnctErrMsg.hpp) :
    - inline std::string **GetPossibleCause**_inl(const enum errorCodes errCode,
const int port) :\
      Gets description for possible error cause for errors [connecting (via TCP)
      to BSD sockets server](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Client) in [blocking mode](
    http://en.wikipedia.org/wiki/Berkeley_sockets#Blocking_and_non-blocking_mode
      ) in English language.
  - [**gethostbyname**.h](OperatingSystem/BSD/socket/gethostbyname.h) :
    - includes header files for BSD sockets API's "[gethostbyname](
      http://linux.die.net/man/3/gethostbyname)(...)"
      function specific to Linux & Microsoft Windows
    - "**enum gethostbynameRslt**" for cross-POSIX/-Windows state ([h_errno](
      http://pubs.opengroup.org/onlinepubs/009695399/functions/h_errno.html)) after calling
      the "[gethostbyname](OperatingSystem/BSD/socket/gethostbyname.h)" function
  - **getHostDBentry**.h :
    - enum gethostbynameRslt **GetHostDataBaseEntry**(...) :\
      Calls BSD sockets API's function "[gethostbyname](
      http://linux.die.net/man/3/gethostbyname)" and performs
      cross-POSIX/-Microsoft Windows error handling.
  - **getSocketError**.h
    - inline int **getSocketError**(const int socketFileDescriptor) :\
      Gets (error) code from calling [getsockopt](
    http://pubs.opengroup.org/onlinepubs/007908799/xns/getsockopt.html)(...,
      [SOL_SOCKET](
http://www.gnu.org/software/libc/manual/html_node/Socket_002dLevel-Options.html)
, [SO_ERROR](http://pubs.opengroup.org/onlinepubs/007908799/xns/getsockopt.html)
, ...);
  - **getSocketFileDesc**.h :
    - inline int **GetSocketFileDesc**(...) :\
      Documented (source code comments) way of calling BSD sockets API's
      "[socket](
   http://pubs.opengroup.org/onlinepubs/009604499/functions/socket.html)"(...)
      function in order to create a socket and get its [file descriptor](
      http://en.wikipedia.org/wiki/File_descriptor) number
  - **initSrv**.cpp / initSrv.h :
    - enum InitSrvRslt **initSrv**(...) :\
      Performs [socket server](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Server) initialization with steps common to both [TCP](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Server) and [UDP](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Server_2),
      accepting all incoming sockets (via [INADDR_ANY](
http://www.oreilly.com/library/view/practical-c-programming/9781838641108/d27298fa-6ef4-45b4-9e6d-62c1e3aef7ed.xhtml))
    - std::string **getErrorMsg**(**enum InitSrvRslt** & initSrvRslt) :\
      Gets English (error) message for [server socket](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Server) initialization.
  - **interruptSelect**.h :
    - inline void **interruptSelect**(void * p_v) :\
      Interrupts the BSD socket API's "[select](
      http://pubs.opengroup.org/onlinepubs/7908799/xsh/select.html)"(...)
      function (for [non-blocking](
   http://en.wikipedia.org/wiki/Berkeley_sockets#Blocking_and_non-blocking_mode)
      connection attempts) in cross-POSIX/-Microsoft Windows manner
  - **isNonBlckngCnnctRtrnCode**.h :
    - bool **isNonBlckngCnnctRtrnCode**() :\
      Microsoft Windows-/POSIX-specific determination if a return code means a
      [non-blocking](
    http://en.wikipedia.org/wiki/Berkeley_sockets#Blocking_and_non-blocking_mode
      ) connection attempt is running (and not completed yet?).
  - **NonBlockingConnect**.h :
    - inline bool **NonBlckingIsCnnctd**(...) :\
      True if the BSD sockets' "[select](
      http://pubs.opengroup.org/onlinepubs/7908799/xsh/select.html)" function
      completed and the BSD sockets [client](
      http://en.wikipedia.org/wiki/Client_(computing)) is connected (via [TCP](
      http://en.wikipedia.org/wiki/Transmission_Control_Protocol)) in
      [non-blocking](
    http://en.wikipedia.org/wiki/Berkeley_sockets#Blocking_and_non-blocking_mode
      ) mode.
  - **prepAccept**.cpp / prepAccept.h :
    - enum InitSrvRslt **prepAccept**(...) :\
      Prepares [server socket](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Server) steps that are
      neccessary to call the BSD socket API's "[accept](
      http://pubs.opengroup.org/onlinepubs/009695399/functions/accept.html)"
      function for [TCP](
      http://en.wikipedia.org/wiki/Transmission_Control_Protocol)):
      1. Calls initSrv(...) from "initSrv.cpp"
      2. Calls BSD sockets' "[listen](
     http://pubs.opengroup.org/onlinepubs/009695399/functions/listen.html)"(...)
       function.
  - **prepCnnctToSrv.c** :
    - **prepCnnctToSrv**(...) :\
    Prepares the client socket common for both [UDP](
      http://en.wikipedia.org/wiki/User_Datagram_Protocol) and for [TCP](
      http://en.wikipedia.org/wiki/Transmission_Control_Protocol)) (before
      calling BSD sockets' "[connect](
    http://pubs.opengroup.org/onlinepubs/009695399/functions/connect.html)"(...)
    function in order to connect to socket server) by performing the necessary
    steps and their error handling:
      1. calls GetSocketFileDesc(...)
      2. checks for error from calling GetSocketFileDesc(...)
      3. calls GetHostDataBaseEntry(...)
      4. checks for error from calling GetHostDataBaseEntry(...)
      5. copies/sets server address, [address family] and server [port number](
      http://en.wikipedia.org/wiki/Port_(computer_networking)#Port_number)
      for the struct "[sockaddr_in](
http://docs.microsoft.com/de-de/windows/win32/api/ws2def/ns-ws2def-sockaddr_in)"
  - **prepCnnctToSrv.h** :
    - Provides "**enum PrepCnnctToSrvRslt**" for return codes of
      "prepCnnctToSrv(...)"
  - **setBlockingMode**.h :\
    Includes (Operating System-)specific files to set a BSD socket to [blocking
    or non-blocking mode ](
    http://en.wikipedia.org/wiki/Berkeley_sockets#Blocking_and_non-blocking_mode
    ) in a cross-POSIX/-Microsoft Windows way. These files should provide the
    following [function signatures](
    http://en.wikipedia.org/wiki/Type_signature#C/C++_2):
    - inline int **setBlockingSocket**(const int socketFileDesc)
    - inline int **setNonBlockingSocket**(const int socketFileDesc)
  - **sockaddr_in**.h :\
    Includes struct "[sockaddr_in](
http://docs.microsoft.com/de-de/windows/win32/api/ws2def/ns-ws2def-sockaddr_in)"
in a cross-POSIX/Microsoft Windows way
  - **socket.h** :
    - int **readFromSocket**(...) :\
      Reads from [BSD socket](http://en.wikipedia.org/wiki/Berkeley_sockets)
      using  "[recv](
      http://pubs.opengroup.org/onlinepubs/007904975/functions/recv.html)" or
      "[read](
      http://pubs.opengroup.org/onlinepubs/009604599/functions/read.html)"
      (system call) function.
    - int **readFromSocket2**(...) :\
      Reads from [BSD socket](http://en.wikipedia.org/wiki/Berkeley_sockets)
      in a loop until all bytes to read have been read.
  - [**socketTimeout**.cpp](OperatingSystem/BSD/socket/socketTimeout.cpp) /
      socketTimeout.h :
    - int **get**SocketTimeout(...) :\
      Sets receive or send [timeout](
      http://en.wikipedia.org/wiki/Timeout_(computing)) via [BSD sockets API's](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Socket_API_functions)
      "[setsockopt](
    http://pubs.opengroup.org/onlinepubs/009695399/functions/setsockopt.html)"
      function.
    - int **set**SocketTimeout(...) :\
      Gets receive or send timeout via [BSD sockets API's](
      http://en.wikipedia.org/wiki/Berkeley_sockets#Socket_API_functions)
      "[getsockopt](
    http://pubs.opengroup.org/onlinepubs/009696799/functions/getsockopt.html)"
      function.
    - enum GetSocketTimeoutRslt **GetSocketTimeoutInS**(const int
      socketFileDesc, double * p_timeoutInS) :\
      Retrieves the send and receive timeouts and sets the timeout to the
      smaller one of both.
    - inline std::string **GetPossibleCause**_inl(const enum errorCodes) :\
      Gets description for possible error cause in English language.
- /OperatingSystem/**POSIX/BSD_sockets/sockets**.h
  - inline void CloseSocket() :\
    Dummy/empty function for unification to the implementation for Microsoft
    Windows.
  - inline enum errorCodes OperatingSystem::BSD::sockets::**GetLastError**()/
    **GetLastBSDsockError**() :\
    Conversion of [errno](http://en.wikipedia.org/wiki/Errno.h) from calls to
    the BSD sockets API to OS-independent "enum
    OperatingSystem::BSD::sockets::errorCodes".
  - inline void InitSocket() \
    Dummy/empty function for unification to the implementation for Microsoft
    Windows.
- /OperatingSystem/**Windows/BSD_sockets/sockets**.h :
  - inline void **CloseSocket**() :\
    Calls function "[WSACleanup](
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsacleanup)()".
  - inline enum errorCodes OperatingSystem::BSD::sockets::**GetLastError**()/
    **GetLastBSDsockError**() :\
    Conversion of last Windows sockets error (got from call to function "[WSAGetLastError](
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
    )") to OS-independent "enum OperatingSystem::BSD::sockets::errorCodes".
  - inline void **InitSocket**() :\
    Performs [Winsock](http://en.wikipedia.org/wiki/Winsock) initialization
    (calls function [WSAStartup](
http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
    )(...) )
