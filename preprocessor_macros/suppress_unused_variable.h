/*
 * supress_unused_variable.h
 *
 *  Created on: Jul 2, 2010
 *      Author: Stefan
 */

#ifndef SUPRESS_UNUSED_VARIABLE_H_
#define SUPRESS_UNUSED_VARIABLE_H_

//Adapted from http://stackoverflow.com/questions/487108/
//how-to-supress-specific-warnings-in-g :
#define SUPPRESS_UNUSED_VARIABLE_WARNING(X)((void)(&(X)));

#endif /* SUPRESS_UNUSED_VARIABLE_H_ */
