#ifdef KANZI_FEATURE_3D

/**
* \file
* Ray picking utility.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_RAYPICK_H
#define KZU_RAYPICK_H

#include <kanzi/core/cpp/memory.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>

/* Forward declarations */
struct KzcVector2;
struct KzcVector3;
struct KzuObjectSource;
struct KzcRay;
struct KzuTransformedObjectNode;

namespace kanzi
{
class Camera;
class GraphicsOutput;
class Node;
class Scene;
class Renderer3D;
typedef shared_ptr<Node> NodeSharedPtr;
}

/**
* Finds ObjectNode positioned in 3d space on a ray shot from point on near clip plane at viewport x,y to the
* direction of viewport x,y on far clip plane.
*
* After the call:
*  If object was hit:
*   - out_distance will contain the distance from camera to object bounding box hit position.
*   - out_node will contain the node hit
*   - out_vector_to_origin will contain the vector from object's origin to hit position
*
*  If object was not hit
*   - out_distance will be KZ_FLOAT_MAXIMUM
*   - out_node will be KZ_NULL 
*   - out_vector_to_origin will will be a vector with all components set to KZ_FLOAT_MAXIMUM
*
* \param source Object source used for picking. It can be used to invalidate parts of scene from picking.
* \param out_transformedNode Transformed node of the hit object. Can be KZ_NULL
*/
KANZI_API kzsError kzuRayPick(const kanzi::Renderer3D* renderer, const struct KzcVector2* limits, const kanzi::Scene* scene,
                              kanzi::Camera* cameraNode, kzInt positionX, kzInt positionY, kzFloat* out_distance, kanzi::Node** out_objectNode,
                              struct KzuTransformedObjectNode** out_transformedNode, struct KzcVector3* out_offsetFromOrigin,
                              struct KzcRay* out_ray);
/** As kzuRayPick, but take the limits from a graphics output. */
KANZI_API kzsError kzuRayPickFromGraphicsOutput(const kanzi::Renderer3D* renderer, const kanzi::GraphicsOutput& graphicsOutput,
                                              const kanzi::Scene* scene, kanzi::Camera* transformedCameraNode, kzInt positionX,
                                              kzInt positionY, kzFloat* out_distance, kanzi::Node** out_objectNode, struct KzuTransformedObjectNode** out_transformedNode,
                                              struct KzcVector3* out_offsetFromOrigin, struct KzcRay* out_ray);

/** Input hit testing. Finds the closest visible node that was pointed. */
KANZI_API kanzi::NodeSharedPtr kzuInputHitTest(const struct KzcVector2* limits, kanzi::Scene* scene, kanzi::Camera* camera,
                                               kzInt positionX, kzInt positionY, struct KzcRay* out_ray, kzFloat* out_distance);

/** Calculates a ray in world space from active window and given pointer coordinates. */
KANZI_API kzsError kzuRayPickCalculateRay(kzInt pointerX, kzInt pointerY, const struct KzcVector2* limits, kanzi::Camera* cameraNode,
                                          struct KzcRay* out_ray);
/** As kzuRayPickCalculateRay, but take limits from a graphics output. */
KANZI_API kzsError kzuRayPickCalculateRayFromGraphicsOutput(kzInt pointerX, kzInt pointerY, const kanzi::GraphicsOutput& graphicsOutput,
                                                            kanzi::Camera* camera, struct KzcRay* out_ray);


#endif

#endif
