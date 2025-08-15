// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_BUFFER_HANDLE_HPP
#define KZ_GL_BUFFER_HANDLE_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

/// GLBufferHandle manages RAII ownership for GL buffer object
class GLBufferHandle
{
    typedef void (GLBufferHandle::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:
    /// Constructs an empty GLBufferHandle which does not own any GL buffer object
    explicit GLBufferHandle();

    /// Creates a new GL buffer object with renderer and constructs a GLBufferHandle which owns it
    /// \param renderer Renderer
    explicit GLBufferHandle(Renderer* renderer);
    ~GLBufferHandle();

    /// Creates a wrapper for pre-existing GL buffer object. If takeOwnership is true, the GL buffer
    /// object is externally managed, and it will not be deleted when the handle is destroyed.
    /// \param renderer Renderer
    /// \param handle Pre-existing GL buffer object name
    /// \param takeOwnership Should newly created GLBufferHandle take ownership of the GL buffer object
    explicit GLBufferHandle(Renderer* renderer, unsigned int handle, bool takeOwnership);

    /// Releases the ownership of the GL buffer if any. get() returns 0 after the call.
    /// \return Handle to the GL buffer object
    unsigned int release();

    friend void swap(GLBufferHandle& left, GLBufferHandle& right)
    {
        using std::swap;
        swap(left.m_renderer, right.m_renderer);
        swap(left.m_handle, right.m_handle);
    }

    GLBufferHandle(KZ_RV_REF(GLBufferHandle) other) :
        m_renderer(other.m_renderer),
        m_handle(other.m_handle)
    {
        other.m_renderer = 0;
        other.m_handle = 0;
    }

    GLBufferHandle& operator=(KZ_RV_REF(GLBufferHandle) other)
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

    /// Returns GL handle to the buffer object, or 0 if no GL buffer is owned
    unsigned int get() const
    {
        return m_handle;
    }

    /// Destroys the GL buffer object currently managed by the GLBufferHandle (if any)
    void reset();

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR
    explicit operator bool() const
    {
        return (m_handle != 0);
    }
#else
    operator bool_type() const
    {
        return (m_handle != 0) ? &GLBufferHandle::this_type_does_not_support_comparisons : 0;
    }
#endif

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(GLBufferHandle)

    /// Pointer to Renderer. If 0, GL buffer object is externally managed and won't be deleted when handle is deleted.
    Renderer* m_renderer;

    /// GL buffer object name.
    unsigned int m_handle;
};

} // namespace kanzi

#endif
