// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RECTANGLE_INT_HPP
#define KZ_RECTANGLE_INT_HPP

#include "vector4.hpp"

namespace kanzi
{

/// 2-dimensional integer rectangle.
/// The rectangle sizes remain non-negative for all operations as long as the input sizes are non-negative.
template<typename T>
class Rectangle
{
public:
    /// Empty constructor.
    explicit Rectangle() :
        m_x(),
        m_y(),
        m_width(),
        m_height()
    {
    }

    /// Constructor.
    explicit Rectangle(T x, T y, T width, T height) :
        m_x(x),
        m_y(y),
        m_width(width),
        m_height(height)
    {
    }

    /// Gets X offset.
    T getX() const
    {
        return m_x;
    }

    /// Gets Y offset.
    T getY() const
    {
        return m_y;
    }

    /// Gets width.
    T getWidth() const
    {
        return m_width;
    }

    /// Gets height.
    T getHeight() const
    {
        return m_height;
    }

    /// Sets X offset.
    /// \param x New offset.
    void setX(T x)
    {
        m_x = x;
    }

    /// Sets Y offset.
    /// \param y New offset.
    void setY(T y)
    {
        m_y = y;
    }

    /// Sets width.
    /// \param width New width.
    void setWidth(T width)
    {
        m_width = width;
    }

    /// Sets height.
    /// \param height New height.
    void setHeight(T height)
    {
        m_height = height;
    }

    /// Equals operator.
    /// \param rhs Right-hand-side operand of the comparison.
    friend bool operator==(const Rectangle<T>& lhs, const Rectangle<T>& rhs)
    {
        return ((lhs.getX() == rhs.getX()) &&
            (lhs.getY() == rhs.getY()) &&
            (lhs.getWidth() == rhs.getWidth()) &&
            (lhs.getHeight() == rhs.getHeight()));
    }

    /// Not equals operator.
    /// \param rhs Right-hand-side operand of the comparison.
    friend bool operator!=(const Rectangle<T>& lhs, const Rectangle<T>& rhs)
    {
        return !(lhs == rhs);
    }

private:
    /// X offset.
    T m_x;
    /// Y offset.
    T m_y;
    /// Width.
    T m_width;
    /// Height.
    T m_height;
};

template <typename T>
Rectangle<T> intersection(const Rectangle<T>& rectangle1, const Rectangle<T>& rectangle2)
{
    T x = max(rectangle1.getX(), rectangle2.getX());
    T y = max(rectangle1.getY(), rectangle2.getY());
    T width = max(min(rectangle1.getX() + rectangle1.getWidth(), rectangle2.getX() + rectangle2.getWidth()) - x, 0.0f);
    T height = max(min(rectangle1.getY() + rectangle1.getHeight(), rectangle2.getY() + rectangle2.getHeight()) - y, 0.0f);

    return Rectangle<T>(x, y, width, height);
}

}

#endif