// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BOX_HPP
#define KZ_BOX_HPP


#include <kanzi/core/math/vector3.hpp>


namespace kanzi
{

/// Class for box volume.
class KANZI_API Box
{
public:
    /// Constructs an empty box.
    /// \note The box will contain (0, 0, 0).
    explicit Box()
    {
    }

    /// Creates a box from two points. The box will contain the given two points.
    /// \param point1 First point.
    /// \param point2 Second point.
    /// \return Box which contains both of the given points.
    static Box fromContainedPoints(Vector3 point1, Vector3 point2);

    /// Creates a box from a point and box size.
    /// \param point Minimum corner point for the box.
    /// \param size Size for the box.
    /// \return Box which has a specified minimumCorner and size.
    static Box fromCornerAndSize(Vector3 minimumCorner, Vector3 size);

    /// Creates a box from center and size.
    /// \param center Center for the box.
    /// \param size Size for the box.
    /// \return Box which has specified center and size.
    static Box fromCenterAndSize(Vector3 center, Vector3 size);

    /// Creates a box from minimum and maximum corners.
    /// \param minimumCorner Minimum corner for the box.
    /// \param maximumCorner Maximum corner for the box.
    /// \return Box which has specified minimum and maximum corners.
    static Box fromCorners(Vector3 minimumCorner, Vector3 maximumCorner);

    /// Constructs a box which contains a single point.
    /// \param point Point for box to contain.
    explicit Box(Vector3 point) :
        m_minimumCorner(point),
        m_maximumCorner(point)
    {
        kzAssert(isValid());
    }

    /// Returns a box extended to include a given point.
    /// \param point Point to be included in the box.
    /// \return Box extended with given point.
    Box extendedBy(Vector3 point) const
    {
        return Box(componentWiseMin(m_minimumCorner, point),
                   componentWiseMax(m_maximumCorner, point));
    }

    /// Gets minimum corner of box.
    /// \return Minimum corner of the box.
    Vector3 getMinimumCorner() const
    {
        return m_minimumCorner;
    }

    /// Gets maximum corner of box.
    /// \return Maximum corner of the box.
    Vector3 getMaximumCorner() const
    {
        return m_maximumCorner;
    }

    /// Gets center of the box.
    /// \return Center of the box.
    Vector3 getCenter() const
    {
        return m_minimumCorner + 0.5f * getSize();
    }
   
    /// Gets size of box.
    /// \return Size of the box.
    Vector3 getSize() const
    {
        return m_maximumCorner - m_minimumCorner;
    }

    /// Indicates whether the box is empty.
    /// \return true if box is empty, false if box is not empty.
    bool isEmpty() const
    {
        return getMinimumCorner() == getMaximumCorner();
    }

    /// Indicates whether the box is valid.
    /// Box is valid when minimum corner is componentwise less or equal to maximum corner.
    /// \return true if minimum corner is componentwise less or equal to maximum corner, otherwise false.
    bool isValid() const
    {
        Vector3 minimum = getMinimumCorner();
        Vector3 maximum = getMaximumCorner();
        return (minimum.getX() <= maximum.getX()) &&
               (minimum.getY() <= maximum.getY()) &&
               (minimum.getZ() <= maximum.getZ());
    }

    /// Checks if the given point is inside the box.
    /// \note The box is considered closed from minimum corner (left/right) but open from maximum corner (right/bottom).
    /// \param point Point to check to be in the box.
    /// \return true if given point was in the box, otherwise false.
    bool contains(Vector3 point) const
    {
        Vector3 minimum = getMinimumCorner();
        Vector3 maximum = getMaximumCorner();
        return (point.getX() >= minimum.getX()) &&
               (point.getY() >= minimum.getY()) &&
               (point.getZ() >= minimum.getZ()) &&
               (point.getX() < maximum.getX()) &&
               (point.getY() < maximum.getY()) &&
               (point.getZ() < maximum.getZ());
    }

