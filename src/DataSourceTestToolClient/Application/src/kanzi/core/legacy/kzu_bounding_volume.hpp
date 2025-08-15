/**
* \file
* Bounding volume structure, that is, volume that bounds some area, typically geometry.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_BOUNDING_VOLUME_H
#define KZU_BOUNDING_VOLUME_H


#include <kanzi/core/legacy/util/math/kzc_matrix4x4.hpp>
#include <kanzi/core/legacy/util/math/kzc_plane.hpp>
#include <kanzi/core/legacy/util/math/kzc_vector3.hpp>

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

class Box;
}

/** Type of bounding volume. */
enum KzuBoundingVolumeType
{
    KZU_BOUNDING_VOLUME_TYPE_AXIS_ALIGNED_BOX, /**< Axis aligned bounding box. */
    KZU_BOUNDING_VOLUME_TYPE_SPHERE            /**< Sphere bounding volume. */
};


/* Forward declaration structures. */
struct KzcMemoryManager;
struct KzcPlane;
struct KzcVertexList;
struct KzcMatrix4x4;
struct KzcVector3;


/** Bounding box corners. */
#define KZU_BOUNDING_BOX_CORNER_BACK_BOTTOM_LEFT 0   /**< Bottom left. */
#define KZU_BOUNDING_BOX_CORNER_BACK_TOP_LEFT 1      /**< Top left. */
#define KZU_BOUNDING_BOX_CORNER_BACK_TOP_RIGHT 2     /**< Top right. */
#define KZU_BOUNDING_BOX_CORNER_BACK_BOTTOM_RIGHT 3  /**< Bottom right. */
#define KZU_BOUNDING_BOX_CORNER_FRONT_BOTTOM_LEFT 4  /**< Bottom left. */
#define KZU_BOUNDING_BOX_CORNER_FRONT_TOP_LEFT 5     /**< Top left. */
#define KZU_BOUNDING_BOX_CORNER_FRONT_TOP_RIGHT 6    /**< Top right. */
#define KZU_BOUNDING_BOX_CORNER_FRONT_BOTTOM_RIGHT 7 /**< Bottom right. */

#if defined _MSC_VER
#pragma warning(push)

// warning C26495: Variable 'KzuBoundingVolumeAxisAlignedBox::cornerPoints' is uninitialized. Always initialize a member variable (type.6).
#pragma warning(disable : 26495)
#endif

/**
* \struct KzuBoundingVolumeAxisAlignedBox
* Axis aligned bounding box, inherited from KzuBoundingVolume.
*/
struct KzuBoundingVolumeAxisAlignedBox
{
    explicit KzuBoundingVolumeAxisAlignedBox() :
        minimumCorner(kzcVector3(0.0f, 0.0f, 0.0f)),
        maximumCorner(kzcVector3(0.0f, 0.0f, 0.0f)),
        cornerPoints()
    {
        cornerPoints[0] = kzcVector3(0.0f, 0.0f, 0.0f);
        cornerPoints[1] = kzcVector3(0.0f, 0.0f, 0.0f);
        cornerPoints[2] = kzcVector3(0.0f, 0.0f, 0.0f);
        cornerPoints[3] = kzcVector3(0.0f, 0.0f, 0.0f);
        cornerPoints[4] = kzcVector3(0.0f, 0.0f, 0.0f);
        cornerPoints[5] = kzcVector3(0.0f, 0.0f, 0.0f);
        cornerPoints[6] = kzcVector3(0.0f, 0.0f, 0.0f);
        cornerPoints[7] = kzcVector3(0.0f, 0.0f, 0.0f);
    }

    struct KzcVector3 minimumCorner;   /**< Minimum corner vector in local coordinates. */
    struct KzcVector3 maximumCorner;   /**< Maximum corner vector in local coordinates. */
    struct KzcVector3 cornerPoints[8]; /**< Corner points. */
};

#if defined _MSC_VER
#pragma warning(pop)
#endif

/**
* \struct KzuBoundingVolumeSphere
* Sphere volume, inherited from KzuBoundingVolume.
*/
struct KzuBoundingVolumeSphere
{
    explicit KzuBoundingVolumeSphere() :
        center(kzcVector3(0.0f, 0.0f, 0.0f)),
        radius(0.0f)
    {
    }

    struct KzcVector3 center; /**< Local center location. */
    kzFloat radius;           /**< Sphere radius. */
};

/**
* \struct KzuBoundingVolume
* Base structure for bounding volume.
*/
struct KzuBoundingVolume
{
    explicit KzuBoundingVolume()
    {
    }

    struct KzuBoundingVolumeAxisAlignedBox aabb; /**< Axis-aligned bounding box. */
    struct KzuBoundingVolumeSphere sphere;       /**< Bounding sphere. */
};

