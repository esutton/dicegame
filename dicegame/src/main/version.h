/*!
 * \file version.h
 *
 *  Created on: Dec 10, 2013
 *      Author: esutton
 */

#ifndef VERSION_H_
#define VERSION_H_

/// Stringizing macro
#define VAL(str)        #str

/// Stringizing macro
#define TOSTRING(str)   VAL(str)

/// Major
#define VERSION_SOFTWARE_MAJOR   1
/// Minor
#define VERSION_SOFTWARE_MINOR   0

/// \todo Use a build a script that sets VERSION_CONTROL_REVISION to match the repository this release was built from
#define VERSION_CONTROL_REVISION     68

#define VERSION_NUMBER  ( TOSTRING(VERSION_SOFTWARE_MAJOR) "." TOSTRING(VERSION_SOFTWARE_MINOR) "." TOSTRING(VERSION_CONTROL_REVISION) )

/// The gcc time at the time of build
#define COMPILE_TIME __TIME__

/// The gcc date at the time of build
#define COMPILE_DATE __DATE__

/// Date of build
#define DATE_OF_SOFTWARE_BUILD	 COMPILE_DATE " " COMPILE_TIME

#endif /* VERSION_H_ */
