// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for StackLayoutConcept.
// Do not include this file directly. Include stack_layout.hpp instead.



    /// Direction property.
    /// Defines the axis along which the stack layout arranges its items.
    /// The default value is StackLayoutConcept::DirectionX.
    /// \see setDirection(), getDirection()
    static PropertyType<StackLayoutConcept::LayoutDirection> DirectionProperty;


    /// Reversed property.
    /// Defines whether the stack layout arranges its items in reverse order.
    /// The default value is false.
    /// \see setReversed(), isReversed()
    static PropertyType<bool> ReversedProperty;


