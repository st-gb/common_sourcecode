#pragma once //Include guard

#include <string> //class std::string


BYTE GetProcessFileName(DWORD dwProcessID,
    std::string & r_std_strProcessFileName);
