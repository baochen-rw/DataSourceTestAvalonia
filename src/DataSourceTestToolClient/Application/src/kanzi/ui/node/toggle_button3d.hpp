// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_UI_TOGGLE_BUTTON_H
#define KZU_UI_TOGGLE_BUTTON_H


#include <kanzi/ui/node/concept/button.hpp>
#include <kanzi/core.ui/node/node3d.hpp>


namespace kanzi
{

class ToggleButton3D;

/// ToggleButton shared pointer.
typedef shared_ptr<ToggleButton3D> ToggleButton3DSharedPtr;


/// Toggle button node.
class KANZI_UI_API ToggleButton3D : public ButtonConceptImpl<Node3D, ToggleButton3D>
{
public:

    /// Button concept used to implement this class.
    typedef ButtonConceptImpl<Node3D, ToggleButton3D> ConceptClass;

    /// Creates a toggle button node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the toggle button.
    static ToggleButton3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(ToggleButton3D, ConceptClass, "Kanzi.ToggleButton3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit ToggleButton3D(Domain* domain, string_view name);

private:

    /// Default value for #ToggleStateCountProperty.
    ClassPropertyDefaultValue<int> m_classValueToggleStateCountProperty;
};

}
#endif
#endif
