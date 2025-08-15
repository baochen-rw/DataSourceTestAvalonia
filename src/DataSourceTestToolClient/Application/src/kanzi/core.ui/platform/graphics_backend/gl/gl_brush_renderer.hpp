// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_BRUSH_RENDERER_HPP
#define KZ_GL_BRUSH_RENDERER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/brush_renderer.hpp>

namespace kanzi
{

// Forward declarations.
class Material;
typedef shared_ptr<Material> MaterialSharedPtr;

/// OpenGL brush renderer specifics.
class KANZI_API GlBrushRenderer : public BrushRenderer
{
public:
    /// Constructor.
    ///
    /// \param node Node to attach to.
    /// \param brush Brush to attach to.
    explicit GlBrushRenderer(Brush* brush, Node* node) :
             BrushRenderer(brush, node) {}

    /// Destructor.
    virtual ~GlBrushRenderer() {}

    /// Acquire error material for rendering.
    ///
    /// To be used when the assigned material applicable.
    MaterialSharedPtr acquireErrorMaterial();
};

}

#endif
