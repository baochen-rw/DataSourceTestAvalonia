// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_VECTOR2_HPP
#define KANZI_VECTOR2_HPP


#include "vector3.hpp"

#include <kanzi/core/cpp/algorithm.hpp>
#include <kanzi/core/cpp/limits.hpp>
#include <kanzi/core/cpp/math.hpp>

#include <kanzi/core/legacy/wrappers/kzs_math.hpp>


namespace kanzi
{

/// Vector with 2 floating point components: (x, y).
class KANZI_API Vector2
{
public:

    /// Default constructor, initializes the vector to (0.0, 0.0).
    explicit Vector2():
        data()
    {
        data[0] = 0.0f;
        data[1] = 0.0f;
    }

    /// Constructor, initializes the vector to (x, y).
    /// \param x x component of the vector.
    /// \param y y component of the vector.
    explicit Vector2(float x, float y):
        data()
    {
        data[0] = x;
        data[1] = y;
    }

    /// Access to individual elements of the vector.
    /// \param index Index of the accessed element. Should be either 0 or 1.
    /// \return If index is 0, x element. If index is 1, y element.
    const float& operator[] (size_t index) const
    {
        kzAssert(index < 2);

        return data[index];
    }

    /// Access to individual elements of the vector.
    /// \param index Index of the accessed element. Should be either 0 or 1.
    /// \return If index is 0, reference to x element. If index is 1, reference to y element.
    float& operator[] (size_t index)
    {
        kzAssert(index < 2);

        return data[index];
    }

    /// Multiplies each vector element with a scalar.
    /// \param scalar Multiplier for each vector element.
    /// \return This vector.
    Vector2& operator*=(float scalar)
    {
        data[0] *= scalar;
        data[1] *= scalar;
        return *this;
    }

    /// Divides each vector element with a scalar.
    /// \param scalar Divider for each vector element.
    /// \return This vector.
    Vector2& operator/=(float scalar)
    {
        data[0] /= scalar;
        data[1] /= scalar;
        return *this;
    }

    /// Modifies this vector by adding another vector.
    /// \param v Another vector.
    /// \return This vector.
    Vector2& operator+=(const Vector2& v)
    {
        data[0] += v.data[0];
        data[1] += v.data[1];
        return *this;
    }

