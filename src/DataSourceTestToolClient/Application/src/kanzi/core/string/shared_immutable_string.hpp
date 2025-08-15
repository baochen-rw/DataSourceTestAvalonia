// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SHARED_IMMUTABLE_STRING_HPP
#define KZ_SHARED_IMMUTABLE_STRING_HPP

#include "immutable_string.hpp"

namespace kanzi
{

/// Shared immutable string container.
/// Represents a shared string that is allocated dynamically but cannot be changed.
class SharedImmutableString
{
public:

    /// Constructor.
    explicit SharedImmutableString()
    {
    }

    /// Constructor.
    /// \param content String to construct from.
    explicit SharedImmutableString(string_view content)
    {
        detail::CharArrayPtr contentPtr(detail::createCharArrayPtr(content));
        m_sharedString = shared_ptr<const char>(contentPtr.release(), detail::CharArrayDeleter());
    }

    /// Copy constructor.
    /// \param other Source string.
    SharedImmutableString(const SharedImmutableString& other) :
        m_sharedString(other.m_sharedString)
    {
    }

    /// Move constructor.
    /// \param other Source string.
    SharedImmutableString(KZ_RV_REF(SharedImmutableString) other) :
        m_sharedString(kanzi::move(other.m_sharedString))
    {
    }

    /// Access string data.
    /// \return C string.
    const char* c_str() const
    {
        return m_sharedString.get();
    }

    /// Swap operation.
    /// \param left Left operand.
    /// \param right Right operand.
    friend void swap(SharedImmutableString& left, SharedImmutableString& right)
    {
        using std::swap;
        swap(left.m_sharedString, right.m_sharedString);
    }

    /// string_view operator.
    /// \return View to contained string.
    operator string_view() const
    {
        return string_view(c_str());
    }

    /// Assignment operator.
    /// \param other Source string.
    /// \return This.
    SharedImmutableString& operator=(const SharedImmutableString& other)
    {
        m_sharedString = other.m_sharedString;
        return *this;
    }

    /// Move operator.
    /// \param other Source string.
    /// \return This.
    SharedImmutableString& operator=(KZ_RV_REF(SharedImmutableString) other)
    {
        m_sharedString = kanzi::move(other.m_sharedString);
        return *this;
    }

private:

    /// String data.
    shared_ptr<const char> m_sharedString;
};

}

#endif // KZ_SHARED_IMMUTABLE_STRING_HPP