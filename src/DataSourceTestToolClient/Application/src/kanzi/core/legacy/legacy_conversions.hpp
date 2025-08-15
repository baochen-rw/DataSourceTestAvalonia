// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_LEGACY_CONVERSIONS_HPP
#define KANZI_LEGACY_CONVERSIONS_HPP


#include <kanzi/core/math/matrix3x3.hpp>
#include <kanzi/core/math/matrix4x4.hpp>
#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/math/vector3.hpp>
#include <kanzi/core/math/vector4.hpp>

#include <kanzi/core/legacy/util/math/kzc_matrix3x3.hpp>
#include <kanzi/core/legacy/util/math/kzc_matrix4x4.hpp>
#include <kanzi/core/legacy/util/math/kzc_vector2.hpp>
#include <kanzi/core/legacy/util/math/kzc_vector3.hpp>
#include <kanzi/core/legacy/util/math/kzc_vector4.hpp>


namespace legacy
{


inline KzcVector2 convert(const kanzi::Vector2& v)
{
    return kzcVector2(v[0], v[1]);
}

inline kanzi::Vector2 convert(KzcVector2 v)
{
    return kanzi::Vector2(v.data[0], v.data[1]);
}

inline KzcVector3 convert(const kanzi::Vector3& v)
{
    return kzcVector3(v[0], v[1], v[2]);
}

inline kanzi::Vector3 convert(KzcVector3 v)
{
    return kanzi::Vector3(v.data[0], v.data[1], v.data[2]);
}

inline KzcVector4 convert(const kanzi::Vector4& v)
{
    return kzcVector4(v[0], v[1], v[2], v[3]);
}

inline kanzi::Vector4 convert(KzcVector4 v)
{
    return kanzi::Vector4(v.data[0], v.data[1], v.data[2], v.data[3]);
}

inline KzcMatrix3x3 convert(const kanzi::Matrix3x3& v)
{
    return kzcMatrix3x3(
        v[0], v[3], v[6],
        v[1], v[4], v[7],
        v[2], v[5], v[8]);
}

inline kanzi::Matrix3x3 convert(const KzcMatrix3x3& v)
{
    return kanzi::Matrix3x3(
        v.data[0], v.data[1], v.data[2],
        v.data[3], v.data[4], v.data[5],
        v.data[6], v.data[7], v.data[8]);
}

inline KzcMatrix4x4 convert(const kanzi::Matrix4x4& v)
{
    return kzcMatrix4x4(
        v[0], v[4], v[8], v[12],
        v[1], v[5], v[9], v[13],
        v[2], v[6], v[10], v[14],
        v[3], v[7], v[11], v[15]);
}

inline kanzi::Matrix4x4 convert(const KzcMatrix4x4& v)
{
    return kanzi::Matrix4x4(
        v.data[0], v.data[1], v.data[2], v.data[3],
        v.data[4], v.data[5], v.data[6], v.data[7],
        v.data[8], v.data[9], v.data[10], v.data[11],
        v.data[12], v.data[13], v.data[14], v.data[15]);
}

}


#endif
