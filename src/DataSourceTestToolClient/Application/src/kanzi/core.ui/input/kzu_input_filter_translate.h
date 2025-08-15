/**
* \file
* Translating input filter.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_INPUT_FILTER_TRANSLATE_H
#define KZU_INPUT_FILTER_TRANSLATE_H

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>


/* Forward declarations. */
struct KzsEventQueue;


/** Translate input events. */
kzsError KANZI_API kzuInputFilterTranslateProcessEventQueue(const struct KzsEventQueue* queueIn, struct KzsEventQueue* queueOut, enum KzsInputTranslation translation);


#endif
