// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_COLOR_RGBA_HPP
#define KANZI_COLOR_RGBA_HPP

#include <kanzi/core/cpp/math.hpp>

#include <kanzi/core/legacy/wrappers/kzs_math.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

#include <kanzi/core/cpp/algorithm.hpp>
#include <kanzi/core/cpp/limits.hpp>

namespace kanzi
{

// TODO: move KANZI_API to non inline functions
/// Color with 4 floating point components: red, green, blue and alpha (r, g, b, a).
class KANZI_API ColorRGBA
{
public:

    /// Default constructor, initializes the color to (0.0, 0.0, 0.0, 0.0).
    explicit ColorRGBA():
        data()
    {
        data[0] = 0.0f;
        data[1] = 0.0f;
        data[2] = 0.0f;
        data[3] = 0.0f;
    }

    /// Constructor, initializes the color to (r, g, b, 1.0).
    /// \param r Red component of the color.
    /// \param g Green component of the color.
    /// \param b Blue component of the color.
    explicit ColorRGBA(float r, float g, float b):
        data()
    {
        data[0] = r;
        data[1] = g;
        data[2] = b;
        data[3] = 1.0;
    }

    /// Constructor, initializes the color to (r, g, b, a).
    /// \param r Red component of the color.
    /// \param g Green component of the color.
    /// \param b Blue component of the color.
    /// \param a Alpha component of the color.
    explicit ColorRGBA(float r, float g, float b, float a):
        data()
    {
        data[0] = r;
        data[1] = g;
        data[2] = b;
        data[3] = a;
    }

    /// Access to individual elements of the color.
    /// \param index Index of the accessed element. Should be either 0, 1, 2, or 3.
    /// \return If index is 0, r element. If index is 1, g element. If index is 2, b element. If index is 3, a element.
    const float& operator[] (size_t index) const
    {
        kzAssert(index < 4);

        return data[index];
    }

    /// Access to individual elements of the color.
    /// \param index Index of the accessed element. Should be either 0, 1, 2, or 3.
    /// \return If index is 0, r element. If index is 1, g element. If index is 2, b element. If index is 3, a element.
    float& operator[] (size_t index)
    {
        kzAssert(index < 4);

        return data[index];
    }

    /// Multiplies each color element with a scalar.
    /// \param scalar Multiplier for each color element.
    /// \return This color.
    ColorRGBA& operator*=(float scalar)
    {
        data[0] *= scalar;
        data[1] *= scalar;
        data[2] *= scalar;
        data[3] *= scalar;
        return *this;
    }

    /// Divides each color element with a scalar.
    /// \param scalar Divider for each color element.
    /// \return This color.
    ColorRGBA& operator/=(float scalar)
    {
        data[0] /= scalar;
        data[1] /= scalar;
        data[2] /= scalar;
        data[3] /= scalar;
        return *this;
    }

    /// Modifies this color by adding another color.
    /// \param v Another color.
    /// \return This color.
    ColorRGBA& operator+=(const ColorRGBA& v)
    {
        data[0] += v.data[0];
        data[1] += v.data[1];
        data[2] += v.data[2];
        data[3] += v.data[3];
        return *this;
    }

    /// Modifies this color by subtracting another color from this color.
    /// \param v Another color.
    /// \return This color.
    ColorRGBA& operator-=(const ColorRGBA& v)
    {
        data[0] -= v.data[0];
        data[1] -= v.data[1];
        data[2] -= v.data[2];
        data[3] -= v.data[3];
        return *this;
    }

    /// Returns the red element of the color
    /// \return The red element.
    float getRed() const
    {
        return data[0];
    }

    /// Returns the green element of the color
    /// \return The green element.
    float getGreen() const
    {
        return data[1];
    }

    /// Returns the blue element of the color
    /// \return The blue element.
    float getBlue() const
    {
        return data[2];
    }

