// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_PORTAL_LAYER_H
#define KZU_PORTAL_LAYER_H

#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/node/scene.hpp>


namespace kanzi
{

class Portal;
class Viewport2D;
class TransformedScene3D;


typedef shared_ptr<Portal> PortalSharedPtr;


/// Portal layer.
class KANZI_API Portal : public Node2D
{
public:
    KZ_METACLASS_BEGIN(Portal, Node2D, "Kanzi.PortalView")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Destructor.
    virtual ~Portal() {}

    /// Creates a Portal layer.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    static PortalSharedPtr create(Domain* domain, string_view name);

    /// Creates a Portal layer.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    /// \param width Node width.
    /// \param width Node height.
    static PortalSharedPtr create(Domain* domain, string_view name, float width, float height);

    /// Node2D::measure() implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;

    /// Node2D::renderSelfOverride() implementation.
    virtual void renderSelfOverride(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform) KZ_OVERRIDE;

    /// Access scene from portal layer.
    ///
    /// \return Scene shared pointer.
    SceneSharedPtr getScene() const
    {
        return m_scene;
    }

protected:
    /// Constructor.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    explicit Portal(Domain* domain, string_view name);

private:
    /// Refresh portal layer internals.
    void refresh();

    /// Refresh sub-rectangle of portal layer.
    ///
    /// \return True if sub-rectangle is enabled, false if not.
    bool refreshSubRectangle();

protected:
    ClassPropertyDefaultValue<bool> m_classValueSnapToPixelProperty;   ///< Default value for #LayerSnapToPixelProperty.

    Viewport2D* m_parentViewport;              /**< Viewport layer we're looking into. */
    SceneSharedPtr m_scene;                  /**< Scene acquired from an upper viewport layer. */ 
    TransformedScene3D* m_transformedScene; /**< Transformed scene acquired from an upper viewport layer. */
    KzcRectangle m_subRectangle;             /**< Cached sub-rectangle compared to parent. */
    bool m_subRectangleCached;               /**< Has sub-rectangle been calculated? */
    bool m_subRectangleEnabled;              /**< Axis-aligned, can draw using sub-rectangle. */
};

}

#endif

#endif  // KANZI_FEATURE_3D