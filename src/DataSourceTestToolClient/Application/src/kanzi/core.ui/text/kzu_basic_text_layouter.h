// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_BASIC_TEXT_LAYOUTER_H
#define KZU_BASIC_TEXT_LAYOUTER_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations */
struct KzcMemoryManager;
struct KzuFont;
struct KzuTextLayouter;


/** Creates a basic text layouter with the given font. */
KANZI_API kzsError kzuBasicTextLayouterCreate(const struct KzcMemoryManager* memoryManager, struct KzuFont* font,
                                    struct KzuTextLayouter** out_textLayouter);


#endif
