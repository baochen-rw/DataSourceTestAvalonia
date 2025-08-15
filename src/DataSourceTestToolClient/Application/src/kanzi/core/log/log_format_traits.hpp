// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LOG_FORMAT_TRAITS_HPP
#define KZ_LOG_FORMAT_TRAITS_HPP

#include <kanzi/core/cpp/type_traits.hpp>

namespace kanzi
{

namespace detail
{

/// Checks whether type T supports formatting.
/// \{
template<typename T>
struct LogArgumentSupportsFormatting
{
    enum
    {
        value = is_arithmetic<T>::value || is_pointer<T>::value || is_array<T>::value
    };
};

template <>
struct LogArgumentSupportsFormatting<bool>
{
    enum
    {
        value = false
    };
};

template<typename T>
struct LogArgumentSupportsPrecisionFormatting
{
    enum
    {
        value = is_floating_point<T>::value
    };
};

/// \}

}

}

#endif
