/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * logarithm.c
 *
 *  Created on: Aug 18, 2010
 *      Author: Stefan
 */
#include <math.h> //for log10(...);

// this function was created because there is no logarithm for base 2 in
//the standard library
double log_dualis(double fValue)
{
  return
    //MSVC++ has no log2() function (in <math.h>).
    //So emulate it by:  log(2)x = (log(10)x)/(log(10)2)
    log10
    (
      fValue
    )
    / log10(2.0f) ;

}

double log_x(double dBase, double dValue)
{
  return
    //MSVC++ has no log2() function (in <math.h>).
    //So emulate it by:  log(2)x = (log(10)x)/(log(10)2)
    log10
    (
      dValue
    )
    / log10(dBase) ;
}
