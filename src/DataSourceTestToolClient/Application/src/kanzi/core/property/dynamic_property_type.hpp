// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DYNAMIC_PROPERTY_TYPE_HPP
#define KZ_DYNAMIC_PROPERTY_TYPE_HPP

#include <kanzi/core/property/property_type.hpp>
#include <kanzi/core/cpp/stdexcept.hpp>


namespace kanzi
{

/// DynamicPropertyType is a handle for property types that are unknown.
///
/// You can use DynamicPropertyType to access property types if you know their data type and name.
template <class Type>
class DynamicPropertyType : public PropertyType<Type>
{
public:

    explicit DynamicPropertyType(string_view name)
    {
        typedef typename PropertyType<Type>::Descriptor Descriptor;

        using std::swap;

        AbstractPropertyTypeDescriptor* abstractDescriptor = AbstractPropertyTypeDescriptor::findDescriptor(name);

        if (!abstractDescriptor)
        {
            kzThrowException(logic_error("Failed to find property type '" + string(name) + "'"));
        }

        Descriptor* descriptor = dynamic_cast<Descriptor*>(abstractDescriptor);
        if (!descriptor)
        {
            kzThrowException(logic_error("Trying to construct DynamicPropertyType '" + string(name) + "' with wrong data type"));
        }

        swap(PropertyType<Type>::m_propertyType, descriptor);
    }

    explicit DynamicPropertyType(AbstractPropertyType abstractPropertyType)
    {
        typedef typename PropertyType<Type>::Descriptor Descriptor;

        using std::swap;

        if (!abstractPropertyType)
        {
            kzThrowException(invalid_argument("Trying to construct DynamicPropertyType from null AbstractPropertyType"));
        }

        AbstractPropertyTypeDescriptor* abstractDescriptor = abstractPropertyType.get();
        Descriptor* descriptor = dynamic_cast<Descriptor*>(abstractDescriptor);
        if (!descriptor)
        {
            kzThrowException(logic_error("Trying to construct DynamicPropertyType '" + string(abstractPropertyType.getName()) + "' with wrong data type"));
        }

        swap(PropertyType<Type>::m_propertyType, descriptor);
    }

    ~DynamicPropertyType()
    {
        PropertyType<Type>::m_propertyType = 0;
    }
};

}

#endif
