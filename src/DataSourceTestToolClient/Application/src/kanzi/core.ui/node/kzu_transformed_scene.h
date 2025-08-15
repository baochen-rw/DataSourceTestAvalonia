#ifdef KANZI_FEATURE_3D

/**
* \file
* Transformed scene object. Transformed scene is extracted from a scene object.
* After extracting it holds all the data needed to perform updates and to render the scene.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_TRANSFORMED_SCENE_H
#define KZU_TRANSFORMED_SCENE_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#include <kanzi/core/cpp/memory.hpp>



/* Forward declarations */
struct KzcMemoryManager;
struct KzuObjectSourceRuntimeData;
struct KzuTransformedObjectNode;
struct KzcDynamicArray;

namespace kanzi
{

class Camera;
class RenderPass;
class Scene;
class Viewport2D;

class KANZI_API TransformedScene3D
{
public:

    explicit TransformedScene3D(const KzcMemoryManager* memoryManager);
    ~TransformedScene3D();

    KzcMemoryManager* quickMemoryManager; /**< Quick memory manager for internal data. This is created only once for the whole transformed scene. */

    /* The following members are created in every extract call. */
    Camera* camera; /**< Camera to use. */
    Camera* hitTestCamera; /**< Hit test camera to use. */
    Scene* originalScene; /**< Original scene used to create this transformed scene. */
    KzcDynamicArray* transformedObjects; /**< Extracted object list. */
    KzuTransformedObjectNode* extractedRootNode; /**< Extracted (transformed) root node. */
    KzuObjectSourceRuntimeData* objectSourceRuntimeData; /**< Runtime data for object sources. */
    KzuTransformedObjectNode* extractedCameraNode; /**< Transformed view camera that was extracted. */
};

}


/** Generates a transformed scene from a scene. */
KANZI_API kzsError kzuTransformedSceneExtract(kanzi::TransformedScene3D* transformedScene, kanzi::Scene* scene);

/** Clear a transformed scene object. */
KANZI_API kzsError kzuTransformedSceneClear(kanzi::TransformedScene3D* transformedScene);

/** Get the camera that was determined to be used when rendering this transformed scene. */
KANZI_API kanzi::Camera* kzuTransformedSceneGetCamera(const kanzi::TransformedScene3D* transformedScene);
/** Get the scene that was used to generate the transformed scene. */
KANZI_API kanzi::Scene* kzuTransformedSceneGetScene(const kanzi::TransformedScene3D* transformedScene);
/** Get the transformed object array KzcDynamicArray<struct KzuTransformedObjectNode*>. */
KANZI_API struct KzcDynamicArray* kzuTransformedSceneGetObjects(const kanzi::TransformedScene3D* transformedScene);
/** Get the transformed root object node. */
KANZI_API struct KzuTransformedObjectNode* kzuTransformedSceneGetRootNode(const kanzi::TransformedScene3D* transformedScene);

/** Get the object source runtime data. */
KANZI_API struct KzuObjectSourceRuntimeData* kzuTransformedSceneGetObjectSourceRuntimeData(const kanzi::TransformedScene3D* transformedScene);

/** Get current transformed camera node. */
KANZI_API struct KzuTransformedObjectNode* kzuTransformedSceneResolveHitTestCameraNode(const kanzi::TransformedScene3D* transformedScene);

/** Sets view camera of transformed scene. */
KANZI_API void kzuTransformedSceneSetExtractedViewCamera(kanzi::TransformedScene3D* transformedScene, struct KzuTransformedObjectNode* transformedObjectNode);
/** Gets view camera of transformed scene. */
KANZI_API struct KzuTransformedObjectNode* kzuTransformedSceneGetExtractedViewCamera(const kanzi::TransformedScene3D* transformedScene);





#endif

#endif
