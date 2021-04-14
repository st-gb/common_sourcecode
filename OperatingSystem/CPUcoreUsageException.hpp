#include <string>///class std::wstring

class CPUcoreUsageException
{
private:
  std::wstring m_msg;
public:
  CPUcoreUsageException(/*LPWSTR*/const wchar_t* lpwstr){
    m_msg = lpwstr;
    }
  const wchar_t * getMessage() const {return m_msg.c_str();}
};
