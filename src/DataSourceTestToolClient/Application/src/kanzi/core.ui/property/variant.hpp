// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_VARIANT_HPP
#define KZ_VARIANT_HPP

#include <kanzi/core/math/srt_value_2d.hpp>
#include <kanzi/core/math/srt_value_3d.hpp>
#include <kanzi/core/property/property_type.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/variant.hpp>


namespace kanzi
{


/// Union container for manipulating an object from a heterogeneous set of types in a uniform manner.
struct Variant : public variant<monostate, bool, int, float, ColorRGBA, Vector2, Vector3, Vector4, SRTValue2D, SRTValue3D, Matrix3x3, Matrix4x4, string, ResourceID, ResourceSharedPtr, void*, KzcQuaternion>
{
    typedef variant<monostate, bool, int, float, ColorRGBA, Vector2, Vector3, Vector4, SRTValue2D, SRTValue3D, Matrix3x3, Matrix4x4, string, ResourceID, ResourceSharedPtr, void*, KzcQuaternion> BaseClass;

    explicit Variant()
    {
    }

    template <typename T>
    explicit Variant(const T& v) : BaseClass(v)
    {
    }

    template <typename T>
    Variant& operator=(const T& v)
    {
        BaseClass::operator=(v);
        return *this;
    }

    Variant(const Variant& v) : BaseClass(static_cast<const BaseClass&>(v))
    {
    }

    Variant& operator=(Variant other)
    {
        swap(other);
        return *this;
    }

    friend bool operator==(const Variant& lhs, const Variant& rhs)
    {
        return static_cast<const BaseClass&>(lhs) == static_cast<const BaseClass&>(rhs);
    }
};

}


/** Set a variant to be empty. Empty variants are considered invalid. */
KANZI_API kzsError kzuVariantSetEmpty(struct kanzi::Variant* variant);
/** Checks if a variant is empty. Empty variants are considered invalid. */
KANZI_API kzBool kzuVariantIsEmpty(const struct kanzi::Variant* variant);
/** Get the type of the value stored in a variant. */
KANZI_API kanzi::PropertyDataType kzuVariantGetType(const struct kanzi::Variant* variant);

/** Set a float field of a variant. */
KANZI_API kzsError kzuVariantSetFloatWithField(struct kanzi::Variant* variant, kanzi::PropertyField field, float value);
/** Get the float value stored in a variant, also use field. */
KANZI_API float kzuVariantGetFloatWithField(const struct kanzi::Variant* variant, kanzi::PropertyField field);

/** Check if variants are equal. Empty variants are not equal to each other.
* KZU_PROPERTY_DATA_TYPE_STRUCT and KZU_PROPERTY_DATA_TYPE_ARRAY data types are not supported.
* \return KZ_TRUE if the variants are equal, KZ_FALSE otherwise.
*/
KANZI_API kzBool kzuVariantIsEqual(const struct kanzi::Variant* variantA, const struct kanzi::Variant* variantB);

/** Resolve the actual data type of a variant, including the field.
* \param variant Variant to examine.
* \param field Field.
* \return Data type.
*/
KANZI_API kanzi::PropertyDataType kzuVariantResolveType(const struct kanzi::Variant* variant, kanzi::PropertyField field);

/** Cast a variant into the target variant.
* \param targetVariant The variant which value is written.
* \param targetDataType ::KzuPropertyDataType to use as the target variant's data type.
* \param sourceVariant The variant which value is read.
* \param out_cast Set on success. The value is KZ_TRUE if the cast succeeded, otherwise KZ_FALSE.
* \return KZS_SUCCESS on success.
*/
KANZI_API kzsError kzuVariantCast(struct kanzi::Variant* targetVariant, kanzi::PropertyDataType targetDataType, const struct kanzi::Variant* sourceVariant, kzBool* out_cast);

/**
* Gets an object's property from a property manager and sets the property value to the given variant.
* \param object Object owning the property to read.
* \param propertyType ::KzuPropertyType of the property to read.
* \param field The field to read from the property.
* \param variant Previously created variant which value is set.
* \param out_found Set on success. The value is KZ_TRUE if the property was found, otherwise KZ_FALSE.
* \return KZS_SUCCESS on success, KZS_ERROR_ENUM_OUT_OF_RANGE in case of unsuitable data type or field.
*/
KANZI_API kzsError kzuVariantInitializeFromProperty(const kanzi::Object* object,
                                                    kanzi::AbstractPropertyType propertyType, kanzi::PropertyField field,
                                                    struct kanzi::Variant* variant, kzBool* out_found);

/** Sets an object's property from a variant.
* \param variant Variant which value is read.
* \param object Object owning the property to set.
* \param propertyType ::KzuPropertyType of the property to set.
* \param field ::KzuPropertyField of the property to set.
* \param out_written Set on success. The value is KZ_TRUE if the property was written, otherwise KZ_FALSE.
* \return KZS_SUCCESS on success, KZU_ERROR_WRONG_PROPERTY_DATA_TYPE if the field is not suitable, KZS_ERROR_ENUM_OUT_OF_RANGE if the variant data type is invalid.
*/
KANZI_API kzsError kzuVariantSetToProperty(const struct kanzi::Variant* variant, kanzi::Object* object,
                                           kanzi::AbstractPropertyType propertyType, kanzi::PropertyField field,
                                           kzBool* out_written);

/** Changes the value and the type of the variant to a sub-value and a sub-type of the variant.
* \param variant Variant which value is filtered.
* \param field The field to filter by.
* \return KZS_SUCCESS on success, KZU_ERROR_WRONG_PROPERTY_DATA_TYPE if the field is not suitable for filtering,
          KZS_ERROR_ENUM_OUT_OF_RANGE if the variant data type is invalid.
*/
KANZI_API kzsError kzuVariantFilterWithField(struct kanzi::Variant* variant, kanzi::PropertyField field);


#endif
