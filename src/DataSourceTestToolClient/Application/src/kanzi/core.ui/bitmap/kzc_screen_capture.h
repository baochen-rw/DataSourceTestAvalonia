/**
* \file
* Screen capturing utility.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_SCREEN_CAPTURE_H
#define KZC_SCREEN_CAPTURE_H

#include <kanzi/core.ui/bitmap/bitmap_image.hpp>

/** Creates image from color buffer attached to window */
KANZI_API kanzi::BitmapImageUniquePtr kzcScreenCaptureToImage(kzUint width, kzUint height, kanzi::GraphicsFormat format);

#endif
