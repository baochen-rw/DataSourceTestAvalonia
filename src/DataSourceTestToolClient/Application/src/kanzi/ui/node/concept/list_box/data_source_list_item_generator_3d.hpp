// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_3D_HPP
#define KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_3D_HPP

#include "data_source_list_item_generator.hpp"

namespace kanzi
{

class DataSourceListItemGenerator3D;
typedef shared_ptr<DataSourceListItemGenerator3D> DataSourceListItemGenerator3DSharedPtr;

class KANZI_UI_API DataSourceListItemGenerator3D : public DataSourceListItemGenerator<ListBoxItemGenerator3D>
{
public:

    static DataSourceListItemGenerator3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(DataSourceListItemGenerator3D, DataSourceListItemGenerator<ListBoxItemGenerator3D>, "Kanzi.DataSourceListItemGenerator3D")
    KZ_METACLASS_END()

protected:

    explicit DataSourceListItemGenerator3D(Domain* domain);
};

}

#endif

#endif
