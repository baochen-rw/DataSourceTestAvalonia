// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_2D_HPP
#define KZ_DATA_SOURCE_LIST_ITEM_GENERATOR_2D_HPP

#include "data_source_list_item_generator.hpp"

namespace kanzi
{

class DataSourceListItemGenerator2D;
typedef shared_ptr<DataSourceListItemGenerator2D> DataSourceListItemGenerator2DSharedPtr;

class KANZI_UI_API DataSourceListItemGenerator2D : public DataSourceListItemGenerator<ListBoxItemGenerator2D>
{
public:

    static DataSourceListItemGenerator2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(DataSourceListItemGenerator2D, DataSourceListItemGenerator<ListBoxItemGenerator2D>, "Kanzi.DataSourceListItemGenerator2D")
    KZ_METACLASS_END()

protected:

    explicit DataSourceListItemGenerator2D(Domain* domain);
};

}

#endif
