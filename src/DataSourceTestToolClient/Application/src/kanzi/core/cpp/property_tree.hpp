// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_TREE_HPP
#define KZ_PROPERTY_TREE_HPP

#include "platform.hpp"

#if defined (__GNUC__)
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 6)
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif
#endif
#pragma GCC diagnostic ignored "-Wtype-limits"
#pragma GCC diagnostic ignored "-Wsign-compare"
#endif

#if defined _MSC_VER
#pragma warning(push)

// warning C26495: Variable 'boost::multi_index::detail::index_matcher::entry::pile_top_entry' is uninitialized. Always initialize a member variable (type.6).
#pragma warning(disable : 26495)

#endif

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

#if defined _MSC_VER
#pragma warning(pop)
#endif

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif

namespace kanzi
{

using boost::property_tree::ptree;

}

#endif
