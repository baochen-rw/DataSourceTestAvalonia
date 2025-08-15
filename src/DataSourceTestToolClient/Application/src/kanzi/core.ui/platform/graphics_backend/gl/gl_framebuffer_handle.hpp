// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_FRAMEBUFFER_HANDLE_HPP
#define KZ_GL_FRAMEBUFFER_HANDLE_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

/// GLFramebufferHandle manages RAII ownership for GL framebuffer object
class GLFramebufferHandle
{
    typedef void (GLFramebufferHandle::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:
    /// Constructs an empty GLFramebufferHandle which does not own any GL framebuffer object
    explicit GLFramebufferHandle();

    /// Creates a new GL framebuffer object with renderer and constructs a GLFramebufferHandle which owns it
    /// \param renderer Renderer
    explicit GLFramebufferHandle(Renderer* renderer);
    ~GLFramebufferHandle();

    /// Releases the ownership of the GL framebuffer if any. get() returns 0 after the call.
    /// \return Handle to the GL framebuffer object
    unsigned int release();

    friend void swap(GLFramebufferHandle& left, GLFramebufferHandle& right)
    {
        using std::swap;
        swap(left.m_renderer, right.m_renderer);
        swap(left.m_handle, right.m_handle);
    }

    GLFramebufferHandle(KZ_RV_REF(GLFramebufferHandle) other) :
        m_renderer(other.m_renderer),
        m_handle(other.m_handle)
    {
        other.m_renderer = 0;
        other.m_handle = 0;
    }

    GLFramebufferHandle& operator=(KZ_RV_REF(GLFramebufferHandle) other)
    {
        if (this != &other)
        {
            m_handle = other.m_handle;
            m_renderer = other.m_renderer;
            other.m_renderer = 0;
            other.m_handle = 0;
        }
        return *this;
    }

    /// Returns GL handle to the framebuffer object, or 0 if no GL framebuffer is owned
    unsigned int get() const
    {
        return m_handle;
    }

    /// Destroys the GL framebuffer object currently managed by the GLFramebufferHandle (if any)
    void reset();

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR
    explicit operator bool() const
    {
        return (m_handle != 0);
    }
#else
    operator bool_type() const
    {
        return (m_handle != 0) ? &GLFramebufferHandle::this_type_does_not_support_comparisons : 0;
    }
#endif

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(GLFramebufferHandle)

    /// Pointer to Renderer.
    Renderer* m_renderer;

    /// GL framebuffer object name.
    unsigned int m_handle;
};

} // namespace kanzi

#endif
