// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_MATRIX3X3_HPP
#define KANZI_MATRIX3X3_HPP


#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/cpp/optional.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>

namespace kanzi
{

/// Matrix with 3x3 elements.
class KANZI_API Matrix3x3
{
public:

    /// Default constructor, initializes the matrix to identity matrix.
    explicit Matrix3x3():
        data()
    {
        data[0] = 1.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;

        data[3] = 0.0f;
        data[4] = 1.0f;
        data[5] = 0.0f;

        data[6] = 0.0f;
        data[7] = 0.0f;
        data[8] = 1.0f;
    }

    /// Constructs the matrix from elements.
    explicit Matrix3x3(
        float x0, float x1, float x2,
        float x3, float x4, float x5,
        float x6, float x7, float x8):
        data()
    {
        data[0] = x0;
        data[1] = x1;
        data[2] = x2;

        data[3] = x3;
        data[4] = x4;
        data[5] = x5;

        data[6] = x6;
        data[7] = x7;
        data[8] = x8;
    }

    /// Constructs the matrix from 3 vectors.
    explicit Matrix3x3(
        const Vector2& x,
        const Vector2& y,
        const Vector2& translation):
        data()
    {
        data[0] = x[0];
        data[1] = x[1];
        data[2] = 0.0f;

        data[3] = y[0];
        data[4] = y[1];
        data[5] = 0.0f;

        data[6] = translation[0];
        data[7] = translation[1];
        data[8] = 1.0f;
    }

    /// Access to individual elements of the matrix.
    /// \param index Index of the accessed element. Should be at least 0 and at most 15.
    /// \return 
    const float& operator[] (size_t index) const
    {
        kzAssert(index < 9);

        return data[index];
    }

    /// Access to individual elements of the matrix.
    /// \param index Index of the accessed element. Should be at least 0 and at most 15.
    /// \return 
    float& operator[] (size_t index)
    {
        kzAssert(index < 9);

        return data[index];
    }

    Vector2 getXAxis() const
    {
        return Vector2(data[0], data[1]);
    }

    Vector2 getYAxis() const
    {
        return Vector2(data[3], data[4]);
    }

    Vector2 getTranslation() const
    {
        return Vector2(data[6], data[7]);
    }

    /// Get X scale component.
    float getScaleX() const
    {
        return sqrt(data[0] * data[0] + data[1] * data[1]);
    }
    /// Get Y scale component.
    float getScaleY() const
    {
        return sqrt(data[3] * data[3] + data[4] * data[4]);
    }
    /// Get scale as a vector.
    Vector2 getScale() const
    {
        return Vector2(getScaleX(), getScaleY());
    }

    void scale(const Vector2& v)
    {
        data[0] *= v[0]; data[3] *= v[1];
        data[1] *= v[0]; data[4] *= v[1];
    }

    void setXAxis(Vector2 v)
    {
        data[0] = v[0];
        data[1] = v[1];
    }

    void setYAxis(Vector2 v)
    {
        data[3] = v[0];
        data[4] = v[1];
    }

    /// Set translation.
    ///
    /// \param translation Translation vector.
    void setTranslation(Vector2 translation)
    {
        data[6] = translation[0];
        data[7] = translation[1];
    }

    /// Set translation.
    ///
    /// \param translationX Translation X component.
    /// \param translationY Translation Y component.
    void setTranslation(float translationX, float translationY)
    {
        data[6] = translationX;
        data[7] = translationY;
    }

    /// Get translation on X axis.
    ///
    /// \return Translation X component.
    float getTranslationX() const
    {
        return data[6];
    }

    /// Set translation on X axis.
    ///
    /// \param translationX Translation X component.
    void setTranslationX(float translationX)
    {
        data[6] = translationX;
    }

    /// Get translation on Y axis.
    ///
    /// \return Translation Y component.
    float getTranslationY() const
    {
        return data[7];
    }

