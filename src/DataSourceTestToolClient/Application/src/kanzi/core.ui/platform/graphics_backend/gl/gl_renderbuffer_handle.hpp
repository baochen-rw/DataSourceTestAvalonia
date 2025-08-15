// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_RENDERBUFFER_HANDLE_HPP
#define KZ_GL_RENDERBUFFER_HANDLE_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

/// GLRenderbufferHandle manages RAII ownership for GL renderbuffer object
class GLRenderbufferHandle
{
    typedef void (GLRenderbufferHandle::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:
    /// Constructs an empty GLRenderbufferHandle which does not own any GL renderbuffer object
    explicit GLRenderbufferHandle();

    /// Creates a new GL renderbuffer object with renderer and constructs a GLRenderbufferHandle which owns it
    /// \param renderer Renderer
    explicit GLRenderbufferHandle(Renderer* renderer);
    ~GLRenderbufferHandle();

    /// Releases the ownership of the GL renderbuffer if any. get() returns 0 after the call.
    /// \return Handle to the GL renderbuffer object
    unsigned int release();

    friend void swap(GLRenderbufferHandle& left, GLRenderbufferHandle& right)
    {
        using std::swap;
        swap(left.m_renderer, right.m_renderer);
        swap(left.m_handle, right.m_handle);
    }

    GLRenderbufferHandle(KZ_RV_REF(GLRenderbufferHandle) other) :
        m_renderer(other.m_renderer),
        m_handle(other.m_handle)
    {
        other.m_renderer = 0;
        other.m_handle = 0;
    }

    GLRenderbufferHandle& operator=(KZ_RV_REF(GLRenderbufferHandle) other)
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

    /// Returns GL handle to the renderbuffer object, or 0 if no GL renderbuffer is owned
    unsigned int get() const
    {
        return m_handle;
    }

    /// Destroys the GL renderbuffer object currently managed by the GLRenderbufferHandle (if any)
    void reset();

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR
    explicit operator bool() const
    {
        return (m_handle != 0);
    }
#else
    operator bool_type() const
    {
        return (m_handle != 0) ? &GLRenderbufferHandle::this_type_does_not_support_comparisons : 0;
    }
#endif

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(GLRenderbufferHandle)

    /// Pointer to Renderer. If 0, GL renderbuffer object is externally managed and won't be deleted when handle is deleted.
    Renderer* m_renderer;

    /// GL renderbuffer object name.
    unsigned int m_handle;
};

} // namespace kanzi

#endif
