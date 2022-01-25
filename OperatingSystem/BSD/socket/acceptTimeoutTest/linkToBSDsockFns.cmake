if(WIN32)#If building for (also <> 32 bit) Microsoft Windows 
#http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept :
# "Library 	Ws2_32.lib"
#http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-bind :
# "Library 	Ws2_32.lib"
#http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-htons :
# "Library 	Ws2_32.lib"
#http://docs.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-inet_ntoa
# : "Library 	Ws2_32.lib"
#http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen :
# "Library 	Ws2_32.lib"
#http://docs.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-socket
# "Library 	Ws2_32.lib"
target_link_libraries(${exeFileName} ws2_32)#For Windows socket functions.
endif()