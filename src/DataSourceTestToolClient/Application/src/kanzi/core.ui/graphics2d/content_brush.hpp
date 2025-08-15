// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CONTENT_BRUSH_HPP
#define KZ_CONTENT_BRUSH_HPP

#include "color_brush.hpp"

namespace kanzi
{

// Forward declaration.
class ContentBrush;

/// Shared pointer type.
typedef shared_ptr<ContentBrush> ContentBrushSharedPtr;

/// Texture brush class.
///
/// Implements a textured brush used to fill areas with patterns.
class KANZI_API ContentBrush : public Brush
{
public:

    KZ_METACLASS_BEGIN(ContentBrush, Brush, "Kanzi.ContentBrush")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a new content brush.
    ///
    /// \param uiDomain uiDomain the brush belongs to.
    /// \param Name of this texture brush.
    static ContentBrushSharedPtr create(Domain* domain, string_view name);

    /// Brush::clone() implementation.
    virtual BrushSharedPtr clone() KZ_OVERRIDE;

    /// Brush::createBrushRenderer() implementation.
    virtual BrushRendererPtr createBrushRenderer(Node* node) KZ_OVERRIDE;

protected:

    /// Constructor.
    ///
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush.
    explicit ContentBrush(Domain* domain, string_view name) :
             Brush(domain, name) {}

    /// Calculate rendering properties for this.
    void calculateRenderingProperties();

    /// Object::initialize() interface.
    void initialize();
};

}

#endif