typedef kanzi::shared_ptr<KzuBoundingVolume> KzuBoundingVolumeSharedPtr;

/**
* \struct KzuTransformedBoundingVolume
* Bounding volume in world coordinates.
*/
struct KzuTransformedBoundingVolume
{
    struct KzcVector3 cornerPoints[8];   /**< Transformed corner points in world coordinates. */
    struct KzcVector3 transformedCenter; /**< Transformed center position in world coordinates. */
    kzFloat margin;                      /**< Margin. */
};


void kzuBoundingVolumeAssign(KzuBoundingVolume* first, const KzuBoundingVolume* second);

/** Creates an empty bounding volume. */
KANZI_API kzsError kzuBoundingVolumeCreate(const struct KzcMemoryManager* memoryManager, struct KzuBoundingVolume** out_boundingVolume);
/** Creates copy of bounding volume. */
kzsError kzuBoundingVolumeCopy(const struct KzcMemoryManager* memoryManager, const struct KzuBoundingVolume* sourceBoundingVolume, struct KzuBoundingVolume** out_targetBoundingVolume);
/** Deletes a bounding volume. */
KANZI_API kzsError kzuBoundingVolumeDelete(struct KzuBoundingVolume* boundingVolume);


/** Calculates world transformed bounding volume from bounding volume and world transformation. */
KANZI_API void kzuBoundingVolumeCalculateTransformedBoundingVolume(const struct KzuBoundingVolume* boundingVolume, const struct KzcMatrix4x4* worldTransformation,
                                                                   struct KzuTransformedBoundingVolume* out_transformedBoundingVolume);
/** Transforms an AABB and calculates a new AABB. */
void kzuAxisAlignedBoundingBoxFromTransformedAABB(const struct KzcVector3* aabbMin, const struct KzcVector3* aabbMax, const struct KzcMatrix4x4* transform,
                                                  struct KzcVector3* out_aabbMin, struct KzcVector3* out_aabbMax);
/** Creates a transformed bounding volume from an axis aligned bounding box. */
void kzuTransformedBoundingVolumeCreateFromAABB(const struct KzcVector3* aabbMin, const struct KzcVector3* aabbMax, const struct KzcMatrix4x4* worldTransformation,
                                                struct KzuTransformedBoundingVolume* out_transformedBoundingVolume);
/** Gets axis-aligned bounding box values (minimum & maximum) from transformed bounding volume. */
void kzuTransformedBoundingVolumeGetAABB(const struct KzuTransformedBoundingVolume* transformedBoundingVolume, struct KzcVector3* out_minimum,
                                         struct KzcVector3* out_maximum);
/** Checks if transformed bounding volume is above plane. Used in frustum culling. */
kzBool kzuTransformedBoundingVolumeIsAbovePlane(const struct KzuTransformedBoundingVolume* transformedBoundingVolume, const struct KzcPlane* plane);
/** Gets corner point from transformed bounding box. */
KANZI_API struct KzcVector3 kzuTransformedBoundingVolumeBoxGetCornerPoint(const struct KzuTransformedBoundingVolume* boundingVolume, kzUint cornerIndex);
/** Sets margin to transformed bounding volume. */
void kzuTransformedBoundingVolumeSetMargin(struct KzuTransformedBoundingVolume* transformedBoundingVolume, kzFloat margin);
/** Gets margin from transformed bounding volume. */
kzFloat kzuTransformedBoundingVolumeGetMargin(const struct KzuTransformedBoundingVolume* transformedBoundingVolume);


/** Sets bounding volume from volume. */
KANZI_API void kzuBoundingVolumeSetVolume(struct KzuBoundingVolume* boundingVolume, const kanzi::Box& volume);


/** Gets axis aligned box from bounding volume. */
KANZI_API const struct KzuBoundingVolumeAxisAlignedBox* kzuBoundingVolumeGetAxisAlignedBox(const struct KzuBoundingVolume* boundingVolume);

/** Gets sphere from bounding volume. */
const struct KzuBoundingVolumeSphere* kzuBoundingVolumeGetSphere(const struct KzuBoundingVolume* boundingVolume);


/** Gets minimum corner from axis aligned box. */
KANZI_API struct KzcVector3 kzuBoundingVolumeAxisAlignedBoxGetMinimumCorner(const struct KzuBoundingVolumeAxisAlignedBox* boundingVolume);
/** Gets maximum corner from axis aligned box. */
KANZI_API struct KzcVector3 kzuBoundingVolumeAxisAlignedBoxGetMaximumCorner(const struct KzuBoundingVolumeAxisAlignedBox* boundingVolume);


/** Gets radius of bounding volume sphere. */
kzFloat kzuBoundingVolumeSphereGetRadius(const struct KzuBoundingVolumeSphere* boundingVolume);


#endif
