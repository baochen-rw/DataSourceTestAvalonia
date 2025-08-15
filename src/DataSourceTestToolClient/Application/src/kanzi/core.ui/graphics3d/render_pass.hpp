// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_RENDER_PASS_HPP
#define KZ_RENDER_PASS_HPP

#include <kanzi/core.ui/graphics2d/composition_requirements.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/framebuffer.hpp>

namespace kanzi
{

// Forward declaration.
class CompositionStack;
class KzbFile;
class KzbMemoryParser;
class MaterialRenderer;
class Mesh;
class Morph;
class Node3D;
class ReadOnlyMemoryFile;
class Renderer3D;
class RenderPass;
class TransformedScene3D;

/// RenderPass shared pointer type.
typedef shared_ptr<RenderPass> RenderPassSharedPtr;

/// RenderPass is the base class for Kanzi render passes.
///
/// Use render passes to perform singular render pass operations in 3D scenes. For example, use a render pass
/// to clear the background, render nodes for a specific object source, set up a composition target, and so on.
///
/// Combine render passes into a hierarchy to create the rendering result you want to achieve.
///
/// Render pass rendering and execution order
/// =========================================
///
/// The base #RenderPass class does not implement any functionality, but renders its descendant render passes.
/// This is the reason why the base RenderPass class is called Group Render Pass in Kanzi Studio.
/// All other render passes either perform draw operations or set the state for successive render passes.
/// In both cases, they pass the control to their descendant render passes only after they execute their
/// own operations. Keep this in mind when you define your own render passes. See Creating your own render pass.
/// 
/// Render passes that perform draw operations are:
/// - BlitRenderPass
/// - ClearRenderPass
/// - DrawObjectsRenderPass
/// - DrawObjectsWithMaterialRenderPass
///
/// Render passes that set state are:
/// - CompositionTargetRenderPass
/// - MaterialSetupRenderPass
/// - PipelineStateRenderPass
///
/// Kanzi excutes render passes by iterating the tree depth-first. This is similar to how Kanzi iterates
/// nodes when it renders the scene graph. Each render pass first executes itself, then, one at a time,
/// all of its child render passes. Since the child render passes execute themselves, Kanzi executes the full
/// tree starting from a child render pass before it executes the next child render pass. In the same way,
/// the successive Kanzi executes the sibling render passes before it returns the control returns to the parent
/// render pass.
///
/// Using textures created with render passes
/// =======================================
///
/// You can use a render pass to create a texture and then use that texture in other render passes.
/// The texture bindings are resolved on render. For example, you can show on the screen a texture that a
/// CompositionTargetRenderPass creates, with a BlitRenderPass.
///
/// Creating render passes
/// ======================
///
/// When you create a render pass, the create function calls the constructor, initializes the render pass, and
/// returns the pointer to the render pass. The render pass constructors are protected and only inheriting
/// classes can access them.
///
/// For example, to create a Group Render Pass:
/// \snippet test_render_pass_snippets.cpp Create group render pass
///
/// Render pass hierarchy
/// =====================
///
/// You can combine render passes into a hierarchy to create the rendering result you cannot achieve with any
/// single render pass. When you select a render pass for a Scene or a Viewport2D node, you can select either
/// the root render pass or a specific render pass within such hierarchy. If you select a specific render pass
/// within such hierarchy, Kanzi uses only that render pass and its descendants to render the content.
///
/// If a render pass is the root of its own tree, it does not have a parent render pass. In the same
/// manner, if a render pass is a leaf render pass, it does not have any child render passes.
///
/// To create a render pass hierarchy:
/// \snippet test_render_pass_snippets.cpp Create render pass tree
///
/// To access descendant render passes (child render passes of the current render pass):
/// \snippet test_render_pass_snippets.cpp Access render pass child
///
/// To access ascendant render pass (parent render pass of the current render pass):
/// \snippet test_render_pass_snippets.cpp Access render pass parent
///
/// Creating your own render pass class
/// ===================================
///
/// If you cannot achieve the rendering result with the render passes that come with Kanzi, you can create your
/// own render pass.
///
/// Defining the class
/// ------------------
///
/// Start creating your own render pass by inheriting from the #RenderPass base class. Define metaclass and
/// declare property types in the same way as you would in the Node classes. See Node2D.
///
/// To create a simple custom render pass:
/// \snippet test_render_pass_snippets.cpp Custom RenderPass example
///
/// RenderPass override functions
/// -----------------------------
///
/// When you need to override the functionality of the #RenderPass class, override the #renderOverride() virtual
/// method:
/// \snippet test_render_pass_snippets.cpp Custom RenderPass renderOverride
///
/// The #RenderPass base class loads all render pass properties that you define in your render pass. However,
/// if you need to implement custom loading for your render pass, you can override the #loadFromKzb() method.
class KANZI_API RenderPass : public Resource, public enable_shared_from_this<RenderPass>
{
public:

