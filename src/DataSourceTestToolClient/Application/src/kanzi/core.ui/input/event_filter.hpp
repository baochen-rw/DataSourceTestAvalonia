// Copyright 2008-2021 by Rightware. All rights reserved.


#ifndef KZ_EVENT_FILTER_HPP
#define KZ_EVENT_FILTER_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core.ui/input/event_source_properties.hpp>
#include <kanzi/core/math/matrix3x3.hpp>

#include <kanzi/core.ui/platform/input/common/kzs_input.h>


namespace kanzi
{

/// EventFilter class.
///
/// Translates, orients, transforms and coalesces events.
class KANZI_API EventFilter
{
public:
    /// Constructor.
    explicit EventFilter(const EventSourceProperties& properties);

    /// Destructor.
    ~EventFilter();

    /// Filters events.
    ///
    /// The events in the given event queue are filtered based on the settings of the filter.
    /// \note The length of the event queue may be different after filtering.
    void process(struct KzsEventQueue& queue);

    /// Sets the transformation property.
    void setTransformation(const Matrix3x3& transformation);

protected:
    /// Discards events as specified by the constructor arguments.
    void processDiscardFilter(const struct KzsEventQueue& queueIn, struct KzsEventQueue& queueOut);

    /// Translation of input event coordinates.
    enum KzsInputTranslation m_eventTranslation;

    /// Input event area height
    Matrix3x3 m_eventTransformation;

    /// Buffer used during calculations.
    struct KzsEventQueue* m_eventQueueBuffer;

    /// Whether pointer events are discarded.
    bool m_discardPointerEvents;

    /// Whether touch events are discarded.
    bool m_discardTouchEvents;
};

}

#endif
