// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SCROLL_VIEW_CONCEPT_IMPL_HPP
#define KZ_SCROLL_VIEW_CONCEPT_IMPL_HPP

#include "scroll_view.hpp"

#include <kanzi/core.ui/animation/scenegraph_timeline_playback_context.hpp>
#include <kanzi/core.ui/animation/timeline_clock.hpp>
#include <kanzi/core.ui/domain/domain.hpp>


namespace kanzi
{

template <typename TBaseClass, class TDerivedClass>
const size_t ScrollViewConceptImpl<TBaseClass, TDerivedClass>::m_maxSpeedMeasurements = 30;

template <typename TBaseClass, class TDerivedClass>
const chrono::milliseconds ScrollViewConceptImpl<TBaseClass, TDerivedClass>::m_minMeasurementTime = chrono::milliseconds(3);

template <typename TBaseClass, class TDerivedClass>
const chrono::milliseconds ScrollViewConceptImpl<TBaseClass, TDerivedClass>::m_maxMeasurementTime = chrono::milliseconds(140);

template <typename TBaseClass, class TDerivedClass>
ScrollViewConceptImpl<TBaseClass, TDerivedClass>::ScrollViewConceptImpl(Domain* domain, string_view name) :
    TBaseClass(domain, name),
    m_panManipulator(PanManipulator::create(domain)),
    m_speedMeasurerX(m_maxSpeedMeasurements, m_minMeasurementTime, m_maxMeasurementTime),
    m_speedMeasurerY(m_maxSpeedMeasurements, m_minMeasurementTime, m_maxMeasurementTime),
    m_slideAccelerationCoefficient(0.0f),
    m_slideDragCoefficient(0.0f),
    m_dragAccelerationCoefficient(0.0f),
    m_dragDragCoefficient(0.0f),
    m_dragImpulseFactor(0.0f),
    m_swipeDistance(0.0f),
    m_scrollingMode(ScrollViewModeSlide),
    m_panEndMeasuredSpeedX(0.0f),
    m_panEndMeasuredSpeedY(0.0f),
    m_lastNonZeroSpeedX(0.0f),
    m_lastNonZeroSpeedY(0.0f),
    m_panState(PanInitial),
    m_scrollPositionX(0.0f, m_dragAccelerationCoefficient, m_dragDragCoefficient),
    m_scrollPositionY(0.0f, m_dragAccelerationCoefficient, m_dragDragCoefficient),
    m_previousZoom(1.0f),
    m_classValueHitTestable(*this, TBaseClass::HitTestableProperty, true),
    m_classValueHitTestableContainer(*this, TBaseClass::HitTestableContainerProperty, true)
{
    getThisObject()->addInputManipulator(m_panManipulator);

    // Create timeline for scrolling.
    m_scrollViewTimeline = make_polymorphic_shared_ptr<ScrollViewTimeline>(new ScrollViewTimeline(*this));

    m_scrollPositionX.setLooping(isLoopingXEnabled());
    m_scrollPositionY.setLooping(isLoopingYEnabled());

    // Update scrolling configuration.
    refreshScrollConfiguration();

    // Update recognition threshold.
    refreshThreshold();

    // Update minimum number of touch points
    refreshMinimumNumberOfTouches();

    // Update maximum number of touch points
    refreshMaximumNumberOfTouches();
}

template <typename TBaseClass, class TDerivedClass>
PanManipulatorSharedPtr ScrollViewConceptImpl<TBaseClass, TDerivedClass>::getPanManipulator() const
{
    return m_panManipulator;
}

template <typename TBaseClass, class TDerivedClass>
PropertyTypeEditorInfoSharedPtr ScrollViewConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Scroll View";

