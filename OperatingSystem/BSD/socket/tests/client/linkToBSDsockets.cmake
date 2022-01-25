if(WIN32)#If building for Microsoft Windows (also <> 32 bit)
  # "ws2_32" library for gethostbyaddr(...),inet_ntoa(...),connect(...),
  # socket(...),gethostbyname(...),WSAGetLastError(...),htons(...) :
  #http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-gethostbyaddr
  # : "Library 	Ws2_32.lib"
  #http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-inet_ntoa
  # : "Library 	Ws2_32.lib"
  #http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-connect
  # : "Library 	Ws2_32.lib"
  #http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
  # : "Library 	Ws2_32.lib"
  #http://docs.microsoft.com/en-us/windows/win32/api/wsipv6ok/nf-wsipv6ok-gethostbyname
  # : "Library 	Ws2_32.lib"
  #http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsagetlasterror
  # : "Library  Ws2_32.lib"
  target_link_libraries(${exeFileName} ws2_32)
endif()
