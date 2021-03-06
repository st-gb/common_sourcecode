/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/** ReadFileContent.cpp
 *  Created on: Jun 12, 2010
 *      Author: Stefan  */
#include <fstream> //for std::ifstream
//#include <global.h> //LOGN()
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
// OperatingSystem::GetErrorMessageFromLastErrorCodeA(...)
#include <OperatingSystem/GetErrorMessageFromLastErrorCode.hpp>
#include "ReadFileContent.hpp"
#include <data_structures/ByteArray.hpp> //class ByteArray
//#include <windef.h> //BYTE

BYTE ReadFileContent( const char * strFilePath, ByteArray & byteArray )
{
  BYTE by = 0 ;
  std::ifstream stdifstream ;
  stdifstream.open( strFilePath
    , //std::ifstream::in
    std::ios_base::in ///works with clang
    // std::_S_in
    );
  if( stdifstream.is_open() )
  {
//    char * buffer ;
    LOGN_TYPE("successfully opened file \"" << strFilePath << "\"",
      LogLevel::success)
    //http://www.cplusplus.com/reference/iostream/istream/seekg/:
    stdifstream.seekg(0, std::ios::end);
    const fastestUnsignedDataType fileSizeInBytes = stdifstream.tellg();
    stdifstream.seekg (0, std::ios::beg);
    
    // allocate memory:
//    buffer = new uint8_t [length /*+ 1*/ ];
    byteArray.SetCapacity(fileSizeInBytes);

    // read data as a block:
    stdifstream.read( (char*) /*buffer*/ byteArray.GetArray(), fileSizeInBytes);
//    buffer[ length ] =
//      //string terminating NULL char.
//      '\0' ;
//    r_stdstrFilePath = std::string( buffer ) ;
    stdifstream.close();
//    delete[] buffer;
    by = 1 ;
  }
  else
  {
    LOGN_TYPE("failed to open file \"" << strFilePath << "\": error code:"
      << //stdifstream.rdstate()
      OperatingSystem::GetErrorMessageFromLastErrorCodeA(),
      LogLevel::error)

  }
  return by ;
}

#include <map> //class std::map
void ReadPropertiesFile(const std::string & r_stdstrFilePath,
  std::map<std::string, std::string> & r_std_map)
{
  std::ifstream stdifstream ;
  stdifstream.open( r_stdstrFilePath.c_str()
    , //std::ifstream::in
    std::ios_base::in ///works with clang compiler
    // std::_S_in
    );
  if( stdifstream.is_open() )
  {
    std::string strLine;
    std::getline ( stdifstream, strLine );

    stdifstream.close();
  }
}
