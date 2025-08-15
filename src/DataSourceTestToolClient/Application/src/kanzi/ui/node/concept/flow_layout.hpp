// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FLOW_LAYOUT_HPP
#define KZ_FLOW_LAYOUT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>


namespace kanzi
{

/// Flow layout concept base class.
///
/// FlowLayoutConcept defines the data and property types used to implement a flow layout.
/// FlowLayoutConceptImpl derives from StackLayoutConcept to provide the functionality to implement a flow layout.
/// Do not use these classes directly. To use a flow layout in your application use FlowLayout3D or FlowLayout2D.
/// To implement a custom flow layout derive from FlowLayoutConceptImpl.
class KANZI_UI_API FlowLayoutConcept
{
public:

    /// Direction (or axis) of the layout, used in both primary and secondary direction.
    enum LayoutDirection
    {
        // X axis.
        /// Left to right direction.
        DirectionLeftToRight,
        /// Left to right direction.
        DirectionRightToLeft,
        // Y axis.
        /// Top to bottom direction.
        DirectionTopToBottom,
        /// Bottom to top direction.
        DirectionBottomToTop,
        // Z axis.
        /// Near to far direction.
        DirectionNearToFar,
        /// Far to near direction.
        DirectionFarToNear
    };

#include "flow_layout_properties.h"

    KZ_MIXIN_METACLASS_BEGIN(FlowLayoutConcept, "Kanzi.FlowLayoutConcept")
        KZ_METACLASS_PROPERTY_TYPE(PrimaryDirectionProperty)
        KZ_METACLASS_PROPERTY_TYPE(SecondaryDirectionProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

/// Flow layout concept implementation base class.
///
/// FlowLayoutConceptImpl provides the functionality to implement a flow layout.
/// FlowLayoutConceptImpl derives from FlowLayoutConcept, which defines the data and property types used by the implementation.
/// Do not use these classes directly. To use a flow layout in your application use FlowLayout3D or FlowLayout2D.
/// To implement a custom flow layout derive from FlowLayoutConceptImpl. The expected inheritance graph is TBaseClass <- FlowLayoutConceptImpl <- YourClass.
template <typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API FlowLayoutConceptImpl : public TBaseClass, public FlowLayoutConcept
{
    /// Internal accessor for curiously recurring template pattern.
    TDerivedClass* getThisObject();

    /// Internal accessor for curiously recurring template pattern.
    const TDerivedClass* getThisObject() const;

public:

    KZ_TEMPLATE_METACLASS_BEGIN(FlowLayoutConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(FlowLayoutConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of #PrimaryDirectionProperty.
    /// \see setPrimaryDirection()
    LayoutDirection getPrimaryDirection() const;
    /// Sets the value of #PrimaryDirectionProperty.
    /// \see getPrimaryDirection()
    void setPrimaryDirection(LayoutDirection value);

    /// Gets the value of #SecondaryDirectionProperty.
    /// \see setSecondaryDirection()
    LayoutDirection getSecondaryDirection() const;
    /// Sets the value of #SecondaryDirectionProperty.
    /// \see getSecondaryDirection()
    void setSecondaryDirection(LayoutDirection value);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit FlowLayoutConceptImpl(Domain* domain, string_view name);
};

}

#endif
