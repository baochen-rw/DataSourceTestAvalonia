// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SRT_VALUE_3D_HPP
#define KZ_SRT_VALUE_3D_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/math/vector3.hpp>
#include <kanzi/core/math/matrix4x4.hpp>
#include <kanzi/core/legacy/util/math/kzc_quaternion.hpp>

namespace kanzi
{

/// Structure describing scale, rotation and translation transformation in 3D space.
class KANZI_API SRTValue3D
{
public:

    explicit SRTValue3D() :
        m_scale(1.0f, 1.0f, 1.0f),
        m_rotation(),
        m_translation()
    {
    }

    explicit SRTValue3D(Vector3 scale, Vector3 rotationAnglesInRadians, Vector3 translation) :
        m_scale(scale),
        m_rotation(kzcQuaternionFromRotationAngles(rotationAnglesInRadians[0], rotationAnglesInRadians[1], rotationAnglesInRadians[2])),
        m_translation(translation)
    {
    }

    explicit SRTValue3D(Vector3 scale, KzcQuaternion rotation, Vector3 translation) :
        m_scale(scale),
        m_rotation(rotation),
        m_translation(translation)
    {
    }

    Vector3 getScale() const
    {
        return m_scale;
    }

    void setScale(Vector3 value)
    {
        m_scale = value;
    }

    float getScaleX() const
    {
        return m_scale.getX();
    }

    void setScaleX(float value)
    {
        m_scale.setX(value);
    }

    float getScaleY() const
    {
        return m_scale.getY();
    }

    void setScaleY(float value)
    {
        m_scale.setY(value);
    }

    float getScaleZ() const
    {
        return m_scale.getZ();
    }

    void setScaleZ(float value)
    {
        m_scale.setZ(value);
    }

    void scale(Vector3 factor)
    {
        m_scale = componentWiseMultiply(m_scale, factor);
    }

    KzcQuaternion getRotation() const
    {
        return m_rotation;
    }

    void setRotation(KzcQuaternion value)
    {
        m_rotation = value;
    }

    void setRotation(Vector3 rotationAnglesInRadians)
    {
        m_rotation = kzcQuaternionFromRotationAngles(rotationAnglesInRadians[0], rotationAnglesInRadians[1], rotationAnglesInRadians[2]);
    }

    Vector3 getTranslation() const
    {
        return m_translation;
    }

    void setTranslation(Vector3 value)
    {
        m_translation = value;
    }

    float getTranslationX() const
    {
        return m_translation.getX();
    }

    void setTranslationX(float value)
    {
        m_translation.setX(value);
    }

    float getTranslationY() const
    {
        return m_translation.getY();
    }

    void setTranslationY(float value)
    {
        m_translation.setY(value);
    }

    float getTranslationZ() const
    {
        return m_translation.getZ();
    }

    void setTranslationZ(float value)
    {
        m_translation.setZ(value);
    }

    void rotate(KzcQuaternion rotation);

    Matrix4x4 toMatrix() const;

    static optional<SRTValue3D> create(const Matrix4x4& matrix);
    
    static SRTValue3D createScale(Vector3 scale)
    {
        return SRTValue3D(scale, KzcQuaternion(), Vector3());
    }

    static SRTValue3D createUniformScale(float scale)
    {
        return createScale(Vector3(scale, scale, scale));
    }

    static SRTValue3D createTranslation(Vector3 translation)
    {
        return SRTValue3D(Vector3(1.0f, 1.0f, 1.0f), KzcQuaternion(), translation);
    }

    friend bool operator==(const SRTValue3D& left, const SRTValue3D& right)
    {
        return left.m_scale == right.m_scale &&
               left.m_rotation == right.m_rotation &&
               left.m_translation == right.m_translation;
    }

    friend bool operator!=(const SRTValue3D& left, const SRTValue3D& right)
    {
        return !(left == right);
    }

private:

    Vector3 m_scale;
    KzcQuaternion m_rotation;
    Vector3 m_translation;
};

class KANZI_API SRTValue3DLongerPath: public SRTValue3D
{
public:
    explicit SRTValue3DLongerPath(const SRTValue3D& value):
        SRTValue3D(value)
    {
    }
};

}


#endif
