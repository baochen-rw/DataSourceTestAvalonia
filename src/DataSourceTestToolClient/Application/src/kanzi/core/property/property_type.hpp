// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_TYPE_HPP
#define KZ_PROPERTY_TYPE_HPP


#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/math/color_rgba.hpp>
#include <kanzi/core/math/matrix3x3.hpp>
#include <kanzi/core/math/matrix4x4.hpp>
#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/math/vector3.hpp>
#include <kanzi/core/math/vector4.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/type_traits.hpp>
#include <kanzi/core/cpp/unordered_map.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/property/property_data_type.hpp>
#include <kanzi/core/property/property_field.hpp>
#include <kanzi/core/property/resource_id.hpp>
#include <kanzi/core/property/property_type_descriptor.hpp>
#include <kanzi/core/property/abstract_property_type.hpp>


namespace kanzi
{

// Forward declarations.
class Object;
class Node;
class Resource;
typedef shared_ptr<Resource> ResourceSharedPtr;
template <typename DataType>
class DynamicPropertyType;


/// Property type represents a property type for the property system.
///
/// You can use PropertyType class to define a property type.
/// Instances of PropertyType uniquely identify property types in functions that operate on properties.
template <typename Type, typename = void>
class PropertyType
{
    friend class Object;
    friend class Node;
    friend class AbstractPropertyType;
    friend class DynamicPropertyType<Type>;

public:
    
    typedef Type DataType;
    typedef PropertyTypeDescriptor<Type> Descriptor;
    typedef typename PropertyTypeDescriptor<Type>::Traits Traits;

    explicit PropertyType(FixedString name):
        m_propertyType(create(name, DataType(), 0, false, PropertyTypeEditorInfoSharedPtr()))
    {
    }

    explicit PropertyType(MetadataGeneratedName name) :
        m_propertyType(create(name, DataType(), 0, false, PropertyTypeEditorInfoSharedPtr()))
    {
    }

    explicit PropertyType(FixedString name, DataType defaultValue, uint32_t changeFlags, bool inheritable) :
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr()))
    {
    }

    explicit PropertyType(MetadataGeneratedName name, DataType defaultValue, uint32_t changeFlags, bool inheritable) :
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr()))
    {
    }

    explicit PropertyType(FixedString name, DataType defaultValue, uint32_t changeFlags, bool inheritable, PropertyTypeEditorInfo* editorInfo) :
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr(editorInfo)))
    {
    }

    explicit PropertyType(MetadataGeneratedName name, DataType defaultValue, uint32_t changeFlags, bool inheritable, PropertyTypeEditorInfo* editorInfo) :
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr(editorInfo)))
    {
    }

    ~PropertyType()
    {
        delete m_propertyType;
    }

    operator AbstractPropertyType() const
    {
        return AbstractPropertyType(m_propertyType);
    }

    /// Returns the default value for the property type.
    /// The default value is returned by getProperty functions when no other value is available.
    typename Traits::ReturnType getDefaultValue() const
    {
        return m_propertyType->getDefaultValue();
    }

    /// Returns the fully qualified name of the property type in form "Class.PropertyType".
    const char* getName() const
    {
        return m_propertyType->getName();
    }

    /// Returns the unqualified name of the property type in form "PropertyType", where the qualified name is "Class.PropertyType".
    const char* getUnqualifiedName() const
    {
        return m_propertyType->getUnqualifiedName();
    }

    /// Returns the data type of the property type.
    /// The data type of the property type defines the data representation type of each property value, for example float.
    PropertyDataType getDataType() const
    {
        return m_propertyType->getDataType();
    }

    /// Returns true if the property type is inheritable, false otherwise.
    /// Inheritable property types provide values for all objects down the hierarchy.
    bool isInherited() const
    {
        return m_propertyType->isInherited();
    }

    /// Returns the change flags of the property type.
    /// Change flags can indicate that particular aspect of an object should be invalidated when you modify a property, for example layout.
    uint32_t getChangeFlags() const
    {
        return m_propertyType->getChangeFlags();
    }

    /// Returns the editor information of the property type.
    PropertyTypeEditorInfoSharedPtr getEditorInfo() const
    {
        return m_propertyType->getEditorInfo();
    }

    Descriptor* get() const
    {
        return m_propertyType;
    }

protected:

    explicit PropertyType():
        m_propertyType(0)
    {
    }

