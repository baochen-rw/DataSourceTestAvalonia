// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DRAW_OBJECTS_RENDER_PASS_HPP
#define KZ_DRAW_OBJECTS_RENDER_PASS_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/renderer3d.hpp>
#include <kanzi/core.ui/graphics3d/render_pass.hpp>

namespace kanzi
{

// Forward declaration.
class DrawObjectsRenderPass;

/// DrawObjectsRenderPass shared pointer type.
typedef shared_ptr<DrawObjectsRenderPass> DrawObjectsRenderPassSharedPtr;

/// Use the Draw Objects Render Pass to render only nodes in a Scene node provided by an object
/// source you set in this render pass. The Draw Objects Render Pass renders objects from the
/// object source you set in the #ObjectSourceProperty property with the Camera node that the
/// Scene node uses. The Camera node that a Draw Objects Render Pass uses must be in the same
/// Scene node as the objects that the Draw Objects Render Pass renders.
///
/// Internally, to render content, a Draw Objects Render Pass creates object type filters for
/// light nodes and renderable objects that both set the assigned object source as their source.
/// Before it iterates renderable objects, the render pass iterates the light filter to set up
/// the light state.
///
/// Examples
/// ===
/// To render only objects that have the StandardMaterial::BlendIntensityProperty property:
/// \snippet test_render_pass_snippets.cpp Draw objects render pass object source
///
/// To set which Camera node you want to use to render the objects, use the #CameraProperty:
/// \snippet test_render_pass_snippets.cpp Draw objects render pass camera
class KANZI_API DrawObjectsRenderPass : public RenderPass
{
public:

    /// Function object type for applying specific type of nodes for rendering.
    typedef function<void(Renderer3D&, DrawObjectsRenderPass&, KzuTransformedObjectNode&)> ApplyNodeFunction;

    /// \name Properties
    /// \{

    /// Use the Camera property to set the Camera node that you want to use to render the nodes.
    /// The Camera node that a Draw Objects Render Pass uses must be in the same Scene node
    /// as the nodes that the Draw Objects Render Pass renders.
    /// The default value is "", which means that the Draw Objects Render Pass uses the default
    /// Camera node in that Scene node.
    /// \see setCamera(), getCamera()
    static PropertyType<string> CameraProperty;
    /// Gets the value of the #CameraProperty.
    /// \see setCamera()
    string getCamera() const { return getProperty(CameraProperty); }
    /// Sets the value of the #CameraProperty.
    /// \see getCamera()
    void setCamera(string value) { setProperty(CameraProperty, value); }

    /// Use the %Object Source property to set the object source which collects the nodes that
    /// you want to render with this render pass.
    /// The default value is ResourceSharedPtr(), which means that the Draw Objects Render Pass
    /// uses the Root %Object Source which includes all nodes in a Scene node.
    /// \see setObjectSource(), getObjectSource()
    static PropertyType<ResourceSharedPtr> ObjectSourceProperty;
    /// Gets the value of the #ObjectSourceProperty.
    /// \see setObjectSource()
    ResourceSharedPtr getObjectSource() const { return getProperty(ObjectSourceProperty); }
    /// Sets the value of the #ObjectSourceProperty.
    /// \see getObjectSource()
    void setObjectSource(ResourceSharedPtr value) { setProperty(ObjectSourceProperty, value); }

    /// FrustumCulling property.
    static PropertyType<bool> FrustumCullingEnabledProperty;
    /// Gets the value of #FrustumCullingEnabledProperty.
    /// \return Property value.
    bool isFrustumCullingEnabled() const
    {
        return getProperty(FrustumCullingEnabledProperty);
    }
    /// Sets the value of #FrustumCullingEnabledProperty.
    /// \param value Property value.
    void setFrustumCullingEnabled(bool value)
    {
        setProperty(FrustumCullingEnabledProperty, value);
    }

    /// \}

