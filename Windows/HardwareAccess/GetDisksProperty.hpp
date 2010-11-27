/*
 * GetDisksProperty.hpp
 *
 *  Created on: Nov 26, 2010
 *      Author: Stefan
 */

#ifndef GETDISKSPROPERTY_HPP_
#define GETDISKSPROPERTY_HPP_

#include "HardwareAccess.hpp" //PSTORAGE_DEVICE_DESCRIPTOR
#include <windef.h> //BOOL

BOOL GetDisksProperty(HANDLE hDevice, PSTORAGE_DEVICE_DESCRIPTOR pDevDesc) ;

#endif /* GETDISKSPROPERTY_HPP_ */
