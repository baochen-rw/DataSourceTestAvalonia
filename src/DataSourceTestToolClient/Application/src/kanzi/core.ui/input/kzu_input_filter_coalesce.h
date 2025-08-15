/**
* \file
* Coalescing input filter.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_FILTER_COALESCE_H
#define KZU_INPUT_FILTER_COALESCE_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>





/* Forward declarations. */
struct KzsEventQueue;


/** Coalesce input events. */
kzsError KANZI_API kzuInputFilterCoalesceProcessEventQueue(const struct KzsEventQueue* queueIn, struct KzsEventQueue* queueOut);





#endif