    /// Struct containing resource binding information.
    struct ResourceBinding
    {
    public:

        /// Constructor.
        /// \param targetPropertyType Target property type to be written.
        /// \param renderPassPath Path to source render pass.
        /// \param attachmentPoint The attachment point this resource binding binds to.
        /// \param fromKzb Indicates whether the resource binding has been loaded from a kzb file.
        explicit ResourceBinding(AbstractPropertyType targetPropertyType, string_view renderPassPath, Framebuffer::AttachmentPoint attachmentPoint, bool fromKzb) :
            propertyType(targetPropertyType),
            path(renderPassPath),
            attachment(attachmentPoint),
            isFromKzb(fromKzb)
        {
        }

        /// Property type to bind to.
        AbstractPropertyType propertyType;

        /// Path to source render pass.
        string path;

        /// Type of the composition target being bound.
        Framebuffer::AttachmentPoint attachment;

        /// Flag indicating whether this resource binding is loaded from a kzb file.
        bool isFromKzb;
    };

    KZ_METACLASS_BEGIN(RenderPass, Resource, "Kanzi.RenderPass")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    typedef vector<RenderPassSharedPtr> ChildContainer;

    /// Create a render pass.
    /// \param domain The domain to use.
    /// \param name The name for the render pass.
    static RenderPassSharedPtr create(Domain *domain, string_view name);

    /// Resolve a render pass by path.
    /// \param path The relative path to the render pass.
    /// \return The render pass, if none found, 0.
    RenderPassSharedPtr lookupRenderPass(string_view path);

    /// Recursively render RenderPass and all of its child render passes.
    /// Calls #renderOverride that you can implement by inheriting classes.
    /// \param renderer The renderer to use.
    /// \param transformedScene The transformed scene to render.
    /// \param compositionStack The composition stack to use.
    void render(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack);

    /// Use this function to render a mesh owned by a node using the material renderer that the node owns.
    /// \param node Node being rendered.
    /// \param morph Morph, if applicable.
    /// \param mesh Mesh being rendered.
    /// \param clusterIndex Cluster being drawn.
    /// \param materialRenderer Material renderer provided to use for rendering the mesh.
    void renderMesh(Node3D& node, Morph* morph, Mesh& mesh, unsigned int clusterIndex, MaterialRenderer& materialRenderer);

    /// Adds a render pass as the last child of the render pass you set.
    /// \param childRenderPass The render pass to add.
    void addChild(RenderPassSharedPtr childRenderPass);

    /// Adds a render pass as a child render pass at given index of the render pass you set.
    /// \param index The index at which to insert the child render pass.
    /// \param childRenderPass The render pass to add.
    void insertChild(size_t index, RenderPassSharedPtr childRenderPass);

    /// Removes a child render pass. If the render pass is not a child of this render pass,
    /// silently does nothing.
    /// \param childRenderPass The render pass to remove.
    void removeChild(RenderPass& childRenderPass);

    /// Removes all child render passes from a render pass.
    void removeAllChildren();

    /// Gets the parent of a render pass.
    /// \return Shared pointer to the parent render pass of a render pass, an empty shared pointer if the render pass does not have a parent.
    RenderPassSharedPtr getParent() const
    {
        return m_parent.lock();
    }
    /// Sets the parent of a render pass.
    /// \param parent The parent render pass.
    void setParent(RenderPassSharedPtr parent)
    {
        m_parent = parent;
    }

