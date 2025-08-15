// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MATH_HPP
#define KZ_MATH_HPP

#include "platform.hpp"
#include <cmath>
#include <cstdlib>

#if defined(KZ_EMULATE_CXX11_STD) || defined(KZ_EMULATE_CXX11_MATH)

#ifdef __QNXNTO__
#undef isfinite
#undef isnan
#endif

#include <boost/math/special_functions/fpclassify.hpp>
#include <boost/math/special_functions/round.hpp>

namespace kanzi
{

using boost::math::isfinite;
using boost::math::isnan;
using boost::math::round;
using boost::math::iround;
using boost::math::lround;

}

#else

namespace kanzi
{

using std::isfinite;
using std::isnan;
using std::round;
using std::lround;

/// Round float to integer.
///
/// \param value Input value to round.
/// \return Value rounded to closest signed integer.
inline int iround(float value)
{
    return static_cast<int>(round(value));
}

}

#endif

namespace kanzi
{

using std::cos;
using std::sin;
using std::tan;
using std::acos;
using std::asin;
using std::atan;
using std::atan2;

using std::exp;
using std::log;

using std::pow;
using std::sqrt;

using std::ceil;
using std::floor;
using std::fmod;

using std::fabs;
using std::abs;

}

#endif
