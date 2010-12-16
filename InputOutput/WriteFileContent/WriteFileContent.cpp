#include <fstream> //for std::ofstream
//#include <global.h> //LOGN()
#include <preprocessor_macros/logging_preprocessor_macros.h> //LOGN(...)
//#include <windef.h> //BYTE
typedef unsigned char BYTE ;

BYTE WriteFileContent(
  const std::string & cr_stdstrFilePath , 
  const std::string & cr_stdstrFileContent
  )
{
  BYTE by = 0 ;
  std::ofstream stdofstream ;
  stdofstream.open( cr_stdstrFilePath.c_str()
    , //std::ifstream::in
    // std::ios_base::in
    std::_S_out |
    std::_S_trunc
    );
  if( stdofstream.is_open() )
  {
    LOGN("successfully opened file \"" << cr_stdstrFilePath << "\"" )
//    //http://www.cplusplus.com/reference/iostream/istream/seekg/:
//    stdifstream.seekg(0, std::ios::end);
//    int length = stdifstream.tellg();
//    stdifstream.seekg (0, std::ios::beg);
    // allocate memory:
//    buffer = new char [length + 1 ];

    // read data as a block:
    stdofstream.write (
      cr_stdstrFileContent.c_str() ,
      cr_stdstrFileContent.length()
      );
//    buffer[ length ] =
//      //string terminating NULL char.
//      '\0' ;
    stdofstream.close();
    by = 1 ;
  }
  else
  {
    LOGN("failed to open file \"" << cr_stdstrFilePath << "\"" )
  }
  return by ;
}
