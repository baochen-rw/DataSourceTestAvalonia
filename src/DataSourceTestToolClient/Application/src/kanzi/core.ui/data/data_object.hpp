// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_OBJECT_HPP
#define KZ_DATA_OBJECT_HPP

#include <kanzi/core.ui/coreui_api.hpp>
#include <kanzi/core.ui/data/data_context.hpp>

#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <memory>

namespace kanzi
{
class DataObject;

typedef shared_ptr<DataObject> DataObjectSharedPtr;

/**
* DataObject is the base class for data. 
* All data within the data source is described as a tree of data objects. 
* The base class provides support for the hierarchy as the derived classes provide support for different value types.
**/
class KANZI_COREUI_API DataObject : public DataContext, public enable_shared_from_this<DataObject>
{
public:
    /// Type enumerations for different data object types.
    enum Type
    {
        Object = 0,
        Integer,
        Real,
        Bool,
        String,
        Enum,
        List
    };

    /// Standard constructor.
    /// \param name Name of the data object.
    explicit DataObject(Domain* domain, string_view name);

    /// Allows to retrieve the name of the object.
    /// \return Returns the name of the object.
    string getName() const;

    /// Sets the name of the object.
    /// \param value New name that is assigned to object.
    void setName(string_view value);

    /// Allows to retrieve the type of the object.
    /// \return Type enumeration of the object.
    virtual Type getType() const
    {
        return DataObject::Object;
    }

    /// Retrieves the count of child objects in this data object.
    /// \return Child object count.
    size_t getChildCount() const;

    /// Retrieves a child object in given index.
    /// \return Child data object in given index.
    DataObjectSharedPtr getChild(size_t index) const;

    /// Retrieves the index of a child data object.
    /// \return Index of the item in question, throws exception if there is no such child.
    size_t getChildIndex(const DataObject& child) const;

    /// Checks whether or not the child exists.
    /// \return true if there is such child, otherwise false.
    bool hasChild(const DataObject& child) const;

    /// Adds data object as child of this object.
    /// \param child Child object to add.
    void addChild(const DataObjectSharedPtr& child);

    /// Inserts data object as child of this object, allows to specify index of the object.
    /// \param index Index where to add given object.
    /// \param child Child object to add.
    void insertChild(size_t index, const DataObjectSharedPtr& child);

    /// Removes a child object from list of childs.
    /// \param child Child object to remove.
    void removeChild(const DataObject& child);

    /// Removes a child object in given index.
    /// \param Index of the child object to remove.
    void removeChild(size_t index);

    /// Removes all children.
    void removeAllChildren();

    /** Iterators for children */
    typedef vector<DataObjectSharedPtr> ChildContainer;
    typedef ChildContainer::const_iterator ChildConstIterator;
    typedef ChildContainer::const_reverse_iterator ChildConstReverseIterator;

    /// Returns iterator to start of the child container.
    /// \return Iterator at the beginning of the container.
    ChildConstIterator beginChildren() const;

    /// Returns iterator in the end of the child container.
    /// \return Iterator in the end of the container.
    ChildConstIterator endChildren() const;

    /// Tries to find a child with given name.
    /// \return Child object that was found, or empty pointer if there is no such child.
    DataObjectSharedPtr findChild(string_view name);

    /// DataContext interface.
    virtual DataObjectSharedPtr getData() KZ_OVERRIDE;
    virtual DataContextSharedPtr lookupDataContext(string_view relativePath) KZ_OVERRIDE;

private:
    /// Children of the data object.
    ChildContainer m_children;

    string m_name;
};

/**
* Template class that can be used with standard types.
* Provides functions to host / set / get value of given type.
**/
template <class DataType, DataObject::Type DataTypeEnum>
class KANZI_COREUI_TEMPLATE_API DataObjectTyped : public DataObject
{
public:
    /// Constructor that initializes a typed data object from name and value.
    /// \param name Name of the data object.
    /// \param value Initial value of the contained data.
    explicit DataObjectTyped(Domain* domain, string_view name, const DataType& value) :
        DataObject(domain, name),
        m_value(value)
    {
    }

    /// Retrieves the type of this data object.
    /// \return Type enumeration of this data object.
    virtual Type getType() const
    {
        return DataTypeEnum;
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
            notifyModified();
        }
    }

private:
    DataType m_value;
};

// Explicit instantiation.
#if defined(KANZI_COREUI_API_IMPORT)
extern template class DataObjectTyped<bool, DataObject::Bool>;
extern template class DataObjectTyped<int32_t, DataObject::Integer>;
extern template class DataObjectTyped<double, DataObject::Real>;
extern template class DataObjectTyped<string, DataObject::String>;
#endif

typedef DataObjectTyped<bool, DataObject::Bool> DataObjectBool;
typedef DataObjectTyped<int32_t, DataObject::Integer> DataObjectInt;
typedef DataObjectTyped<double, DataObject::Real> DataObjectReal;
typedef DataObjectTyped<string, DataObject::String> DataObjectString;
}

#endif
