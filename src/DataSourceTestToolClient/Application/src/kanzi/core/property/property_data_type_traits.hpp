// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_DATA_TYPE_TRAITS_HPP
#define KZ_PROPERTY_DATA_TYPE_TRAITS_HPP

#include <kanzi/core/property/property_data_type.hpp>

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>

#include <kanzi/core/math/color_rgba.hpp>
#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/math/vector3.hpp>
#include <kanzi/core/math/vector4.hpp>
#include <kanzi/core/math/matrix3x3.hpp>
#include <kanzi/core/math/matrix4x4.hpp>
#include <kanzi/core/math/srt_value_2d.hpp>
#include <kanzi/core/math/srt_value_3d.hpp>


namespace kanzi
{

template <typename T>
struct PropertyDataTypeTraits
{
    /// typedef ... StorageType;
    /// typedef ... ParameterType;
    /// typedef ... ReturnType;
    /// static const PropertyDataType dataType;
};

class Resource;
typedef shared_ptr<Resource> ResourceSharedPtr;

namespace detail
{

template <typename T>
struct PrimitiveDataTypeTraits
{
    typedef T StorageType;
    typedef T ParameterType;
    typedef T ReturnType;

    static inline void write(StorageType& storage, ParameterType value)
    {
        storage = value;
    }

    static inline ReturnType read(StorageType storage)
    {
        return storage;
    }
};

template <typename T>
struct VectorDataTypeTraits
{
    typedef T StorageType;
    typedef T ParameterType;
    typedef T ReturnType;

    static inline void write(StorageType& storage, ParameterType value)
    {
        storage = value;
    }

    static inline const ReturnType& read(const StorageType& storage)
    {
        return storage;
    }
};

template <typename T>
struct ComplexDataTypeTraits
{
    typedef T StorageType;
    typedef const T& ParameterType;
    typedef T ReturnType;

    static inline void write(StorageType& storage, ParameterType value)
    {
        storage = value;
    }

    static inline const ReturnType& read(const StorageType& storage)
    {
        return storage;
    }
};

}

template <>
struct PropertyDataTypeTraits<bool> : public detail::PrimitiveDataTypeTraits<bool>
{
    static const PropertyDataType dataType = PropertyDataTypeBool;
};

template <>
struct PropertyDataTypeTraits<int> : public detail::PrimitiveDataTypeTraits<int>
{
    static const PropertyDataType dataType = PropertyDataTypeInt;
};

template <>
struct PropertyDataTypeTraits<float> : public detail::PrimitiveDataTypeTraits<float>
{
    static const PropertyDataType dataType = PropertyDataTypeFloat;
};

template <>
struct PropertyDataTypeTraits<void*> : public detail::PrimitiveDataTypeTraits<void*>
{
    static const PropertyDataType dataType = PropertyDataTypePointer;
};

template <>
struct PropertyDataTypeTraits<ColorRGBA> : public detail::VectorDataTypeTraits<ColorRGBA>
{
    static const PropertyDataType dataType = PropertyDataTypeColor;
};

template <>
struct PropertyDataTypeTraits<Vector2> : public detail::VectorDataTypeTraits<Vector2>
{
    static const PropertyDataType dataType = PropertyDataTypeVector2;
};

template <>
struct PropertyDataTypeTraits<Vector3> : public detail::VectorDataTypeTraits<Vector3>
{
    static const PropertyDataType dataType = PropertyDataTypeVector3;
};

template <>
struct PropertyDataTypeTraits<Vector4> : public detail::VectorDataTypeTraits<Vector4>
{
    static const PropertyDataType dataType = PropertyDataTypeVector4;
};

template <>
struct PropertyDataTypeTraits<Matrix3x3> : public detail::ComplexDataTypeTraits<Matrix3x3>
{
    static const PropertyDataType dataType = PropertyDataTypeMatrix3x3;
};

template <>
struct PropertyDataTypeTraits<Matrix4x4> : public detail::ComplexDataTypeTraits<Matrix4x4>
{
    static const PropertyDataType dataType = PropertyDataTypeMatrix4x4;
};

template <>
struct PropertyDataTypeTraits<SRTValue2D> : public detail::ComplexDataTypeTraits<SRTValue2D>
{
    static const PropertyDataType dataType = PropertyDataTypeSRT2D;
};

template <>
struct PropertyDataTypeTraits<SRTValue3D> : public detail::ComplexDataTypeTraits<SRTValue3D>
{
    static const PropertyDataType dataType = PropertyDataTypeSRT3D;
};

template <>
struct PropertyDataTypeTraits<ResourceSharedPtr> : public detail::ComplexDataTypeTraits<ResourceSharedPtr>
{
    static const PropertyDataType dataType = PropertyDataTypeResource;
};

template <>
struct PropertyDataTypeTraits<string>
{
    typedef string StorageType;
    typedef string_view ParameterType;
    typedef string ReturnType;

    static const PropertyDataType dataType = PropertyDataTypeString;

    static inline void write(StorageType& storage, ParameterType parameter)
    {
        storage.assign(cbegin(parameter), cend(parameter));
    }

    static inline const string& read(const StorageType& storage)
    {
        return storage;
    }
};

}


#endif