    /// Gets a child render pass at the given index. Throws an error if the index is invalid.
    /// \param index The index of the child render pass that you want get.
    /// \return Shared pointer to the child render pass at the given index.
    RenderPassSharedPtr getChild(size_t index)
    {
        kzAssert(index < getChildCount());
        return m_children[index];
    }

    /// Returns the number of child render passes.
    size_t getChildCount() const
    {
        return m_children.size();
    }

    /// Returns an iterator to the beginning of the container of child render passes.
    ChildContainer::const_iterator beginChildren() const
    {
        return m_children.begin();
    }

    /// Returns an iterator to the end of the container of child render passes.
    ChildContainer::const_iterator endChildren() const
    {
        return m_children.end();
    }

    /// Gets color composition target that was used for rendering.
    /// Internally calls the #getCompositionResultOverride() method.
    /// Only returns non-empty shared pointer values by render passes actually using composition targets.
    /// \param attachmentPoint The attachment point of the composition result to acquire.
    /// \return Texture shared pointer, may be empty.
    TextureSharedPtr getCompositionResult(Framebuffer::AttachmentPoint attachmentPoint)
    {
        return getCompositionResultOverride(attachmentPoint);
    }

    /// Gets the number of texture bindings.
    /// \return The number of texture bindings in the render pass.
    size_t getTextureBindingCount() const
    {
        return m_textureBindings.size();
    }
    /// Gets a texture binding by index.
    /// \return The texture binding at the given index.
    ResourceBinding getTextureBinding(size_t index) const
    {
        return m_textureBindings[index];
    }

    /// Adds a texture binding. Use texture bindings to map the composition result values
    /// from other render passes to property values.
    ///
    /// Path of the texture binding describes the relative path to another render pass from which the
    /// composition is acquired. After the  relative path, an optional dot followed by an attachment point name
    /// can be specified. Valid attachment points accepted are:
    /// * "Color0", "Color1", "Color2" or "Color3"
    /// * "Depth"
    /// Not specifying anything for the attachment point name is the same as specifying ".Color0" for the first
    /// color attachment point.
    ///
    /// \param propertyType The property type to map to.
    /// \param path The path to the render pass to which you want to add texture binding.
    /// \param fromKzb Indicates whether the resource binding is loaded from a kzb file.
    void addTextureBinding(AbstractPropertyType propertyType, string_view path, bool fromKzb);
    /// Adds a texture binding. Use texture bindings to map the composition result values
    /// from other render passes to property values. The binding added is set to not come from a kzb file.
    /// \param propertyType The property type to map to.
    /// \param path The path to the render pass to which you want to add texture binding.
    void addTextureBinding(AbstractPropertyType propertyType, string_view path)
    {
        addTextureBinding(propertyType, path, false);
    }
    /// Removes the texture binding.
    /// \param propertyType The property type for which you want to remove the binding.
    /// \return True when the function finds a binding and removes it, otherwise false.
    bool removeTextureBinding(AbstractPropertyType propertyType);
    /// Removes the resource bindings loaded from kzb files.
    /// This function is analogous to #removeKzbProperties().
    void removeKzbTextureBindings();

    /// Queries if a render pass requires a depth buffer.
    /// Use this function to determine the depth buffer requirement for automatically created render targets.
    /// \param allowDepthClear Output parameter, true if node can clear depth buffer.
    /// \param requiresDepth Output parameter, true if node requires composition target to have depth buffer.
    virtual CompositionRequirements getCompositionRequirements() const;

    /// Recursively calls #restoreResources for a RenderPass and all its children.
    /// Calls happen in depth-first order.
    void restoreResourcesRecursive();
    /// Restore resources after suspend.
    /// Inheriting classes should call parent class methods.
    virtual void restoreResources();

