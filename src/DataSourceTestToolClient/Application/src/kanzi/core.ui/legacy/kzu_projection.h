#ifdef KANZI_FEATURE_3D

/**
* \file
* Utility for calculating 2D pixel coordinate from 3D point and camera projection.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_PROJECTION_H
#define KZU_PROJECTION_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>





/* Forward declarations. */
struct KzcVector3;
struct KzcDynamicArray;

namespace kanzi
{
class Camera;
}


/** Projection vec3 in world coordinates to actual pixel coordinates. Result in X, Y pixel coordinates using mathematical coordinate
    system from bottom-left growing to top-right. */
kzsError kzuProjectionVector3ToPixelCoordinates(const KzcVector3& vectorInWorldCoordinates, kanzi::Camera& cameraNode,
                                                const KzcDynamicArray* transformedObjects,
                                                kzInt viewportX, kzInt viewportY, kzUint viewportWidth, kzUint viewportHeight,
                                                kzInt* out_x, kzInt* out_y);





#endif

#endif
