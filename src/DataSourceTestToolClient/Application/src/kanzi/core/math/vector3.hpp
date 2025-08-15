// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_VECTOR3_HPP
#define KANZI_VECTOR3_HPP


#include <kanzi/core/cpp/algorithm.hpp>
#include <kanzi/core/cpp/limits.hpp>
#include <kanzi/core/cpp/math.hpp>

#include <kanzi/core/legacy/wrappers/kzs_math.hpp>


namespace kanzi
{

// TODO: move KANZI_API to non inline functions
// TODO: initialize 4th element with NaN
/// Vector with 3 floating point components: (x, y, z).
class KANZI_API Vector3
{
public:

    /// Default constructor, initializes the vector to (0.0, 0.0, 0.0).
    explicit Vector3():
        data()
    {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }

    /// Constructor, initializes the vector to (x, y, z).
    /// \param x x component of the vector.
    /// \param y y component of the vector.
    /// \param z z component of the vector.
    explicit Vector3(float x, float y, float z):
        data()
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
        data[3] = 0.0f;
    }

    /// Access to individual elements of the vector.
    /// \param index Index of the accessed element. Should be either 0, 1, or 2.
    /// \return If index is 0, x element. If index is 1, y element. If index is 2, z element.
    const float& operator[] (size_t index) const
    {
        kzAssert(index < 3);

        return data[index];
    }

    /// Access to individual elements of the vector.
    /// \param index Index of the accessed element. Should be either 0, 1, or 2.
    /// \return If index is 0, reference to x element. If index is 1, reference to y element. If index is 2, reference to z element.
    float& operator[] (size_t index)
    {
        kzAssert(index < 3);

        return data[index];
    }

    /// Multiplies each vector element with a scalar.
    /// \param scalar Multiplier for each vector element.
    /// \return This vector.
    Vector3& operator*=(float scalar)
    {
        data[0] *= scalar;
        data[1] *= scalar;
        data[2] *= scalar;
        return *this;
    }

    /// Divides each vector element with a scalar.
    /// \param scalar Divider for each vector element.
    /// \return This vector.
    Vector3& operator/=(float scalar)
    {
        data[0] /= scalar;
        data[1] /= scalar;
        data[2] /= scalar;
        return *this;
    }

    /// Modifies this vector by adding another vector.
    /// \param v Another vector.
    /// \return This vector.
    Vector3& operator+=(const Vector3& v)
    {
        data[0] += v.data[0];
        data[1] += v.data[1];
        data[2] += v.data[2];
        return *this;
    }

