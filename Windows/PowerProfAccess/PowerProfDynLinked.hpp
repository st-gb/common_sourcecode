#pragma once

#include <Controller/IDynFreqScalingAccess.hpp>
#include <Controller/character_string/stdtstr.hpp> //for std::tstring
//#include <preprocessor_macros/Windows_compatible_typedefs.h> //for BYTE
#include <windef.h> //for BYTE, DWORD
//#include <string> //for std::wstring 
#include <set> //std::set

class I_PowerProfDynLinked ;

//Class for both Window version >=6 and Windows version < 6 
//Power prof access mainly for Dynamic Voltage and Freq Scal. access.
//So only this 1 class is needed if one wants to cover all Windows versions.
class PowerProfDynLinked
  : public IDynFreqScalingAccess
{
public:
    //return: true=success
  PowerProfDynLinked(
    std::wstring & r_stdwstrProgramName ) ;
//    std::tstring & r_stdtstrProgramName ) ;
  //PowerProfDynLinked(std::string & stdstrPowerSchemeNameToChoose ) ;
  //"virtual" too avoid g++ warning: "warning: `class PowerProfDynLinked' has
  //  virtual functions but non-virtual destructor"
  virtual ~PowerProfDynLinked() ;
  //Must be a pointer because the concrete type is determined at
  //runtime. The advantage of the other DVFS access as a member function 
  //instead of a factory is that as a member THIS class k�mmert sich um
  //deletion of the dyn. allocated object.
  //IDynFreqScalingAccess * mp_dynfreqscalingaccess ;
  I_PowerProfDynLinked * mp_i_powerprofdynlinked ;
  bool ChangeOtherDVFSaccessPossible() ;
  BYTE CreatePowerScheme(const std::wstring & wstr ) ;
  virtual unsigned char CreatePowerSchemeWithWantedName() { return 0 ; }
  BYTE DeletePowerScheme( const std::tstring & cr_stdtstrPowerSchemeName ) ;
  bool DisableFrequencyScalingByOS() ;
  unsigned char EnableFrequencyScalingByOS() ;
  bool EnablingIsPossible() ;
  void GetActivePowerSchemeName( std::wstring & r_wstr) ;
  void GetAllPowerSchemeNames( std::set<std::wstring> &
      r_stdset_stdwstrPowerSchemeName ) ;
  IDynFreqScalingAccess::string_type GetEnableDescription() ;
  bool OtherDVFSisEnabled() ;
  void OutputAllPowerSchemes() ;
  virtual unsigned char PowerSchemeToSetExists() { return 0 ; }
  //BYTE
  DWORD SetActivePowerScheme(
    const std::wstring & r_stdwstrPowerSchemeName ) ;
};
