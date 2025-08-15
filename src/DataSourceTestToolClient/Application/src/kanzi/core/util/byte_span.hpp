// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BYTE_SPAN_HPP
#define KZ_BYTE_SPAN_HPP

#include <kanzi/core/cpp/cstddef.hpp>
#include <kanzi/core/cpp/string_view.hpp>

namespace kanzi
{

/// ConstByteSpan refers to constant contiguous sequence of bytes.
typedef basic_string_view<const byte> ConstByteSpan;

}

#endif // KZ_BYTE_SPAN_HPP