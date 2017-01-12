/*
 * GetSectorSize.h
 *
 *  Created on: 01.01.2016
 *      Author: ubuntu
 */

#ifndef GETSECTORSIZE_H_
#define GETSECTORSIZE_H_

#include <stdint.h> //uint64_t

#ifdef __cplusplus
extern "C"
uint64_t GetLogicalSectorSizeInBytes(const char * const fileName);
#endif

#endif /* GETSECTORSIZE_H_ */
