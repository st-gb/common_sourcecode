#include "GetCurrentWorkingDir.hpp"


namespace Linux
{
	void GetCurrentWorkingDirA(std::string & r_stdstr )
	{
		Linux_::GetCurrentWorkingDirA_inl(r_stdstr);
	}
}
