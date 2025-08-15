// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SHADER_BRUSH_HPP
#define KZ_SHADER_BRUSH_HPP

#include <kanzi/core.ui/graphics2d/brush.hpp>
#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>
#include <kanzi/core.ui/graphics3d/material.hpp>
#include <kanzi/core/cpp/string_view.hpp>

namespace kanzi
{

// Forward declaration.
class MaterialBrush;

/// Shared pointer definition.
typedef shared_ptr<MaterialBrush> MaterialBrushSharedPtr;

/// Freeform shader brush.
class KANZI_API MaterialBrush : public Brush
{
public:

    /// \name Properties
    /// \{

    /// Material property.
    /// The default value is ResourceSharedPtr().
    /// \see setMaterial(), getMaterial()
    static PropertyType<ResourceSharedPtr> MaterialProperty;
    /// Gets the value of #MaterialProperty.
    /// \see setMaterial()
    ResourceSharedPtr getMaterial() const { return getProperty(MaterialProperty); }
    /// Sets the value of #MaterialProperty.
    /// \see getMaterial()
    void setMaterial(ResourceSharedPtr value) { setProperty(MaterialProperty, value); }

    /// \}

    KZ_METACLASS_BEGIN(MaterialBrush, Brush, "Kanzi.MaterialBrush")
        KZ_METACLASS_PROPERTY_TYPE(MaterialProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a new shader brush.
    ///
    /// Leaves all properties unset.
    ///
    /// \param domain uiDomain the brush belongs to.
    /// \param name of this texture brush.
    static MaterialBrushSharedPtr create(Domain* domain, string_view name);

    /// Create a new shader brush.
    ///
    /// Leaves all properties unset.
    ///
    /// \param domain uiDomain the brush belongs to.
    /// \param name of this texture brush.
    /// \param material Material to use.
    static MaterialBrushSharedPtr create(Domain* domain, string_view name, MaterialSharedPtr material);

    /// Brush::clone() implementation.
    virtual BrushSharedPtr clone() KZ_OVERRIDE;

    /// Brush::createBrushRenderer() implementation.
    virtual BrushRendererPtr createBrushRenderer(Node* node) KZ_OVERRIDE;

    /// Brush::load() implementation.
    virtual void load(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file) KZ_OVERRIDE;

protected:

    /// Constructor.
    /// Leaves all properties unset.
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush.
    explicit MaterialBrush(Domain* domain, string_view name) :
        Brush(domain, name)
    {
    }

    /// Constructor.
    /// Leaves all properties unset.
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush.
    /// \param material Material to use.
    explicit MaterialBrush(Domain* domain, string_view name, MaterialSharedPtr material) :
        Brush(domain, name)
    {
        setMaterial(material);
    }

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Refresh material.
    ///
    /// Re-acquires material resource from resource ID.
    ///
    /// \param resourceManager Resource manager to use for acquiring.
    void acquireMaterialResource(ResourceManager* resourceManager);

    /// Recalculate rendering properties.
    ///
    /// Must be called when a relevant property has been reassigned.
    void calculateRenderingProperties();

    /// Object::initialize() interface.
    void initialize();

private:

    /// Material in use.
    MaterialSharedPtr m_cachedMaterial;
};

}

#endif
