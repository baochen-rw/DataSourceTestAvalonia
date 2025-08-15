// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_ADAPTER_CALL_GLES_HPP
#define KZ_GL_GRAPHICS_ADAPTER_CALL_GLES_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_adapter.hpp>

namespace kanzi
{

/// OpenGL API call handler which calls the implementation
/// from dynamically loaded GLES library
class GlGraphicsAdapterCallGles : public GlGraphicsAdapter
{
public:
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_extensions_hpp.inl>
};

}

#endif
