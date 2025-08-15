// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MATERIAL_RENDERER_HPP
#define KZ_MATERIAL_RENDERER_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_render_state.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/gl_render_value_binding.hpp>

namespace kanzi
{

// Forward declarations.
class Material;
class Mesh;
class Node3D;
typedef shared_ptr<Material> MaterialSharedPtr;
typedef shared_ptr<Mesh> MaeshSharedPtr;

/// Material renderer.
/// Connects material, mesh and 3D node like a brush renderer connects material, brush and 2D node.
class KANZI_API MaterialRenderer
{
public:

    /// Constructor.
    static unique_ptr<MaterialRenderer> create();

    /// Reattaches material renderer to a model and a mesh.
    /// Called by Node3D when material or mesh is updated.
    /// \param material Material to use.
    /// \param node Node to attach to.
    void attach(MaterialSharedPtr material, Node3D& node);

    /// Bind material renderer for rendering.
    /// Must be called before calling #draw().
    /// \param renderer Renderer to use.
    void bind(Renderer3D& renderer);

    /// Draw the given morph using attached material.
    /// \param renderer Renderer to use.
    /// \param node The node being drawn.
    /// \param mesh The mesh to draw.
    /// \param transformedObjects List of transformed objects.
    void draw(Renderer3D& renderer, Node3D& node, Mesh& mesh, KzcDynamicArray* transformedObjects) const;

    /// Mark all property notification handlers dirty.
    void invalidateRenderValues();

    /// Access render state.
    /// \return Reference to the render state.
    GlRenderState& getRenderState()
    {
        return m_renderState;
    }

    /// Access brush.
    /// \return Material shared pointer.
    MaterialSharedPtr getMaterial() const
    {
        return m_renderState.getMaterial();
    }

    /// Tells if this material renderer can be used for rendering.
    /// \return True if yes, false if no.
    bool isRenderable() const
    {
        return static_cast<bool>(getMaterial());
    }

    /// Get texture handle for contained render state.
    /// \param name Texture uniform name.
    /// \return Handle to named texture in current attached material or -1.
    GlRenderState::HandleType getTextureHandle(string_view name)
    {
        return m_renderState.getHandle<TextureSharedPtr>(name);
    }
    /// Get content texture handle for contained render state.
    /// This function is provided as a shorthand because access to content texture is a common use case.
    /// \return Handle to content texture in current attached material.
    GlRenderState::HandleType getContentTextureHandle()
    {
        return getTextureHandle("ContentTexture");
    }
    /// Set texture value in contained render state.
    /// A valid texture handle must have been acquired by getTextureHandle prior to calling this function.
    /// \param handle Handle to content texture.
    /// \param value Texture value.
    void setTextureValue(GlRenderState::HandleType handle, TextureSharedPtr value)
    {
        m_renderState.setValue<TextureSharedPtr>(handle, value);
    }

    /// Marks the notification handlers as invalid.
    /// Use this function when you destroy a node before destroying the MaterialRenderer.
    void invalidateNotificationHandlers()
    {
        m_renderValueBinding.invalidate();
    }

protected:

    /// Constructor.
    /// \param material Material to use.
    /// \param mesh Mesh to use.
    /// \param node Node to attach to.
    explicit MaterialRenderer():
        m_propertyChangeCounter(0)
    {
    }

    /// Check if property change counter matches that of the brush.
    /// \param material Material currently used.
    /// \return True if matches and no update is necessary, false otherwise.
    bool isChangeCounterSame(Material& material) const
    {
        return (material.getPropertyChangeCounter() == m_propertyChangeCounter);
    }
    /// Update property change counter to match brush.
    /// \param material Material currently used.
    void updateChangeCounter(Material& material)
    {
        m_propertyChangeCounter = material.getPropertyChangeCounter();
    }

private:

    /// Render state.
    GlRenderState m_renderState;

    /// Render value bindings.
    GlRenderValueBinding m_renderValueBinding;

    /// Property change counter to track material.
    unsigned int m_propertyChangeCounter;
};

/// MaterialRenderer unique pointer type.
typedef unique_ptr<MaterialRenderer> MaterialRendererPtr;

}

#endif // KZ_MATERIAL_RENDERER_HPP