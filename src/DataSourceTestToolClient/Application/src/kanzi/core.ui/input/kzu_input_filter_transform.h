/**
* \file
* Transforming input filter.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_FILTER_TRANSFORM_H
#define KZU_INPUT_FILTER_TRANSFORM_H

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>


/* Forward declarations. */
struct KzsEventQueue;
struct KzcMatrix3x3; 

/** Translate input events. */
kzsError kzuInputFilterTransformProcessEventQueue(const struct KzsEventQueue* queueIn, struct KzsEventQueue* queueOut, const struct KzcMatrix3x3* transform);


#endif
