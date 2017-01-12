/*
 * GetDeviceSize.h
 *
 *  Created on: 28.11.2015
 *      Author: ubuntu
 */

#ifndef GETDEVICESIZE_H_
#define GETDEVICESIZE_H_

#include <stdint.h> //uint64_t

#ifdef __cplusplus
extern "C" {
#endif //#ifdef __cplusplus
uint64_t GetDeviceSizeInBytes(const char * const fileName);
#ifdef __cplusplus
}
#endif //#ifdef __cplusplus

#endif /* GETDEVICESIZE_H_ */
