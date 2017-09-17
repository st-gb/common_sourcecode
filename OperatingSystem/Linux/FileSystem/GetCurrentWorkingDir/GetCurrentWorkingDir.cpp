#include "GetCurrentWorkingDir.hpp"

namespace /*Linux*/ OperatingSystem
{
	void GetCurrentWorkingDirA(std::string & r_stdstr )
	{
		/*Linux_*/ OperatingSystem::GetCurrentWorkingDirA_inl(r_stdstr);
	}
}