    /// Modifies this vector by subtracting another vector from this vector.
    /// \param v Another vector.
    /// \return This vector.
    Vector2& operator-=(const Vector2& v)
    {
        data[0] -= v.data[0];
        data[1] -= v.data[1];
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

    /// Calculates the length a vectors.
    /// \return sqrt(x*x + y*y)
    float length() const;

    /// Calculates the squared length a vectors.
    /// \return x*x + y*y
    inline float squaredLength() const;

    /// Normalizes the vector and returns the resulting vector.
    /// \return The normalized vector.
    inline Vector2 normalized() const;

    /// Returns the vector with each element having the most negative float value.
    /// \return Vector with the lowest possible value.
    static inline Vector2 lowestValue();

    /// Returns the vector with each element having the most positive float value.
    /// \return Vector with the highest possible value.
    static inline Vector2 highestValue();

    /// Returns the vector with each element being NaN.
    /// \return Vector with NaN elements.
    static inline Vector2 nan();

    /// Returns true if and only if at least one of the vector values is NaN.
    inline bool isNaN() const
    {
        return isnan(data[0]) || isnan(data[1]);
    }

    /// Returns the vector with each element being the positive infinity.
    /// \return Vector with positive infinity elements.
    static inline Vector2 positiveInfinity();

    /// Returns the vector with each element being the negative infinity.
    /// \return Vector with negative infinity elements.
    static inline Vector2 negativeInfinity();

    // TODO: remove
    /// Creates a Vector2 from Vector3 by dropping the z-coordinate.
    /// \param v Input vector.
    /// \return The input vector without z-coordinate.
    static Vector2 createFromVector3(Vector3 v)
    {
        return Vector2(v.getX(), v.getY());
    }

private:

    /// Vector elements.
    float data[2];
};

/// Calculates component wise absolute value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector2 componentAbs(Vector2 v)
{
    return Vector2(
        abs(v[0]),
        abs(v[1]));
}

/// Calculates component wise ceil value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector2 componentCeil(Vector2 v)
{
    return Vector2(
        ceil(v[0]),
        ceil(v[1]));
}

/// Calculates component wise floor value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector2 componentFloor(Vector2 v)
{
    return Vector2(
        floor(v[0]),
        floor(v[1]));
}

/// Calculates component wise rounded value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector2 componentRound(Vector2 v)
{
    return Vector2(
        round(v[0]),
        round(v[1]));
}

/// Calculates component wise square root all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector2 componentSqrt(Vector2 v)
{
    return Vector2(
        sqrt(v[0]),
        sqrt(v[1]));
}

/// Calculates the component wise maximum for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector2 componentWiseMax(Vector2 v1, Vector2 v2)
{
    return Vector2(
        max(v1[0], v2[0]),
        max(v1[1], v2[1]));
}

/// Calculates the component wise minimum for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector2 componentWiseMin(Vector2 v1, Vector2 v2)
{
    return Vector2(
        min(v1[0], v2[0]),
        min(v1[1], v2[1]));
}

/// Does component wise multiply for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector2 componentWiseMultiply(Vector2 v1, Vector2 v2)
{
    return Vector2(
        v1[0] * v2[0],
        v1[1] * v2[1]);
}

/// Does component wise divide for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector2 componentWiseDivide(Vector2 v1, Vector2 v2)
{
    return Vector2(
        v1[0] / v2[0],
        v1[1] / v2[1]);
}

/// Does component wise remainder for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector2 componentWiseRemainder(Vector2 v1, Vector2 v2)
{
    return Vector2(
        fmod(v1[0], v2[0]),
        fmod(v1[1], v2[1]));
}

/// Adds a value to all elements of a vector and returns the result.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector2 componentAdd(Vector2 v, float scalar)
{
    return Vector2(
        v[0] + scalar,
        v[1] + scalar);
}

/// Subtracts a value from all elements of a vector and returns the result.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector2 componentSubtract(Vector2 v, float scalar)
{
    return Vector2(
        v[0] - scalar,
        v[1] - scalar);
}

/// Returns true if each component of the first vector is less than the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is less than the corresponding component of the second vector, false otherwise.
inline bool componentAllLessThan(Vector2 a, Vector2 b)
{
    return (a[0] < b[0] && a[1] < b[1]);
}

/// Returns true if each component of the first vector is less than or equal to the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is less than or equal to the corresponding component of the second vector, false otherwise.
inline bool componentAllLessThanOrEqual(Vector2 a, Vector2 b)
{
    return (a[0] <= b[0] && a[1] <= b[1]);
}

/// Returns true if each component of the first vector is greater than the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is greater than the corresponding component of the second vector, false otherwise.
inline bool componentAllGreaterThan(Vector2 a, Vector2 b)
{
    return (a[0] > b[0] && a[1] > b[1]);
}

/// Returns true if each component of the first vector is greater than or equal to the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is greater than or equal to the corresponding component of the second vector, false otherwise.
inline bool componentAllGreaterThanOrEqual(Vector2 a, Vector2 b)
{
    return (a[0] >= b[0] && a[1] >= b[1]);
}

/// Adds two vectors and returns the sum.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return The result vector.
inline Vector2 operator+(Vector2 v1, Vector2 v2)
{
    return Vector2(v1) += v2;
}

/// Subtracts two vectors and returns the difference.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return The result vector.
inline Vector2 operator-(Vector2 v1, Vector2 v2)
{
    return Vector2(v1) -= v2;
}

/// Multiplies all vector elements with a scalar and returns the resulting vector.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector2 operator*(Vector2 v, float scalar)
{
    return Vector2(v) *= scalar;
}

/// Multiplies all vector elements with a scalar and returns the resulting vector.
/// \param scalar A scalar.
/// \param v A vector.
/// \return The result vector.
inline Vector2 operator*(float scalar, Vector2 v)
{
    return Vector2(v) *= scalar;
}

/// Divides all vector elements with a scalar and returns the resulting vector.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector2 operator/(Vector2 v, float scalar)
{
    return Vector2(v) /= scalar;
}

/// Negates all vector elements and returns the resulting vector.
/// \param v A vector.
/// \return The result vector.
inline Vector2 operator-(Vector2 v)
{
    return v * -1.0f;
}

/// Unary plus, doesn't do anything and returns the resulting vector.
/// \param v A vector.
/// \return The result vector.
inline Vector2 operator+(Vector2 v)
{
    return v;
}

/// Compares two vectors for equality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return True if vectors are equal.
inline bool operator==(Vector2 v1, Vector2 v2)
{
    return v1[0] == v2[0] && v1[1] == v2[1];
}

/// Compares two vectors for inequality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return True if vectors are different.
inline bool operator!=(Vector2 v1, Vector2 v2)
{
    return !(v1 == v2);
}

/// Calculates the dot product of two vectors.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The dot product of the vectors.
inline float dotProduct(Vector2 v1, Vector2 v2)
{
    Vector2 v = componentWiseMultiply(v1, v2);
    return v[0] + v[1];
}

/// Calculates pseudo-cross product of two 2D vectors. 
/// U x V = Uy * Vx - Ux * Vy.
/// \param left The first vector.
/// \param right The second vector.
/// \return The pseudo-cross product of the vectors.
inline float pseudoCrossProduct(const Vector2& left, const Vector2& right)
{
    return (left[1] * right[0]) - (left[0] * right[1]);
}

inline float Vector2::squaredLength() const
{
    return dotProduct(*this, *this);
}

inline Vector2 Vector2::normalized() const
{
    float vectorLength = length();

    return vectorLength == 0.0f ? nan() : *this / vectorLength;
}

inline Vector2 Vector2::lowestValue()
{
    return -highestValue();
}

inline Vector2 Vector2::highestValue()
{
    return Vector2(numeric_limits<float>::max(), numeric_limits<float>::max());
}

inline Vector2 Vector2::nan()
{
    return Vector2(numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN());
}

inline Vector2 Vector2::positiveInfinity()
{
    return Vector2(numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
}

inline Vector2 Vector2::negativeInfinity()
{
    return Vector2(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());
}


}

#endif
