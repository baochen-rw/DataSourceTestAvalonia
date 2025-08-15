/**
* \file
* Allows suspending the execution of current thread.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_SLEEP_H
#define KZS_SLEEP_H


#include <kanzi/core/legacy/kzs_types.hpp>


/** Suspends the execution of current thread until the time-out interval elapses. */
KANZI_API void kzsSleep(kzUint milliseconds);


#endif
