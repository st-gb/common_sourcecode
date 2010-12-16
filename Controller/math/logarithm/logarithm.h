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
