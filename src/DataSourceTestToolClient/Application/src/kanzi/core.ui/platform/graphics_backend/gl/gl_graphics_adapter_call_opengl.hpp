// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_ADAPTER_CALL_OPENGL_HPP
#define KZ_GL_GRAPHICS_ADAPTER_CALL_OPENGL_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_adapter.hpp>

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) && defined(KZ_SUPPORT_GRAPHICS_API_OPENGL)

namespace kanzi
{

/// OpenGL API call handler which calls the implemenation
/// from dynamically loaded OpenGL library
class GlGraphicsAdapterCallOpenGl : public GlGraphicsAdapter
{
public:
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_opengl_extensions_hpp.inl>
};

}

#endif

#endif
