/*
 * GetNumberOfLogicalCPUcores.c
 *
 *  Created on: 30.08.2010
 *      Author: sgebauer
 */

//#include <fstream> //for std::ifstream
#include <stdio.h>

typedef unsigned short WORD ;
typedef unsigned char BYTE ;

unsigned short GetNumberOfLogicalCPUcores()
{
  WORD wNumCPUcores = 0 ;

//  std::ifstream stdifstream ;
//  stdifstream.open( r_stdstrFilePath.c_str()
//  while(stdifstream.)
  FILE * p_file = fopen("/proc/cpuinfo", "r") ;
  if( p_file )
  {
    BYTE bPreviousCharIsCarriageReturn = 0 ;
    int nChar ;
    do
    {
      nChar = fgetc (p_file);
      if( nChar == 0xA )
      {
        //1 CPU core info set ends with 2 newline characters
        if( bPreviousCharIsCarriageReturn )
          ++ wNumCPUcores ;
        bPreviousCharIsCarriageReturn = 1 ;
      }
      else
        bPreviousCharIsCarriageReturn = 0 ;
    }while( nChar != EOF ) ;
    fclose( p_file ) ;
  }
  return wNumCPUcores ;
}
