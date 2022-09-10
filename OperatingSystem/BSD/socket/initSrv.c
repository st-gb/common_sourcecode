///(c)from 2022:Stefan Gebauer,Computer Science Master(TU Berlin,matric.#361095)

/**TU_Bln361095BSDsktNmSpcBgn,TU_Bln361095BSDsktNmSpcEnd,
 * TU_Bln361095BSDsktInitSrvNmSpcBgn,TU_Bln361095BSDsktInitSrvNmSpcEnd*/
#include "initSrv.h"
#include <compiler/GCC/avoid_write_strings_warning.h>///CAST_TO_CHAR_POINTER

TU_Bln361095BSDsktNmSpcBgn
TU_Bln361095BSDsktInitSrvNmSpcBgn

const char * const TU_Bln361095BSDsktInitSrvDef(enErrorMsgs)[] = {
  CAST_TO_CHAR_POINTER "listen succeeded",
  CAST_TO_CHAR_POINTER "bound to socket",
  CAST_TO_CHAR_POINTER "create socket failed",
  CAST_TO_CHAR_POINTER "failed to bind to socket",
  CAST_TO_CHAR_POINTER "listen to socket failed"
};

const char * const TU_Bln361095BSDsktInitSrvDef(bindToSktPossCause) =
  CAST_TO_CHAR_POINTER
  "Maybe because trying to bind to a well-known (1-1023) port\n"
  "Maybe start this program as root/admin to fix.\n";

TU_Bln361095BSDsktInitSrvNmSpcEnd
TU_Bln361095BSDsktNmSpcEnd