// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SLIDER_CONCEPT_HPP
#define KZ_SLIDER_CONCEPT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core/metadata/metaclass.hpp>
#include <kanzi/core/property/property_type.hpp>


namespace kanzi
{

/// SliderConcept contains the trajectory ResourceID property.
class KANZI_UI_API SliderConcept
{
public:
    /// \name Properties
    /// \{
#include "slider_properties.h"
    /// \}

    KZ_MIXIN_METACLASS_BEGIN(SliderConcept, "Kanzi.SliderConcept")
        KZ_METACLASS_PROPERTY_TYPE(MaxDistanceFromCurveProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};
}


#endif
