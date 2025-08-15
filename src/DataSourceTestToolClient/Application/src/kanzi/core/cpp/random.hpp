// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RANDOM_HPP
#define KZ_RANDOM_HPP

#include "platform.hpp"

#ifdef KZ_EMULATE_CXX11_STD

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <boost/random/uniform_real_distribution.hpp>

namespace kanzi
{

typedef boost::mt19937 default_random_engine;

using boost::random::uniform_int_distribution;
using boost::random::uniform_real_distribution;

}

#else

#include <random>

namespace kanzi
{

using std::default_random_engine;

using std::uniform_int_distribution;
using std::uniform_real_distribution;

}

#endif

#endif
