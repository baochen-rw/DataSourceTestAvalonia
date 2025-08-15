// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_METADATA_HPP
#define KZ_METADATA_HPP


#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>

namespace kanzi
{

struct MetadataGeneratedName
{
    explicit MetadataGeneratedName(string_view name) : name(name)
    {
    }

    string_view name;
};

}


#endif