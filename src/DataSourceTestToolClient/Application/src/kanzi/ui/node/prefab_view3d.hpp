// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_PREFAB_VIEW_3D_HPP
#define KZ_PREFAB_VIEW_3D_HPP


#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/prefab_view.hpp>

namespace kanzi
{

// Forward declarations.
class PrefabView3D;

/// Prefab view 3D shared pointer.
typedef shared_ptr<PrefabView3D> PrefabView3DSharedPtr;

/// Prefab view 3D node.
/// Use Prefab view 3D to switch 3D nodes at runtime.
///
/// Examples
/// ----
///
/// To use a Prefab view 3D node, create a prefab with 3D content and set it using `setPrefab()` :
/// \snippet kz_test_prefab_view.cpp Using PrefabView3D

class KANZI_UI_API PrefabView3D : public PrefabViewConceptImpl<Node3D, PrefabView3D>
{
public:

    /// Prefab view 3D concept used to implement this class.
    typedef PrefabViewConceptImpl<Node3D, PrefabView3D> ConceptClass;

    /// Creates a prefab view 3D node.
    /// \param domain The domain the new node belongs to.
    /// \param name The name of the node.
    static PrefabView3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(PrefabView3D, ConceptClass, "Kanzi.PrefabView3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The domain the new node belongs to.
    /// \param name The name of the node.
    explicit PrefabView3D(Domain* domain, string_view name);

    /// Node3D::measureOverride() implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;
};

}

#endif

#endif
