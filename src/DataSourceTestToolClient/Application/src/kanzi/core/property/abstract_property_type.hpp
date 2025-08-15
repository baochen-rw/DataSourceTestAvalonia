// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_PROPERTY_TYPE_HPP
#define KZ_ABSTRACT_PROPERTY_TYPE_HPP


#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/property/property_type_descriptor.hpp>


namespace kanzi
{

/// AbstractPropertyType is a homogeneous property type handle.
///
/// AbstractPropertyType can be used to operate on property types when the actual property type and its data type are unknown or irrelevant.
/// To set or get property values a DynamicPropertyType with corresponding data type must be constructed from an AbstractPropertyType.
class KANZI_API AbstractPropertyType
{
    typedef void (AbstractPropertyType::*bool_type)() const;
    void this_type_does_not_support_comparisons() const {}

public:

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR

    explicit operator bool() const
    {
        return m_descriptor ? true : false;
    }

#else

    operator bool_type() const
    {
        return m_descriptor ? &AbstractPropertyType::this_type_does_not_support_comparisons : 0;
    }

#endif

    friend bool operator==(const AbstractPropertyType& left, const AbstractPropertyType& right)
    {
        return left.m_descriptor == right.m_descriptor;
    }

    friend bool operator!=(const AbstractPropertyType& left, const AbstractPropertyType& right)
    {
        return !(left == right);
    }

    friend bool operator<(const AbstractPropertyType& left, const AbstractPropertyType& right)
    {
        return left.m_descriptor < right.m_descriptor;
    }

    friend bool operator>(const AbstractPropertyType& left, const AbstractPropertyType& right)
    {
        return left.m_descriptor > right.m_descriptor;
    }

    AbstractPropertyTypeDescriptor* get() const
    {
        return m_descriptor;
    }

    /// Gets the fully qualified name of a property type in the form "Class.PropertyType".
    /// \return The fully qualified name of a property type.
    /// \see getUnqualifiedName()
    const char* getName() const
    {
        kzAssert(m_descriptor);
        return m_descriptor->getName();
    }

    /// Gets the unqualified name of a property type in the form "PropertyType".
    /// \return The unqualified name of a property type.
    /// \see getName()
    const char* getUnqualifiedName() const
    {
        kzAssert(m_descriptor);
        return m_descriptor->getUnqualifiedName();
    }

    /// Gets the data type of a property type. The data type of a property type defines
    /// the data representation type of each property value. For example, float.
    /// \return The data type of a property type.
    PropertyDataType getDataType() const
    {
        kzAssert(m_descriptor);
        return m_descriptor->getDataType();
    }

    /// Returns whether a property type is inheritable.
    /// Inheritable property types provide values to all descendant nodes.
    /// \return If the property type is inheritable, true, otherwise false.
    bool isInherited() const
    {
        kzAssert(m_descriptor);
        return m_descriptor->isInherited();
    }

    /// Gets the change flags for a property type.
    /// Change flags indicate whether a modification of property value invalidates
    /// a particular aspect of a node. For example, when you change the Node::HeightProperty
    /// or Node::WidthProperty in a node Kanzi recalculates the layout.
    /// \return The change flags for a property type.
    uint32_t getChangeFlags() const
    {
        kzAssert(m_descriptor);
        return m_descriptor->getChangeFlags();
    }

    /// Gets the editor information of a property type.
    /// \return The editor information of a property type.
    PropertyTypeEditorInfoSharedPtr getEditorInfo() const
    {
        kzAssert(m_descriptor);
        return m_descriptor->getEditorInfo();
    }

    explicit AbstractPropertyType() :
        m_descriptor(0)
    {
    }

    explicit AbstractPropertyType(AbstractPropertyTypeDescriptor* descriptor) :
        m_descriptor(descriptor)
    {
    }

    explicit AbstractPropertyType(string_view name) :
        m_descriptor(AbstractPropertyTypeDescriptor::findDescriptor(name))
    {
    }

private:

    AbstractPropertyTypeDescriptor* m_descriptor;
};

}

KZ_CPP_SPECIALIZE_TR1_BEGIN

/// Specialization of std::hash for AbstractPropertyType.
template<>
struct hash<kanzi::AbstractPropertyType>
{
public:

    size_t operator()(kanzi::AbstractPropertyType propertyType) const
    {
        return hash<void*>()(propertyType.get());
    }
};

KZ_CPP_SPECIALIZE_TR1_END

#endif
