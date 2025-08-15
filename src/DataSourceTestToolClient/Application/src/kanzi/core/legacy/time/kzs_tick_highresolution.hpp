/**
* \file
* Provides relative time in microseconds from the system.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_TICK_HIGHRESOLUTION_H
#define KZS_TICK_HIGHRESOLUTION_H


#include <kanzi/core/legacy/kzs_types.hpp>


/**
 * Returns current time from the system in microseconds.
 * Values should be only used relative to each other because starting time is not specified.
 */
KANZI_API kzU64 kzsTimeGetCurrentTimeMicroseconds();


#endif
