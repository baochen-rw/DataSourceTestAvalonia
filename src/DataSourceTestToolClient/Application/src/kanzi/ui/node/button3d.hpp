// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_UI_BUTTON_H
#define KZU_UI_BUTTON_H

#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/button.hpp>

namespace kanzi
{

// Forward declarations.
class Button3D;

/// Button shared pointer.
typedef shared_ptr<Button3D> Button3DSharedPtr;


/// Button node.
class KANZI_UI_API Button3D : public ButtonConceptImpl<Node3D, Button3D>
{
public:

    /// Button concept used to implement this class.
    typedef ButtonConceptImpl<Node3D, Button3D> ConceptClass;

    /// Creates a button node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    static Button3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Button3D, ConceptClass, "Kanzi.Button3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit Button3D(Domain* domain, string_view name);
};

}

#endif

#endif  // KANZI_FEATURE_3D