    KZ_METACLASS_BEGIN(DrawObjectsRenderPass, RenderPass, "Kanzi.DrawObjectsRenderPass")
        KZ_METACLASS_PROPERTY_TYPE(CameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(ObjectSourceProperty)
        KZ_METACLASS_PROPERTY_TYPE(FrustumCullingEnabledProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a Draw Objects Render Pass.
    /// \param domain The domain to use.
    /// \param name The name of the Draw Objects Render Pass.
    /// \return The created Draw Objects Render Pass.
    static DrawObjectsRenderPassSharedPtr create(Domain* domain, string_view name);

protected:

    /// Constructor.
    /// \param domain The domain to use.
    /// \param name The name of the Draw Objects Render Pass.
    explicit DrawObjectsRenderPass(Domain* domain, string_view name);

    /// Acquire transformed Camera node to use for rendering.
    /// \param transformedScene The transformed Scene to be rendered.
    /// \return Tuple of the Camera node and the transformed Camera node.
    tuple<Camera*, KzuTransformedObjectNode*> acquireTransformedCamera(TransformedScene3D& transformedScene) const;

    /// RenderPass::renderOverride() implementation.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack) KZ_OVERRIDE;

    /// RenderPass::renderMeshOverride() implementation.
    virtual void renderMeshOverride(Node3D& node, Morph* morph, Mesh& mesh, unsigned int clusterIndex, MaterialRenderer& materialRenderer) KZ_OVERRIDE;

    /// Apply a Camera node projection using the current Viewport 2D node.
    /// \param renderer The renderer to use.
    /// \param cameraNode The base Camera node.
    /// \param transformedCamera The transformed Camera node.
    /// \param viewportSize The current size of the Viewport 2D node.
    /// \return The projection matrix used.
    virtual Matrix4x4 applyCamera(Renderer3D& renderer, Camera& cameraNode, KzuTransformedObjectNode& transformedCamera, Vector2 viewportSize);

    /// Apply all objects from a given object source.
    /// \param renderer The renderer to use.
    /// \param objectSource The object source to apply.
    /// \param transformedScene The transformed Scene node to be rendered.
    /// \param transformedCamera The transformed Camera node to use.
    /// \param applyFunction The apply function to use for applying the objects from the object source.
    virtual void applyObjectSource(Renderer3D& renderer, KzuObjectSource& objectSource, TransformedScene3D& transformedScene,
                                   KzuTransformedObjectNode& transformedCamera, ApplyNodeFunction applyFunction);

    /// Renderer3D apply function for applying lights.
    /// \param renderer The renderer to use.
    /// \param transformedNode Transformed node to apply.
    virtual void applyLight(Renderer3D& renderer, KzuTransformedObjectNode& transformedNode);

    /// Renderer3D apply function for applying nodes.
    /// \param renderer The renderer to use.
    /// \param transformedNode Transformed node to apply.
    virtual void applyNode(Renderer3D& renderer, KzuTransformedObjectNode& transformedNode);

protected:
    /// Functor for passing the applyLight to the Renderer in the renderOverride.
    struct ApplyLightFunctor;
    /// Functor for passing the applyNode to the Renderer in the renderOverride.
    struct ApplyNodeFunctor;

    /// %Object source for light nodes.
    FilterObjectSourceSharedPtr m_renderableObjectSource;
    /// %Object source for renderable objects.
    FilterObjectSourceSharedPtr m_lightObjectSource;
    /// Frustum cull object source to act as an intermediate object source if enabled.
    FilterObjectSourceSharedPtr m_frustumCullObjectSource;
};

struct DrawObjectsRenderPass::ApplyLightFunctor
{
    void operator()(Renderer3D& renderer, DrawObjectsRenderPass& renderPass, KzuTransformedObjectNode& transformedNode)
    {
        renderPass.applyLight(renderer, transformedNode);
    }
};

struct DrawObjectsRenderPass::ApplyNodeFunctor
{
    void operator()(Renderer3D& renderer, DrawObjectsRenderPass& renderPass, KzuTransformedObjectNode& transformedNode)
    {
        renderPass.applyNode(renderer, transformedNode);
    }
};

} // namespace kanzi

#endif // KZ_DRAW_OBJECTS_RENDER_PASS_HPP