// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_ADAPTER_CHECK_FOR_ERRORS_HPP
#define KZ_GL_GRAPHICS_ADAPTER_CHECK_FOR_ERRORS_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_adapter.hpp>

namespace kanzi
{

/// Check for GL errors. This call handler should be chained
/// after a handler which has performed a call.
class GlGraphicsAdapterCheckForErrors : public GlGraphicsAdapter
{
public:
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_extensions_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_opengl_extensions_hpp.inl>
};

}

#endif
