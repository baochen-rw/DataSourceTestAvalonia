// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_COMPOSITION_BRUSH_HPP
#define KZ_COMPOSITION_BRUSH_HPP


#include "content_brush.hpp"


namespace kanzi
{


// Forward declaration.
class CompositionBrush;


/// Shared pointer type.
typedef shared_ptr<CompositionBrush> CompositionBrushSharedPtr;


/// Texture brush class.
///
/// Implements a textured brush used to fill areas with patterns.
class KANZI_API CompositionBrush : public ContentBrush
{
public:

    KZ_METACLASS_BEGIN(CompositionBrush, ContentBrush, "Kanzi.CompositionBrush")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a new composition brush.
    ///
    /// Leaves all properties unset.
    ///
    /// \param uiDomain uiDomain the brush belongs to.
    /// \param Name of this texture brush.
    static CompositionBrushSharedPtr create(Domain* domain, string_view name);

    /// Brush::clone() implementation.
    virtual BrushSharedPtr clone() KZ_OVERRIDE;

    /// Brush::createBrushRenderer() implementation.
    virtual BrushRendererPtr createBrushRenderer(Node* node) KZ_OVERRIDE;

protected:
    /// Constructor.
    ///
    /// Leaves all properties unset.
    ///
    /// \param domain domain the brush belongs to.
    /// \param name Name of the brush.
    explicit CompositionBrush(Domain* domain, string_view name) :
             ContentBrush(domain, name) {}
};


}


#endif
