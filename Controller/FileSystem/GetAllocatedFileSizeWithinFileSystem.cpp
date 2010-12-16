/*
 * GetAllocatedFileSizeWithinFileSystem.cpp
 *
 *  Created on: Nov 5, 2010
 *      Author: Stefan
 */
#include <windows.h> //ULARGE_INTEGER

ULARGE_INTEGER GetAllocatedFileSizeWithinFileSystem(
  DWORD dwFileSizeHigh,
  DWORD dwFileSizeLow,
  DWORD dwClusterSize
  )
{
  ULARGE_INTEGER uliFileSize;
  ULARGE_INTEGER uliAllocatedClustersOr1Less;
  uliFileSize.HighPart=dwFileSizeHigh;
  uliFileSize.LowPart=dwFileSizeLow;

  uliAllocatedClustersOr1Less.QuadPart = (ULONGLONG)(
    uliFileSize.QuadPart / dwClusterSize);
  //wenn nicht alle Cluster voll mit Dateiinhalt sind
  if((ULONGLONG)(uliAllocatedClustersOr1Less.QuadPart*
    dwClusterSize) != uliFileSize.QuadPart)
    //ungenutzer Platz des letzten Clusters
    uliFileSize.QuadPart=(ULONGLONG)((ULONGLONG)
      (uliAllocatedClustersOr1Less.QuadPart+1)*
      dwClusterSize);
  return uliFileSize;
}
