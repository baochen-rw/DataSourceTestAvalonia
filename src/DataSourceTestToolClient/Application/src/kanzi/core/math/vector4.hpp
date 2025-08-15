// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_VECTOR4_HPP
#define KANZI_VECTOR4_HPP


#include <kanzi/core/cpp/algorithm.hpp>
#include <kanzi/core/cpp/limits.hpp>
#include <kanzi/core/cpp/math.hpp>

#include <kanzi/core/legacy/wrappers/kzs_math.hpp>

#include <kanzi/core/cpp/math.hpp>
#include <kanzi/core/cpp/limits.hpp>

namespace kanzi
{

// TODO: move KANZI_API to non inline functions
/// Vector with 4 floating point components: (x, y, z, w).
class KANZI_API Vector4
{
public:

    /// Default constructor, initializes the vector to (0.0, 0.0, 0.0, 0.0).
    explicit Vector4():
        data()
    {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }

    /// Constructor, initializes the vector to (x, y, z, w).
    /// \param x x component of the vector.
    /// \param y y component of the vector.
    /// \param z z component of the vector.
    /// \param w w component of the vector.
    explicit Vector4(float x, float y, float z, float w):
        data()
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = w;
    }

    /// Access to individual elements of the vector.
    /// \param index Index of the accessed element. Should be either 0, 1, 2, or 3.
    /// \return If index is 0, x element. If index is 1, y element. If index is 2, z element. If index is 3, w element.
    const float& operator[] (size_t index) const
    {
        kzAssert(index < 4);

        return data[index];
    }

    /// Access to individual elements of the vector.
    /// \param index Index of the accessed element. Should be either 0, 1, 2, or 3.
    /// \return If index is 0, x element. If index is 1, y element. If index is 2, z element. If index is 3, w element.
    float& operator[] (size_t index)
    {
        kzAssert(index < 4);

        return data[index];
    }

    /// Multiplies each vector element with a scalar.
    /// \param scalar Multiplier for each vector element.
    /// \return This vector.
    Vector4& operator*=(float scalar)
    {
        data[0] *= scalar;
        data[1] *= scalar;
        data[2] *= scalar;
        data[3] *= scalar;
        return *this;
    }

    /// Divides each vector element with a scalar.
    /// \param scalar Divider for each vector element.
    /// \return This vector.
    Vector4& operator/=(float scalar)
    {
        data[0] /= scalar;
        data[1] /= scalar;
        data[2] /= scalar;
        data[3] /= scalar;
        return *this;
    }

    /// Modifies this vector by adding another vector.
    /// \param v Another vector.
    /// \return This vector.
    Vector4& operator+=(const Vector4& v)
    {
        data[0] += v.data[0];
        data[1] += v.data[1];
        data[2] += v.data[2];
        data[3] += v.data[3];
        return *this;
    }

    /// Modifies this vector by subtracting another vector from this vector.
    /// \param v Another vector.
    /// \return This vector.
    Vector4& operator-=(const Vector4& v)
    {
        data[0] -= v.data[0];
        data[1] -= v.data[1];
        data[2] -= v.data[2];
        data[3] -= v.data[3];
        return *this;
    }

    /// Returns the x element of the vector
    /// \return The x element.
    float getX() const
    {
        return data[0];
    }

    /// Returns the y element of the vector
    /// \return The y element.
    float getY() const
    {
        return data[1];
    }

    /// Returns the z element of the vector
    /// \return The z element.
    float getZ() const
    {
        return data[2];
    }

    /// Returns the w element of the vector
    /// \return The w element.
    float getW() const
    {
        return data[3];
    }

    /// Sets the x element of the vector.
    /// \param value The new value of the x element.
    void setX(float value)
    {
        data[0] = value;
    }

    /// Sets the y element of the vector.
    /// \param value The new value of the y element.
    void setY(float value)
    {
        data[1] = value;
    }

    /// Sets the z element of the vector.
    /// \param value The new value of the z element.
    void setZ(float value)
    {
        data[2] = value;
    }