                return dict;
            }()
        ));
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);

    if (propertyType == RecognitionThresholdProperty)
    {
        refreshThreshold();
    }
    else if (propertyType == MinimumNumberOfTouchesProperty)
    {
        refreshMinimumNumberOfTouches();
    }
    else if (propertyType == MaximumNumberOfTouchesProperty)
    {
        refreshMaximumNumberOfTouches();
    }
    else if (propertyType == ScrollBoundsMinimumProperty)
    {
        Vector2 propertyValue = getScrollBoundsMinimum();

        // Set lower limit for interpolated values for scrolling.
        m_scrollPositionX.setMinimumValue(propertyValue.getX());
        m_scrollPositionY.setMinimumValue(propertyValue.getY());
    }
    else if (propertyType == ScrollBoundsMaximumProperty)
    {
        Vector2 propertyValue = getScrollBoundsMaximum();

        // Set upper limit for interpolated values for scrolling.
        m_scrollPositionX.setMaximumValue(propertyValue.getX());
        m_scrollPositionY.setMaximumValue(propertyValue.getY());
    }
    else if (propertyType == ZoomEnabledProperty)
    {
        TDerivedClass* self = getThisObject();

        if (isZoomEnabled())
        {
            if (!m_pinchManipulator)
            {
                m_pinchManipulator = PinchManipulator::create(self->getDomain());
                self->addInputManipulator(m_pinchManipulator);
                self->setProperty(ZoomProperty, getZoom());

                self->addMessageHandler(PinchManipulator::StartedMessage, self, &TDerivedClass::pinchBeginHandler);
                self->addMessageHandler(PinchManipulator::MovedMessage, self, &TDerivedClass::pinchMoveHandler);
                self->addMessageHandler(PinchManipulator::FinishedMessage, self, &TDerivedClass::pinchEndHandler);
            }
        }
        else
        {
            if (m_pinchManipulator)
            {
                getThisObject()->removeInputManipulator(*m_pinchManipulator);
                m_pinchManipulator.reset();
            }
        }
    }
    else if (propertyType == LoopingXEnabledProperty)
    {
        m_scrollPositionX.setLooping(isLoopingXEnabled());
    }
    else if (propertyType == LoopingYEnabledProperty)
    {
        m_scrollPositionY.setLooping(isLoopingYEnabled());
    }
    else if (propertyType == AllowedScrollAxisProperty)
    {
        refreshThreshold();
    }
}

