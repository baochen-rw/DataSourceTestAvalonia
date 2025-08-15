// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INTERPOLATION_HPP
#define KZ_INTERPOLATION_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/property/resource_id.hpp>
#include <kanzi/core/math/srt_value_2d.hpp>
#include <kanzi/core/math/srt_value_3d.hpp>


// Animation interpolation helpers for different data types.

namespace kanzi
{

class Resource;
typedef shared_ptr<Resource> ResourceSharedPtr;

template <typename T>
T animationInterpolate(const T& from, const T& to, float phase)
{
    return T(from * (1.0f - phase) + to * phase);
}

inline bool animationInterpolate(bool from, bool to, float phase)
{
    return phase < 1.0f ? from : to;
}

inline string animationInterpolate(const string& from, const string& to, float phase)
{
    return phase < 1.0f ? from : to;
}

inline ResourceID animationInterpolate(const ResourceID& from, const ResourceID& to, float phase)
{
    return phase < 1.0f ? from : to;
}

inline const ResourceSharedPtr& animationInterpolate(const ResourceSharedPtr& from, const ResourceSharedPtr& to, float phase)
{
    return phase < 1.0f ? from : to;
}

inline SRTValue3D animationInterpolate(const SRTValue3D& from, const SRTValue3D& to, float phase)
{
    Vector3 resultScale = animationInterpolate(from.getScale(), to.getScale(), phase);
    Vector3 resultTranslation = animationInterpolate(from.getTranslation(), to.getTranslation(), phase);
    KzcQuaternion fromRotation = from.getRotation();
    KzcQuaternion toRotation = to.getRotation();
    KzcQuaternion resultRotation;

    kzcQuaternionSlerp(&fromRotation, &toRotation, phase, &resultRotation);

    SRTValue3D result(resultScale, resultRotation, resultTranslation);

    return result;
}

inline SRTValue3DLongerPath animationInterpolate(const SRTValue3DLongerPath& from, const SRTValue3DLongerPath& to, float phase)
{
    Vector3 resultScale = animationInterpolate(from.getScale(), to.getScale(), phase);
    Vector3 resultTranslation = animationInterpolate(from.getTranslation(), to.getTranslation(), phase);
    KzcQuaternion fromRotation = from.getRotation();
    KzcQuaternion toRotation = to.getRotation();
    KzcQuaternion resultRotation;

    kzcQuaternionSlerpLongerPath(&fromRotation, &toRotation, phase, &resultRotation);

    SRTValue3D result(resultScale, resultRotation, resultTranslation);

    return SRTValue3DLongerPath(result);
}

inline SRTValue2D animationInterpolate(const SRTValue2D& from, const SRTValue2D& to, float phase)
{
    Vector2 resultScale = animationInterpolate(from.getScale(), to.getScale(), phase);
    Vector2 resultTranslation = animationInterpolate(from.getTranslation(), to.getTranslation(), phase);
    float resultRotation = animationInterpolate(from.getRotation(), to.getRotation(), phase);

    SRTValue2D result(resultScale, resultRotation, resultTranslation);

    return result;
}

template <typename T>
T animationConcatenate(const T& lhs, const T& rhs)
{
    return T(lhs + rhs);
}

inline bool animationConcatenate(bool lhs, bool rhs)
{
    return lhs || rhs;
}

inline ResourceSharedPtr animationConcatenate(ResourceSharedPtr /*lhs*/, ResourceSharedPtr rhs)
{
    // Concatenation is not defined for resources, always return rhs resource.
    return rhs;
}

inline SRTValue2D animationConcatenate(const SRTValue2D& lhs, const SRTValue2D& rhs)
{
    return SRTValue2D(lhs.getScale() + rhs.getScale(), lhs.getRotation() + rhs.getRotation(), lhs.getTranslation() + rhs.getTranslation());
}

inline SRTValue3D animationConcatenate(const SRTValue3D& lhs, const SRTValue3D& rhs)
{
    // Quaternions are multiplied in the same order as column-major matrices.
    return SRTValue3D(lhs.getScale() + rhs.getScale(), rhs.getRotation() * lhs.getRotation(), lhs.getTranslation() + rhs.getTranslation());
}
}


#endif
