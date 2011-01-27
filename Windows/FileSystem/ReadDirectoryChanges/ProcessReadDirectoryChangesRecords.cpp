/*
 * ProcessReadDirectoryChangesRecords.cpp
 *
 *  Created on: Dec 25, 2010
 *      Author: Stefan
 */
#include <string> //class std::string

//for ProcessReadDirectoryChangesRecords(...), this array should be defined in
//a source file, else if #included (multiple times) then there might be
//"multiple definitions" of this array.
std::string g_ar_stdstrFileActions [] = {
  "" ,
  "FILE_ACTION_ADDED" , //FILE_ACTION_ADDED should have index 0x00000001
  "FILE_ACTION_REMOVED" ,
  "FILE_ACTION_MODIFIED" ,
  "FILE_ACTION_RENAMED_OLD_NAME" ,
  "FILE_ACTION_RENAMED_NEW_NAME"
};
