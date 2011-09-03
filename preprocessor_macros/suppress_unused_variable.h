/* Do not remove this header/ copyright information.
 *
 * Copyright © Trilobyte Software Engineering GmbH, Berlin, Germany 2010-2011.
 * You are allowed to modify and use the source code from
 * Trilobyte Software Engineering GmbH, Berlin, Germany for free if you are not
 * making profit with it or its adaption. Else you may contact Trilobyte SE.
 */
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
// (if not used: g++ (MinGW) compiler output: "unused variable ..."
#define SUPPRESS_UNUSED_VARIABLE_WARNING(X)((void)(&(X)));

#endif /* SUPRESS_UNUSED_VARIABLE_H_ */
