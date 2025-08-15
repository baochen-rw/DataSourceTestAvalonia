// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_COLOR_BRUSH_HPP
#define KZ_COLOR_BRUSH_HPP


#include "brush.hpp"
#include <kanzi/core.ui/platform/graphics_backend/gl/brush_renderer.hpp>
#include <kanzi/core/cpp/string_view.hpp>


namespace kanzi
{

// Forward declarations.
class ColorBrush;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;


typedef shared_ptr<ColorBrush> ColorBrushSharedPtr;


/// Color brush class.
///
/// Implements a solid-color brush used to fill areas.
class KANZI_API ColorBrush : public Brush
{
public:

    /// \name Properties
    /// \{

    /// Color property.
    /// \see setColor(), getColor()
    static PropertyType<ColorRGBA> ColorProperty;
    /// Gets the value of #ColorProperty.
    /// \see setColor()
    ColorRGBA getColor() const { return getProperty(ColorProperty); }
    /// Sets the value of #ColorProperty.
    /// \see getColor()
    void setColor(ColorRGBA value) { setProperty(ColorProperty, value); }

    /// \}

    KZ_METACLASS_BEGIN(ColorBrush, Brush, "Kanzi.ColorBrush")
        KZ_METACLASS_PROPERTY_TYPE(ColorProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a new color brush.
    ///
    /// Color assumes default property value.
    ///
    /// Default rendering is used.
    ///
    /// \param uiDomain uiDomain the brush belongs to.
    /// \param name Name of the color brush
    static ColorBrushSharedPtr create(Domain* domain, string_view name);

    // TODO pass color by value
    /// Create a new color brush.
    ///
    /// Default rendering is used.
    ///
    /// \param uiDomain uiDomain the brush belongs to.
    /// \param name Name of the color brush
    static ColorBrushSharedPtr create(Domain* domain, string_view name, const ColorRGBA& color);

    /// Brush::clone() implementation.
    virtual BrushSharedPtr clone() KZ_OVERRIDE;

    /// Brush::createBrushRenderer() implementation.
    virtual BrushRendererPtr createBrushRenderer(Node* node) KZ_OVERRIDE;

protected:

    /// Constructor.
    /// Leaves color unset.
    /// \param domain domain the brush belongs to.
    /// \param name Name of the color brush
    explicit ColorBrush(Domain* domain, string_view name) :
        Brush(domain, name)
    {
    }

    /// Constructor.
    /// \param domain domain the brush belongs to.
    /// \param name Name of the color brush
    /// \param color Color to use.
    explicit ColorBrush(Domain* domain, string_view name, const ColorRGBA& color) :
        Brush(domain, name)
    {
        setColor(color);
    }

    /// Object::onPropertyChanged() implementation.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Calculate rendering properties for this.
    void calculateRenderingProperties();

    /// Object::initialize() interface.
    void initialize();
};

}


#endif