    /// Modifies this vector by subtracting another vector from this vector.
    /// \param v Another vector.
    /// \return This vector.
    Vector3& operator-=(const Vector3& v)
    {
        data[0] -= v.data[0];
        data[1] -= v.data[1];
        data[2] -= v.data[2];
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

    /// Returns axis based on the minimum component of Vector3.
    /// \return If X component is smallest, (1, 0, 0), else if Y component is smallest, (0, 1, 0), else (0, 0, 1).
    Vector3 minimumAxis() const
    {
        float absX = abs(data[0]);
        float absY = abs(data[1]);
        float absZ = abs(data[2]);
        if ((absX < absY) && (absX < absZ))
        {
            return right();
        }
        else if ((absY < absX) && (absY < absZ))
        {
            return up();
        }
        else
        {
            return backward();
        }
    }

    /// Returns axis based on the largest component of Vector3.
    /// \return If X component is largest, (1, 0, 0), else if Y component is largest, (0, 1, 0), else (0, 0, 1).
    Vector3 maximumAxis() const
    {
        float absX = abs(data[0]);
        float absY = abs(data[1]);
        float absZ = abs(data[2]);
        if ((absX > absY) && (absX > absZ))
        {
            return right();
        }
        else if ((absY > absX) && (absY > absZ))
        {
            return up();
        }
        else
        {
            return backward();
        }
    }

    /// Calculates the length a vectors.
    /// \return sqrt(x*x + y*y + z*z)
    float length() const;

    /// Calculates the squared length a vectors.
    /// \return x*x + y*y + z*z
    inline float squaredLength() const;

    /// Normalizes the vector and returns the resulting vector.
    /// \return The normalized vector.
    inline Vector3 normalized() const;

    /// Returns the vector with each element having the most negative float value.
    /// \return Vector with the lowest possible value.
    static inline Vector3 lowestValue();

    /// Returns the vector with each element having the most positive float value.
    /// \return Vector with the highest possible value.
    static inline Vector3 highestValue();

    /// Returns the vector with each element being NaN.
    /// \return Vector with NaN elements.
    static inline Vector3 nan();

    // TODO: make 2 methods isAnyNaN, isAllNaN
    /// Returns true if and only if at least one of the vector values is NaN.
    inline bool isNaN() const
    {
        return isnan(data[0]) || isnan(data[1]) || isnan(data[2]);
    }

    /// Returns the vector with each element being the positive infinity.
    /// \return Vector with positive infinity elements.
    static inline Vector3 positiveInfinity();

    /// Returns the vector with each element being the negative infinity.
    /// \return Vector with negative infinity elements.
    static inline Vector3 negativeInfinity();

    // TODO: rename to positiveX and so on
    /// Returns the unit vector pointing right.
    /// \return Vector3(1.0f, 0.0f, 0.0f).
    static inline Vector3 right();

    /// Returns the unit vector pointing up.
    /// \return Vector3(0.0f, 1.0f, 0.0f).
    static inline Vector3 up();

    /// Returns the unit vector pointing backward.
    /// \return Vector3(0.0f, 0.0f, 1.0f).
    static inline Vector3 backward();

    /// Returns the unit vector pointing left.
    /// \return Vector3(-1.0f, 0.0f, 0.0f).
    static inline Vector3 left();

    /// Returns the unit vector pointing down.
    /// \return Vector3(0.0f, -1.0f, 0.0f).
    static inline Vector3 down();

    /// Returns the unit vector pointing forward.
    /// \return Vector3(0.0f, 0.0f, -1.0f).
    static inline Vector3 forward();

private:

    /// Vector elements.
    float data[4];
};

/// Calculates component wise absolute value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector3 componentAbs(Vector3 v)
{
    return Vector3(
        abs(v[0]),
        abs(v[1]),
        abs(v[2]));
}

/// Calculates component wise ceil value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector3 componentCeil(Vector3 v)
{
    return Vector3(
        ceil(v[0]),
        ceil(v[1]),
        ceil(v[2]));
}

/// Calculates component wise floor value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector3 componentFloor(Vector3 v)
{
    return Vector3(
        floor(v[0]),
        floor(v[1]),
        floor(v[2]));
}

/// Calculates component wise rounded value for all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector3 componentRound(Vector3 v)
{
    return Vector3(
        round(v[0]),
        round(v[1]),
        round(v[2]));
}

/// Calculates component wise square root all elements and returns resulting vector.
/// \param v Vector input.
/// \return The result vector.
inline Vector3 componentSqrt(Vector3 v)
{
    return Vector3(
        sqrt(v[0]),
        sqrt(v[1]),
        sqrt(v[2]));
}

/// Calculates the component wise maximum for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector3 componentWiseMax(Vector3 v1, Vector3 v2)
{
    return Vector3(
        max(v1[0], v2[0]),
        max(v1[1], v2[1]),
        max(v1[2], v2[2]));
}

/// Calculates the component wise minimum for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector3 componentWiseMin(Vector3 v1, Vector3 v2)
{
    return Vector3(
        min(v1[0], v2[0]),
        min(v1[1], v2[1]),
        min(v1[2], v2[2]));
}

/// Does component wise multiply for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector3 componentWiseMultiply(Vector3 v1, Vector3 v2)
{
    return Vector3(
        v1[0] * v2[0],
        v1[1] * v2[1],
        v1[2] * v2[2]);
}

/// Does component wise divide for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector3 componentWiseDivide(Vector3 v1, Vector3 v2)
{
    return Vector3(
        v1[0] / v2[0],
        v1[1] / v2[1],
        v1[2] / v2[2]);
}

/// Does component wise remainder for all vector elements and returns the resulting vector.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The result vector.
inline Vector3 componentWiseRemainder(Vector3 v1, Vector3 v2)
{
    return Vector3(
        fmod(v1[0], v2[0]),
        fmod(v1[1], v2[1]),
        fmod(v1[2], v2[2]));
}

/// Adds a value to all elements of a vector and returns the result.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector3 componentAdd(Vector3 v, float scalar)
{
    return Vector3(
        v[0] + scalar,
        v[1] + scalar,
        v[2] + scalar);
}

/// Subtracts a value from all elements of a vector and returns the result.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector3 componentSubtract(Vector3 v, float scalar)
{
    return Vector3(
        v[0] - scalar,
        v[1] - scalar,
        v[2] - scalar);
}

/// Returns true if each component of the first vector is less than the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is less than the corresponding component of the second vector, false otherwise.
inline bool componentAllLessThan(Vector3 a, Vector3 b)
{
    return (a[0] < b[0] && a[1] < b[1] && a[2] < b[2]);
}

/// Returns true if each component of the first vector is less than or equal to the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is less than or equal to the corresponding component of the second vector, false otherwise.
inline bool componentAllLessThanOrEqual(Vector3 a, Vector3 b)
{
    return (a[0] <= b[0] && a[1] <= b[1] && a[2] <= b[2]);
}

/// Returns true if each component of the first vector is greater than the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is greater than the corresponding component of the second vector, false otherwise.
inline bool componentAllGreaterThan(Vector3 a, Vector3 b)
{
    return (a[0] > b[0] && a[1] > b[1] && a[2] > b[2]);
}

/// Returns true if each component of the first vector is greater than or equal to the corresponding component of the second vector.
/// \param a First vector.
/// \param b Second vector.
/// \return True if each component of the first vector is greater than or equal to the corresponding component of the second vector, false otherwise.
inline bool componentAllGreaterThanOrEqual(Vector3 a, Vector3 b)
{
    return (a[0] >= b[0] && a[1] >= b[1] && a[2] >= b[2]);
}

/// Adds two vectors and returns the sum.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return The result vector.
inline Vector3 operator+(Vector3 v1, Vector3 v2)
{
    return Vector3(v1) += v2;
}

/// Subtracts two vectors and returns the difference.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return The result vector.
inline Vector3 operator-(Vector3 v1, Vector3 v2)
{
    return Vector3(v1) -= v2;
}

/// Multiplies all vector elements with a scalar and returns the resulting vector.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector3 operator*(Vector3 v, float scalar)
{
    return Vector3(v) *= scalar;
}

/// Multiplies all vector elements with a scalar and returns the resulting vector.
/// \param scalar A scalar.
/// \param v A vector.
/// \return The result vector.
inline Vector3 operator*(float scalar, Vector3 v)
{
    return Vector3(v) *= scalar;
}

/// Divides all vector elements with a scalar and returns the resulting vector.
/// \param v A vector.
/// \param scalar A scalar.
/// \return The result vector.
inline Vector3 operator/(Vector3 v, float scalar)
{
    return Vector3(v) /= scalar;
}

/// Negates all vector elements and returns the resulting vector.
/// \param v A vector.
/// \return The result vector.
inline Vector3 operator-(Vector3 v)
{
    return v * -1.0f;
}

/// Unary plus, doesn't do anything and returns the resulting vector.
/// \param v A vector.
/// \return The result vector.
inline Vector3 operator+(Vector3 v)
{
    return v;
}

// TODO: remove all equality operators
/// Compares two vectors for equality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return True if vectors are equal.
inline bool operator==(Vector3 v1, Vector3 v2)
{
    return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2];
}

