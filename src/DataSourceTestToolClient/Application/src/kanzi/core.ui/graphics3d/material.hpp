// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MATERIAL_HPP
#define KZ_MATERIAL_HPP

#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core.ui/resource/resource_manager.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>

struct KzcInputStream;
struct KzuBinaryFileInfo;

namespace kanzi
{

// Forward declarations.
class Domain;
class Framebuffer;
class KzbFile;
class KzbMemoryParser;
class Material;
class ReadOnlyMemoryFile;
class ShaderProgram;
class Texture;
typedef shared_ptr<Framebuffer> FramebufferSharedPtr;
typedef shared_ptr<Material> MaterialSharedPtr;
typedef shared_ptr<Material const> MaterialSharedConstPtr;
typedef shared_ptr<ShaderProgram> ShaderProgramSharedPtr;
typedef shared_ptr<Texture> TextureSharedPtr;

/// A material is an instance of a material type (ShaderProgram) that contains the property values for the material type properties.
/// These values can be overriden in the nodes that use the material.
class KANZI_API Material : public Resource
{
public:
    KZ_METACLASS_BEGIN(Material, Object, "Kanzi.Material")
    KZ_METACLASS_END()

    /// Create material.
    ///
    /// \param domain Domain to use.
    /// \param name Name of material.
    static MaterialSharedPtr create(Domain* domain, string_view name);

    /// Create material with shader.
    ///
    /// \param domain Domain to use.
    /// \param name Name of material.
    /// \param shaderProgram ShaderProgram to use for this material.
    static MaterialSharedPtr create(Domain* domain, string_view name, ShaderProgramSharedPtr shaderProgram);

    static Material* createEmpty(Domain* domain, string_view name);

    bool isRenderable() const;

    TextureSharedPtr getTexture(AbstractPropertyType propertyType) const;
    void setTexture(AbstractPropertyType propertyType, TextureSharedPtr texture);

    /// Gets shader program from material.
    /// \return Material shader program.
    ShaderProgramSharedPtr getShaderProgram() const
    {
        return m_shaderProgram;
    }
    /// Sets material shader program.
    /// \param shaderProgram New shader program.
    void setShaderProgram(ShaderProgramSharedPtr shaderProgram)
    {
        m_shaderProgram = shaderProgram;
    }

    /// Legacy kzb loading interface
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Gets the material property change counter.
    /// \return Total number of property changes in the material.
    unsigned int getPropertyChangeCounter() const
    {
        return m_propertyChangeCounter;
    }
    /// Update property change counter.
    /// Called when a property in the material is changed. Increments the change counter by one.
    void updatePropertyChangeCounter()
    {
        ++m_propertyChangeCounter;
    }

#ifdef KANZI_FEATURE_3D
    /// Acquires debug material (solid color variant).
    /// TODO: Remove when possible.
    static MaterialSharedPtr acquireDebugMaterialSolid(ResourceManager& resourceManager);
    /// Acquires debug material (textured variant).
    /// TODO: Remove when possible.
    static MaterialSharedPtr acquireDebugMaterialTextured(ResourceManager& resourceManager);
    /// Acquires error material.
    /// TODO: Remove when possible.
    static MaterialSharedPtr acquireErrorMaterial(ResourceManager& resourceManager);
    /// Tries to acquires error material.
    /// May return an empty shared pointer.
    /// TODO: Remove when possible.
    static MaterialSharedPtr tryAcquireErrorMaterial(ResourceManager& resourceManager);
    /// Acquires text material.
    /// TODO: Remove when possible.
    static MaterialSharedPtr acquireDefaultFontMaterial(ResourceManager& resourceManager);

#endif

    /// Factory function for Material Load Task, which loads a material from a kzb file.
    /// \param name Name of the material that you want to load.
    /// \param kzbFile Pointer to the instance of KzbFile, which holds the information about the kzb file.
    /// \param file Pointer to the instance of ReadOnlyMemoryFile, which wraps the kzb file.
    /// \return Shared pointer to the created load task.
    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

protected:
    /// Constructor.
    /// \param domain Domain to use.
    /// \param name Name of the material.
    Material(Domain* domain, string_view name);

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

private:
    /// Shader program used by the material.
    ShaderProgramSharedPtr m_shaderProgram;

    /// Counter for tracking property updates in material.
    /// Updated each time the properties in material are changed.
    /// #BrushRenderer and #MaterialRenderer store the last state of this counter to know when material has been updated.
    unsigned int m_propertyChangeCounter;
};

} // namespace kanzi

#endif // KZ_MATERIAL_HPP
