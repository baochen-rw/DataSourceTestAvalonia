// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GRID_LIST_BOX_CONCEPT_HPP
#define KZ_GRID_LIST_BOX_CONCEPT_HPP

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/ui/node/concept/grid_layout_concept.hpp>

namespace kanzi
{

/// Properties and messages for grid list boxes.
class KANZI_UI_API GridListBoxConcept
{
public:
    enum GridDirection
    {
        GridDirectionRight = GridLayoutConcept::GridDirectionRight, ///< Layout first right, then down.
        GridDirectionDown = GridLayoutConcept::GridDirectionDown    ///< Layout first down, then right.
    };

    /// \name Properties
    /// \{
#include "grid_list_box_properties.h"
    /// \}

    KZ_MIXIN_METACLASS_BEGIN(GridListBoxConcept, "Kanzi.GridListBoxConcept")
        KZ_METACLASS_PROPERTY_TYPE(DirectionProperty)
        KZ_METACLASS_PROPERTY_TYPE(CellWidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(CellHeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemAreaBeginProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemAreaEndProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollAxisProperty)
        KZ_METACLASS_PROPERTY_TYPE(RecognitionThresholdProperty)
        KZ_METACLASS_PROPERTY_TYPE(MinimumNumberOfTouchesProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaximumNumberOfTouchesProperty)
        KZ_METACLASS_PROPERTY_TYPE(SensitivityProperty)
        KZ_METACLASS_PROPERTY_TYPE(SlidingAccelerationCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(SlidingDragCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(DraggingAccelerationCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(DraggingDragCoefficientProperty)
        KZ_METACLASS_PROPERTY_TYPE(DraggingImpulseFactorProperty)
        KZ_METACLASS_PROPERTY_TYPE(SwipeDistanceProperty)
        KZ_METACLASS_PROPERTY_TYPE(CalculatedOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollPositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollTargetPositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollSpeedProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollingProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};
}


#endif
