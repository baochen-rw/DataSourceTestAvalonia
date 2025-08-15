/**
* \file
* Provides relative time in milliseconds from the system.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_TICK_H
#define KZS_TICK_H


#include <kanzi/core/legacy/kzs_types.hpp>


/**
 * Returns current time from the system in milliseconds. The returned value is guaranteed to be monotonic.
 * Values should be only used relative to each other because starting time is not specified.
 */
KANZI_API kzUint kzsTimeGetCurrentTimestamp(void);


#endif
