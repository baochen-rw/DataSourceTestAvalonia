// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PREFAB_VIEW_2D_HPP
#define KZ_PREFAB_VIEW_2D_HPP


#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/prefab_view.hpp>

namespace kanzi
{

// Forward declarations.
class PrefabView2D;

/// Prefab view 2D shared pointer.
typedef shared_ptr<PrefabView2D> PrefabView2DSharedPtr;

/// Prefab view 2D node.
/// Use Prefab view 2D to switch 2D nodes at runtime.
///
/// Examples
/// ----
///
/// To use a Prefab view 2D node, create a prefab with 2D content and set it using `setPrefab()` :
/// \snippet kz_test_prefab_view.cpp Using PrefabView2D

class KANZI_UI_API PrefabView2D : public PrefabViewConceptImpl<Node2D, PrefabView2D>
{
public:

    /// Prefab view 2D concept used to implement this class.
    typedef PrefabViewConceptImpl<Node2D, PrefabView2D> ConceptClass;

    /// Creates a prefab view 2D node.
    /// \param domain The domain the new node belongs to.
    /// \param name The name of the node.
    static PrefabView2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(PrefabView2D, ConceptClass, "Kanzi.PrefabView2D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The domain the new node belongs to.
    /// \param name The name of the node.
    explicit PrefabView2D(Domain* domain, string_view name);

    /// Node2D::measureOverride() implementation.
    virtual Vector2 measureOverride(Vector2 availableSize) KZ_OVERRIDE;
};

}

#endif
