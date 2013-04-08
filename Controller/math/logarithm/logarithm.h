/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
/*
 * logarithm.h
 *
 *  Created on: Aug 18, 2010
 *      Author: Stefan
 */

#ifndef LOGARITHM_H_
#define LOGARITHM_H_

//This function was created because there is no logarithm for base 2
//in the standard library.
double log_dualis(double fValue);
//Logarithm to a VARIABLE base.
double log_x(double dBase, double dValue) ;

#endif /* LOGARITHM_H_ */
