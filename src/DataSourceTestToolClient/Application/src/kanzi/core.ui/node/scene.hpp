// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_SCENE_H
#define KZU_SCENE_H


#include "camera.hpp"
#include "node_reference.hpp"
#include "node.hpp"

#include <kanzi/core.ui/node/resource_reference.hpp>

#include <kanzi/core.ui/graphics3d/render_pass.hpp>


namespace kanzi
{

class Scene;

/// Scene shared pointer.
typedef shared_ptr<Scene> SceneSharedPtr;
/// CameraNode shared pointer.
typedef shared_ptr<Camera> CameraSharedPtr;
/// CameraNode weak pointer.
typedef weak_ptr<Camera> CameraWeakPtr;


/// Scene is a 3D node that is the root node for other 3D nodes.
///
/// A scene node is special 3D node in the sense that their parent is always a viewport layer, so they create a connection between 2D and 3D nodes.
///
/// Besides bridging 2D and 3D nodes, the scene also specifies which camera is used to render the contents of its
/// parent viewport.
/// \see KzuViewportLayer
class KANZI_API Scene : public Node3D
{
public:

    /// Creates a new scene node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the node.
    /// \return The created node.
    static SceneSharedPtr create(Domain* domain, string_view name);

    /// \name Properties
    /// \{

    /// HitTestCamera property.
    /// Defines the camera that is used when hit testing the objects in the scene. When the property is not set, the default camera is used.
    /// The default value is "".
    /// \see setHitTestCamera(), getHitTestCamera()
    static PropertyType<string> HitTestCameraProperty;

    /// Camera property.
    /// Defines the camera for viewing the scene.
    /// The default value is "".
    /// \see setCamera(), getCamera()
    static PropertyType<string> CameraProperty;

    /// RenderPass property.
    /// Defines the composer that is used to render the scene.
    /// The default value is ResourceSharedPtr().
    /// \see setRenderPass(), getRenderPass()
    static PropertyType<ResourceSharedPtr> RenderPassProperty;
    /// Gets the value of #RenderPassProperty.
    /// \see setComposer()
    RenderPassSharedPtr getRenderPass() const { return dynamic_pointer_cast<RenderPass>(getProperty(RenderPassProperty)); }
    /// Sets the value of #RenderPassProperty.
    /// \see getComposer()
    void setRenderPass(ResourceSharedPtr value) { setProperty(RenderPassProperty, value); }

    /// \}

    KZ_METACLASS_BEGIN(Scene, Node3D, "Kanzi.Scene")
        KZ_METACLASS_PROPERTY_TYPE(HitTestCameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(CameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets currently active camera (override or default).
    /// \return The current active camera.
    CameraSharedPtr getCurrentCamera() const;

    // TODO: Consider removing this and using only getCurrentCamera.
    /// Gets the current default (i.e. non-override) camera.
    /// \return The camera resource currently in use.
    /// \see setDefaultCamera(), setOverrideCamera()
    CameraSharedPtr getCamera() const;

    /// Sets the scene camera that will be used for rendering. The camera should be a descendant of the scene.
    /// \param camera The new scene camera.
    void setCamera(const CameraSharedPtr& camera);

    // TODO: Consider removing this and fixing free and orbit cameras to keep track of their own scene.
    /// Gets the current override camera.
    /// \return The current override camera.
    /// \see setOverrideCamera()
    CameraSharedPtr getOverrideCamera() const;

    /// Gets currently active hit test camera (hit test, override or default).
    /// \return The current active camera.
    CameraSharedPtr getCurrentHitTestCamera() const;

    /// Get hit test camera.
    ///
    /// This returns the hit test camera explicitly set. To return camera usable for hit testing even if the hit test
    /// camera is not set, use getCurrentHitTestCamera()
    ///
    /// \return Hit test camera.
    CameraSharedPtr getHitTestCamera() const;
    void setHitTestCamera(const CameraSharedPtr& camera);

    /// Sets or removes the override camera. If the override camera is set, it overrides the current camera resource. The override camera should be a descendant of the scene.
    /// Note that the scene does not take ownership of the camera, so the override camera must remain externally alive in order to work.
    /// \param overrideCamera The new override camera. Can be set to nullptr to remove the old override camera reference.
    void setOverrideCamera(const CameraSharedPtr& overrideCamera);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit Scene(Domain* domain, string_view name);

private:

    /// Default camera node reference.
    NodeReference<Camera> m_camera;

    /// Hit test camera node reference.
    NodeReference<Camera> m_hitTestCamera;

    /// Override camera.
    CameraWeakPtr m_overrideCamera;

    /// Default value for composer property.
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueComposer;
};

}


#endif

#endif
