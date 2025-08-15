// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STABLE_VECTOR_HPP
#define KZ_STABLE_VECTOR_HPP

#include "platform.hpp"

#if defined _MSC_VER
#pragma warning(push)
// warning C4457: declaration of 'p' hides function parameter
#pragma warning(disable : 4457)
// warning C26495: Variable 'boost::intrusive::header_holder_plus_last<boost::intrusive::detail::default_header_holder<boost::intrusive::slist_node_traits<void *> >,boost::intrusive::slist_node<void *> *,1>::last_' is uninitialized. Always initialize a member variable (type.6).
#pragma warning(disable : 26495)
#endif

#include <boost/container/stable_vector.hpp>

#if defined _MSC_VER
#pragma warning(pop)
#endif

namespace kanzi
{

using boost::container::stable_vector;

}

#endif