    /// Set translation on Y axis.
    ///
    /// \param translationY Translation Y component.
    void setTranslationY(float translationY)
    {
        data[7] = translationY;
    }

    /// Modifies this matrix by adding another matrix.
    /// \param m Another matrix.
    /// \return This matrix.
    Matrix3x3& operator+=(const Matrix3x3& m)
    {
        for(int i = 0; i < 9; ++i)
        {
            data[i] += m.data[i];
        }
        return *this;
    }

    /// Modifies this matrix by subtracting another matrix from this matrix.
    /// \param m Another matrix.
    /// \return This matrix.
    Matrix3x3& operator-=(const Matrix3x3& m)
    {
        for(int i = 0; i < 9; ++i)
        {
            data[i] -= m.data[i];
        }
        return *this;
    }

    /// Modifies this matrix by multiplying it with another matrix.
    /// \param m Another matrix.
    /// \return This matrix.
    Matrix3x3& operator*=(const Matrix3x3& m);

    static Matrix3x3 createTranslation(Vector2 translation)
    {
        return Matrix3x3(Vector2(1.0f, 0.0f), Vector2(0.0f, 1.0f), translation);
    }

    static Matrix3x3 createTranslation(float x, float y)
    {
        return createTranslation(Vector2(x, y));
    }

    static Matrix3x3 createScale(Vector2 scale)
    {
        return Matrix3x3(Vector2(scale.getX(), 0.0f), Vector2(0.0f, scale.getY()), Vector2(0.0f, 0.0f));
    }

    static Matrix3x3 createIdentity()
    {
        return Matrix3x3();
    }

    static Matrix3x3 createRotationInDegrees(float angleInDegrees);
    static Matrix3x3 createRotationInRadians(float angleInRadians);

    /// Create an SRT matrix.
    ///
    /// \param scale Scales by axises.
    /// \param rotationInRadians Rotation component in radians.
    /// \param translation Translation component.
    /// \return Newly constructed matrix.
    static Matrix3x3 createSRT(Vector2 scale, float rotationInRadians, Vector2 translation);

private:

    /// Matrix elements.
    float data[9];
};

/// Multiplies two matrices and returns the product.
/// \param m1 Left hand side matrix.
/// \param m2 Right hand side matrix.
/// \return The result matrix.
KANZI_API Matrix3x3 operator*(Matrix3x3 m1, Matrix3x3 m2);

/// Multiplies matrix with vector and returns the product.
/// \param m Left hand side matrix.
/// \param v Right hand side vector.
/// \return The result vector.
KANZI_API Vector2 operator*(Matrix3x3 m, Vector2 v);

// TODO remove
/// Compares two matrices for equality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param m1 Left hand side matrix.
/// \param m2 Right hand side matrix.
/// \return True if vectors are equal.
inline bool operator==(Matrix3x3 m1, Matrix3x3 m2)
{
    return
        m1[0] == m2[0] &&
        m1[1] == m2[1] &&
        m1[2] == m2[2] &&
        m1[3] == m2[3] &&
        m1[4] == m2[4] &&
        m1[5] == m2[5] &&
        m1[6] == m2[6] &&
        m1[7] == m2[7] &&
        m1[8] == m2[8];
}

/// Compares two matrices for inequality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param m1 Left hand side matrix.
/// \param m2 Right hand side matrix.
/// \return True if vectors are equal.
inline bool operator!=(Matrix3x3 m1, Matrix3x3 m2)
{
    return !(m1 == m2);
}


KANZI_API optional<Matrix3x3> inverse(const Matrix3x3& matrix);

KANZI_API bool isTranslationOnly(const Matrix3x3& matrix);

KANZI_API bool isScalingOnly(const Matrix3x3& matrix);

KANZI_API void extractSRT(const Matrix3x3& matrix, Vector2& scale, float& rotationInRadians, Vector2& translation);

KANZI_API optional<Matrix3x3> normalized(const Matrix3x3& matrix);

}


#endif