template <typename TBaseClass, class TDerivedClass>
ScrollViewConceptImpl<TBaseClass, TDerivedClass>::~ScrollViewConceptImpl()
{
    // Stop scroll updating timer.
    stopUpdate();

    // Remove timer handler if it exists.
    unsubscribePanInertiaTimeoutHandler();
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::initialize()
{
    TBaseClass::initialize();

    TDerivedClass* node = getThisObject();

    node->addMessageHandler(PanManipulator::StartedMessage, node, &TDerivedClass::panBeginHandler);
    node->addMessageHandler(PanManipulator::MovedMessage, node, &TDerivedClass::panMoveHandler);
    node->addMessageHandler(PanManipulator::FinishedMessage, node, &TDerivedClass::panEndHandler);

    node->addMessageHandler(SetScrollTargetMessage, node, &TDerivedClass::setScrollTargetHandler);
    node->addMessageHandler(SetScrollMessage, node, &TDerivedClass::setScrollHandler);

    node->addMessageHandler(Keyboard::KeyDownMessage, node, &TDerivedClass::onKeyDown);

    node->addMessageHandler(ScrollDirectionMessage, node, &TDerivedClass::scrollDirectionMessageHandler);
    node->addMessageHandler(ScrollPageMessage, node, &TDerivedClass::scrollPageMessageHandler);
    node->addMessageHandler(ScrollEdgeMessage, node, &TDerivedClass::scrollEdgeMessageHandler);
}

template <typename TBaseClass, typename TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::onKeyDown(Keyboard::KeyDownMessageArguments& arguments)
{
    KzsInputKey key = arguments.getKey();
    switch (key)
    {
        case KZS_KEY_ARROW_UP:
        {
            scroll(ScrollUp);
            break;
        }
        case KZS_KEY_ARROW_DOWN:
        {
            scroll(ScrollDown);
            break;
        }
        case KZS_KEY_ARROW_LEFT:
        {
            scroll(ScrollLeft);
            break;
        }
        case KZS_KEY_ARROW_RIGHT:
        {
            scroll(ScrollRight);
            break;
        }
        case KZS_KEY_PAGE_UP:
        {
            scroll(ScrollPageUp);
            break;
        }
        case KZS_KEY_PAGE_DOWN:
        {
            scroll(ScrollPageDown);
            break;
        }
        case KZS_KEY_HOME:
        {
            scroll(ScrollHome);
            break;
        }
        case KZS_KEY_END:
        {
            scroll(ScrollEnd);
            break;
        }
        default:
        {
            arguments.setHandled(false);
            return;
        }
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scroll(ScrollDirection direction)
{
    if (isDragging())
    {
        return;
    }

    Vector2 scrollBoundsMaximum = getScrollBoundsMaximum();
    Vector2 scrollBoundsMinimum = getScrollBoundsMinimum();

    const float step = getThisObject()->getStepMultiplier();
    float newTargetX = m_scrollPositionX.getTarget();
    float newTargetY = m_scrollPositionY.getTarget();

    switch (direction)
    {
        case ScrollUp:
        {
            newTargetY -= TBaseClass::layoutUp() * (getThisObject()->getActualSize().getY() * step);
            break;
        }
        case ScrollDown:
        {
            newTargetY += TBaseClass::layoutUp() * (getThisObject()->getActualSize().getY() * step);
            break;
        }
        case ScrollLeft:
        {
            newTargetX += getThisObject()->getActualSize().getX() * step;
            break;
        }
        case ScrollRight:
        {
            newTargetX -= getThisObject()->getActualSize().getX() * step;
            break;
        }
    }

    Vector2 scrollTarget = componentWiseMin(componentWiseMax(Vector2(newTargetX, newTargetY), scrollBoundsMinimum), scrollBoundsMaximum);
    scrollToPosition(scrollTarget);
}


template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scroll(ScrollPage direction)
{
    if (isDragging())
    {
        return;
    }

    Vector2 scrollBoundsMaximum = getScrollBoundsMaximum();
    Vector2 scrollBoundsMinimum = getScrollBoundsMinimum();
    float newTargetY = m_scrollPositionY.getTarget();

    switch (direction)
    {
        case ScrollPageUp:
        {
            newTargetY -= TBaseClass::layoutUp() * getThisObject()->getActualSize().getY();
            break;
        }
        case ScrollPageDown:
        {
            newTargetY += TBaseClass::layoutUp() * getThisObject()->getActualSize().getY();
            break;
        }
    }

    float clampedTargetY = min(scrollBoundsMaximum.getY(), max(scrollBoundsMinimum.getY(), newTargetY));
    scrollToPosition(Vector2(m_scrollPositionX.getTarget(), clampedTargetY));
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scroll(ScrollEdge direction)
{
    if (isDragging())
    {
        return;
    }

    Vector2 scrollBoundsMinimum = getScrollBoundsMinimum();
    Vector2 scrollBoundsMaximum = getScrollBoundsMaximum();
    if (scrollBoundsMinimum == scrollBoundsMaximum)
    {
        return;
    }

    float homeY = scrollBoundsMinimum.getY();
    float endY = scrollBoundsMaximum.getY() - getThisObject()->getActualSize().getY();

    Vector2 newTarget;
    switch (direction)
    {
        case ScrollHome:
        {
            if (TBaseClass::layoutUp() >= 0.0f)
            {
                newTarget = Vector2(scrollBoundsMinimum.getX(), homeY);
            }
            else
            {
                newTarget = Vector2(scrollBoundsMinimum.getX(), endY);
            }
            break;
        }
        case ScrollEnd:
        {
            if (TBaseClass::layoutUp() >= 0.0f)
            {
                newTarget = Vector2(scrollBoundsMaximum.getX(), endY);
            }
            else
            {
                newTarget = Vector2(scrollBoundsMaximum.getX(), homeY);
            }
            break;
        }
    }

    if (newTarget != getScrollTarget())
    {
        scrollToPosition(newTarget);
    }
}

template <typename TBaseClass, class TDerivedClass>
bool ScrollViewConceptImpl<TBaseClass, TDerivedClass>::isDragging() const
{
    return (m_scrollingMode == ScrollViewModeDrag);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::setEnabledX(bool state)
{
    if (state)
    {
        setAllowedScrollAxis(isEnabledY() ? AllAxes : XAxis);
    }
    else
    {
        setAllowedScrollAxis(isEnabledY() ? YAxis : AllAxes);
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::setEnabledY(bool state)
{
    if (state)
    {
        setAllowedScrollAxis(isEnabledX() ? AllAxes : YAxis);
    }
    else
    {
        setAllowedScrollAxis(isEnabledX() ? XAxis : AllAxes);
    }
}

template <typename TBaseClass, class TDerivedClass>
bool ScrollViewConceptImpl<TBaseClass, TDerivedClass>::isEnabledX() const
{
    return (getAllowedScrollAxis() & XAxis) == XAxis;
}

template <typename TBaseClass, class TDerivedClass>
bool ScrollViewConceptImpl<TBaseClass, TDerivedClass>::isEnabledY() const
{
    return (getAllowedScrollAxis() & YAxis) == YAxis;
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::setScrollBoundsX(float minimum, float maximum)
{
    Vector2 scrollBoundsMinimum = getScrollBoundsMinimum();
    Vector2 scrollBoundsMaximum = getScrollBoundsMaximum();

    scrollBoundsMinimum.setX(minimum);
    scrollBoundsMaximum.setX(maximum);

    setScrollBoundsMinimum(scrollBoundsMinimum);
    setScrollBoundsMaximum(scrollBoundsMaximum);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::setScrollBoundsY(float minimum, float maximum)
{
    Vector2 scrollBoundsMinimum = getScrollBoundsMinimum();
    Vector2 scrollBoundsMaximum = getScrollBoundsMaximum();

    scrollBoundsMinimum.setY(minimum);
    scrollBoundsMaximum.setY(maximum);

    setScrollBoundsMinimum(scrollBoundsMinimum);
    setScrollBoundsMaximum(scrollBoundsMaximum);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::jumpToPosition(Vector2 scrollPosition)
{
    float targetX = scrollPosition.getX();
    float targetY = scrollPosition.getY();

    // Apply scroll.
    AllowedScrollAxis gestures = getAllowedScrollAxis();
    if (gestures & XAxis)
    {
        m_scrollPositionX.setValue(targetX, true);
    }

    if (gestures & YAxis)
    {
        m_scrollPositionY.setValue(targetY, true);
    }

    // Start updating interpolator so that scrolled message is sent only between start scroll and end scroll.
    startUpdate();

    // Update values and send scrolled message.
    updateScroll();
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scrollToPosition(Vector2 scrollPosition)
{
    float targetX = scrollPosition.getX();
    float targetY = scrollPosition.getY();

    // Apply scroll target.
    AllowedScrollAxis gestures = getAllowedScrollAxis();
    if (gestures & XAxis)
    {
        m_scrollPositionX.setTarget(targetX);
    }

    if (gestures & YAxis)
    {
        m_scrollPositionY.setTarget(targetY);
    }

    if (!m_scrollPositionX.interpolationEnded() || !m_scrollPositionY.interpolationEnded())
    {
        // Start updating interpolator.
        startUpdate();
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scrollToPositionLooping(Vector2 scrollPosition)
{
    Vector2 correctedTarget = scrollPosition;

    // Correct the target to take the shortest path.

    AllowedScrollAxis gestures = getAllowedScrollAxis();
    // X axis.
    if ((gestures & XAxis) && m_scrollPositionX.isLooping())
    {
        float period = m_scrollPositionX.getMaximumValue() - m_scrollPositionX.getMinimumValue();
        float normalizedTarget = m_scrollPositionX.getTarget();
        float newTarget = scrollPosition.getX();
        float distanceLeft = abs(normalizedTarget + period - newTarget);
        float distanceCurrent = abs(normalizedTarget - newTarget);
        float distanceRight = abs(normalizedTarget - period - newTarget);

        if (distanceLeft < distanceCurrent && distanceLeft < distanceRight)
        {
            correctedTarget.setX(newTarget - period);
        }
        else if (distanceRight < distanceCurrent)
        {
            correctedTarget.setX(newTarget + period);
        }
    }

    // Y axis.
    if ((gestures & YAxis) && m_scrollPositionY.isLooping())
    {
        float period = m_scrollPositionY.getMaximumValue() - m_scrollPositionY.getMinimumValue();
        float normalizedTarget = m_scrollPositionY.getTarget();
        float newTarget = scrollPosition.getY();
        float distanceLeft = abs(normalizedTarget + period - newTarget);
        float distanceCurrent = abs(normalizedTarget - newTarget);
        float distanceRight = abs(normalizedTarget - period - newTarget);

        if (distanceLeft < distanceCurrent && distanceLeft < distanceRight)
        {
            correctedTarget.setY(newTarget - period);
        }
        else if (distanceRight < distanceCurrent)
        {
            correctedTarget.setY(newTarget + period);
        }
    }

    scrollToPosition(correctedTarget);
}

template <typename TBaseClass, class TDerivedClass>
Vector2 ScrollViewConceptImpl<TBaseClass, TDerivedClass>::getScroll() const
{
    const float x = m_scrollPositionX.getValue();
    const float y = m_scrollPositionY.getValue();

    return Vector2(x, y);
}

template <typename TBaseClass, class TDerivedClass>
Vector2 ScrollViewConceptImpl<TBaseClass, TDerivedClass>::getScrollTarget() const
{
    const float x = m_scrollPositionX.getTargetNonNormalized();
    const float y = m_scrollPositionY.getTargetNonNormalized();

    return Vector2(x, y);
}

template <typename TBaseClass, class TDerivedClass>
Vector2 ScrollViewConceptImpl<TBaseClass, TDerivedClass>::getScrollTargetLooping() const
{
    const float x = m_scrollPositionX.getTarget();
    const float y = m_scrollPositionY.getTarget();

    return Vector2(x, y);
}

template <typename TBaseClass, class TDerivedClass>
Vector2 ScrollViewConceptImpl<TBaseClass, TDerivedClass>::getSpeed() const
{
    const float x = m_scrollPositionX.getSpeed();
    const float y = m_scrollPositionY.getSpeed();

    return Vector2(x, y);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::refreshScrollConfiguration()
{
    // Read values.
    m_slideAccelerationCoefficient = getSlidingAccelerationCoefficient();
    m_slideDragCoefficient = getSlidingDragCoefficient();
    m_dragAccelerationCoefficient = getDraggingAccelerationCoefficient();
    m_dragDragCoefficient = getDraggingDragCoefficient();
    m_dragImpulseFactor = getDraggingImpulseFactor();
    m_swipeDistance = getSwipeDistance();

    // Update values.
    if (isDragging())
    {
        m_scrollPositionX.initializeBoundMode(m_dragAccelerationCoefficient, m_dragDragCoefficient);
        m_scrollPositionY.initializeBoundMode(m_dragAccelerationCoefficient, m_dragDragCoefficient);
    }
    else if (m_scrollingMode == ScrollViewModeSlide)
    {
        m_scrollPositionX.initializeBoundMode(m_slideAccelerationCoefficient, m_slideDragCoefficient);
        m_scrollPositionY.initializeBoundMode(m_slideAccelerationCoefficient, m_slideDragCoefficient);
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::refreshThreshold()
{    
    float threshold = getThisObject()->getProperty(RecognitionThresholdProperty);

    AllowedScrollAxis gestures = getAllowedScrollAxis();
    // X only.
    if (gestures == XAxis)
    {
        m_panManipulator->setRecognitionThreshold(Vector2(threshold, TBaseClass::unboundedLayoutValue()));
    }
    // Y only.
    else if (gestures == YAxis)
    {
        m_panManipulator->setRecognitionThreshold(Vector2(TBaseClass::unboundedLayoutValue(), threshold));
    }
    else
    {
        // Fallback is to not use directional pan threshold.
        m_panManipulator->setRecognitionThreshold(Vector2(threshold, threshold));
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::refreshMinimumNumberOfTouches()
{
    optional<int> minimumNumberOfTouches = getThisObject()->getOptionalProperty(MinimumNumberOfTouchesProperty);
    if (minimumNumberOfTouches)
    {
        m_panManipulator->setMinimumNumberOfTouches(*minimumNumberOfTouches);

        // Enable tunneling routing mode when minimum number of touches is greater than one.
        m_panManipulator->setTouchEventRoutingMode((*minimumNumberOfTouches > 1) ? InputManipulator::RoutingTunneling : InputManipulator::RoutingBubbling);
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::refreshMaximumNumberOfTouches()
{
    optional<int> maximumNumberOfTouches = getThisObject()->getOptionalProperty(MaximumNumberOfTouchesProperty);
    if (maximumNumberOfTouches)
    {
        m_panManipulator->setMaximumNumberOfTouches(*maximumNumberOfTouches);
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::panInertiaTimeoutHandler(weak_ptr<TDerivedClass> object)
{
    shared_ptr<TDerivedClass> node = object.lock();
    if (node)
    {
        node->cancelInertia();
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::cancelInertia()
{
    // Only do anything if there is inertia but no pan gesture is in progress.
    if (m_panState == PanInitial)
    {
        Vector2 current(m_scrollPositionX.getValue(), m_scrollPositionY.getValue());
        Vector2 target(m_scrollPositionX.getTarget(), m_scrollPositionY.getTarget());

        if (current != target)
        {
            m_panState = PanCancelling;
        }
    }

    unsubscribePanInertiaTimeoutHandler();
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::unsubscribePanInertiaTimeoutHandler()
{
    if (m_panInertiaTimeoutSubscription)
    {
        removeTimerHandler(getThisObject()->getMessageDispatcher(), m_panInertiaTimeoutSubscription);
        m_panInertiaTimeoutSubscription.reset();
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::panBeginHandler(PanManipulator::StartedMessageArguments& arguments)
{
    // Reset pan status.
    m_panState = PanInitial;
    m_scrollingMode = ScrollViewModeDrag;

    // Unsubscribe earlier handler if it exists.
    unsubscribePanInertiaTimeoutHandler();
    // Add timer to stop scrolling if pan has not been started in time. 
    {
        shared_ptr<TDerivedClass> sharedReference = static_pointer_cast<TDerivedClass>(getThisObject()->shared_from_this());
        weak_ptr<TDerivedClass> weakReference(sharedReference);

        m_panInertiaTimeoutSubscription = addTimerHandler(getThisObject()->getMessageDispatcher(), chrono::milliseconds(250), KZU_TIMER_MESSAGE_MODE_ONCE,
                                                          bind(&TDerivedClass::panInertiaTimeoutHandler, weakReference));
    }

    // Get current time.
    chrono::milliseconds messageTime = arguments.getTimestamp();

    // Get local point.
    optional<Vector2> panPosition = getThisObject()->calculatePanPosition(arguments);

    // Initialize speed measurers.
    m_speedMeasurerX.reset();
    m_speedMeasurerY.reset();
    if (panPosition)
    {
        if (isZoomAffectsScrolling())
        {
            *panPosition /= getZoom();
        }

        m_speedMeasurerX.addMeasurement(messageTime, panPosition->getX());
        m_speedMeasurerY.addMeasurement(messageTime, panPosition->getY());
        m_previousPanPosition = *panPosition;
    }

    // Notice: Interpolators are reset only at pan move.

    // Reset last non-zero speed.
    m_lastNonZeroSpeedX = 0.0f;
    m_lastNonZeroSpeedY = 0.0f;

    // User scroll started.
    sendUserScrollStartedMessage();
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::panMoveHandler(PanManipulator::MovedMessageArguments& arguments)
{
    // Mark pan as started.
    if (m_panState != PanStarted)
    {
        m_panState = PanStarted;

        // Update scrolling configuration.
        refreshScrollConfiguration();

        AllowedScrollAxis gestures = getAllowedScrollAxis();
        float scrollX = ((gestures & XAxis) ? m_scrollPositionX.getValue() : 0.0f);
        float scrollY = ((gestures & YAxis) ? m_scrollPositionY.getValue() : 0.0f);
        m_scrollPositionX.setTarget(scrollX);
        m_scrollPositionY.setTarget(scrollY);
    }

    // Get current time.
    chrono::milliseconds messageTime = arguments.getTimestamp();

    // Get local point on pan plane.
    optional<Vector2> panPosition = getThisObject()->calculatePanPosition(arguments);
    if (panPosition)
    {
        if (isZoomAffectsScrolling())
        {
            *panPosition /= getZoom();
        }

        // Get amount of pan that happened in this update.
        Vector2 panOffset = *panPosition - m_previousPanPosition;

        AllowedScrollAxis gestures = getAllowedScrollAxis();
        // Update target for position interpolator.
        if (gestures & XAxis)
        {
            m_scrollPositionX.modifyTarget(panOffset.getX());
            m_scrollPositionX.modifySpeed(panOffset.getX() * m_dragImpulseFactor);
        }
        if (gestures & YAxis)
        {
            m_scrollPositionY.modifyTarget(panOffset.getY());
            m_scrollPositionY.modifySpeed(panOffset.getY() * m_dragImpulseFactor);
        }

        // Add pointing device speed measurement.
        if (gestures & XAxis)
        {
            m_speedMeasurerX.addMeasurement(messageTime, panPosition->getX());
        }
        if (gestures & YAxis)
        {
            m_speedMeasurerY.addMeasurement(messageTime, panPosition->getY());
        }

        // Update last non-zero speed.
        optional<float> speedX = m_speedMeasurerX.getSpeed(messageTime);
        optional<float> speedY = m_speedMeasurerY.getSpeed(messageTime);

        if (((gestures & XAxis) && speedX && abs(*speedX) >= numeric_limits<float>::epsilon()) ||
            ((gestures & YAxis) && speedY && abs(*speedY) >= numeric_limits<float>::epsilon()))
        {
            m_lastNonZeroSpeedX = speedX.value_or(0.0f);
            m_lastNonZeroSpeedY = speedY.value_or(0.0f);
        }

        // Start interpolator if it is not started yet or has stopped.
        startUpdate();

        m_previousPanPosition = *panPosition;
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::panEndHandler(PanManipulator::FinishedMessageArguments& arguments)
{
    chrono::milliseconds messageTime = arguments.getTimestamp();

    // Unsubscribe earlier handler if it still exists.
    unsubscribePanInertiaTimeoutHandler();

    // Drag ended.
    sendUserScrollEndedMessage();

    // Only change target if there was movement or if inertia was canceled.
    if (m_panState != PanInitial)
    {
        // Save measured speeds.
        // If pointer speed is zero, scrolling target is taken from current scroll position.
        // If there is any current scrolling speed, this will cause some oscillation.
        optional<float> speedX = m_speedMeasurerX.getSpeed(messageTime);
        optional<float> speedY = m_speedMeasurerY.getSpeed(messageTime);

        m_panEndMeasuredSpeedX = speedX.value_or(0.0f);
        m_panEndMeasuredSpeedY = speedY.value_or(0.0f);

        // Calculate scrolling target.
        // Get position.
        float positionX = m_scrollPositionX.getValue();
        float positionY = m_scrollPositionY.getValue();
        Vector2 currentPosition(positionX, positionY);

        // Calculate acceleration.
        Vector2 speed(m_panEndMeasuredSpeedX, m_panEndMeasuredSpeedY);

        float velocity = speed.length();
        float velocityScale = m_swipeDistance * velocity;

        Vector2 difference = speed * velocityScale;
        Vector2 endingPosition = currentPosition + difference;

        // Set target to the new value.
        scrollToPosition(endingPosition);

        // Enforce bounds by default, unless overridden by snap request.
        m_scrollPositionX.enforceBounds();
        m_scrollPositionY.enforceBounds();

        // Send snap request message.
        SnapRequestMessageArguments snapRequest;
        snapRequest.setSnapPosition(endingPosition);
        snapRequest.setSnapDirection(Vector2(m_lastNonZeroSpeedX, m_lastNonZeroSpeedY));

        getThisObject()->dispatchMessage(SnapRequestMessage, snapRequest);

        // Start interpolator if it is not started yet or has stopped.
        startUpdate();
    }

    // Reset bound mode config.
    m_scrollingMode = ScrollViewModeSlide;

    refreshScrollConfiguration();
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::pinchBeginHandler(PinchManipulator::StartedMessageArguments&)
{
    if (!m_pinchManipulator)
    {
        return;
    }

    m_previousZoom = getZoom();
    m_previousScrollPosition = getScroll();
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::pinchMoveHandler(PinchManipulator::MovedMessageArguments& arguments)
{
    if (!m_pinchManipulator)
    {
        return;
    }

    // Get local point on the plane.
    optional<Vector2> panPosition = getThisObject()->calculatePanPosition(arguments);
    if (panPosition)
    {
        float zoom = clamp(m_previousZoom * arguments.getScale(), getZoomMinimum(), getZoomMaximum());
        getThisObject()->setProperty(ZoomProperty, zoom);

        if (isZoomAffectsScrolling())
        {
            *panPosition /= zoom;
        }

        if (!m_previousPinchPosition)
        {
            // We need the middle point of the two touch points, but due to the input manipulators
            // limitation only the first touch point is reported in pinchBeginHandler().
            m_previousPinchPosition = panPosition;
        }
        else
        {
            m_scrollPositionX.setValue(m_previousScrollPosition.getX() + panPosition->getX() - m_previousPinchPosition->getX(), true);
            m_scrollPositionY.setValue(m_previousScrollPosition.getY() + panPosition->getY() - m_previousPinchPosition->getY(), true);

            updateScroll();
        }

        ZoomedMessageArguments zoomMessage;
        zoomMessage.setZoom(zoom);
        getThisObject()->dispatchMessage(ZoomedMessage, zoomMessage);
    }
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::pinchEndHandler(PinchManipulator::FinishedMessageArguments&)
{
    if (!m_pinchManipulator)
    {
        return;
    }

    m_previousPinchPosition = nullopt;
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::fillScrollMessageParameters(ScrollMessageArguments& arguments)
{
    Vector2 scrollPosition = getScroll();
    Vector2 scrollSpeed = getSpeed();

    arguments.setScrollPosition(scrollPosition);
    arguments.setScrollSpeed(scrollSpeed);

    // TODO: remove these two after Kanzi Studio gets better support for Vector2.
    arguments.setScrollPositionX(scrollPosition.getX());
    arguments.setScrollPositionY(scrollPosition.getY());
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::sendScrollStartedMessage()
{
    // Set property.
    getThisObject()->setProperty(ScrollingProperty, true);

    // Send message.
    ScrollStartedMessageArguments arguments;
    fillScrollMessageParameters(arguments);

    getThisObject()->dispatchMessage(ScrollStartedMessage, arguments);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::sendScrollEndedMessage()
{
    // Set property.
    getThisObject()->setProperty(ScrollingProperty, false);

    // Send message.
    ScrollFinishedMessageArguments arguments;
    fillScrollMessageParameters(arguments);

    getThisObject()->dispatchMessage(ScrollFinishedMessage, arguments);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::sendUserScrollStartedMessage()
{
    // Send message.
    UserScrollStartedMessageArguments arguments;
    fillScrollMessageParameters(arguments);

    getThisObject()->dispatchMessage(UserScrollStartedMessage, arguments);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::sendUserScrollEndedMessage()
{
    // Send message.
    UserScrollFinishedMessageArguments arguments;
    fillScrollMessageParameters(arguments);

    getThisObject()->dispatchMessage(UserScrollFinishedMessage, arguments);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::setScrollTargetHandler(SetScrollTargetMessageArguments& arguments)
{
    Vector2 scrollPosition = arguments.getScrollTarget();
    scrollToPosition(scrollPosition);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::setScrollHandler(SetScrollMessageArguments& arguments)
{
    Vector2 scrollPosition = arguments.getScrollPosition();
    jumpToPosition(scrollPosition);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scrollDirectionMessageHandler(ScrollDirectionMessageArguments& arguments)
{
    ScrollDirection direction = arguments.getScroll();
    scroll(direction);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scrollPageMessageHandler(ScrollPageMessageArguments& arguments)
{
    ScrollPage direction = arguments.getScroll();
    scroll(direction);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::scrollEdgeMessageHandler(ScrollEdgeMessageArguments& arguments)
{
    ScrollEdge direction = arguments.getScroll();
    scroll(direction);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::updateScroll()
{
    Vector2 scrollPosition = getScroll();
    Vector2 scrollSpeed = getSpeed();

    // Set properties.
    getThisObject()->setProperty(ScrollPositionProperty, scrollPosition);
    getThisObject()->setProperty(ScrollSpeedProperty, scrollSpeed);

    // Send messages.
    ScrolledMessageArguments arguments;
    fillScrollMessageParameters(arguments);

    getThisObject()->dispatchMessage(ScrolledMessage, arguments);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::onScrollViewTimelinePlaybackTick(chrono::milliseconds deltaTime)
{
    // Pan may be flagged as canceling.
    if (m_panState == PanCancelling)
    {
        m_panState = PanCanceled;
        scrollToPosition(getScroll());
    }

    // Stop playback if interpolation has ended.
    if (m_scrollPositionX.interpolationEnded() && m_scrollPositionY.interpolationEnded())
    {
        stopUpdate();
        return;
    }

    // Update scroll value.
    m_scrollPositionX.update(deltaTime);
    m_scrollPositionY.update(deltaTime);

    // Send scroll position.
    updateScroll();
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::startUpdate()
{
    if (!m_scrollViewTimelinePlayback)
    {
        Domain* domain = getThisObject()->getDomain();

        // Refresh scrolling configuration.
        refreshScrollConfiguration();

        // Send start scroll message.
        sendScrollStartedMessage();

        // Start scroll playback.
        SceneGraphTimelinePlaybackContext context(*getThisObject());
        m_scrollViewTimelinePlayback = m_scrollViewTimeline->createPlayback(context);
        domain->getRootTimelineClock()->addTimelinePlayback(m_scrollViewTimelinePlayback);
    }

    // Set scroll target property.
    Vector2 scrollTarget = getScrollTargetLooping();
    getThisObject()->setProperty(ScrollTargetPositionProperty, scrollTarget);
}

template <typename TBaseClass, class TDerivedClass>
void ScrollViewConceptImpl<TBaseClass, TDerivedClass>::stopUpdate()
{
    if (m_scrollViewTimelinePlayback)
    {
        // Stop scroll playback. Stopped playback will be eventually removed from the the clock.
        m_scrollViewTimelinePlayback->stop();
        m_scrollViewTimelinePlayback.reset();

        // Send end scroll message.
        sendScrollEndedMessage();
    }
}

}

#endif
