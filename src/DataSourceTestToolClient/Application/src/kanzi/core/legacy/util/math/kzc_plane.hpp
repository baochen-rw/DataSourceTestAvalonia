/**
* \file
* Plane structure and operations.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_PLANE_H
#define KZC_PLANE_H


#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations */
struct KzcVector3;
struct KzcRay;


/** Structure for a plane. Mathematically, a plane is defined as: a*x + b*y + c*z + d = 0. */
struct KzcPlane
{
    kzFloat a; /**< X component of normal. */
    kzFloat b; /**< Y component of normal. */
    kzFloat c; /**< Z component of normal. */
    kzFloat d; /**< Negative distance component. */
};


/** Creates a plane structure from a point (x,y,z) on the plane and negative distance from origin. */
KZ_INLINE struct KzcPlane kzcPlane(kzFloat x, kzFloat y, kzFloat z, kzFloat negativeDistance)
{
    struct KzcPlane plane;
    plane.a = x;
    plane.b = y;
    plane.c = z;
    plane.d = negativeDistance;

    return plane;
}

/** Constructs a plane from point and normal. The normal must be of unit length. */
KANZI_API void kzcPlaneCreateFromPointAndNormal(struct KzcPlane* plane, const struct KzcVector3* point, const struct KzcVector3* normal);

/** Gets point's distance to plane. */
KANZI_API kzFloat kzcPlaneDistanceToPoint(const struct KzcPlane* plane, const struct KzcVector3* point);

/**
* Gets ray and plane intersection point.
* The plane and the ray are tested for parallelness using the tolerance value.
* If the tolerance test does not pass, output values are filled with NaNs and KZ_FALSE is returned.
*/
KANZI_API kzBool kzcPlaneRayIntersection(const struct KzcPlane* plane, const struct KzcRay* ray, kzFloat parallelTolerance, kzFloat* out_distance, struct KzcVector3* out_intersectionPoint);

/** Project a direction vector onto a plane. */
KANZI_API void kzcPlaneProjectDirectionVector3(const struct KzcPlane* plane, const struct KzcVector3* vector, struct KzcVector3* out_vector);

/** Project a position vector onto the plane. */
KANZI_API void kzcPlaneProjectPositionVector3(const struct KzcPlane* plane, const struct KzcVector3* position, struct KzcVector3* out_position);


/** Outputs plane normal into out_normal. */
KANZI_API void kzcPlaneGetNormal(const struct KzcPlane* plane, struct KzcVector3* out_normal);


#endif
