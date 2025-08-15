// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BRUSH_HPP
#define KZ_BRUSH_HPP

#include <kanzi/core.ui/node/abstract_resource_reference.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/texture.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

namespace kanzi
{

// Forward declarations.
class Brush;
class BrushRenderer;
class KzbMemoryParser;
class ResourceManager;

/// Brush shared pointer.
typedef shared_ptr<Brush> BrushSharedPtr;

/// Brush renderer unique pointer.
typedef unique_ptr<BrushRenderer> BrushRendererPtr;

/// Brush class.
///
/// Implements a brush that can be used to fill areas, typically layer backgrounds.
class KANZI_API Brush : public Resource
{
public:
    /// \name Properties
    /// \{

    /// ModulateColor property.
    /// The default value is ColorRGBA(1.0f, 1.0f, 1.0f, 1.0f).
    /// \see setModulateColor(), getModulateColor()
    static PropertyType<ColorRGBA> ModulateColorProperty;
    /// Gets the value of #ModulateColorProperty.
    /// \see setModulateColor()
    ColorRGBA getModulateColor() const
    {
        return getProperty(ModulateColorProperty);
    }
    /// Sets the value of #ModulateColorProperty.
    /// \see getModulateColor()
    void setModulateColor(ColorRGBA value)
    {
        setProperty(ModulateColorProperty, value);
    }

    /// HorizontalTiling property.
    /// The default value is 1.0f.
    /// \see setHorizontalTiling(), getHorizontalTiling()
    static PropertyType<float> HorizontalTilingProperty;
    /// Gets the value of #HorizontalTilingProperty.
    /// \see setHorizontalTiling()
    float getHorizontalTiling() const
    {
        return getProperty(HorizontalTilingProperty);
    }
    /// Sets the value of #HorizontalTilingProperty.
    /// \see getHorizontalTiling()
    void setHorizontalTiling(float value)
    {
        setProperty(HorizontalTilingProperty, value);
    }

    /// VerticalTiling property.
    /// The default value is 1.0f.
    /// \see setVerticalTiling(), getVerticalTiling()
    static PropertyType<float> VerticalTilingProperty;
    /// Gets the value of #VerticalTilingProperty.
    /// \see setVerticalTiling()
    float getVerticalTiling() const
    {
        return getProperty(VerticalTilingProperty);
    }
    /// Sets the value of #VerticalTilingProperty.
    /// \see getVerticalTiling()
    void setVerticalTiling(float value)
    {
        setProperty(VerticalTilingProperty, value);
    }

    /// \}

    KZ_ABSTRACT_METACLASS_BEGIN(Brush, Object, "Kanzi.Brush")
        KZ_METACLASS_PROPERTY_TYPE(ModulateColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(HorizontalTilingProperty)
        KZ_METACLASS_PROPERTY_TYPE(VerticalTilingProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a brush renderer for this brush.
    ///
    /// \param node Node to attach to.
    /// \return Newly allocated brush renderer.
    virtual BrushRendererPtr createBrushRenderer(Node* node) = 0;

    /// Create clone of this brush.
    ///
    /// \return Shared pointer to clone of brush.
    virtual BrushSharedPtr clone() = 0;

    /// Perform brush-specific loading.
    ///
    /// \param inputStream Input stream to load from.
    /// \param file File to load from.
    virtual void load(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);
    /// Patch brush.
    ///
    /// \param inputStream Input stream to load from.
    /// \param file File to load from.
    virtual void previewPatch(struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

    /// Access property change counter.
    unsigned int getPropertyChangeCounter() const
    {
        return m_propertyChangeCounter;
    }
    /// Update property change counter.
    void updatePropertyChangeCounter()
    {
        ++m_propertyChangeCounter;
    }

    /// Access content texture.
    ///
    /// \return Content texture shared pointer.
    TextureSharedPtr getContentTexture() const
    {
        return m_contentTexture;
    }
    /// Set content texture.
    ///
    /// \return texture New content texture.
    void setContentTexture(TextureSharedPtr texture)
    {
        m_contentTexture = texture;
    }

    /// Get tiling vector.
    ///
    /// \return Tiling vector.
    Vector2 getTiling() const
    {
        return m_tiling;
    }

    /// Tell whether or not the brush needs rendering.
    ///
    /// \return True if yes, false if no.
    bool isRenderable() const
    {
        return m_renderable;
    }

    /// Tell if the brush is opaque.
    ///
    /// Brush may not need rendering but still not be considered opaque, for example if it is full transparent black.
    ///
    /// \return True if yes, false if no.
    bool isOpaque() const
    {
        return m_opaque;
    }

    /// Get null brush URL.
    static const char* getNullBrushUrl()
    {
        return "defaultresources://Brushes/NullBrush";
    }
    /// Acquire default null brush.
    static BrushSharedPtr acquireNullBrush(ResourceManager& resourceManager);

    /// Factory function for Brush Load Task, which loads a brush from a kzb file.
    /// \param name Name of the brush that you want to load.
    /// \param kzbFile Pointer to the instance of KzbFile, which holds the information about the kzb file.
    /// \param file Pointer to the instance of ReadOnlyMemoryFile, which wraps the kzb file.
    /// \return Shared pointer to the created load task.
    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

protected:
    /// Constructor.
    ///
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush
    explicit Brush(Domain* domain, string_view name);

    /// Destructor.
    virtual ~Brush()
    {
    }

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Set renderable status.
    ///
    /// \param renderable Does this brush need rendering?
    void setRenderable(bool renderable)
    {
        m_renderable = renderable;
    }

    /// Set opaqueness status.
    ///
    /// \param opaque Is this brush opaque?
    void setOpaque(bool opaque)
    {
        m_opaque = opaque;
    }

private:
    /// Content texture, if set.
    ///
    /// By default, content texture would be set into brush renderer, but it may be set into the brush itself.
    TextureSharedPtr m_contentTexture;

    /// Tiling coordinate multipliers in both directions.
    Vector2 m_tiling;

    /// Counter for tracking property updates in brush.
    /// Brush renderer stores last state of this counter to know when brush has been updated.
    unsigned int m_propertyChangeCounter;

    /// Flag for renderable status.
    bool m_renderable;

    /// Flag for opaqueness.
    bool m_opaque;
};
}

#endif
