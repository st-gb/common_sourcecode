#pragma once

class File
  : public I_File
  , public CFile
{
  inline ULONGLONG Seek(
    LONGLONG lOff,
    UINT nFrom 
    )
  {
    CFile::Seek() ;
  }

  inline Read
  {
    try
    {
      CFile::Read()
    }
    catch( CFileException * pcfe )
    {
      int nCause = pcfe->m_cause ;
      Sync::FileException exc(
        nCause,
        pcfe->m_strFileName
        ) ;
      pcfe->Delete();
      throw exc ;
    }
    //Only pointers work with catch().
    catch(//Use the most general exception because other exceptions
      //than CFileException may be thrown.
      CException * pexception)
    {
      pexception->ReportError();
      //MFC Library Reference: "Do not use the delete operator directly"
      pexception->Delete();
      //bProceed=false;
      Sync::FileException exc ;
      throw exc ;
    }
  }

  Write
  {
    try
    {
      CFile::Write()
    }
    catch( CFileException * pcfe )
    {
      int nCause = pcfe->m_cause ;
      Sync::FileException exc(
        nCause,
        pcfe->m_strFileName
        ) ;
      pcfe->Delete();
      throw exc ;
    }
    //Only pointers work with catch().
    catch(//Use the most general exception because other exceptions
      //than CFileException may be thrown.
      CException * pexception)
    {
      pexception->ReportError();
      //MFC Library Reference: "Do not use the delete operator directly"
      pexception->Delete();
      //bProceed=false;
      Sync::FileException exc ;
      throw exc ;
    }
  }
};
