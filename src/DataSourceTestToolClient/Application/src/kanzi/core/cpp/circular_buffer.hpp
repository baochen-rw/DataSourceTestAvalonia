// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CIRCULAR_BUFFER_HPP
#define KZ_CIRCULAR_BUFFER_HPP

#include "platform.hpp"

#if defined _MSC_VER
#pragma warning(push)

// warning C26495: Variable 'boost::circular_buffer<...>::m_buff' is uninitialized. Always initialize a member variable (type.6).
#pragma warning(disable : 26495)

#endif

#include <boost/circular_buffer.hpp>

#if defined _MSC_VER
#pragma warning(pop)
#endif

namespace kanzi
{

using boost::circular_buffer;

}

#endif
