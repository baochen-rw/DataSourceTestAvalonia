// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FIXED_STRING_HPP
#define KZ_FIXED_STRING_HPP


#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <cstring>

namespace kanzi
{

#ifdef KZ_SUPPORTS_USER_DEFINED_LITERAL
class FixedString;
namespace literal_operators
{

/// User defined literal operator that creates FixedString.
FixedString operator"" _kzfixed(const char* s, std::size_t);

}
#endif

/// String that points to a string literal.
///
/// You can use FixedString objects to indicate that a string will have the lifetime equal to the duration of the program.
/// You should use the kzMakeFixedString macro to construct FixedString objects.
/// Compilers with C++11 support will emit an error if the parameter you supply to kzMakeFixedString is not a string literal.
class FixedString
{
    /// Pointer to literal.
    const char* m_fixedString;

#ifdef KZ_SUPPORTS_USER_DEFINED_LITERAL
    friend FixedString literal_operators::operator"" _kzfixed(const char* s, std::size_t);
#endif

public:

    friend bool operator==(const FixedString& left, const FixedString& right)
    {
        if (left.c_str() == right.c_str())
        {
            return true;
        }

        return std::strcmp(left.c_str(), right.c_str()) == 0;
    }

    operator string_view() const
    {
        return string_view(c_str());
    }

    /// Returns the pointer to string literal.
    const char* c_str() const
    {
        return m_fixedString;
    }

#ifdef KZ_SUPPORTS_USER_DEFINED_LITERAL
private:
#endif

    /// Constructor.
    explicit FixedString(const char* literal) : m_fixedString(literal)
    {
    }    
};

#ifdef KZ_SUPPORTS_USER_DEFINED_LITERAL

namespace literal_operators
{

inline FixedString operator"" _kzfixed(const char* s, std::size_t)
{
    return FixedString(s);
}

}

#endif


inline bool operator==(string_view left, FixedString right)
{
    return left == string_view(right.c_str());
}

inline bool operator==(FixedString left, string_view right)
{
    return string_view(left.c_str()) == right;
}

inline bool operator!=(string_view left, FixedString right)
{
    return left != string_view(right.c_str());
}

inline bool operator!=(FixedString left, string_view right)
{
    return string_view(left.c_str()) != right;
}

inline string to_string(FixedString fixedString)
{
    return string(fixedString.c_str());
}

}


#if defined KZ_SUPPORTS_USER_DEFINED_LITERAL

using namespace kanzi::literal_operators;

/// Use this macro to construct FixedString objects.
#define kzMakeFixedString(x)    x ## _kzfixed

#else

/// Use this macro to construct FixedString objects.
#define kzMakeFixedString(x)    ::kanzi::FixedString("" x "")

#endif


#endif