    /// Sets the w element of the vector.
    /// \param value The new value of the w element.
    void setW(float value)
    {
        data[3] = value;
    }

    /// Returns the vector with each element having the most negative float value.
    /// \return Vector with the lowest possible value.
    static inline Vector4 lowestValue();

    /// Returns the vector with each element having the most positive float value.
    /// \return Vector with the highest possible value.
    static inline Vector4 highestValue();

    /// Returns the vector with each element being NaN.
    /// \return Vector with NaN elements.
    static inline Vector4 nan();

    // TODO: rename to hasNaN
    /// Returns true if and only if at least one of the vector values is NaN.
    inline bool isNaN() const
    {
        return isnan(data[0]) || isnan(data[1]) || isnan(data[2]) || isnan(data[3]);
    }

    /// Returns the vector with each element being the positive infinity.
    /// \return Vector with positive infinity elements.
    static inline Vector4 positiveInfinity();

    /// Returns the vector with each element being the negative infinity.
    /// \return Vector with negative infinity elements.
    static inline Vector4 negativeInfinity();

private:

    /// Vector elements.
    float data[4];
};

/// Calculates component wise absolute value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector4 componentAbs(Vector4 v)
{
    return Vector4(
        abs(v[0]),
        abs(v[1]),
        abs(v[2]),
        abs(v[3]));
}

/// Calculates component wise ceil value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector4 componentCeil(Vector4 v)
{
    return Vector4(
        ceil(v[0]),
        ceil(v[1]),
        ceil(v[2]),
        ceil(v[3]));
}

/// Calculates component wise floor value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector4 componentFloor(Vector4 v)
{
    return Vector4(
        floor(v[0]),
        floor(v[1]),
        floor(v[2]),
        floor(v[3]));
}

/// Calculates component wise rounded value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector4 componentRound(Vector4 v)
{
    return Vector4(
        round(v[0]),
        round(v[1]),
        round(v[2]),
        round(v[3]));
}

/// Calculates component wise square root all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector4 componentSqrt(Vector4 v)
{
    return Vector4(
        sqrt(v[0]),
        sqrt(v[1]),
        sqrt(v[2]),
        sqrt(v[3]));
}

/// Calculates the component wise maximum for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector4 componentWiseMax(Vector4 v1, Vector4 v2)
{
    return Vector4(
        max(v1[0], v2[0]),
        max(v1[1], v2[1]),
        max(v1[2], v2[2]),
        max(v1[3], v2[3]));
}

/// Calculates the component wise minimum for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector4 componentWiseMin(Vector4 v1, Vector4 v2)
{
    return Vector4(
        min(v1[0], v2[0]),
        min(v1[1], v2[1]),
        min(v1[2], v2[2]),
        min(v1[3], v2[3]));
}

/// Does component wise multiply for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector4 componentWiseMultiply(Vector4 v1, Vector4 v2)
{
    return Vector4(
        v1[0] * v2[0],
        v1[1] * v2[1],
        v1[2] * v2[2],
        v1[3] * v2[3]);
}

/// Does component wise divide for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector4 componentWiseDivide(Vector4 v1, Vector4 v2)
{
    return Vector4(
        v1[0] / v2[0],
        v1[1] / v2[1],
        v1[2] / v2[2],
        v1[3] / v2[3]);
}

/// Does component wise remainder for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector4 componentWiseRemainder(Vector4 v1, Vector4 v2)
{
    return Vector4(
        fmod(v1[0], v2[0]),
        fmod(v1[1], v2[1]),
        fmod(v1[2], v2[2]),
        fmod(v1[3], v2[3]));
}

/// Adds a value to all elements of a vector and returns the result.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector4 componentAdd(Vector4 v, float scalar)
{
    return Vector4(
        v[0] + scalar,
        v[1] + scalar,
        v[2] + scalar,
        v[3] + scalar);
}

