/*
 * IPv4.h
 *
 *  Created on: Nov 7, 2010
 *      Author: Stefan
 */

#ifndef IPV4_H_
#define IPV4_H_

#include <stdint.h> //uint32_t

bool IsPrivateIPv4Address(
  const char * pchIPAddress,
  const char * pchNetworkMask
  ) ;

uint32_t GetIPv4AddressAs32bitNumber(const char * const c_p_chIPv4Address);

#endif /* IPV4_H_ */
