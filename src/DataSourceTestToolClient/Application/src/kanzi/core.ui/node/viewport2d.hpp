// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_VIEWPORT2D_HPP
#define KZ_VIEWPORT2D_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/node/scene.hpp>
#include <kanzi/core.ui/node/kzu_transformed_scene.h>

// Forward declarations
struct KzcRay;

namespace kanzi
{

class Camera;
class RenderPass; 
class Scene;
class Viewport2D;

typedef shared_ptr<Viewport2D> Viewport2DSharedPtr;

/// Use a Viewport 2D to set the size of a render target surface onto which content is projected.
/// Viewport 2D is a 2D node that can project a 3D scene through a camera. Viewport 2D is a special
/// node because it can render both 2D nodes, such as Image, Page, Button 2D, and a Scene,
/// which is a 3D node.
///
/// When you create a new project in Kanzi Studio, that project has a Viewport 2D with a Scene that
/// contains a Camera and a Directional Light. However, when you create a Viewport 2D using the API
/// you have to manually add the Scene and any contents of the Scene.
///
/// Examples
/// ----
///
/// To create a Viewport 2D node, attach it to the RootPage, and add to it either a Scene or 2D content:
/// \snippet test_viewport2d.cpp Using Viewport2D
class KANZI_API Viewport2D : public Node2D
{
public:

    virtual ~Viewport2D();

    /// \name Properties
    /// \{
#include "viewport2d_properties.h"

    /// RenderPass property.
    /// The default value is ResourceSharedPtr().
    static PropertyType<ResourceSharedPtr> RenderPassProperty;
    /// Gets value of #RenderPassProperty.
    /// If this node has no #RenderPassProperty set, returns the value from the scene.
    /// \return RenderPassSharedPtr, may be empty.
    RenderPassSharedPtr getRenderPass() const
    {
        return dynamic_pointer_cast<RenderPass>(getProperty(RenderPassProperty));
    }
    /// Sets value of #RenderPassProperty.
    /// \param renderPass New RenderPass to use, setting an empty shared pointer will default to render pass from the scene.
    void setRenderPass(RenderPassSharedPtr renderPass)
    {
        setProperty(RenderPassProperty, renderPass);
    }

    /// \}

    /// Creates a Viewport2D node.
    ///
    /// The viewport is created without a scene.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    static Viewport2DSharedPtr create(Domain* domain, string_view name);

    /// Creates a Viewport2D node.
    ///
    /// The viewport is created without a scene.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    /// \param width Node width.
    /// \param width Node height.
    static Viewport2DSharedPtr create(Domain* domain, string_view name, float width, float height);

    KZ_METACLASS_BEGIN(Viewport2D, Node2D, "Kanzi.Viewport2D")
        KZ_METACLASS_PROPERTY_TYPE(CameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(HitTestCameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderPassProperty)
    KZ_METACLASS_END()

    /// Creates a Viewport2D node.
    ///
    /// A scene is created at the same time.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    static Viewport2DSharedPtr createDefault(Domain* domain, string_view name);

    /// Creates a Viewport2D node.
    ///
    /// A scene is created at the same time.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    /// \param width Node width.
    /// \param width Node height.
    static Viewport2DSharedPtr createDefault(Domain* domain, string_view name, float width, float height);

    /// Render viewport scene.
    ///
    /// TODO: Should be a member function, refactor.
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param node Node area to use.
    /// \param scene Scene to render.
    /// \param transformedScene Transformed scene of the scene.
    /// \param composer Composer to use.
    static void renderScene(Renderer3D& renderer, CompositionStack& compositionStack, const Node2D& node,
                            TransformedScene3D& transformedScene, RenderPass& composer);

    /// Render viewport background quad.
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param node Node to render the background for.
    /// \param enableDepth True to enable depth buffer.
    static void renderViewportBackgroundQuad(Renderer3D& renderer, CompositionStack& compositionStack, Node2D &node,
                                             bool enableDepth);

    /// Access viewport camera.
    /// \return Pointer to camera.
    CameraSharedPtr getCamera() const;

    /// Access viewport hit test camera.
    /// \return Pointer to hit test camera.
    CameraSharedPtr getHitTestCamera() const;

    /// Get current render pass used for rendering the scene under this viewport.
    /// Returns scene render pass if viewport has no render pass set.
    /// \return Render pass shared pointer. If empty, rendering the viewport is not possible.
    RenderPassSharedPtr getCurrentRenderPass() const;

    void setHitTestCamera(CameraSharedPtr camera);

    void setCamera(CameraSharedPtr camera);

    void setScene(SceneSharedPtr scene);

    /// Get viewport scene.
    ///
    /// \return Scene shared pointer.
    SceneSharedPtr getScene() const
    {
        return m_scene;
    }

    /// Get transformed scene.
    ///
    /// \return Transformed scene pointer.
    TransformedScene3D* getTransformedScene()
    {
        return &m_transformedScene;
    }

    /// Get transformed scene.
    ///
    /// \return Transformed scene pointer.
    const TransformedScene3D* getTransformedScene() const
    {
        return &m_transformedScene;
    }

    /// Tells if background brush rendering is required after rendering the scene.
    /// This differs from normal background brush rendering, which is checked before scene rendering.
    /// \return True if should render, false if not.
    bool requiresPostSceneBackgroundBrushRendering() const
    {
        return getBackgroundBrushRenderer() && isForegroundHintOpaque();
    }

protected:

    explicit Viewport2D(Domain* domain, string_view name);

    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;

    virtual NodeSharedPtr findAbstractChildOverride(string_view name) KZ_OVERRIDE;
    virtual VisitorResult visitAbstractChildOverride(const Visitor& visitor, VisitorOrder order) KZ_OVERRIDE;

    virtual void onExtract() KZ_OVERRIDE;

    virtual bool measureRecursive() KZ_OVERRIDE;
    virtual void arrangeRecursive(const Matrix3x3& worldTransform, const Matrix3x3& parentTransform, bool arrangeNeeded, bool transformChanged) KZ_OVERRIDE;

    /// Node2D::updateRenderOverride() implementation.
    virtual void updateRenderOverride() KZ_OVERRIDE;

    /// Node2D::renderSelfOverride() implementation.
    virtual void renderSelfOverride(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform) KZ_OVERRIDE;

    /// Node::onNodePropertyChanged() implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Node::restoreResources() implementation.
    virtual void restoreResources() KZ_OVERRIDE;

    /// Node2D::hitTestContent() implementation.
    virtual tuple<NodeSharedPtr, KzcRay, float> hitTestContent(Vector2 point) KZ_OVERRIDE;

    /// Default value for background brush property.
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueBackgroundBrush;
    /// Default value for snap to pixel property.
    ClassPropertyDefaultValue<bool> m_classValueSnapToPixelProperty;

    /// Scene to render in this viewport.
    SceneSharedPtr m_scene;
    /// Transformed version of the scene.
    TransformedScene3D m_transformedScene;

    /// Camera node reference.
    NodeReference<Camera> m_camera;

    /// Hit test camera node reference.
    NodeReference<Camera> m_hitTestCamera;
};

}

#endif

#endif  // KANZI_FEATURE_3D
