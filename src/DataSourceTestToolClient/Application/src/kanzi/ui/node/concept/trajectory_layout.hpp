// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TRAJECTORY_LAYOUT_HPP
#define KZ_TRAJECTORY_LAYOUT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>


namespace kanzi
{

/// TrajectoryLayoutConcept contains trajectory layout related properties.
class KANZI_UI_API TrajectoryLayoutConcept
{
public:

    /// \name Properties
    /// \{
#include "trajectory_layout_properties.h"
    /// \}

    KZ_MIXIN_METACLASS_BEGIN(TrajectoryLayoutConcept, "Kanzi.TrajectoryLayoutConcept")
        KZ_METACLASS_PROPERTY_TYPE(TrajectoryProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemAreaBeginProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemAreaEndProperty)
        KZ_METACLASS_PROPERTY_TYPE(OverrideDistanceProperty)
        KZ_METACLASS_PROPERTY_TYPE(StartOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(AlignToTangentProperty)
        KZ_METACLASS_PROPERTY_TYPE(CalculatedOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(OverrideOffsetProperty)
        KZ_METACLASS_PROPERTY_TYPE(StretchProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

}

#endif