    /// Checks if box contains other box completely.
    /// \param volume2 Other box to test
    /// \return true if volume2 is completely inside this box.
    bool contains(const Box& volume2) const
    {
        Vector3 minimum1 = getMinimumCorner();
        Vector3 maximum1 = getMaximumCorner();
        Vector3 minimum2 = volume2.getMinimumCorner();
        Vector3 maximum2 = volume2.getMaximumCorner();
        return (minimum2.getX() >= minimum1.getX()) &&
               (minimum2.getY() >= minimum1.getY()) &&
               (minimum2.getZ() >= minimum1.getZ()) &&
               (maximum2.getX() <= maximum1.getX()) &&
               (maximum2.getY() <= maximum1.getY()) &&
               (maximum2.getZ() <= maximum1.getZ());
    }

    /// Checks if intersection of two given boxes is non-empty.
    /// \param box1 First box.
    /// \param box2 Second box.
    /// \return true if intersection of two given boxes is non-empty, otherwise false.
    friend bool intersects(const Box& box1, const Box& box2)
    {
        Vector3 minimum1 = box1.getMinimumCorner();
        Vector3 maximum1 = box1.getMaximumCorner();
        Vector3 minimum2 = box2.getMinimumCorner();
        Vector3 maximum2 = box2.getMaximumCorner();
        return (minimum1.getX() < maximum2.getX()) &&
               (minimum1.getY() < maximum2.getY()) &&
               (minimum1.getZ() < maximum2.getZ()) &&
               (minimum2.getX() < maximum1.getX()) &&
               (minimum2.getY() < maximum1.getY()) &&
               (minimum2.getZ() < maximum1.getZ());
    }

    /// Checks if two given box volumes have equal corners.
    /// \param box1 First box volume.
    /// \param box2 Second box volume.
    /// \return true if given boxes have equal corners.
    friend bool operator==(const Box& box1, const Box& box2)
    {
        return (box1.getMinimumCorner() == box2.getMinimumCorner()) &&
               (box1.getMaximumCorner() == box2.getMaximumCorner());
    }

    /// Checks if two given boxes do not have equal corners.
    /// \param box1 First box.
    /// \param box2 Second box.
    /// \return true if given boxes do not have equal corners.
    friend bool operator!=(const Box& box1, const Box& box2)
    {
        return !(box1 == box2);
    }

    /// Calculates a minimum bounding box for given two boxes.
    /// \param box1 First box.
    /// \param box2 Second box.
    /// \return Minimum bounding box for given two boxes.
    friend Box minimumBoundingBox(const Box& box1, const Box& box2)
    {
         return Box(componentWiseMin(box1.getMinimumCorner(), box2.getMinimumCorner()),
                    componentWiseMax(box1.getMaximumCorner(), box2.getMaximumCorner()));
    }

    /// Calculates intersection of two boxes.
    /// \param box1 First box.
    /// \param box2 Second box.
    /// \return Intersection of two given boxes.
    friend Box intersection(const Box& box1, const Box& box2)
    {
         return Box(componentWiseMax(box1.getMinimumCorner(), box2.getMinimumCorner()),
                    componentWiseMin(box1.getMaximumCorner(), box2.getMaximumCorner()));
    }

    /// Calculates the volume of the box.
    /// \return Volume of the box.
    float getVolume() const
    {
        Vector3 size = getSize();
        return size.getX() * size.getY() * size.getZ();
    }

    /// Translates a box.
    /// \param translation Translation amount.
    Box translatedBy(Vector3 translation) const
    {
        return Box(m_minimumCorner + translation, m_maximumCorner + translation);
    }

private:
    /// Constructs a box from minimum and maximum corner points.
    /// \note Caller should ensure that minimumCorner components are less or equal to components of maximum corner.
    /// \param minimumCorner Minimum corner point for the box.
    /// \param maximumCorner Maximum corner point for the box.
    explicit Box(Vector3 minimumCorner, Vector3 maximumCorner) :
        m_minimumCorner(minimumCorner),
        m_maximumCorner(maximumCorner)
    {
        kzAssert(isValid());
    }

    /// Minimum corner of the box.
    Vector3 m_minimumCorner;

    /// Maximum corner of the box.
    Vector3 m_maximumCorner;
};

}

#endif
