// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_OBJECT_LIST_HPP
#define KZ_DATA_OBJECT_LIST_HPP

#include "data_object.hpp"

namespace kanzi
{
class DataObjectList;

typedef shared_ptr<DataObjectList> DataObjectListSharedPtr;

/**
* DataObjectList is the base class for list data object. 
**/
class KANZI_API DataObjectList : public DataObject
{
public:
    /// Standard constructor.
    /// \param name Name of the data object.
    explicit DataObjectList(Domain* domain, string_view name) :
        DataObject(domain, name)
    {
    }

    /// Retrieves the type of this data object.
    /// \return Type enumeration of this data object.
    virtual Type getType() const
    {
        return DataObject::List;
    }

    virtual size_t itemCount() = 0;

    virtual DataObjectSharedPtr acquireItem(size_t index) = 0;

    virtual void releaseItem(size_t index) = 0;

    /// Returns tree structure of the data source for individual list item.
    /// Only hierarchy and object types are valid, the data might not be.
    virtual DataObjectSharedPtr getItemTemplate() = 0;
};
}

#endif