/// Subtracts a value from all elements of a vector and returns the result.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector4 componentSubtract(Vector4 v, float scalar)
{
    return Vector4(
        v[0] - scalar,
        v[1] - scalar,
        v[2] - scalar,
        v[3] - scalar);
}

/// Returns true if each component of the first vector is less than the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is less than the corresponding component of the second vector, false otherwise.
inline bool componentAllLessThan(Vector4 a, Vector4 b)
{
    return (a[0] < b[0] && a[1] < b[1] && a[2] < b[2] && a[3] < b[3]);
}

/// Returns true if each component of the first vector is less than or equal to the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is less than or equal to the corresponding component of the second vector, false otherwise.
inline bool componentAllLessThanOrEqual(Vector4 a, Vector4 b)
{
    return (a[0] <= b[0] && a[1] <= b[1] && a[2] <= b[2] && a[3] <= b[3]);
}

/// Returns true if each component of the first vector is greater than the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is greater than the corresponding component of the second vector, false otherwise.
inline bool componentAllGreaterThan(Vector4 a, Vector4 b)
{
    return (a[0] > b[0] && a[1] > b[1] && a[2] > b[2] && a[3] > b[3]);
}

/// Returns true if each component of the first vector is greater than or equal to the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is greater than or equal to the corresponding component of the second vector, false otherwise.
inline bool componentAllGreaterThanOrEqual(Vector4 a, Vector4 b)
{
    return (a[0] >= b[0] && a[1] >= b[1] && a[2] >= b[2] && a[3] >= b[3]);
}

/// Adds two vectors and returns the sum.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return The result vector.
inline Vector4 operator+(Vector4 v1, Vector4 v2)
{
    return Vector4(v1) += v2;
}

/// Subtracts two vectors and returns the difference.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return The result vector.
inline Vector4 operator-(Vector4 v1, Vector4 v2)
{
    return Vector4(v1) -= v2;
}

/// Multiplies all vector elements with a scalar and returns the resulting vector.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector4 operator*(Vector4 v, float scalar)
{
    return Vector4(v) *= scalar;
}

/// Multiplies all vector elements with a scalar and returns the resulting vector.
/// \param scalar A scalar.
/// \param v A vector.
/// \return The result vector.
inline Vector4 operator*(float scalar, Vector4 v)
{
    return Vector4(v) *= scalar;
}

/// Divides all vector elements with a scalar and returns the resulting vector.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector4 operator/(Vector4 v, float scalar)
{
    return Vector4(v) /= scalar;
}

/// Negates all vector elements and returns the resulting vector.
/// \param v A vector.
/// \return The result vector.
inline Vector4 operator-(Vector4 v)
{
    return v * -1.0f;
}

/// Unary plus, doesn't do anything and returns the resulting vector.
/// \param v A vector.
/// \return The result vector.
inline Vector4 operator+(Vector4 v)
{
    return v;
}

// TODO: remove all equality operators
/// Compares two vectors for equality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return True if vectors are equal.
inline bool operator==(Vector4 v1, Vector4 v2)
{
    return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2] && v1[3] == v2[3];
}

/// Compares two vectors for inequality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return True if vectors are different.
inline bool operator!=(Vector4 v1, Vector4 v2)
{
    return !(v1 == v2);
}

/// Calculates the dot product of two vectors.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The dot product of the vectors.
inline float dotProduct(Vector4 v1, Vector4 v2)
{
    Vector4 v = componentWiseMultiply(v1, v2);
    return v[0] + v[1] + v[2] + v[3];
}

inline Vector4 Vector4::lowestValue()
{
    return -highestValue();
}

inline Vector4 Vector4::highestValue()
{
    return Vector4(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
}

inline Vector4 Vector4::nan()
{
    return Vector4(numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN());
}

inline Vector4 Vector4::positiveInfinity()
{
    return Vector4(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
}

inline Vector4 Vector4::negativeInfinity()
{
    return Vector4(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());
}


}


#endif
