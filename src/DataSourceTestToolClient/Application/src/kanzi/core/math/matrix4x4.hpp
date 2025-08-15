// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_MATRIX4X4_HPP
#define KANZI_MATRIX4X4_HPP


#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/math/matrix3x3.hpp>
#include <kanzi/core/math/vector4.hpp>


namespace kanzi
{

/// Matrix with 4x4 elements.
class KANZI_API Matrix4x4
{
public:
    /// Default constructor, initializes the matrix to identity matrix.
    explicit Matrix4x4() :
        data()
    {
        data[0] = 1.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
        data[3] = 0.0f;

        data[4] = 0.0f;
        data[5] = 1.0f;
        data[6] = 0.0f;
        data[7] = 0.0f;

        data[8] = 0.0f;
        data[9] = 0.0f;
        data[10] = 1.0f;
        data[11] = 0.0f;

        data[12] = 0.0f;
        data[13] = 0.0f;
        data[14] = 0.0f;
        data[15] = 1.0f;
    }

    /// Constructs the matrix from elements.
    explicit Matrix4x4(
        float x0, float x1, float x2, float x3,
        float x4, float x5, float x6, float x7,
        float x8, float x9, float x10, float x11,
        float x12, float x13, float x14, float x15) :
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
        data[9] = x9;
        data[10] = x10;
        data[11] = x11;

        data[12] = x12;
        data[13] = x13;
        data[14] = x14;
        data[15] = x15;
    }

    /// Constructs the matrix from 4 vectors.
    explicit Matrix4x4(
        const Vector3& x,
        const Vector3& y,
        const Vector3& z,
        const Vector3& translation):
        data()
    {
        data[0] = x[0];
        data[1] = x[1];
        data[2] = x[2];
        data[3] = 0.0f;

        data[4] = y[0];
        data[5] = y[1];
        data[6] = y[2];
        data[7] = 0.0f;

        data[8] = z[0];
        data[9] = z[1];
        data[10] = z[2];
        data[11] = 0.0f;

        data[12] = translation[0];
        data[13] = translation[1];
        data[14] = translation[2];
        data[15] = 1.0f;
    }

    /// Access to individual elements of the matrix.
    /// \param index Index of the accessed element. Should be at least 0 and at most 15.
    /// \return
    const float& operator[](size_t index) const
    {
        kzAssert(index < 16);

        return data[index];
    }

    /// Access to individual elements of the matrix.
    /// \param index Index of the accessed element. Should be at least 0 and at most 15.
    /// \return
    float& operator[](size_t index)
    {
        kzAssert(index < 16);

        return data[index];
    }

    Vector3 getXAxis() const
    {
        return Vector3(data[0], data[1], data[2]);
    }

    Vector3 getYAxis() const
    {
        return Vector3(data[4], data[5], data[6]);
    }

    Vector3 getZAxis() const
    {
        return Vector3(data[8], data[9], data[10]);
    }

    Vector3 getTranslation() const
    {
        return Vector3(data[12], data[13], data[14]);
    }

    Vector3 getScale() const;

    void scale(const Vector3& scale)
    {
        float scaleX = scale.getX();
        float scaleY = scale.getY();
        float scaleZ = scale.getZ();
        data[0] *= scaleX;
        data[1] *= scaleX;
        data[2] *= scaleX;
        data[4] *= scaleY;
        data[5] *= scaleY;
        data[6] *= scaleY;
        data[8] *= scaleZ;
        data[9] *= scaleZ;
        data[10] *= scaleZ;
    }


    void setXAxis(Vector3 v)
    {
        data[0] = v[0];
        data[1] = v[1];
        data[2] = v[2];
    }

    void setYAxis(Vector3 v)
    {
        data[4] = v[0];
        data[5] = v[1];
        data[6] = v[2];
    }

    void setZAxis(Vector3 v)
    {
        data[8] = v[0];
        data[9] = v[1];
        data[10] = v[2];
    }

    void setTranslation(Vector3 translation)
    {
        data[12] = translation[0];
        data[13] = translation[1];
        data[14] = translation[2];
    }

    /// Get translation on X axis.
    ///
    /// \return Translation X component.
    float getTranslationX() const
    {
        return data[12];
    }

    /// Set translation on X axis.
    ///
    /// \param translationX Translation X component.
    void setTranslationX(float translationX)
    {
        data[12] = translationX;
    }

    /// Get translation on Y axis.
    ///
    /// \return Translation Y component.
    float getTranslationY() const
    {
        return data[13];
    }

    /// Set translation on Y axis.
    ///
    /// \param translationY Translation Y component.
    void setTranslationY(float translationY)
    {
        data[13] = translationY;
    }

    /// Get translation on Z axis.
    ///
    /// \return Translation Z component.
    float getTranslationZ() const
    {
        return data[14];
    }

    /// Set translation on Z axis.
    ///
    /// \param translationZ Translation Y component.
    void setTranslationZ(float translationZ)
    {
        data[14] = translationZ;
    }

