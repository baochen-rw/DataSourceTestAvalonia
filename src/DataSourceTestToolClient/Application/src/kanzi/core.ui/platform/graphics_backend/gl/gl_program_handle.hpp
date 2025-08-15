// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_PROGRAM_HANDLE_HPP
#define KZ_GL_PROGRAM_HANDLE_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

/// GLProgramHandle manages RAII ownership for GL program object
class GLProgramHandle
{
    typedef void (GLProgramHandle::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:
    /// Creates an empty GL program handle which does not own anything
    explicit GLProgramHandle();

    /// Creates a new GL program object with renderer and constructs a GLProgramHandle which owns it
    explicit GLProgramHandle(kanzi::Renderer* renderer);

    ~GLProgramHandle();

    /// Releases the ownership of the GL program if any. get() returns 0 after the call.
    /// \return Handle to the GL program object
    unsigned int release();

    friend void swap(GLProgramHandle& left, GLProgramHandle& right)
    {
        using std::swap;
        swap(left.m_renderer, right.m_renderer);
        swap(left.m_handle, right.m_handle);
    }

    explicit GLProgramHandle(KZ_RV_REF(GLProgramHandle) other):
        m_renderer(other.m_renderer),
        m_handle(other.m_handle)
    {
        other.m_renderer = 0;
        other.m_handle = 0;
    }

    GLProgramHandle& operator=(KZ_RV_REF(GLProgramHandle) other)
    {
        if (this != &other)
        {
            m_handle = kanzi::move(other.m_handle);
            m_renderer = other.m_renderer;
            other.m_handle = 0;
            other.m_renderer = 0;
        }
        return *this;
    }

    /// Returms GL handle to the program object or 0 if no GL program is owned
    unsigned int get() const
    {
        return m_handle;
    }

    /// Destroys the GL program object currently managed by the GLProgramHandle (if any)
    void reset();

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR
    explicit operator bool() const
    {
        return (m_handle != 0);
    }
#else
    operator bool_type() const
    {
        return (m_handle != 0) ? &GLProgramHandle::this_type_does_not_support_comparisons : 0;
    }
#endif

private:
    KZ_MOVABLE_BUT_NOT_COPYABLE(GLProgramHandle)

    kanzi::Renderer* m_renderer;
    unsigned int m_handle;
};

} // namespace kanzi

#endif // KZ_GL_PROGRAM_HANDLE_HPP