private:

    PropertyType(const PropertyType&) KZ_DELETED_FUNCTION;
    PropertyType& operator=(const PropertyType&) KZ_DELETED_FUNCTION;

    Descriptor* create(FixedString name, DataType defaultValue, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo)
    {
        return new Descriptor(name, defaultValue, changeFlags, inherited, editorInfo);
    }

    Descriptor* create(MetadataGeneratedName name, DataType defaultValue, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo)
    {
        return new Descriptor(name, defaultValue, changeFlags, inherited, editorInfo);
    }

    Descriptor* m_propertyType;
};

/// Specialization for PropertyType for enums. See PropertyType.
template <typename Type>
class PropertyType<Type, typename enable_if<is_enum<Type>::value>::type>
{
    friend class Object;
    friend class Node;
    friend class AbstractPropertyType;
    friend class DynamicPropertyType<Type>;

public:
    
    typedef Type DataType;
    typedef PropertyTypeDescriptor<int> Descriptor;

    struct Traits : public Descriptor::Traits
    {
        typedef int StorageType;
        typedef Type ParameterType;
        typedef Type ReturnType;

        static inline ReturnType read(StorageType storage)
        {
            return static_cast<Type>(storage);
        }

        static inline void write(StorageType& storage, ParameterType value)
        {
            storage = static_cast<int>(value);
        }
    };

    explicit PropertyType(FixedString name, Type defaultValue, uint32_t changeFlags, bool inheritable):
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr()))
    {
    }

    explicit PropertyType(MetadataGeneratedName name, Type defaultValue, uint32_t changeFlags, bool inheritable) :
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr()))
    {
    }

    explicit PropertyType(FixedString name, Type defaultValue, uint32_t changeFlags, bool inheritable, PropertyTypeEditorInfo* editorInfo):
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr(editorInfo)))
    {
    }

    explicit PropertyType(MetadataGeneratedName name, Type defaultValue, uint32_t changeFlags, bool inheritable, PropertyTypeEditorInfo* editorInfo) :
        m_propertyType(create(name, defaultValue, changeFlags, inheritable, PropertyTypeEditorInfoSharedPtr(editorInfo)))
    {
    }

    ~PropertyType()
    {
        delete m_propertyType;
    }

    operator AbstractPropertyType() const
    {
        return AbstractPropertyType(m_propertyType);
    }

    /// Returns the default value for the property type.
    /// The default value is returned by getProperty functions when no other value is available.
    typename Traits::ReturnType getDefaultValue() const
    {
        return static_cast<Type>(m_propertyType->getDefaultValue());
    }

    /// Returns the fully qualified name of the property type in form "Class.PropertyType".
    const char* getName() const
    {
        return m_propertyType->getName();
    }

    /// Returns the unqualified name of the property type in form "PropertyType", where the qualified name is "Class.PropertyType".
    const char* getUnqualifiedName() const
    {
        return m_propertyType->getUnqualifiedName();
    }

    /// Returns the data type of the property type.
    /// The data type of the property type defines the data representation type of each property value, for example float.
    PropertyDataType getDataType() const
    {
        return m_propertyType->getDataType();
    }

    /// Returns true if the property type is inheritable, false otherwise.
    /// Inheritable property types provide values for all objects down the hierarchy.
    bool isInherited() const
    {
        return m_propertyType->isInherited();
    }

    /// Returns the change flags of the property type.
    /// Change flags can indicate that particular aspect of an object should be invalidated when you modify a property, for example layout.
    uint32_t getChangeFlags() const
    {
        return m_propertyType->getChangeFlags();
    }

    /// Returns the editor information of the property type.
    PropertyTypeEditorInfoSharedPtr getEditorInfo() const
    {
        return m_propertyType->getEditorInfo();
    }

    Descriptor* get() const
    {
        return m_propertyType;
    }

protected:

    explicit PropertyType():
        m_propertyType(0)
    {
    }

private:

    PropertyType(const PropertyType&) KZ_DELETED_FUNCTION;
    PropertyType& operator=(const PropertyType&) KZ_DELETED_FUNCTION;

    Descriptor* create(FixedString name, Type defaultValue, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo)
    {
        return new Descriptor(name, static_cast<int>(defaultValue), changeFlags, inherited, editorInfo);
    }

    Descriptor* create(MetadataGeneratedName name, Type defaultValue, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo)
    {
        return new Descriptor(name, static_cast<int>(defaultValue), changeFlags, inherited, editorInfo);
    }

    Descriptor* m_propertyType;
};

}


#endif // KZ_PROPERTY_TYPE_HPP
