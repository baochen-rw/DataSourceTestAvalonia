// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_IMMUTABLE_STRING_HPP
#define KZ_IMMUTABLE_STRING_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/utility.hpp>

namespace kanzi
{

namespace detail
{

/// Deleter for string data.
struct CharArrayDeleter
{
    /// Delete operator.
    void operator()(const char* stringData) const
    {
        delete[] stringData;
    }
};

/// String data.
typedef unique_ptr<const char, CharArrayDeleter> CharArrayPtr;

/// Create string data from a string view.
/// \param content string_view to create from.
/// \return C -style string in unique_ptr.
inline CharArrayPtr createCharArrayPtr(string_view content)
{
    if (content.empty())
    {
        CharArrayPtr empty;
        return KZ_MOVE_RET(CharArrayPtr, empty);
    }

    size_t stringLength = content.length();
    unique_ptr<char, CharArrayDeleter> stringData(new char[stringLength + 1]);

    content.copy(stringData.get(), stringLength);

    // C string needs termination.
    stringData.get()[stringLength] = '\0';

    CharArrayPtr data(stringData.release());
    return KZ_MOVE_RET(CharArrayPtr, data);
}

}

/// Immutable string container.
/// Represents a string that is allocated dynamically but cannot be changed.
class ImmutableString
{
public:

    /// Empty constructor.
    explicit ImmutableString()
    {
    }

    /// Constructor.
    /// \param content String to construct from.
    explicit ImmutableString(string_view content) :
        m_stringData(detail::createCharArrayPtr(content))
    {
    }

    /// Move constructor.
    /// \param other Source string.
    ImmutableString(KZ_RV_REF(ImmutableString) other)
    {
        using std::swap;
        swap(m_stringData, other.m_stringData);
    }

    /// Access string data.
    /// \return C string.
    const char* c_str() const
    {
        return m_stringData.get();
    }

    /// Swap operation.
    /// \param left Left operand.
    /// \param right Right operand.
    friend void swap(ImmutableString& left, ImmutableString& right)
    {
        using std::swap;
        swap(left.m_stringData, right.m_stringData);
    }

    /// string_view operator.
    /// \return View to contained string.
    operator string_view() const
    {
        return string_view(c_str());
    }

    /// Move operator.
    /// \param other Source string.
    /// \return This.
    ImmutableString& operator=(KZ_RV_REF(ImmutableString) other)
    {
        using std::swap;
        swap(m_stringData, other.m_stringData);
        return *this;
    }

    /// Comparison operator.
    /// \param lhs Left-hand side operand.
    /// \param rhs Right-hand side operand.
    /// \return True if equal, false if not equal.
    friend bool operator==(const ImmutableString& lhs, string_view rhs)
    {
        return string_view(lhs) == rhs;
    }

    /// Comparison operator.
    /// \param lhs Left-hand side operand.
    /// \param rhs Right-hand side operand.
    /// \return True if equal, false if not equal.
    friend inline bool operator==(string_view lhs, const ImmutableString& rhs)
    {
        return lhs == string_view(rhs);
    }

    /// Comparison operator.
    /// \param lhs Left-hand side operand.
    /// \param rhs Right-hand side operand.
    /// \return True if equal, false if not equal.
    friend bool operator==(const ImmutableString& lhs, const ImmutableString& rhs)
    {
        return string_view(lhs) == string_view(rhs);
    }

    /// Not equals operator.
    /// \param lhs Left-hand side operand.
    /// \param rhs Right-hand side operand.
    /// \return True if not equal, false if equal.
    friend bool operator!=(const ImmutableString& lhs, string_view rhs)
    {
        return !(lhs == rhs);
    }

    /// Not equals operator.
    /// \param lhs Left-hand side operand.
    /// \param rhs Right-hand side operand.
    /// \return True if not equal, false if equal.
    friend bool operator!=(string_view lhs, const ImmutableString& rhs)
    {
        return !(lhs == rhs);
    }

    /// Not equals operator.
    /// \param lhs Left-hand side operand.
    /// \param rhs Right-hand side operand.
    /// \return True if not equal, false if equal.
    friend bool operator!=(const ImmutableString& lhs, const ImmutableString& rhs)
    {
        return !(lhs == rhs);
    }

    /// Less than operator.
    /// \param lhs Left-hand side operand.
    /// \param rhs Right-hand side operand.
    /// \return True if lhs is lexically 'smaller' than rhs, false otherwise.
    friend bool operator<(const ImmutableString& lhs, const ImmutableString& rhs)
    {
        return strcmp(lhs.c_str(), rhs.c_str()) < 0;
    }

private:

    KZ_MOVABLE_BUT_NOT_COPYABLE(ImmutableString)

    /// String data.
    detail::CharArrayPtr m_stringData;
};

}

#endif // KZ_IMMUTABLE_STRING_HPP