/// Compares two vectors for inequality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side vector.
/// \param v2 Right hand side vector.
/// \return True if vectors are different.
inline bool operator!=(Vector3 v1, Vector3 v2)
{
    return !(v1 == v2);
}

/// Calculates the dot product of two vectors.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The dot product of the vectors.
inline float dotProduct(Vector3 v1, Vector3 v2)
{
    Vector3 v = componentWiseMultiply(v1, v2);
    return v[0] + v[1] + v[2];
}

/// Calculates the cross product of two vectors.
/// \param v1 The first vector.
/// \param v2 The second vector.
/// \return The cross product of the vectors.
inline Vector3 crossProduct(Vector3 v1, Vector3 v2)
{
    return Vector3(
        v1[1] * v2[2] - v1[2] * v2[1],
        v1[2] * v2[0] - v1[0] * v2[2],
        v1[0] * v2[1] - v1[1] * v2[0]);
}

inline float Vector3::squaredLength() const
{
    return dotProduct(*this, *this);
}

inline Vector3 Vector3::normalized() const
{
    float vectorLength = length();

    return vectorLength == 0.0f ? nan() : *this / vectorLength;
}

inline Vector3 Vector3::lowestValue()
{
    return -highestValue();
}

inline Vector3 Vector3::highestValue()
{
    return Vector3(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
}

inline Vector3 Vector3::nan()
{
    return Vector3(numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN());
}

inline Vector3 Vector3::positiveInfinity()
{
    return Vector3(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
}

inline Vector3 Vector3::negativeInfinity()
{
    return Vector3(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());
}

inline Vector3 Vector3::right()
{
    return Vector3(1.0f, 0.0f, 0.0f);
}

inline Vector3 Vector3::up()
{
    return Vector3(0.0f, 1.0f, 0.0f);
}

inline Vector3 Vector3::backward()
{
    return Vector3(0.0f, 0.0f, 1.0f);
}

inline Vector3 Vector3::left()
{
    return Vector3(-1.0f, 0.0f, 0.0f);
}

inline Vector3 Vector3::down()
{
    return Vector3(0.0f, -1.0f, 0.0f);
}

inline Vector3 Vector3::forward()
{
    return Vector3(0.0f, 0.0f, -1.0f);
}


}


#endif
