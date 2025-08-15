#ifndef KZ_EVENT_SOURCE_PROPERTIES_HPP
#define KZ_EVENT_SOURCE_PROPERTIES_HPP

#include <kanzi/core/math/matrix3x3.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>

namespace kanzi
{

/// Configurable event source properties.
struct EventSourceProperties
{
    /// Translation of events from one type to another.
    KzsInputTranslation translation;

    /// Transformation matrix for the event coordinates.
    Matrix3x3 transformation;

    /// Whether pointer events are discarded.
    /// The default value is false.
    bool discardPointerEvents;

    /// Whether touch events are discarded.
    /// The default value is false.
    bool discardTouchEvents;

    /// Input event device path.
    string inputEventDevice;

    /// Constructor.
    explicit EventSourceProperties() :
        translation(KZS_INPUT_TRANSLATE_NONE),
        transformation(Matrix3x3::createIdentity()),
        discardPointerEvents(false),
        discardTouchEvents(false)
    {
    }
};

}

#endif
