// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_ADAPTER_HPP
#define KZ_GL_GRAPHICS_ADAPTER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/kzs_opengl.h>

struct KzsGlGraphicsContext;

namespace kanzi
{

/// Base class for handling calls to OpenGL family.
/// GlGraphicsAdapters can be chained so that several handlers
/// can handle a single call.
///
/// kzsGl* functions in kzs_opengl.h will call a root handler.
/// The root handler and other handlers in the chain are
/// configured by GlGraphicsControl in kzs_opengl.h
///
/// The API functions are listed in opengl_interface_*_hpp.inl
/// files. The base class GlGraphicsAdapter has implementation
/// for all these functions. Each function in the base class
/// will simply check if there is next handler in the chain,
/// and calls it if it exists.
class GlGraphicsAdapter
{
public:
    GlGraphicsAdapter();

    /// Set the next handler in the chain to be called for each API call
    void setNext(GlGraphicsAdapter* value);
    void setContext(struct KzsGlGraphicsContext* context);

protected:
    struct ::KzsGlGraphicsContext* getContext() const;

#if defined(KZ_RUNTIME_GRAPHICS_BACKEND) 
public:
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_extensions_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_opengl_extensions_hpp.inl>
#endif

private:
    GlGraphicsAdapter* next;
    struct ::KzsGlGraphicsContext* m_context;
};

}

#endif
