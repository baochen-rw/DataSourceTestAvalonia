// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_ADAPTER_LOGGER_HPP
#define KZ_GL_GRAPHICS_ADAPTER_LOGGER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_adapter.hpp>

namespace kanzi
{

/// Logs OpenGL API calls.
class GlGraphicsAdapterLogger : public GlGraphicsAdapter
{
public:

    explicit GlGraphicsAdapterLogger():
        m_dumpStateOnDrawCalls(false)
    {
    }

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_gles_extensions_hpp.inl>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_graphics_interface_opengl_extensions_hpp.inl>

protected:
    int glTextureBindingForTarget(unsigned int glTarget);
    int glBufferBindingForTarget(unsigned int glTarget);
    int glFramebufferBindingForTarget(unsigned int glTarget);
    int getIntegerv(unsigned int pname, int defaultValue);
    int getActiveTexture();
    int getTextureBinding(unsigned int glTextureTarget);
    int getBufferBinding(unsigned int glBufferTarget);
    int getFramebufferBinding(unsigned int glFramebufferTarget);
    int getRenderbufferBinding();

public:
    void setDumpStateOnDrawCalls(bool enable);
    bool getDumpStateOnDrawCalls() const;

private:
    bool m_dumpStateOnDrawCalls;
};

}

#endif
