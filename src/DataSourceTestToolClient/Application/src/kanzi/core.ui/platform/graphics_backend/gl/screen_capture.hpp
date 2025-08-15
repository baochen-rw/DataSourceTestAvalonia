// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SCREEN_CAPTURE_HPP
#define KZ_SCREEN_CAPTURE_HPP

#include <kanzi/core.ui/bitmap/bitmap_image.hpp>

namespace kanzi
{

/// Capture the current framebuffer to an image.
/// \param width Capture area width.
/// \param height Capture area height.
/// \param format Graphics format to capture with.
/// \return Captured framebuffer as image.
KANZI_API BitmapImageUniquePtr captureCurrentFramebufferToImage(unsigned int width, unsigned int height, GraphicsFormat format);

/// Capture the screen (default framebuffer) to an image.
/// \param width Capture area width.
/// \param height Capture area height.
/// \param format Graphics format to capture with.
/// \return Captured screen as image.
KANZI_API BitmapImageUniquePtr captureScreenToImage(Renderer& renderer, unsigned int width, unsigned int height, GraphicsFormat format);

}

#endif
