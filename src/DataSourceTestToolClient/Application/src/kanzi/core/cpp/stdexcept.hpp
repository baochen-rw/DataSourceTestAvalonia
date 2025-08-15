// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STDEXCEPT_HPP
#define KZ_STDEXCEPT_HPP

#include "platform.hpp"

#include <stdexcept>
#include <typeinfo>

namespace kanzi
{

using std::exception;
using std::logic_error;
using std::domain_error;
using std::invalid_argument;
using std::length_error;
using std::out_of_range;

using std::runtime_error;
using std::range_error;
using std::overflow_error;
using std::underflow_error;
using std::bad_cast;

}

#endif
