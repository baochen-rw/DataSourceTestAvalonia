// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STACK_LAYOUT_HPP
#define KZ_STACK_LAYOUT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>

namespace kanzi
{

/// Stack layout concept base class.
///
/// \note Do not use this class directly. To use a stack layout in your application use StackLayout3D or StackLayout2D.
///
/// StackLayoutConcept defines the data and property types used to implement a stack layout.
/// StackLayoutConceptImpl derives from StackLayoutConcept to provide the functionality to implement a stack layout.
/// To implement a custom stack layout derive from StackLayoutConceptImpl.
class KANZI_UI_API StackLayoutConcept
{
public:
    
    /// Direction in which stack layout arranges its items.
    enum LayoutDirection
    {
        DirectionX, ///< Arrange items along the x axis.
        DirectionY, ///< Arrange items along the y axis.
        DirectionZ  ///< Arrange items along the z axis.
    };

    static size_t directionToIndex(LayoutDirection direction)
    {
        switch (direction)
        {
            case StackLayoutConcept::DirectionX:
            {
                return 0;
            }
            case StackLayoutConcept::DirectionY:
            {
                return 1;
            }
            case StackLayoutConcept::DirectionZ:
            {
                return 2;
            }
        }

        // return some sane value
        return 0;
    }

    static size_t directionToOppositeIndex(LayoutDirection direction)
    {
        switch (direction)
        {
            case StackLayoutConcept::DirectionX:
            {
                return 1;
            }
            case StackLayoutConcept::DirectionY:
            {
                return 0;
            }
            case StackLayoutConcept::DirectionZ:
            {
                return 0;
            }
        }

        // return some sane value
        return 0;
    }

#include "stack_layout_properties.h"

    KZ_MIXIN_METACLASS_BEGIN(StackLayoutConcept, "Kanzi.StackLayoutConcept")
        KZ_METACLASS_PROPERTY_TYPE(DirectionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ReversedProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};


/// Stack layout concept implementation base class.
///
/// \note Do not use this class directly. To use a stack layout in your application use StackLayout3D or StackLayout2D.
///
/// StackLayoutConceptImpl provides the functionality to implement a stack layout.
/// StackLayoutConceptImpl derives from StackLayoutConcept, which defines the data and property types used by the implementation.
/// To implement a custom stack layout derive from StackLayoutConceptImpl. The expected inheritance graph is TBaseClass <- StackLayoutConceptImpl <- YourClass.
template<typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API StackLayoutConceptImpl : public TBaseClass, public StackLayoutConcept
{
    /// Internal accessor for the Curiously Recurring Template Pattern.
    TDerivedClass* getThisObject();

    /// Internal accessor for the Curiously Recurring Template Pattern.
    const TDerivedClass* getThisObject() const;

public:

    KZ_TEMPLATE_METACLASS_BEGIN(StackLayoutConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(StackLayoutConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of #DirectionProperty.
    /// \see setDirection()
    LayoutDirection getDirection() const;
    /// Sets the value of #DirectionProperty.
    /// \see getDirection()
    void setDirection(LayoutDirection value);

    /// Gets the value of #ReversedProperty.
    /// \see setReversed()
    bool isReversed() const;
    /// Sets the value of #ReversedProperty.
    /// \see isReversed()
    void setReversed(bool value);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit StackLayoutConceptImpl(Domain* domain, string_view name);
};

}

#endif
