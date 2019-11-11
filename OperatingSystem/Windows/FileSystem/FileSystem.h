/*
 * FileSystem.h
 *
 *  Created on: Nov 9, 2010
 *      Author: Stefan
 */

#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

bool FileExtensionIsIncluded(
  const CString & rcstrFullSourceFilePath,
  const std::vector<CString> & vecstrExtensions);
bool FileExtensionIsIncludedInVector(
  const CString & rcstrFilePath,
  const std::vector<CString> * pvecstrExtensions);
//f�r die sp�tere Verkettung(wenn man den VOLLEN Zielpfad
//erstellt), macht es sich am besten, wenn der Wurzel-
//Zielpfad bereits genau 1 Backslash am Ende hat
CString GetDirWith1TrailingBackslash(CString strDestinationDir);
std::vector<CString> * GetStringVectorOfExtensions(
  const CString & str);
CString GetDriveNameOrShareName(const CString & crstrFullPath);
bool IsDriveName(const CString & crstrFullPath);
BOOL IsUSBDrive(const CString & strFullPathOfDir);

std::vector<CString> ParseExcludeExtensionsFromCopying(
  const CString & str);
void ParseExcludeExtensionsFromCopying(
  const CString & str,std::vector<CString> &
  vecStrExcludeFileExtensionsFromCopying);

#endif /* FILESYSTEM_H_ */
