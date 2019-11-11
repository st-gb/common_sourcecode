/*
 * GetCurrentProcessExeFileNameWithoutDirs.cpp
 *
 *  Created on: Apr 27, 2010
 *      Author: Stefan
 */
//#include <string>
//#include "StdAfx.h"
#include "GetCurrentProcessExeFileNameWithoutDirs.hpp"

std::tstring CurrentProcess::GetExeFileNameWithoutDirs()
{
  return GetExeFileNameWithoutDirs_inline();
}
