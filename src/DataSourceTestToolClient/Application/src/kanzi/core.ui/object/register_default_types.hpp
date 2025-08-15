// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_REGISTER_DEFAULT_TYPES_HPP
#define KZ_REGISTER_DEFAULT_TYPES_HPP


#include <kanzi/core/legacy/kzs_types.hpp>


namespace kanzi
{

class ObjectFactory;


/// Registers default Kanzi object types in object factory.
KANZI_API void registerDefaultTypes(ObjectFactory& objectFactory);

}

#endif
