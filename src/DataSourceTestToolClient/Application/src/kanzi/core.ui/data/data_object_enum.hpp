// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_OBJECT_ENUM_HPP
#define KZ_DATA_OBJECT_ENUM_HPP

#include "data_object.hpp"

namespace kanzi
{
class DataObjectEnumBase;

typedef shared_ptr<DataObjectEnumBase> DataObjectEnumBaseSharedPtr;

/**
* DataObjectEnumBase is the base class for enum data. 
* The base class provides the internal value as integer.
**/
class KANZI_API DataObjectEnumBase : public DataObject
{
public:
    /// Standard constructor.
    /// \param name Name of the data object.
    explicit DataObjectEnumBase(Domain* domain, string_view name) :
        DataObject(domain, name),
        m_valueInt(0)
    {
    }

    /// Retrieves the type of this data object.
    /// \return Type enumeration of this data object.
    virtual Type getType() const
    {
        return DataObject::Enum;
    }

    int getValueInt() const
    {
        return m_valueInt;
    }

protected:
    int m_valueInt;
};

/**
* Provides functions to host / set / get value of given type.
**/
template <class DataType>
class DataObjectEnum : public DataObjectEnumBase
{
public:
    /// Constructor that initializes a typed data object from name and value.
    /// \param name Name of the data object.
    /// \param value Initial value of the contained data.
    explicit DataObjectEnum(Domain* domain, string_view name, const DataType& value) :
        DataObjectEnumBase(domain, name),
        m_value(value)
    {
        m_valueInt = (int)value;
    }

    /// Retrieves the value that is represented by this data object.
    /// \return Value within this data object.
    DataType getValue() const
    {
        return m_value;
    }

    /// Sets the value of this data object.
    /// \param value New value that is assigned to this data object.
    void setValue(const DataType& value)
    {
        if (value != m_value)
        {
            m_value = value;
            m_valueInt = (int)value;
            notifyModified();
        }
    }

private:
    DataType m_value;
};
}

#endif
