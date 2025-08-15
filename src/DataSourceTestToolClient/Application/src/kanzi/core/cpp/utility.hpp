// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_UTILITTY_HPP
#define KZ_UTILITTY_HPP

#include <utility>
#include <boost/move/utility.hpp>

#include "algorithm.hpp"
#include "platform.hpp"
#include "string.hpp"
#include "system_error.hpp"

namespace kanzi
{

using std::pair;
using std::make_pair;
using boost::move;

}

#define KZ_MOVABLE_BUT_NOT_COPYABLE(className)      BOOST_MOVABLE_BUT_NOT_COPYABLE(className)
#define KZ_COPYABLE_AND_MOVABLE(className)          BOOST_COPYABLE_AND_MOVABLE(className)
#define KZ_COPY_ASSIGN_REF(className)               BOOST_COPY_ASSIGN_REF(className)
#define KZ_RV_REF(className)                        BOOST_RV_REF(className)
#define KZ_MOVE_RET(returnType, returnValue)        BOOST_MOVE_RET(returnType, returnValue)
#define KZ_MOVE_BASE(baseType, object)              BOOST_MOVE_BASE(baseType, object)

#ifdef BOOST_NO_CXX11_RVALUE_REFERENCES
#define KZ_USE_MOVE_EMULATION
#endif

#ifndef SPANSION

namespace kanzi
{

struct from_chars_result
{
    /// Points at the first character not matching the pattern, or has the value equal to last if all characters matched pattern
    const char* ptr;
    /// Result code of the conversion
    error_code ec;
};

/// Converts character range to int value
///
/// This is available since C++14. According to the standard specification this function should not
/// depend on locale. This implementation does use local to convert character range to value.
///
/// \param first Pointer to first character in range to be converted
/// \param last Pointer to first character beyond last in range to be converted
/// \param value Reference to the storage where converted value is stored
/// \param base Base to be used to convert integer value
/// \returns Result of the value conversion
inline from_chars_result from_chars(const char* first, const char* last, int& value, int base = 10)
{
    string stringValue(first, last);
    char* endPosition = 0;

    long int conversionResult = strtol(stringValue.c_str(), &endPosition, base);

    if (errno == ERANGE && (conversionResult == LONG_MIN || conversionResult == LONG_MAX))
    {
        from_chars_result result = { first, make_error_code(errc::result_out_of_range) };
        return result;
    }
    else if (conversionResult == 0 && endPosition == stringValue.c_str())
    {
        from_chars_result result = { first, make_error_code(errc::invalid_argument) };
        return result;
    }
    else
    {
        ptrdiff_t endOfValueOffset = min(last - first, endPosition - stringValue.c_str());

        value = static_cast<int>(conversionResult);

        from_chars_result result = { first + endOfValueOffset, error_code() };
        return result;
    }
}

/// Scoped reference counter, which takes an unsigned integer value as argument
/// on construction to track. Use the class to guard incremental calls on an object.
class ScopedRefCounter
{
private:
    size_t& m_counter;
public:
    /// Constructs the reference counter and increments its value.
    /// \param counter Reference to the counter to track.
    explicit ScopedRefCounter(size_t& counter) :
        m_counter(counter)
    {
        ++m_counter;
    }
    /// Destroys the reference counter and decrements the tracked counter.
    ~ScopedRefCounter()
    {
        --m_counter;
    }
    /// Returns the reference counter tracked.
    size_t count() const
    {
        return m_counter;
    }
};

}

#endif

#endif
