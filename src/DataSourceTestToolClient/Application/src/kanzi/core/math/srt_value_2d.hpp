// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SRT_VALUE_2D_HPP
#define KZ_SRT_VALUE_2D_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/math/matrix3x3.hpp>

namespace kanzi
{

/// Structure describing scale, rotation and translation transformation in 2D space.
/// Rotation is stored as angle in radians.
class KANZI_API SRTValue2D
{
public:

    /// Default constructor.
    explicit SRTValue2D() : m_scale(1.0f, 1.0f), m_rotation(0.0f), m_translation()
    {
    }

    /// Constructor with supplied scale, rotation and translation.
    explicit SRTValue2D(Vector2 scale, float rotationInRadians, Vector2 translation) : m_scale(scale), m_rotation(rotationInRadians), m_translation(translation)
    {
    }

    /// Returns the scale.
    Vector2 getScale() const
    {
        return m_scale;
    }

    // Sets the scale.
    void setScale(Vector2 value)
    {
        m_scale = value;
    }

    /// Applies scale factor.
    /// Multiplies current scale with provided factor.
    void scale(Vector2 factor)
    {
        m_scale = componentWiseMultiply(m_scale, factor);
    }

    /// Applies uniform scale factor.
    /// Multiplies current scale with provided factor.
    void uniformScale(float factor)
    {
        scale(Vector2(factor, factor));
    }

    /// Returns scale along X.
    float getScaleX() const
    {
        return m_scale.getX();
    }

    /// Sets scale along X.
    void setScaleX(float value)
    {
        m_scale.setX(value);
    }
    
    /// Returns scale along Y.
    float getScaleY() const
    {
        return m_scale.getY();
    }

    /// Sets scale along Y.
    void setScaleY(float value)
    {
        m_scale.setY(value);
    }

    /// Returns rotation.
    /// Rotation is angle in radians.
    float getRotation() const
    {
        return m_rotation;
    }

    /// Sets rotation.
    /// Rotation is angle in radians.
    void setRotation(float rotationInRadians)
    {
        m_rotation = rotationInRadians;
    }

    /// Applies rotation.
    /// Provided angle is added.
    /// Rotation is angle in radians.
    void rotate(float rotationInRadians)
    {
        m_rotation += rotationInRadians;
    }

    /// Returns translation.
    Vector2 getTranslation() const
    {
        return m_translation;
    }

    /// Sets translation.
    void setTranslation(Vector2 value)
    {
        m_translation = value;
    }

    /// Applies translation.
    /// Adds provided translation to existing translation.
    void translate(Vector2 translation)
    {
        m_translation += translation;
    }

    /// Returns translation along X.
    float getTranslationX() const
    {
        return m_translation.getX();
    }

    /// Sets translation along X.
    void setTranslationX(float value)
    {
        m_translation.setX(value);
    }

    /// Returns translation along Y.
    float getTranslationY() const
    {
        return m_translation.getY();
    }

    /// Sets translation along Y.
    void setTranslationY(float value)
    {
        m_translation.setY(value);
    }

    /// Converts the SRT representation to Matrix3x3 transform.
    Matrix3x3 toMatrix() const;

    /// Creates a scale SRT.
    static SRTValue2D createScale(Vector2 scale)
    {
        return SRTValue2D(scale, 0.0f, Vector2());
    }

    /// Creates a rotation SRT.
    /// Rotation is angle in radians.
    static SRTValue2D createRotation(float rotationInRadians)
    {
        return SRTValue2D(Vector2(1.0f, 1.0f), rotationInRadians, Vector2());
    }

    /// Creates a translation SRT.
    static SRTValue2D createTranslation(Vector2 translation)
    {
        return SRTValue2D(Vector2(1.0f, 1.0f), 0.0f, translation);
    }

    /// Attempts to create an SRT from a Matrix3x3.
    /// If SRT cannot be extracted from Matrix3x3 returns nullopt.
    static optional<SRTValue2D> create(const Matrix3x3& matrix);

    /// Operator ==.
    friend bool operator==(const SRTValue2D& left, const SRTValue2D& right)
    {
        return left.m_scale == right.m_scale &&
               left.m_rotation == right.m_rotation &&
               left.m_translation == right.m_translation;
    }

    /// Operator !=.
    friend bool operator!=(const SRTValue2D& left, const SRTValue2D& right)
    {
        return !(left == right);
    }

private:

    /// Scale.
    Vector2 m_scale;
    /// Rotation in radians.
    float m_rotation;
    /// Translation.
    Vector2 m_translation;
};

}


#endif