    /// Returns the alpha element of the color
    /// \return The alpha element.
    float getAlpha() const
    {
        return data[3];
    }

    /// Sets the red element of the color.
    /// \param value The new value of the red element.
    void setRed(float value)
    {
        data[0] = value;
    }

    /// Sets the green element of the color.
    /// \param value The new value of the green element.
    void setGreen(float value)
    {
        data[1] = value;
    }

    /// Sets the blue element of the color.
    /// \param value The new value of the blue element.
    void setBlue(float value)
    {
        data[2] = value;
    }

    /// Sets the alpha element of the color.
    /// \param value The new value of the alpha element.
    void setAlpha(float value)
    {
        data[3] = value;
    }

    /// Returns the color with each element having the most negative float value.
    /// \return Color with the lowest possible value.
    static inline ColorRGBA lowestValue();

    /// Returns the color with each element having the most positive float value.
    /// \return Color with the highest possible value.
    static inline ColorRGBA highestValue();

    /// Returns the color with each element being NaN.
    /// \return Color with NaN elements.
    static inline ColorRGBA nan();

    // TODO: rename to hasNaN
    /// Returns true if and only if at least one of the color values is NaN.
    inline bool isNaN() const
    {
        return isnan(data[0]) || isnan(data[1]) || isnan(data[2]) || isnan(data[3]);
    }

    /// Returns the color with each element being the positive infinity.
    /// \return Color with positive infinity elements.
    static inline ColorRGBA positiveInfinity();

    /// Returns the color with each element being the negative infinity.
    /// \return Color with negative infinity elements.
    static inline ColorRGBA negativeInfinity();

    /// Returns opaque black color (0.0, 0.0, 0.0, 1.0).
    /// \return Opaque black.
    static inline ColorRGBA opaqueBlack();

    /// Returns transparent black color (0.0, 0.0, 0.0, 0.0).
    /// \return Transparent black color.
    static inline ColorRGBA transparentBlack();

private:

