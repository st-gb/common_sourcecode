/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/** ReadFileContent.h
 *  Created on: Jun 12, 2010
 *      Author: Stefan  */

#ifndef READFILECONTENT_H_
#define READFILECONTENT_H_

//#include <string>
//#include <stdint.h> //uint8_t
//#include <hardware/CPU/fastest_data_type.h>
//typedef unsigned char BYTE;

/** Forward declaration. */
class ByteArray;

unsigned char ReadFileContent( const char * const strFilePath, 
  //uint8_t *& buffer, fastestUnsignedDataType & length
  ByteArray & byteArray);

#endif /* READFILECONTENT_H_ */
