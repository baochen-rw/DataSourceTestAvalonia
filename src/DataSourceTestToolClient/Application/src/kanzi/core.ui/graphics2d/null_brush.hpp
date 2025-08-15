// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NULL_BRUSH_HPP
#define KZ_NULL_BRUSH_HPP


#include "brush.hpp"
#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>


namespace kanzi
{

// Forward declaration.
class NullBrush;


typedef shared_ptr<NullBrush> NullBrushSharedPtr;


/// Null brush class.
///
/// Never rendered, no matter what.
class KANZI_API NullBrush : public Brush
{
public:
    KZ_METACLASS_BEGIN(NullBrush, Brush, "Kanzi.NullBrush")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Create a new null brush.
    ///
    /// \param uiDomain uiDomain the brush belongs to.
    /// \param name Name of the null brush
    static NullBrushSharedPtr create(Domain* domain, string_view name);

    /// Brush::clone() implementation.
    virtual BrushSharedPtr clone() KZ_OVERRIDE;

    /// Brush::createBrushRenderer() implementation.
    virtual BrushRendererPtr createBrushRenderer(Node* node) KZ_OVERRIDE;

protected:
    /// Constructor.
    ///
    /// \param domain domain the brush belongs to.
    /// \param name Name of the null brush
    explicit NullBrush(Domain* domain, string_view name);
};


}


#endif
