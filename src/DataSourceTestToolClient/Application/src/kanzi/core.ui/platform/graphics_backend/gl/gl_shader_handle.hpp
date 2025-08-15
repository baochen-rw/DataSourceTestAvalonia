// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_SHADER_HANDLE_HPP
#define KZ_GL_SHADER_HANDLE_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

/// GLShaderHandle manages RAII ownership for GL shader object
class GLShaderHandle
{
    typedef void (GLShaderHandle::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:
    /// Constructs an empty GLShaderHandle which does not own any GL shader object
    explicit GLShaderHandle();

    /// Creates a new GL shader object with renderer and constructs a GLShaderHandle which owns it
    /// \param renderer Renderer
    /// \param type Type of GL shader to create
    explicit GLShaderHandle(kanzi::Renderer* renderer, ShaderType type);
    ~GLShaderHandle();

    /// Releases the ownership of the GL shader if any. get() returns 0 after the call.
    /// \return Handle to the GL shader object
    unsigned int release();

    friend void swap(GLShaderHandle& left, GLShaderHandle& right)
    {
        using std::swap;
        swap(left.m_type, right.m_type);
        swap(left.m_renderer, right.m_renderer);
        swap(left.m_handle, right.m_handle);
    }

    GLShaderHandle(KZ_RV_REF(GLShaderHandle) other):
        m_type(other.m_type),
        m_renderer(other.m_renderer),
        m_handle(other.m_handle)
    {
        other.m_type = ShaderTypeInvalid;
        other.m_renderer = 0;
        other.m_handle = 0;
    }

    GLShaderHandle& operator=(KZ_RV_REF(GLShaderHandle) other)
    {
        if (this != &other)
        {
            m_handle = other.m_handle;
            m_type = other.m_type;
            m_renderer = other.m_renderer;
            other.m_type = ShaderTypeInvalid;
            other.m_renderer = 0;
            other.m_handle = 0;
        }
        return *this;
    }

    /// Returns GL handle to the shader object or 0 if no GL shader is owned
    unsigned int get() const
    {
        return m_handle;
    }

    ShaderType getType() const
    {
        return m_type;
    }

    /// Destroys the GL shader object currently managed by the GLShaderHandle (if any)
    void reset();

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR
    explicit operator bool() const
    {
        return (m_handle != 0);
    }
#else
    operator bool_type() const
    {
        return (m_handle != 0) ? &GLShaderHandle::this_type_does_not_support_comparisons : 0;
    }
#endif

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(GLShaderHandle)

    ShaderType m_type;
    kanzi::Renderer* m_renderer;
    unsigned int m_handle;
};

} // namespace kanzi

#endif // KZ_GL_SHADER_HANDLE_HPP