    /// Color elements.
    float data[4];
};


/// Calculates component wise absolute value for all elements and returns resulting color.
/// \param v Color input.
/// \return The result color.
inline ColorRGBA componentAbs(ColorRGBA v)
{
    return ColorRGBA(
        abs(v[0]),
        abs(v[1]),
        abs(v[2]),
        abs(v[3]));
}

/// Calculates component wise ceil value for all elements and returns resulting color.
/// \param v Color input.
/// \return The result color.
inline ColorRGBA componentCeil(ColorRGBA v)
{
    return ColorRGBA(
        ceil(v[0]),
        ceil(v[1]),
        ceil(v[2]),
        ceil(v[3]));
}

/// Calculates component wise floor value for all elements and returns resulting color.
/// \param v Color input.
/// \return The result color.
inline ColorRGBA componentFloor(ColorRGBA v)
{
    return ColorRGBA(
        floor(v[0]),
        floor(v[1]),
        floor(v[2]),
        floor(v[3]));
}

/// Calculates component wise rounded value for all elements and returns resulting color.
/// \param v Color input.
/// \return The result color.
inline ColorRGBA componentRound(ColorRGBA v)
{
    return ColorRGBA(
        round(v[0]),
        round(v[1]),
        round(v[2]),
        round(v[3]));
}

/// Calculates component wise square root all elements and returns resulting color.
/// \param v Color input.
/// \return The result color.
inline ColorRGBA componentSqrt(ColorRGBA v)
{
    return ColorRGBA(
        sqrt(v[0]),
        sqrt(v[1]),
        sqrt(v[2]),
        sqrt(v[3]));
}

/// Calculates component wise maximum for all color elements and returns the resulting color.
/// \param v1 The first color.
/// \param v2 The second color.
/// \return The result color.
inline ColorRGBA componentWiseMax(ColorRGBA v1, ColorRGBA v2)
{
    return ColorRGBA(
        max(v1[0], v2[0]),
        max(v1[1], v2[1]),
        max(v1[2], v2[2]),
        max(v1[3], v2[3]));
}

/// Calculates component wise minimum for all color elements and returns resulting color.
/// \param v1 The first color.
/// \param v2 The second color.
/// \return The result color.
inline ColorRGBA componentWiseMin(ColorRGBA v1, ColorRGBA v2)
{
    return ColorRGBA(
        min(v1[0], v2[0]),
        min(v1[1], v2[1]),
        min(v1[2], v2[2]),
        min(v1[3], v2[3]));
}

/// Does component wise multiply for all color elements and returns resulting color.
/// \param v1 The first color.
/// \param v2 The second color.
/// \return The result color.
inline ColorRGBA componentWiseMultiply(ColorRGBA v1, ColorRGBA v2)
{
    return ColorRGBA(
        v1[0] * v2[0],
        v1[1] * v2[1],
        v1[2] * v2[2],
        v1[3] * v2[3]);
}

/// Does component wise divide for all color elements and returns the resulting color.
/// \param v1 The first color.
/// \param v2 The second color.
/// \return The result color.
inline ColorRGBA componentWiseDivide(ColorRGBA v1, ColorRGBA v2)
{
    return ColorRGBA(
        v1[0] / v2[0],
        v1[1] / v2[1],
        v1[2] / v2[2],
        v1[3] / v2[3]);
}

/// Does component wise remainder for all color elements and returns the resulting color.
/// \param v1 The first color.
/// \param v2 The second color.
/// \return The result color.
inline ColorRGBA componentWiseRemainder(ColorRGBA v1, ColorRGBA v2)
{
    return ColorRGBA(
        fmod(v1[0], v2[0]),
        fmod(v1[1], v2[1]),
        fmod(v1[2], v2[2]),
        fmod(v1[3], v2[3]));
}

/// Adds a value to all color elements and returns the resulting color.
/// \param v Color.
/// \param scalar Value
/// \return Result color.
inline ColorRGBA componentAdd(ColorRGBA v, float scalar)
{
    return ColorRGBA(
        v[0] + scalar,
        v[1] + scalar,
        v[2] + scalar,
        v[3] + scalar);
}

/// Subtracts a value from all color elements and returns the resulting color.
/// \param v Color.
/// \param scalar Value
/// \return Result color.
inline ColorRGBA componentSubtract(ColorRGBA v, float scalar)
{
    return ColorRGBA(
        v[0] - scalar,
        v[1] - scalar,
        v[2] - scalar,
        v[3] - scalar);
}

/// Adds two colors and returns the sum.
/// \param v1 Left hand side color.
/// \param v2 Right hand side color.
/// \return The result color.
inline ColorRGBA operator+(ColorRGBA v1, ColorRGBA v2)
{
    return ColorRGBA(v1) += v2;
}

/// Subtracts two colors and returns the difference.
/// \param v1 Left hand side color.
/// \param v2 Right hand side color.
/// \return The result color.
inline ColorRGBA operator-(ColorRGBA v1, ColorRGBA v2)
{
    return ColorRGBA(v1) -= v2;
}

/// Multiplies all color elements with a scalar and returns the resulting color.
/// \param v A color.
/// \param scalar A scalar.
/// \return The result color.
inline ColorRGBA operator*(ColorRGBA v, float scalar)
{
    return ColorRGBA(v) *= scalar;
}

/// Multiplies all color elements with a scalar and returns the resulting color.
/// \param scalar A scalar.
/// \param v A color.
/// \return The result color.
inline ColorRGBA operator*(float scalar, ColorRGBA v)
{
    return ColorRGBA(v) *= scalar;
}

/// Divides all color elements with a scalar and returns the resulting color.
/// \param v A color.
/// \param scalar A scalar.
/// \return The result color.
inline ColorRGBA operator/(ColorRGBA v, float scalar)
{
    return ColorRGBA(v) /= scalar;
}

/// Negates all color elements and returns the resulting color.
/// \param v A color.
/// \return The result color.
inline ColorRGBA operator-(ColorRGBA v)
{
    return v * -1.0f;
}

/// Unary plus, doesn't do anything and returns the resulting color.
/// \param v A color.
/// \return The result color.
inline ColorRGBA operator+(ColorRGBA v)
{
    return v;
}

// TODO: remove all equality operators
/// Compares two colors for equality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side color.
/// \param v2 Right hand side color.
/// \return True if colors are equal.
inline bool operator==(ColorRGBA v1, ColorRGBA v2)
{
    return v1[0] == v2[0] && v1[1] == v2[1] && v1[2] == v2[2] && v1[3] == v2[3];
}

/// Compares two colors for inequality. Note that this is a floating point comparison
/// without any tolerance, so you probably don't want to use this.
/// \param v1 Left hand side color.
/// \param v2 Right hand side color.
/// \return True if colors are different.
inline bool operator!=(ColorRGBA v1, ColorRGBA v2)
{
    return !(v1 == v2);
}

/// Calculates the dot product of two colors.
/// \param v1 The first color.
/// \param v2 The second color.
/// \return The dot product of the colors.
inline float dotProduct(ColorRGBA v1, ColorRGBA v2)
{
    ColorRGBA v = componentWiseMultiply(v1, v2);
    return v[0] + v[1] + v[2] + v[3];
}

inline ColorRGBA ColorRGBA::lowestValue()
{
    return -highestValue();
}

inline ColorRGBA ColorRGBA::highestValue()
{
    return ColorRGBA(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max());
}

inline ColorRGBA ColorRGBA::nan()
{
    return ColorRGBA(numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN(), numeric_limits<float>::quiet_NaN());
}

inline ColorRGBA ColorRGBA::positiveInfinity()
{
    return ColorRGBA(numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity(), numeric_limits<float>::infinity());
}

inline ColorRGBA ColorRGBA::negativeInfinity()
{
    return ColorRGBA(-numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity(), -numeric_limits<float>::infinity());
}

inline ColorRGBA ColorRGBA::opaqueBlack()
{
   return ColorRGBA(0.0f, 0.0f, 0.0f, 1.0f);
}

inline ColorRGBA ColorRGBA::transparentBlack()
{
   return ColorRGBA(0.0f, 0.0f, 0.0f, 0.0f);
}

/// Conversion from sRGB to linear for default gamma 2.2.
/// \see https://en.wikipedia.org/wiki/SRGB
float sRGBToLinear(float cs);

/// Conversion from linear to sRGB for default gamma 2.2.
/// \see https://en.wikipedia.org/wiki/SRGB
float linearTosRGB(float cl);

/// Conversion to whole ColorRGBA from sRGB to linear.
/// \param cs Color in sRGB format.
/// \return Color in linear format.
inline ColorRGBA sRGBToLinear(ColorRGBA cs)
{
    return ColorRGBA(sRGBToLinear(cs.getRed()), sRGBToLinear(cs.getGreen()), sRGBToLinear(cs.getBlue()), cs.getAlpha());
}

/// Conversion to whole ColorRGBA from linear to sRGB.
/// \param cs Color in linear format.
/// \return Color in sRGB format.
inline ColorRGBA linearTosRGB(ColorRGBA cs)
{
    return ColorRGBA(linearTosRGB(cs.getRed()), linearTosRGB(cs.getGreen()), linearTosRGB(cs.getBlue()), cs.getAlpha());
}

KANZI_API extern const ColorRGBA ThemeRed;
KANZI_API extern const ColorRGBA ThemeGreen;
KANZI_API extern const ColorRGBA ThemeBlue;
KANZI_API extern const ColorRGBA ThemeYellow;
KANZI_API extern const ColorRGBA ThemeGray;
KANZI_API extern const ColorRGBA ThemeOrange;

}


#endif
