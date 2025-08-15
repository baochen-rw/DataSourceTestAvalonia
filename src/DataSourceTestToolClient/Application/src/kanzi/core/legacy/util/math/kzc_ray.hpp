/**
* \file
* Ray utility.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_RAY_H
#define KZC_RAY_H

#include <kanzi/core/legacy/util/math/kzc_vector3.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations */
struct KzcMatrix4x4;


/// Structure for ray.
/// Ray is defined by starting point and direction.
struct KzcRay
{
    /// Empty constructor.
    explicit KzcRay() :
        origin(KZC_VECTOR3_ZERO),
        direction(KZC_VECTOR3_ZERO)
    {
    }

    /// Constructor.
    explicit KzcRay(struct KzcVector3 originParam, struct KzcVector3 directionParam) :
        origin(originParam),
        direction(directionParam)
    {
    }

    /// Origin of the ray.
    struct KzcVector3 origin;
    /// Direction of the ray, normalized.
    struct KzcVector3 direction;
};


/** Constructs a ray from point and direction vector. Normalizes the direction vector */
KZ_INLINE void kzcRaySet(const struct KzcVector3 origin, const struct KzcVector3 direction, struct KzcRay* out_ray)
{
    out_ray->origin = origin;
    out_ray->direction = direction;
    kzcVector3Normalize(&out_ray->direction);
}

/** Test intersection between ray and sphere and return distance. */
KANZI_API kzBool kzcRaySphereIntersection(const struct KzcRay* ray, const struct KzcVector3* spherePosition,
                                const kzFloat sphereRadius, kzFloat* out_distance);

/** Test intersection between ray and bounding box. */
KANZI_API kzBool kzcRayBoundingBoxIntersection(const struct KzcRay* ray, const struct KzcVector3* boundingBoxMinimum, 
                                     const struct KzcVector3* boundingBoxMaximum, 
                                     const struct KzcMatrix4x4* boxOrientation, kzFloat* out_distance,
                                     struct KzcVector3* out_hitPoint);

/** Test intersection between ray and bounding box back faces. */
KANZI_API kzBool kzcRayBoundingBoxBackfaceIntersection(const struct KzcRay* ray, const struct KzcVector3* boundingBoxMinimum, 
                                             const struct KzcVector3* boundingBoxMaximum, 
                                             const struct KzcMatrix4x4* boxOrientation, kzFloat* out_distance,
                                             struct KzcVector3* out_hitPoint);
/**
* Tests intersection between ray and cylinder aligned in the given unit-axis, ranging [-height/2, height/2].
* 
* The cylinder is first transformed with the given transformation matrix.
*/
KANZI_API kzBool kzcRayCylinderIntersection(const struct KzcRay* ray, kzFloat cylinderRadius, kzFloat cylinderHeight,
                                  const struct KzcVector3* cylinderAxis, const struct KzcMatrix4x4* cylinderTransform,
                                  kzFloat* out_distance);

/** Transform a ray by a 4x4 matrix. */
KANZI_API void kzcRayTransform(struct KzcRay* ray, const struct KzcMatrix4x4* transform);


#endif