    /// Resource::loadFromKZB() implementation.
    /// Legacy kzb loading.
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Factory function for RenderPass Load Task, which loads a RenderPass from a kzb file.
    /// \param name Name of the RenderPass that you want to load.
    /// \param kzbFile Pointer to the instance of KzbFile, which holds the information about the kzb file.
    /// \param file Pointer to the instance of ReadOnlyMemoryFile, which wraps the kzb file.
    /// \return Shared pointer to the created load task.
    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

protected:

    /// Constructor.
    explicit RenderPass(Domain *domain, string_view name);

    /// Override function called by createLoadTask(), after loading render pass.
    /// Allows render pass type specific post loading implementation.
    virtual void onLoaded()
    {
    }

    /// Load child render passes from a kzb file. Kanzi calls this function in individual loadFromKZB implementations.
    /// \param resourceManager The resource manager for accessing the child render passes.
    /// \param parser The file parser to use for loading.
    void loadChildRenderPassesFromKZB(ResourceManager& resourceManager, KzbMemoryParser& parser);

    /// Reimplementation of the loadProperties from parser to accommodate paths in properties.
    /// \param parser The parser to use.
    void loadProperties(KzbMemoryParser& parser);

    /// Reimplementation of the property reading to accommodate paths in properties.
    /// Previous version of the loader.
    kzsError readProperties(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file, ResourceManager* resourceManager);

    /// Reimplementation of reading a single property to accommodate paths in properties.
    /// Previous version of the loader.
    kzsError readProperty(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file, ResourceManager* resourceManager);

    /// Render all child render passes of a render pass.
    /// \param renderer The renderer to use.
    /// \param transformedScene The transformed scene to render.
    /// \param compositionStack The composition stack to use.
    void renderChildren(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack);

    /// Iterates the children for composition requirements.
    /// The requirements for children are merged with the requirements passed.
    /// \param requirements Initial requirements.
    /// \return Requirements combined with all children.
    CompositionRequirements combineChildCompositionRequirements(CompositionRequirements requirements) const;
    /// Iterates the children for composition requirements.
    /// Usually the user should call #combineChildCompositionRequirements() instead.
    /// This function is used if the render pass has no requirements of its own.
    /// \return Requirements combined with all children.
    CompositionRequirements getChildCompositionRequirements() const
    {
        return combineChildCompositionRequirements(CompositionRequirements());
    }

    /// Render implementation specific to the RenderPass class.
    /// The default implementation renders all child render passes, but does nothing else. For this reason the base render
    /// pass class is considered as a Group Render Pass.
    /// \param renderer The renderer to use.
    /// \param transformedScene The transformed scene to render.
    /// \param compositionStack The composition stack to use.
    virtual void renderOverride(Renderer3D& renderer, TransformedScene3D& transformedScene, CompositionStack& compositionStack);

    /// Mesh rendering that is specific for a render pass.
    /// Most of the render passes do not need to override this, because they do not render nodes.
    /// \param node Node being rendered.
    /// \param morph Morph, if applicable.
    /// \param mesh Mesh being rendered.
    /// \param clusterIndex Cluster being drawn.
    /// \param materialRenderer Material renderer provided to use for rendering the mesh.
    virtual void renderMeshOverride(Node3D& node, Morph* morph, Mesh& mesh, unsigned int clusterIndex, MaterialRenderer& materialRenderer);

    /// Acquiring of composition target specific to the RenderPass class.
    /// The default implementation returns an empty shared pointer.
    /// \param attachmentPoint Which composition result to acquire?
    /// \return Shared pointer to the resulting texture.
    virtual TextureSharedPtr getCompositionResultOverride(Framebuffer::AttachmentPoint attachmentPoint)
    {
        (void)attachmentPoint;
        return TextureSharedPtr();
    }

private:

    /// Resource binding container type.
    typedef vector<ResourceBinding> ResourceBindingContainer;

    /// Child render passes.
    ChildContainer m_children;

    /// Pointer to parent render pass.
    weak_ptr<RenderPass> m_parent;

    /// Properties by paths.
    /// Used to refer to properties from other render passes as opposed to resources.
    ResourceBindingContainer m_textureBindings;

    class LoadTaskNew;
    friend class LoadTaskNew;
};
}

#endif

#endif
