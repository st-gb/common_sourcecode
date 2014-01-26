#include "GetCurrentWorkingDir.hpp"


namespace Linux
{
	void GetCurrentWorkingDirA(std::string & r_stdstr )
	{
		GetCurrentWorkingDirA_inl(r_stdstr);
	}
}
