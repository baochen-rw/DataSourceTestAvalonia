// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_TEXTURE_HANDLE_HPP
#define KZ_GL_TEXTURE_HANDLE_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

/// GLTextureHandle manages RAII ownership for GL texture object
class GLTextureHandle
{
    typedef void (GLTextureHandle::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:
    /// Constructs an empty GLTextureHandle which does not own any GL texture object
    explicit GLTextureHandle();

    /// Creates a new GL texture object with renderer and constructs a GLTextureHandle which owns it
    /// \param renderer Renderer
    explicit GLTextureHandle(Renderer* renderer);
    ~GLTextureHandle();

    /// Creates a wrapper for pre-existing GL texture object. If takeOwnership is true, the GL texture
    /// object is externally managed, and it will not be deleted when the handle is destroyed.
    /// \param renderer Renderer
    /// \param handle Pre-existing GL texture object name
    /// \param takeOwnership Should newgly created GLTextureHandle take ownership of the GL texture object
    explicit GLTextureHandle(Renderer* renderer, unsigned int handle, bool takeOwnership);

    /// Releases the ownership of the GL texture if any. get() returns 0 after the call.
    /// \return Handle to the GL texture object
    unsigned int release();

    friend void swap(GLTextureHandle& left, GLTextureHandle& right)
    {
        using std::swap;
        swap(left.m_renderer, right.m_renderer);
        swap(left.m_handle, right.m_handle);
    }

    GLTextureHandle(KZ_RV_REF(GLTextureHandle) other) :
        m_renderer(other.m_renderer),
        m_handle(other.m_handle)
    {
        other.m_renderer = 0;
        other.m_handle = 0;
    }

    GLTextureHandle& operator=(KZ_RV_REF(GLTextureHandle) other)
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

    /// Returns GL handle to the texture object, or 0 if no GL texture is owned
    unsigned int get() const
    {
        return m_handle;
    }

    /// Destroys the GL texture object currently managed by the GLTextureHandle (if any)
    void reset();

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR
    explicit operator bool() const
    {
        return (m_handle != 0);
    }
#else
    operator bool_type() const
    {
        return (m_handle != 0) ? &GLTextureHandle::this_type_does_not_support_comparisons : 0;
    }
#endif

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(GLTextureHandle)

    /// Pointer to Renderer. If 0, GL texture object is externally managed and won't be deleted when handle is deleted.
    Renderer* m_renderer;

    /// GL texture object name.
    unsigned int m_handle;
};

} // namespace kanzi

#endif
