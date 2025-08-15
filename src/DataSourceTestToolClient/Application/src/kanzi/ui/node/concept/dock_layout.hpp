// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DOCK_LAYOUT_HPP
#define KZ_DOCK_LAYOUT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>


namespace kanzi
{

/// Dock layout concept base class.
///
/// DockLayoutConcept defines data and property types used to implement a dock layout.
/// DockLayoutConceptImpl derives from DockLayoutConcept to provide the functionality to implement a dock layout.
/// Do not use this class directly. To use a dock layout in your application use DockLayout2D or DockLayout3D.
/// To implement a custom dock layout derive from DockLayoutConceptImpl.
class KANZI_UI_API DockLayoutConcept
{
public:

    /// Docking side of dock layout item.
    enum DockingSide
    {
        /// Dock left.
        DockLeft,
        /// Dock right.
        DockRight,
        /// Dock top.
        DockTop,
        /// Dock bottom.
        DockBottom
    };

#include "dock_layout_properties.h"

    KZ_MIXIN_METACLASS_BEGIN(DockLayoutConcept, "Kanzi.DockLayoutConcept")
        KZ_METACLASS_PROPERTY_TYPE(LastItemFillProperty)
        KZ_METACLASS_ATTACHED_PROPERTY_TYPE(SideProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

/// Dock layout concept implementation base class.
///
/// DockLayoutConceptImpl provides functionality to implement a dock layout.
/// DockLayoutConceptImpl derives from DockLayoutConcept, which defines the data and property types used by the implementation.
/// Do not use this class directly. To use a dock layout in your application use DockLayout2D or DockLayout3D.
/// To implement a custom dock layout derive from DockLayoutConceptImpl. The expected inheritance graph is TBaseClass <- DockLayoutConceptImpl <- YourClass.
template <typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API DockLayoutConceptImpl : public TBaseClass, public DockLayoutConcept
{
    /// Internal accessor for curiously recurring template pattern.
    TDerivedClass* getThisObject();

    /// Internal accessor for curiously recurring template pattern.
    const TDerivedClass* getThisObject() const;

public:

    KZ_TEMPLATE_METACLASS_BEGIN(DockLayoutConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(DockLayoutConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of the DockLayoutConcept::LastItemFillProperty.
    /// \see setLastItemFill()
    bool isLastItemFill() const;
    /// Sets the value of DockLayoutConcept::LastItemFillProperty.
    void setLastItemFill(bool value);

    /// Gets the docking side of an item.
    /// \see DockLayoutConcept::DockingSide, DockLayoutConceptImpl::setSide()
    static DockingSide getSide(const Node& item);
    /// Sets the docking side of an item.
    /// \see DockLayoutConcept::DockingSide, DockLayoutConceptImpl::getSide()
    static void setSide(Node& item, DockingSide value);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit DockLayoutConceptImpl(Domain* domain, string_view name);
};

}

#endif