    // TODO: remove
    /// Modifies this matrix by adding another matrix.
    /// \param v Another matrix.
    /// \return This matrix.
    Matrix4x4& operator+=(const Matrix4x4& v)
    {
        for (int i = 0; i < 16; ++i)
        {
            data[i] += v.data[i];
        }
        return *this;
    }

    /// Modifies this matrix by subtracting another matrix from this matrix.
    /// \param v Another matrix.
    /// \return This matrix.
    Matrix4x4& operator-=(const Matrix4x4& v)
    {
        for (int i = 0; i < 16; ++i)
        {
            data[i] -= v.data[i];
        }
        return *this;
    }

    /// Multiply a 3-component vector with this matrix.
    /// \param vector A Vector3.
    /// \return Result of the multiplication.
    Vector3 operator*(const Vector3& vector) const
    {
        Vector3 result(data[0] * vector[0] + data[4] * vector[1] + data[8] * vector[2] + data[12],
                       data[1] * vector[0] + data[5] * vector[1] + data[9] * vector[2] + data[13],
                       data[2] * vector[0] + data[6] * vector[1] + data[10] * vector[2] + data[14]);
        return result;
    }

    /// Multiply a 4-component vector with this matrix.
    /// \param vector A Vector4.
    /// \return Result of the multiplication.
    Vector4 operator*(const Vector4& vector) const
    {
        Vector4 result(data[0] * vector[0] + data[4] * vector[1] + data[8] * vector[2] + data[12] * vector[3],
                       data[1] * vector[0] + data[5] * vector[1] + data[9] * vector[2] + data[13] * vector[3],
                       data[2] * vector[0] + data[6] * vector[1] + data[10] * vector[2] + data[14] * vector[3],
                       data[3] * vector[0] + data[7] * vector[1] + data[11] * vector[2] + data[15] * vector[3]);
        return result;
    }

    /// Modifies this matrix by multiplying it with another matrix.
    /// \param m Another matrix.
    /// \return This matrix.
    Matrix4x4& operator*=(const Matrix4x4& m);

    KANZI_API friend bool operator==(const Matrix4x4& left, const Matrix4x4& right);

    /// Inequality operator.
    ///
    /// \param left Left-hand-side operand.
    /// \param right Right-hand-side operand.
    /// \return True if matrices are not equal, false if they are.
    friend bool operator!=(const Matrix4x4& left, const Matrix4x4& right)
    {
        return !(left == right);
    }

    static Matrix4x4 createTranslation(Vector3 translation)
    {
        return Matrix4x4(Vector3::right(), Vector3::up(), Vector3::backward(), translation);
    }

    static Matrix4x4 createTranslation(float x, float y, float z)
    {
        return createTranslation(Vector3(x, y, z));
    }

    static Matrix4x4 createIdentity()
    {
        return Matrix4x4();
    }

    static Matrix4x4 createFromHomogenousMatrix(const Matrix3x3& matrix, float zTranslation)
    {
        return Matrix4x4(matrix[0], matrix[1], 0.0f, matrix[2],
                         matrix[3], matrix[4], 0.0f, matrix[5],
                         0.0f, 0.0f, 1.0f, 0.0f,
                         matrix[6], matrix[7], zTranslation, matrix[8]);
    }

    static Matrix4x4 createFromHomogenousMatrix(const Matrix3x3& matrix)
    {
        return createFromHomogenousMatrix(matrix, 0.0f);
    }

    // TODO add radians function
    // TODO move "degrees" into function name
    static Matrix4x4 createXRotation(float angleInDegrees);
    static Matrix4x4 createYRotation(float angleInDegrees);
    static Matrix4x4 createZRotation(float angleInDegrees);
    static Matrix4x4 createScale(Vector3 scale);
    static Matrix4x4 createOrthogonalProjection(float left, float right, float bottom, float top, float near, float far);
    static optional<Matrix4x4> createLookAtMatrix(Vector3 position, Vector3 lookAtPoint, Vector3 upVector);

    static Matrix4x4 createSRT(Vector3 scale, Vector3 rotationInRadians, Vector3 translation);

    Matrix4x4 transposed() const
    {
        return Matrix4x4(data[0], data[4], data[8], data[12],
                         data[1], data[5], data[9], data[13],
                         data[2], data[6], data[10], data[14],
                         data[3], data[7], data[11], data[15]);
    }

private:
    /// Matrix elements.
    float data[16];
};

KANZI_API Matrix4x4 operator*(const Matrix4x4& left, const Matrix4x4& right);

KANZI_API Matrix4x4 multiplyAffine(const Matrix4x4& left, const Matrix4x4& right);

KANZI_API Matrix4x4 orthonormalizeBase(const Matrix4x4& matrix);
// TODO make member
KANZI_API optional<Matrix4x4> inverse(const Matrix4x4& matrix);
KANZI_API bool isTranslationOnly(const Matrix4x4& matrix);
// TODO specify radians in the name
KANZI_API void extractSRT(const Matrix4x4& matrix, Vector3& scale, Vector3& rotationInRadians, Vector3& translation);
}


#endif
