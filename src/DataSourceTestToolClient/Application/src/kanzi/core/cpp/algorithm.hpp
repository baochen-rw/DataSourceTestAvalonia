// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ALGORITHM_HPP
#define KZ_ALGORITHM_HPP

#include "platform.hpp"
#include <algorithm>
#include <boost/algorithm/clamp.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>

namespace kanzi
{

using boost::algorithm::all_of;

using std::copy;

using std::sort;

using std::find;
using std::find_if;
using std::equal;

using std::transform;
using std::remove;
using std::remove_if;
using std::rotate;

using std::max;
using std::min;

using std::fill;
using std::fill_n;
using std::for_each;

using std::replace;

using std::lower_bound;

using boost::algorithm::clamp;

using boost::algorithm::starts_with;
using boost::algorithm::ends_with;

}

#endif
