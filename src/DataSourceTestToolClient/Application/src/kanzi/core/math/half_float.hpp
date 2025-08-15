// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_HALF_FLOAT_HPP
#define KZ_HALF_FLOAT_HPP


#include <kanzi/core/legacy/kzs_types.hpp>

namespace kanzi
{

/// Converts float to 16 bits representing a half float.
KANZI_API uint16_t floatToHalfFloat(float f);

/// Converts 16 bits representing a half float to a float.
KANZI_API float halfFloatToFloat(uint16_t halfFloatNumber);

}

#endif
