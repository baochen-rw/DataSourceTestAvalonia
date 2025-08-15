// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SCROLL_VIEW_HPP
#define KZ_SCROLL_VIEW_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/animation/timeline.hpp>
#include <kanzi/core.ui/animation/timeline_playback.hpp>
#include <kanzi/core.ui/util/interpolated_value.hpp>
#include <kanzi/core.ui/util/speed_measurer.hpp>
#include <kanzi/core.ui/input/pan_manipulator.hpp>
#include <kanzi/core.ui/input/pinch_manipulator.hpp>
#include <kanzi/core.ui/input/keyboard.hpp>

#include <kanzi/core/message/message_type.hpp>
#include <kanzi/core/cpp/string_view.hpp>

namespace kanzi
{

/// ScrollViewConcept is the base class that provides the functionality for the ScrollView2D and ScrollView3D classes.
/// Both of these Scroll View types inherit the ScrollViewConceptImpl, a specialization of the base class:
/// - ScrollView2D inherits the ScrollViewConceptImpl specialization for the Node2D.
/// - ScrollView3D inherits the ScrollViewConceptImpl specialization for the Node3D.
///
/// Scroll View nodes provide an area that receives touch input which is translated to pan and zoom events. You
/// can listen and react to these events by subscribing to the messages that a Scroll View node sends.
/// You can scroll to a specific position in a Scroll View node by sending the Scroll View messages to that Scroll View node.
///
/// Some Kanzi nodes internally use a Scroll View to achieve a pannable area. For example, the
/// GridListBox2D and TrajectoryListBox3D nodes use a Scroll View.
///
/// \see For details and examples of how to use the Scroll View nodes, see ScrollView2D and ScrollView3D.
class KANZI_UI_API ScrollViewConcept
{
public:

    /// Enumeration for the available directions when scrolling by step.
    enum ScrollDirection
    {
        ScrollUp = 0,
        ScrollDown = 1,
        ScrollLeft = 2,
        ScrollRight = 3
    };

    /// Enumeration for AllowedScrollAxisProperty which sets the axis on which
    /// you want to allow a Scroll View node to scroll.
    enum AllowedScrollAxis
    {
        /// Allow scrolling only on the x axis.
        XAxis = 0x01,
        /// Allow scrolling only on the y axis.
        YAxis = 0x02,
        /// Allow scrolling on both the x and y axes.
        AllAxes = XAxis | YAxis
    };

    /// Enumeration for the available directions when scrolling a Scroll View node by page.
    enum ScrollPage
    {
        ScrollPageUp = 0,
        ScrollPageDown = 1
    };

    /// Enumeration for the available directions when scrolling to the edge of a Scroll View.
    enum ScrollEdge
    {
        ScrollHome = 0,
        ScrollEnd = 1
    };

    /// Enumeration for the state of pan.
    enum PanState
    {
        /// The initial pan state.
        PanInitial = 0,

        /// Pan started.
        PanStarted = 1,

        /// Pan is canceling.
        PanCancelling = 2,

        /// Pan canceled.
        PanCanceled = 3,
    };

    /// \name Properties
    /// \{

    /// Use the MessageArgumentScrollViewScrollPositionX argument to set the x axis coordinate for the new scroll
    /// position of a Scroll View node. Scroll position is a relative position within a Scroll View.
    /// The default value is 0.0f.
    /// \see ScrollMessageArguments::setScrollPositionX(), ScrollMessageArguments::getScrollPositionX()
    static PropertyType<float> MessageArgumentScrollViewScrollPositionXProperty;

    /// Use the MessageArgumentScrollViewScrollPositionY argument to set the y axis coordinate for the new scroll
    /// position of a Scroll View node. Scroll position is a relative position within a Scroll View.
    /// The default value is 0.0f.
    /// \see ScrollMessageArguments::setScrollPositionY(), ScrollMessageArguments::getScrollPositionY()
    static PropertyType<float> MessageArgumentScrollViewScrollPositionYProperty;

    /// Use the MessageArgumentScrollViewScrollPosition argument to set the x and y axis coordinates for the new
    /// scroll position of a Scroll View node. Scroll position is a relative position within a Scroll View.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollMessageArguments::setScrollPosition(), ScrollMessageArguments::getScrollPosition()
    static PropertyType<Vector2> MessageArgumentScrollViewScrollPositionProperty;

    /// Use the MessageArgumentScrollViewScrollSpeed argument to set the scrolling speed of a Scroll View node.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollMessageArguments::setScrollSpeed(), ScrollMessageArguments::getScrollSpeed()
    static PropertyType<Vector2> MessageArgumentScrollViewScrollSpeedProperty;

    /// Use the MessageArgumentScrollViewScrollTarget argument to set the scroll target for a Scroll View node.
    /// Scroll target is a position to which a Scroll View is going to scroll.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollMessageArguments::setScrollTarget(), ScrollMessageArguments::getScrollTarget()
    static PropertyType<Vector2> MessageArgumentScrollViewScrollTargetProperty;

    /// Use the MessageArgumentScrollViewScrollDirection argument to set the scrolling direction for a Scroll View node.
    /// The default value is ScrollViewConcept::ScrollDown.
    /// \see ScrollDirectionMessageArguments::setScroll(), ScrollDirectionMessageArguments::getScroll()
    static PropertyType<int> MessageArgumentScrollViewScrollDirectionProperty;

    /// Use the MessageArgumentScrollViewScrollPage argument to set the direction in which a Scroll View node
    /// scrolls when you instruct it to scroll by the layout height of that Scroll View node.
    /// The default value is ScrollViewConcept::ScrollPageDown.
    /// \see ScrollPageMessageArguments::setScroll(), ScrollPageMessageArguments::getScroll()
    static PropertyType<int> MessageArgumentScrollViewScrollPageProperty;

    /// Use the MessageArgumentScrollViewScrollEdge argument to set the direction in which a Scroll View node
    /// scrolls when you instruct it to scroll to either of the edges.
    /// The default value is ScrollViewConcept::ScrollEnd.
    /// \see ScrollEdgeMessageArguments::setScroll(), ScrollEdgeMessageArguments::getScroll()
    static PropertyType<int> MessageArgumentScrollViewScrollEdgeProperty;

    /// Use the MessageArgumentScrollViewZoom argument to set the zoom level for a Scroll View node.
    /// The default value is 1.0f.
    /// \see ZoomedMessageArguments::setZoom(), ZoomedMessageArguments::getZoom()
    static PropertyType<float> MessageArgumentScrollViewZoomProperty;

    /// Use the MessageArgumentScrollViewSnapPosition argument to set the target of a snap request.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see SnapRequestMessageArguments::setSnapPosition(), SnapRequestMessageArguments::getSnapPosition()
    static PropertyType<Vector2> MessageArgumentScrollViewSnapPositionProperty;

    /// Use the MessageArgumentScrollViewSnapDirection argument to set the direction of a snap request.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see SnapRequestMessageArguments::getSnapDirection, SnapRequestMessageArguments::getSnapDirection()
    static PropertyType<Vector2> MessageArgumentScrollViewSnapDirectionProperty;

    /// Use the Scroll Axis property to set the direction of the primary axis of a Scroll View node.
    /// The default value is Vector2(1.0f,  0.0f).
    /// \see ScrollViewConceptImpl::setScrollAxis(), ScrollViewConceptImpl::getScrollAxis()
    static PropertyType<Vector2> ScrollAxisProperty;

    /// Use the Recognition Threshold property to set the amount a pointing device must move for
    /// the scrolling to start on a Scroll View node.
    /// The default value is 5.0f.
    /// \see ScrollViewConceptImpl::setRecognitionThreshold(), ScrollViewConceptImpl::getRecognitionThreshold()
    static PropertyType<float> RecognitionThresholdProperty;

    /// Use the Minimum Number Of Touches property to set the required number of touch points
    /// pressed for a Scroll View node pan to start. Scroll View nodes with minimum number
    /// of touches greater than one precede the children in touch processing.
    /// The default value is 1.
    /// \see ScrollViewConceptImpl::setMinimumNumberOfTouches(), ScrollViewConceptImpl::getMinimumNumberOfTouches()
    static PropertyType<int> MinimumNumberOfTouchesProperty;

    /// Use the Maximum Number Of Touches property to set the maximum number of touch points
    /// allowed for a Scroll View to pan.
    /// The default value is 10.
    /// \see ScrollViewConceptImpl::setMaximumNumberOfTouches(), ScrollViewConceptImpl::getMaximumNumberOfTouches()
    static PropertyType<int> MaximumNumberOfTouchesProperty;

    /// Use the Sensitivity property to sets the amount the position changes relative
    /// to the movement of the pointer that starts the swiping. The higher the value the more
    /// the position of the node controlled by a Scroll View node changes.
    /// Negative values move that node in the opposite direction.
    /// The default value is 1.0f.
    /// \see ScrollViewConceptImpl::setSensitivity(), ScrollViewConceptImpl::getSensitivity()
    static PropertyType<float> SensitivityProperty;

    /// Use the Sliding Acceleration Coefficient property to set the acceleration of
    /// the node controlled by a Scroll View node after you release the pointer with
    /// which you swipe. Use low values when you want that node to slowly reach the
    /// final position. Use high values when you want that node to quickly reach the final position.
    /// The default value is 40.0f.
    /// \see ScrollViewConceptImpl::setSlidingAccelerationCoefficient(), ScrollViewConceptImpl::getSlidingAccelerationCoefficient()
    static PropertyType<float> SlidingAccelerationCoefficientProperty;

    /// Use the Sliding Drag Coefficient property to set the amount that drag affects
    /// the movement of the node controlled by a Scroll View node after you release
    /// the pointer with which you swipe. The lower the value the higher the drag and
    /// the faster the sliding of the object controlled by the Scroll View node stops.
    /// The default value is 80.0f.
    /// \see ScrollViewConceptImpl::setSlidingDragCoefficient(), ScrollViewConceptImpl::getSlidingDragCoefficient()
    static PropertyType<float> SlidingDragCoefficientProperty;

    /// Use the Dragging Acceleration Coefficient property to set the acceleration of
    /// the node controlled by a Scroll View node while you drag that Scroll View node.
    /// Use low values when you want that node to slowly reach the final position.
    /// Use high values when you want that node to quickly reach the final position.
    /// The default value is 80.0f.
    /// \see ScrollViewConceptImpl::setDraggingAccelerationCoefficient(), ScrollViewConceptImpl::getDraggingAccelerationCoefficient()
    static PropertyType<float> DraggingAccelerationCoefficientProperty;

    /// Use the Dragging Drag Coefficient property to set the amount that drag affects
    /// the movement of the node controlled by a Scroll View node while you drag that
    /// Scroll View node. The lower the value the higher the drag and the faster the
    /// sliding of that node stops.
    /// The default value is 150.0f.
    /// \see ScrollViewConceptImpl::setDraggingDragCoefficient(), ScrollViewConceptImpl::getDraggingDragCoefficient()
    static PropertyType<float> DraggingDragCoefficientProperty;

    /// Use the Dragging Impulse Factor property to set the amount of impulse generated
    /// from the pointing device movement when dragging a Scroll View node.
    /// The default value is 2.0f.
    /// \see ScrollViewConceptImpl::setDraggingImpulseFactor(), ScrollViewConceptImpl::getDraggingImpulseFactor()
    static PropertyType<float> DraggingImpulseFactorProperty;

    /// Use the Swipe Distance property to set the distance that a swipe sends the
    /// scroll value, relative to the pointing device speed.
    /// The default value is 0.005f.
    /// \see ScrollViewConceptImpl::setSwipeDistance(), ScrollViewConceptImpl::getSwipeDistance()
    static PropertyType<float> SwipeDistanceProperty;

    /// Use the Scroll Position property to set the value for the current scroll position.
    /// Scroll position is a relative position within a Scroll View.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollViewConceptImpl::setScrollPosition(), ScrollViewConceptImpl::getScrollPosition()
    static PropertyType<Vector2> ScrollPositionProperty;

    /// Use the Scroll Target Position property to set the value for the current scroll target.
    /// Scroll target is a position to which a Scroll View is going to scroll.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollViewConceptImpl::setScrollTargetPosition(), ScrollViewConceptImpl::getScrollTargetPosition()
    static PropertyType<Vector2> ScrollTargetPositionProperty;

    /// Use the Scroll Speed property to set the current scroll speed.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollViewConceptImpl::setScrollSpeed(), ScrollViewConceptImpl::getScrollSpeed()
    static PropertyType<Vector2> ScrollSpeedProperty;

    /// Use the Scrolling property to find out whether a Scroll View node is currently scrolling.
    /// The default value is False.
    /// \see ScrollViewConceptImpl::setScrolling(), ScrollViewConceptImpl::isScrolling()
    static PropertyType<bool> ScrollingProperty;

    /// Use the Zoom Affects Scrolling property to set whether the scroll position
    /// is scaled according to the zoom level.
    /// The default value is True.
    /// \see ScrollViewConceptImpl::setZoomAffectsScrolling(), ScrollViewConceptImpl::isZoomAffectsScrolling()
    static PropertyType<bool> ZoomAffectsScrollingProperty;

    /// Use the Scroll Bounds Minimum property to set the coordinates of the top-left corner
    /// of the scroll bounds rectangle. Scroll bounds define where the scrolling begins and ends.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollViewConceptImpl::setScrollBoundsMinimum(), ScrollViewConceptImpl::getScrollBoundsMinimum(), LoopingXEnabledProperty, LoopingYEnabledProperty
    static PropertyType<Vector2> ScrollBoundsMinimumProperty;

    /// Use the Scroll Bounds Maximum property to set the coordinates of the bottom-right corner
    /// of the scroll bounds rectangle. Scroll bounds define where the scrolling begins and ends.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see ScrollViewConceptImpl::setScrollBoundsMaximum(), ScrollViewConceptImpl::getScrollBoundsMaximum(), LoopingXEnabledProperty, LoopingYEnabledProperty
    static PropertyType<Vector2> ScrollBoundsMaximumProperty;

    /// Use the Looping X Enabled property to set the node controlled by a Scroll View node
    /// to start scrolling from the beginning when the scroll reaches the scroll bounds on
    /// the x axis. When the scroll value reaches the maximum value of the bound, the value
    /// changes to the minimum value and the other way around. Use the ScrollBoundsMinimumProperty
    /// and ScrollBoundsMaximumProperty properties to set the scroll bounds.
    /// The default value is False.
    /// \see ScrollViewConceptImpl::setLoopingXEnabled(), ScrollViewConceptImpl::isLoopingXEnabled(), ScrollBoundsMinimumProperty, ScrollBoundsMaximumProperty
    static PropertyType<bool> LoopingXEnabledProperty;

    /// Use the Looping Y Enabled property to set the node controlled by a Scroll View node
    /// to start scrolling from the beginning when the scroll reaches the scroll bounds on
    /// the y axis. When the scroll value reaches the maximum value of the bound, the value
    /// changes to the minimum value and the other way around. Use the ScrollBoundsMinimumProperty
    /// and ScrollBoundsMaximumProperty properties to set the scroll bounds.
    /// The default value is False.
    /// \see ScrollViewConceptImpl::setLoopingYEnabled(), ScrollViewConceptImpl::isLoopingYEnabled(), ScrollBoundsMinimumProperty, ScrollBoundsMaximumProperty
    static PropertyType<bool> LoopingYEnabledProperty;

    /// Use the Zoom Enabled property to set whether to install a pinch manipulator
    /// that generates zoom messages.
    /// The default value is False.
    /// \see ScrollViewConceptImpl::setZoomEnabled(), ScrollViewConceptImpl::isZoomEnabled()
    static PropertyType<bool> ZoomEnabledProperty;

    /// Use the Zoom property to set the current zoom level.
    /// The default value is 1.0f.
    /// \see ScrollViewConceptImpl::setZoom(), ScrollViewConceptImpl::getZoom()
    static PropertyType<float> ZoomProperty;

    /// Use the Zoom Minimum property to set the minimum zoom level.
    /// The default value is 0.2f.
    /// \see ScrollViewConceptImpl::setZoomMinimum(), ScrollViewConceptImpl::getZoomMinimum()
    static PropertyType<float> ZoomMinimumProperty;

    /// Use the Zoom Maximum property to set the maximum zoom level.
    /// The default value is 6.0f.
    /// \see ScrollViewConceptImpl::setZoomMaximum(), ScrollViewConceptImpl::getZoomMaximum()
    static PropertyType<float> ZoomMaximumProperty;

    /// Use the Step Multiplier property to set the smallest distance that a Scroll View scrolls.
    /// The default value is 0.25f.
    /// \see ScrollViewConceptImpl::setStepMultiplier(), ScrollViewConceptImpl::getStepMultiplier()
    static PropertyType<float> StepMultiplierProperty;

    /// Sets the axis on which you want to allow a Scroll View node to scroll.
    /// The default value is \l AllAxes.
    static PropertyType<AllowedScrollAxis> AllowedScrollAxisProperty;
    /// \}

    class KANZI_UI_API ScrollTargetMessageArguments
    {
    public:
        KZ_MIXIN_METACLASS_BEGIN(ScrollTargetMessageArguments, "Kanzi.ScrollViewConcept.ScrollTargetMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollTargetProperty)
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ScrollPositionMessageArguments
    {
    public:
        KZ_MIXIN_METACLASS_BEGIN(ScrollPositionMessageArguments, "Kanzi.ScrollViewConcept.ScrollPositionMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollPositionProperty)
        KZ_METACLASS_END()
    };

    class KANZI_UI_API SnapMessageArguments
    {
    public:
        KZ_MIXIN_METACLASS_BEGIN(SnapMessageArguments, "Kanzi.ScrollViewConcept.SnapMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewSnapPositionProperty)
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewSnapDirectionProperty)
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ScrollMessageArguments: public MessageArguments, public ScrollTargetMessageArguments, public ScrollPositionMessageArguments, public SnapMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.ScrollMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollPositionXProperty) // TODO: Remove this property type.
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollPositionYProperty) // TODO: Remove this property type.

            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollSpeedProperty)

            KZ_METACLASS_MIXIN(ScrollTargetMessageArguments)
            KZ_METACLASS_MIXIN(ScrollPositionMessageArguments)
            KZ_METACLASS_MIXIN(SnapMessageArguments)
        KZ_METACLASS_END()

        float getScrollPositionX() const { return getArgument(MessageArgumentScrollViewScrollPositionXProperty); }
        void setScrollPositionX(float value) { setArgument(MessageArgumentScrollViewScrollPositionXProperty, value); }

        float getScrollPositionY() const { return getArgument(MessageArgumentScrollViewScrollPositionYProperty); }
        void setScrollPositionY(float value) { setArgument(MessageArgumentScrollViewScrollPositionYProperty, value); }

        Vector2 getScrollPosition() const { return getArgument(MessageArgumentScrollViewScrollPositionProperty); }
        void setScrollPosition(Vector2 value) { setArgument(MessageArgumentScrollViewScrollPositionProperty, value); }

        Vector2 getScrollSpeed() const { return getArgument(MessageArgumentScrollViewScrollSpeedProperty); }
        void setScrollSpeed(Vector2 value) { setArgument(MessageArgumentScrollViewScrollSpeedProperty, value); }

        Vector2 getScrollTarget() const { return getArgument(MessageArgumentScrollViewScrollTargetProperty); }
        void setScrollTarget(Vector2 value) { setArgument(MessageArgumentScrollViewScrollTargetProperty, value); }
    };

    class KANZI_UI_API ScrollStartedMessageArguments: public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollStartedMessageArguments, ScrollMessageArguments, "Kanzi.ScrollViewConcept.ScrollStartedMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ScrollFinishedMessageArguments: public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollFinishedMessageArguments, ScrollMessageArguments, "Kanzi.ScrollViewConcept.ScrollFinishedMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API UserScrollStartedMessageArguments: public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(UserScrollStartedMessageArguments, ScrollMessageArguments, "Kanzi.ScrollViewConcept.UserScrollStartedMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API UserScrollFinishedMessageArguments: public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(UserScrollFinishedMessageArguments, ScrollMessageArguments, "Kanzi.ScrollViewConcept.UserScrollFinishedMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ScrolledMessageArguments: public ScrollMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrolledMessageArguments, ScrollMessageArguments, "Kanzi.ScrollViewConcept.ScrolledMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ZoomedMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ZoomedMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.ZoomedMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewZoomProperty)
        KZ_METACLASS_END()

        float getZoom() const { return getArgument(MessageArgumentScrollViewZoomProperty); }
        void setZoom(float value) { setArgument(MessageArgumentScrollViewZoomProperty, value); }
    };

    class KANZI_UI_API SnapRequestMessageArguments: public MessageArguments, public SnapMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(SnapRequestMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.SnapRequestMessageArguments")
            KZ_METACLASS_MIXIN(SnapMessageArguments)
        KZ_METACLASS_END()

        Vector2 getSnapPosition() const { return getArgument(MessageArgumentScrollViewSnapPositionProperty); }
        void setSnapPosition(Vector2 value) { setArgument(MessageArgumentScrollViewSnapPositionProperty, value); }

        Vector2 getSnapDirection() const { return getArgument(MessageArgumentScrollViewSnapDirectionProperty); }
        void setSnapDirection(Vector2 value) { setArgument(MessageArgumentScrollViewSnapDirectionProperty, value); }
    };

    class KANZI_UI_API ScrollDirectionMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollDirectionMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.ScrollDirectionMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollDirectionProperty)
        KZ_METACLASS_END()

        ScrollDirection getScroll() const { return static_cast<ScrollDirection>(getArgument(MessageArgumentScrollViewScrollDirectionProperty)); }
        void setScroll(ScrollDirection value) { setArgument(MessageArgumentScrollViewScrollDirectionProperty, static_cast<int>(value)); }
    };

    class KANZI_UI_API ScrollPageMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollPageMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.ScrollPageMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollPageProperty)
        KZ_METACLASS_END()

        ScrollPage getScroll() const { return static_cast<ScrollPage>(getArgument(MessageArgumentScrollViewScrollPageProperty)); }
        void setScroll(ScrollPage value) { setArgument(MessageArgumentScrollViewScrollPageProperty, static_cast<int>(value)); }
    };

    class KANZI_UI_API ScrollEdgeMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ScrollEdgeMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.ScrollEdgeMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentScrollViewScrollEdgeProperty)
        KZ_METACLASS_END()

        ScrollEdge getScroll() const { return static_cast<ScrollEdge>(getArgument(MessageArgumentScrollViewScrollEdgeProperty)); }
        void setScroll(ScrollEdge value) { setArgument(MessageArgumentScrollViewScrollEdgeProperty, static_cast<int>(value)); }
    };

    class KANZI_UI_API SetScrollTargetMessageArguments: public MessageArguments, public ScrollTargetMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(SetScrollTargetMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.SetScrollTargetMessageArguments")
            KZ_METACLASS_MIXIN(ScrollTargetMessageArguments)
        KZ_METACLASS_END()

        Vector2 getScrollTarget() const { return getArgument(MessageArgumentScrollViewScrollTargetProperty); }
        void setScrollTarget(Vector2 value) { setArgument(MessageArgumentScrollViewScrollTargetProperty, value); }
    };

    class KANZI_UI_API SetScrollMessageArguments: public MessageArguments, public ScrollPositionMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(SetScrollMessageArguments, MessageArguments, "Kanzi.ScrollViewConcept.SetScrollMessageArguments")
            KZ_METACLASS_MIXIN(ScrollPositionMessageArguments)
        KZ_METACLASS_END()

        Vector2 getScrollPosition() const { return getArgument(MessageArgumentScrollViewScrollPositionProperty); }
        void setScrollPosition(Vector2 value) { setArgument(MessageArgumentScrollViewScrollPositionProperty, value); }
    };

    /// Scroll View sends this message when scrolling starts, regardless of how the scrolling started.
    static MessageType<ScrollStartedMessageArguments> ScrollStartedMessage;
    /// Scroll View sends this message when scrolling ends, regardless of how the scrolling ended.
    /// A scroll ends when the interpolators reach the target values and the current position no longer changes.
    static MessageType<ScrollFinishedMessageArguments> ScrollFinishedMessage;
    /// Scroll View sends this message when user interaction causes the scrolling to start.
    static MessageType<UserScrollStartedMessageArguments> UserScrollStartedMessage;
    /// Scroll View sends this message when user interaction causes the scrolling to end. At this point the
    /// user interaction ended, but the scrolling movement can still continue.
    static MessageType<UserScrollFinishedMessageArguments> UserScrollFinishedMessage;
    /// Scroll View sends this message when zoom in or zoom out occurs.
    static MessageType<ZoomedMessageArguments> ZoomedMessage;
    /// Scroll View sends this message whenever the Scroll View node scrolls.
    static MessageType<ScrolledMessageArguments> ScrolledMessage;
    /// Scroll View sends this message when scrolling stops, but the Scroll View node needs to snap to the nearest item.
    /// List %Box nodes use this message to react to the snap request to snap to the nearest item in a List %Box node.
    static MessageType<SnapRequestMessageArguments> SnapRequestMessage;

    /// Send this message to a Scroll View node to scroll one step in a given direction.
    /// You can set the size of the step with the #StepMultiplierProperty.
    static MessageType<ScrollDirectionMessageArguments> ScrollDirectionMessage;
    /// Send this message to a Scroll View node to scroll the distance of the layout height of that Scroll View node.
    static MessageType<ScrollPageMessageArguments> ScrollPageMessage;
    /// Send this message to a Scroll View node to scroll to the top or bottom of that Scroll View node.
    static MessageType<ScrollEdgeMessageArguments> ScrollEdgeMessage;

    /// Send this message to a Scroll View to scroll to a specific position in that Scroll View node.
    static MessageType<SetScrollTargetMessageArguments> SetScrollTargetMessage;
    /// Send this message to a Scroll View to go a scroll position immediatelly without scrolling.
    static MessageType<SetScrollMessageArguments> SetScrollMessage;

    KZ_MIXIN_METACLASS_BEGIN(ScrollViewConcept, "Kanzi.ScrollViewConcept")
        KZ_METACLASS_MESSAGE_TYPE(ScrollStartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrollFinishedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ZoomedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrolledMessage)
        KZ_METACLASS_MESSAGE_TYPE(UserScrollStartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(UserScrollFinishedMessage)
        KZ_METACLASS_MESSAGE_TYPE(SetScrollTargetMessage)
        KZ_METACLASS_MESSAGE_TYPE(SetScrollMessage)
        KZ_METACLASS_MESSAGE_TYPE(SnapRequestMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrollDirectionMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrollPageMessage)
        KZ_METACLASS_MESSAGE_TYPE(ScrollEdgeMessage)
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
        KZ_METACLASS_PROPERTY_TYPE(ScrollPositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollTargetPositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollSpeedProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollingProperty)
        KZ_METACLASS_PROPERTY_TYPE(ZoomAffectsScrollingProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollBoundsMinimumProperty)
        KZ_METACLASS_PROPERTY_TYPE(ScrollBoundsMaximumProperty)
        KZ_METACLASS_PROPERTY_TYPE(LoopingXEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(LoopingYEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(ZoomEnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(ZoomProperty)
        KZ_METACLASS_PROPERTY_TYPE(ZoomMinimumProperty)
        KZ_METACLASS_PROPERTY_TYPE(ZoomMaximumProperty)
        KZ_METACLASS_PROPERTY_TYPE(StepMultiplierProperty)
        KZ_METACLASS_PROPERTY_TYPE(AllowedScrollAxisProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};


template <typename TBaseClass, class TDerivedClass>
class KANZI_UI_TEMPLATE_API ScrollViewConceptImpl : public TBaseClass, public ScrollViewConcept
{
public:

    typedef ScrollViewConceptImpl<TBaseClass, TDerivedClass> TScrollView;

    KZ_TEMPLATE_METACLASS_BEGIN(ScrollViewConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(ScrollViewConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Destructor.
    ~ScrollViewConceptImpl();

    /// Returns the pan manipulator.
    PanManipulatorSharedPtr getPanManipulator() const;

    /// Gets the value of the #ScrollAxisProperty.
    /// \see setScrollAxis()
    Vector2 getScrollAxis() const { return getThisObject()->getProperty(ScrollAxisProperty); }

    /// Sets the value of the #ScrollAxisProperty.
    /// \see getScrollAxis()
    void setScrollAxis(Vector2 value) { getThisObject()->setProperty(ScrollAxisProperty, value); }

    /// Gets the value of the #RecognitionThresholdProperty.
    /// \see setRecognitionThreshold()
    float getRecognitionThreshold() const { return getThisObject()->getProperty(RecognitionThresholdProperty); }

    /// Sets the value of the #RecognitionThresholdProperty.
    /// \see getRecognitionThreshold()
    void setRecognitionThreshold(float value) { getThisObject()->setProperty(RecognitionThresholdProperty, value); }

    /// Gets the value of the #MinimumNumberOfTouchesProperty.
    /// \see setMinimumNumberOfTouches()
    int getMinimumNumberOfTouches() const { return getThisObject()->getProperty(MinimumNumberOfTouchesProperty); }

    /// Sets the value of the #MinimumNumberOfTouchesProperty.
    /// Scroll views with minimum number of touches greater than one will precede the descendants in touch event processing.
    /// \see getMinimumNumberOfTouches()
    void setMinimumNumberOfTouches(int value) { getThisObject()->setProperty(MinimumNumberOfTouchesProperty, value); }

    /// Gets the value of the #MaximumNumberOfTouchesProperty.
    /// \see setMaximumNumberOfTouches()
    int getMaximumNumberOfTouches() const { return getThisObject()->getProperty(MaximumNumberOfTouchesProperty); }

    /// Sets the value of the #MaximumNumberOfTouchesProperty.
    /// \see getMaximumNumberOfTouches()
    void setMaximumNumberOfTouches(int value) { getThisObject()->setProperty(MaximumNumberOfTouchesProperty, value); }

    /// Gets the value of the #SensitivityProperty.
    /// \see setSensitivity()
    float getSensitivity() const { return getThisObject()->getProperty(SensitivityProperty); }

    /// Sets the value of the #SensitivityProperty.
    /// \see getSensitivity()
    void setSensitivity(float value) { getThisObject()->setProperty(SensitivityProperty, value); }

    /// Gets the value of the #SlidingAccelerationCoefficientProperty.
    /// \see setSlidingAccelerationCoefficient()
    float getSlidingAccelerationCoefficient() const { return getThisObject()->getProperty(SlidingAccelerationCoefficientProperty); }

    /// Sets the value of the #SlidingAccelerationCoefficientProperty.
    /// \see getSlidingAccelerationCoefficient()
    void setSlidingAccelerationCoefficient(float value) { getThisObject()->setProperty(SlidingAccelerationCoefficientProperty, value); }

    /// Gets the value of the #SlidingDragCoefficientProperty.
    /// \see setSlidingDragCoefficient()
    float getSlidingDragCoefficient() const { return getThisObject()->getProperty(SlidingDragCoefficientProperty); }

    /// Sets the value of the #SlidingDragCoefficientProperty.
    /// \see getSlidingDragCoefficient()
    void setSlidingDragCoefficient(float value) { getThisObject()->setProperty(SlidingDragCoefficientProperty, value); }

    /// Gets the value of the #DraggingAccelerationCoefficientProperty.
    /// \see setDraggingAccelerationCoefficient()
    float getDraggingAccelerationCoefficient() const { return getThisObject()->getProperty(DraggingAccelerationCoefficientProperty); }

    /// Sets the value of the #DraggingAccelerationCoefficientProperty.
    /// \see getDraggingAccelerationCoefficient()
    void setDraggingAccelerationCoefficient(float value) { getThisObject()->setProperty(DraggingAccelerationCoefficientProperty, value); }

    /// Gets the value of the #DraggingDragCoefficientProperty.
    /// \see setDraggingDragCoefficient()
    float getDraggingDragCoefficient() const { return getThisObject()->getProperty(DraggingDragCoefficientProperty); }

    /// Sets the value of the #DraggingDragCoefficientProperty.
    /// \see getDraggingDragCoefficient()
    void setDraggingDragCoefficient(float value) { getThisObject()->setProperty(DraggingDragCoefficientProperty, value); }

    /// Gets the value of the #DraggingImpulseFactorProperty.
    /// \see setDraggingImpulseFactor()
    float getDraggingImpulseFactor() const { return getThisObject()->getProperty(DraggingImpulseFactorProperty); }

    /// Sets the value of the #DraggingImpulseFactorProperty.
    /// \see getDraggingImpulseFactor()
    void setDraggingImpulseFactor(float value) { getThisObject()->setProperty(DraggingImpulseFactorProperty, value); }

    /// Gets the value of the #SwipeDistanceProperty.
    /// \see setSwipeDistance()
    float getSwipeDistance() const { return getThisObject()->getProperty(SwipeDistanceProperty); }

    /// Sets the value of the #SwipeDistanceProperty.
    /// \see getSwipeDistance()
    void setSwipeDistance(float value) { getThisObject()->setProperty(SwipeDistanceProperty, value); }

    /// Gets the value of the #ScrollPositionProperty.
    /// \see setScrollPosition()
    Vector2 getScrollPosition() const { return getThisObject()->getProperty(ScrollPositionProperty); }

    /// Sets the value of the #ScrollPositionProperty.
    /// \see getScrollPosition()
    void setScrollPosition(Vector2 value) { getThisObject()->setProperty(ScrollPositionProperty, value); }

    /// Gets the value of the #ScrollTargetPositionProperty.
    /// \see setScrollTargetPosition()
    Vector2 getScrollTargetPosition() const { return getThisObject()->getProperty(ScrollTargetPositionProperty); }

    /// Sets the value of the #ScrollTargetPositionProperty.
    /// \see getScrollTargetPosition()
    void setScrollTargetPosition(Vector2 value) { getThisObject()->setProperty(ScrollTargetPositionProperty, value); }

    /// Gets the value of the #ScrollSpeedProperty.
    /// \see setScrollSpeed()
    Vector2 getScrollSpeed() const { return getThisObject()->getProperty(ScrollSpeedProperty); }

    /// Sets the value of the #ScrollSpeedProperty.
    /// \see getScrollSpeed()
    void setScrollSpeed(Vector2 value) { getThisObject()->setProperty(ScrollSpeedProperty, value); }

    /// Gets the value of the #ScrollingProperty.
    /// \see setScrolling()
    bool isScrolling() const { return getThisObject()->getProperty(ScrollingProperty); }

    /// Sets the value of the #ScrollingProperty.
    /// \see isScrolling()
    void setScrolling(bool value) { getThisObject()->setProperty(ScrollingProperty, value); }

    /// Checks whether a finger is on the surface.
    bool isDragging() const;

    /// Gets the value of the #ZoomAffectsScrollingProperty.
    /// \see setZoomAffectsScrolling()
    bool isZoomAffectsScrolling() const { return getThisObject()->getProperty(ZoomAffectsScrollingProperty); }

    /// Sets the value of the #ZoomAffectsScrollingProperty.
    /// \see isZoomAffectsScrolling()
    void setZoomAffectsScrolling(bool value) { getThisObject()->setProperty(ZoomAffectsScrollingProperty, value); }

    /// Gets the value of the #ScrollBoundsMinimumProperty.
    /// \see setScrollBoundsMinimum()
    Vector2 getScrollBoundsMinimum() const { return getThisObject()->getProperty(ScrollBoundsMinimumProperty); }

    /// Sets the value of the #ScrollBoundsMinimumProperty.
    /// \see getScrollBoundsMinimum()
    void setScrollBoundsMinimum(Vector2 value) { getThisObject()->setProperty(ScrollBoundsMinimumProperty, value); }

    /// Gets the value of the #ScrollBoundsMaximumProperty.
    /// \see setScrollBoundsMaximum()
    Vector2 getScrollBoundsMaximum() const { return getThisObject()->getProperty(ScrollBoundsMaximumProperty); }

    /// Sets the value of the #ScrollBoundsMaximumProperty.
    /// \see getScrollBoundsMaximum()
    void setScrollBoundsMaximum(Vector2 value) { getThisObject()->setProperty(ScrollBoundsMaximumProperty, value); }

    /// Sets whether the scroll view scrolls along the x axis.
    /// \deprecated Use \l setAllowedScrollAxis() instead.
    void setEnabledX(bool state);

    /// Sets whether the scroll view scrolls along the y axis.
    /// \deprecated Use \l setAllowedScrollAxis() instead.
    void setEnabledY(bool state);

    /// Returns whether the scroll view scrolls along the x axis.
    /// \deprecated Use \l getAllowedScrollAxis() instead.
    bool isEnabledX() const;

    /// Returns whether the scroll view scrolls along the y axis.
    /// \deprecated Use \l getAllowedScrollAxis() instead.
    bool isEnabledY() const;

    /// Sets the value of the #LoopingXEnabledProperty.
    /// \see isLoopingXEnabled()
    void setLoopingXEnabled(bool value) { getThisObject()->setProperty(LoopingXEnabledProperty, value); }

    /// Sets the value of the #LoopingYEnabledProperty.
    /// \see isLoopingYEnabled()
    void setLoopingYEnabled(bool value) { getThisObject()->setProperty(LoopingYEnabledProperty, value); }

    /// Gets the value of the #LoopingXEnabledProperty.
    /// \see setLoopingXEnabled()
    bool isLoopingXEnabled() const { return getThisObject()->getProperty(LoopingXEnabledProperty); }

    /// Gets the value of the #LoopingYEnabledProperty.
    /// \see setLoopingYEnabled()
    bool isLoopingYEnabled() const { return getThisObject()->getProperty(LoopingYEnabledProperty); }

    /// Sets the bounds on the x axis.
    /// When scrolling outside of the bounds, after the scrolling ends, the scroll position converges to the nearest bound value.
    /// \param minimum Represents the right edge of a Scroll View.
    /// \param maximum Represents the left edge of a Scroll View.
    /// \see setLoopingXEnabled(), isLoopingXEnabled()
    void setScrollBoundsX(float minimum, float maximum);
    /// Sets the bounds on the y axis.
    /// When scrolling outside of the bounds, after the scrolling ends, the scroll position converges to the nearest bound value.
    /// \param minimum Represents the bottom edge of a Scroll View.
    /// \param maximum Represents the top edge of a Scroll View.
    /// \see setLoopingYEnabled(), isLoopingYEnabled()
    void setScrollBoundsY(float minimum, float maximum);

    /// Sets the value for the scroll position within a Scroll View and starts scrolling to that value.
    ///
    /// Use this function when you have the exact scroll position in a Scroll View and want to scroll to that position.
    /// If you enabled the looping for the scroll view, the target value can be out of bounds to indicate direction and repetition.
    /// \param scrollPosition The position of the scroll view to which you want to set the scroll view to start scrolling.
    /// \see scrollToPositionLooping(), jumpToPosition(), setLoopingXEnabled(), setLoopingYEnabled()
    void scrollToPosition(Vector2 scrollPosition);

    /// If you enabled the axis looping for a Scroll View, Kanzi uses the shortest path to the target value.
    /// \param scrollPosition The position of a Scroll View to which you want to set the Scroll View to start scrolling.
    /// \see jumpToPosition(), scrollToPositionLooping(), setLoopingXEnabled(), setLoopingYEnabled(), isLoopingXEnabled(), isLoopingYEnabled()
    void scrollToPositionLooping(Vector2 scrollPosition);

    /// Sets the value for a scroll position within a Scroll View and goes to that position immediatelly without scrolling.
    /// \param scrollPosition The scroll position to which you want the Scroll View to go without scrolling.
    /// \see scrollToPositionLooping(), scrollToPosition()
    void jumpToPosition(Vector2 scrollPosition);

    /// Gets the values of the current scroll position of a Scroll View. If you enable looping for that Scroll View,
    /// the value of the position this function returns is normalized so that it is within the bound interval.
    /// \return Returns the current scroll position of the Scroll View.
    Vector2 getScroll() const;

    /// Gets the values of the scroll position of a Scroll View to which the Scroll View is scrolling.
    /// Use this function when you want to find out the scrolling position towards which the Scroll View is scrolling.
    /// If you enable looping for a Scroll View, the value of the position this function returns can be out of bounds of the Scroll View.
    /// \return Returns the scroll position to which the Scroll View is scrolling.
    Vector2 getScrollTarget() const;

    /// When you enable looping, returns the scroll position value normalized to the allowed range of a Scroll View.
    /// Kanzi uses the returned value to set the value of the #ScrollTargetPositionProperty.
    /// \return Returns the normalized value of the scroll position to which the Scroll View is scrolling.
    Vector2 getScrollTargetLooping() const;

    /// Queries the interpolator for the current speed.
    /// Kanzi internally uses the returned value to calculate the target scroll position.
    /// \see getScrollTarget()
    Vector2 getSpeed() const;

    /// Sets the scroll delta to one step and starts scrolling in that direction.
    /// \param direction Scroll direction.
    /// \see #StepMultiplierProperty
    void scroll(ScrollDirection direction);

    /// Sets the scroll delta to one distance of the layout height of a Scroll View and starts scrolling in that direction.
    /// \param direction Scroll direction.
    void scroll(ScrollPage direction);

    /// Sets the scroll target to the edge defined by the scroll bounds and starts scrolling in that direction.
    /// \param direction Scroll direction.
    /// \see #ScrollBoundsMinimumProperty, #ScrollBoundsMaximumProperty
    void scroll(ScrollEdge direction);

    /// Gets the value of the #ZoomEnabledProperty.
    bool isZoomEnabled() const { return getThisObject()->getProperty(ZoomEnabledProperty); }

    /// Sets the value of the #ZoomEnabledProperty.
    void setZoomEnabled(bool value) { getThisObject()->setProperty(ZoomEnabledProperty, value); }

    /// Gets the value of the #ZoomProperty.
    float getZoom() const { return getThisObject()->getProperty(ZoomProperty); }

    /// Gets the value of the #ZoomMinimumProperty.
    /// \see setZoomMinimum()
    float getZoomMinimum() const { return getThisObject()->getProperty(ZoomMinimumProperty); }

    /// Sets the value of the #ZoomMinimumProperty.
    /// \see getZoomMinimum()
    void setZoomMinimum(float value) { getThisObject()->setProperty(ZoomMinimumProperty, value); }

    /// Gets the value of the #ZoomMaximumProperty.
    /// \see setZoomMaximum()
    float getZoomMaximum() const { return getThisObject()->getProperty(ZoomMaximumProperty); }

    /// Sets the value of the #ZoomMaximumProperty.
    /// \see getZoomMaximum()
    void setZoomMaximum(float value) { getThisObject()->setProperty(ZoomMaximumProperty, value); }

    /// Gets the value of the #StepMultiplierProperty.
    /// \see setStepMultiplier(), scroll()
    float getStepMultiplier() const { return getThisObject()->getProperty(StepMultiplierProperty); }

    /// Sets the value of the #StepMultiplierProperty.
    /// \see getStepMultiplier(), scroll()
    void setStepMultiplier(float value) { getThisObject()->setProperty(StepMultiplierProperty, value); }

    /// Returns the value of the #AllowedScrollAxisProperty.
    /// \see setAllowedScrollAxis()
    AllowedScrollAxis getAllowedScrollAxis() const { return getThisObject()->getProperty(AllowedScrollAxisProperty); }

    /// Sets the value of the #AllowedScrollAxisProperty.
    /// \param axis The axis on which you want to allow scrolling.
    /// \see getAllowedScrollAxis.
    void setAllowedScrollAxis(AllowedScrollAxis axis) { getThisObject()->setProperty(AllowedScrollAxisProperty, axis); }

    /// Updates the recognition threshold of the pan manipulator to the value of the #RecognitionThresholdProperty value.
    /// \see PanManipulator::setRecognitionThreshold
    void refreshThreshold();

protected:
    explicit ScrollViewConceptImpl(Domain* domain, string_view name);

    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline TDerivedClass* getThisObject()
    {
        return static_cast<TDerivedClass*>(this);
    }

    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline const TDerivedClass* getThisObject() const
    {
        return static_cast<const TDerivedClass*>(this);
    }

    /// Assigns the message handlers for the pan manipulator and scroll messages.
    void initialize();

    /// Node::onNodePropertyChanged() implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Kanzi internally uses this helper function to update smooth interpolation coefficients
    /// between starting and stopping the interpolator timer, depending on whether a finger is still
    /// on a Scroll View node.
    void refreshScrollConfiguration();

    /// Kanzi internally uses this helper function to update the minimum number of touch points of
    /// the pan manipulator to the value of the #MinimumNumberOfTouchesProperty value.
    /// \see PanManipulator::setMinimumNumberOfTouches
    void refreshMinimumNumberOfTouches();

    /// Kanzi internally updates the maximum number of touch points of the pan manipulator to
    /// the value of the #MaximumNumberOfTouchesProperty value.
    /// \see PanManipulator::setMaximumNumberOfTouches
    void refreshMaximumNumberOfTouches();

private:

    /// Starts the periodic timer for updating the interpolator with timestamps.
    /// This helper function is called to animate scrolling transition to target scroll position.
    void startUpdate();
    /// Stops the periodic timer for updating the interpolator with timestamps.
    /// This helper function is called when the interpolator reached the target value.
    void stopUpdate();

    /// Updates the scroll speed and the current scroll position, and sends `ScrolledMessage` message.
    ///
    /// This method is called after updating the interpolator with a new timestamp.
    void updateScroll();

    /// Sends a user scroll started message upon receiving 'panBeginHandler' message.
    void sendUserScrollStartedMessage();
    /// Sends a user scroll ended message upon receiving 'PanManipulator::FinishedMessage' message.
    void sendUserScrollEndedMessage();
    /// Sends a scroll started message after starting the interpolator timer.
    void sendScrollStartedMessage();
    /// Sends a scroll ended message after stopping the interpolator timer.
    void sendScrollEndedMessage();

    /// Fills scroll message parameters with current speed and scroll position.
    ///
    /// The method is used to fill the parameters before dispatching the scroll message.
    /// \param arguments The scroll message where the parameters will be filled into.
    void fillScrollMessageParameters(ScrollMessageArguments& arguments);

    /// Handler for stop scrolling timer function.
    static void panInertiaTimeoutHandler(weak_ptr<TDerivedClass> object);
    /// Stop scrolling if list is moving with inertia.
    void cancelInertia();
    /// Unsubscribe timer handler for scroll stop.
    void unsubscribePanInertiaTimeoutHandler();

    /// Handles pan begin event.
    void panBeginHandler(PanManipulator::StartedMessageArguments& arguments);
    /// Handles pan move event.
    void panMoveHandler(PanManipulator::MovedMessageArguments& arguments);
    /// Handles pan end event.
    void panEndHandler(PanManipulator::FinishedMessageArguments& arguments);

    /// Handles pinch begin event.
    void pinchBeginHandler(PinchManipulator::StartedMessageArguments& arguments);
    /// Handles pinch move event.
    void pinchMoveHandler(PinchManipulator::MovedMessageArguments& arguments);
    /// Handles pinch end event.
    void pinchEndHandler(PinchManipulator::FinishedMessageArguments& arguments);

    /// Handles key down event.
    void onKeyDown(Keyboard::KeyDownMessageArguments& arguments);

    /// Scroll target message handler.
    void setScrollTargetHandler(SetScrollTargetMessageArguments& arguments);

    /// Scroll message handler.
    void setScrollHandler(SetScrollMessageArguments& arguments);

    /// ScrollDirection message handler.
    void scrollDirectionMessageHandler(ScrollDirectionMessageArguments& arguments);

    /// ScrollPage message handler.
    void scrollPageMessageHandler(ScrollPageMessageArguments& arguments);

    /// ScrollEdge message handler.
    void scrollEdgeMessageHandler(ScrollEdgeMessageArguments& arguments);

    /// Callback for scroll view playback, updates interpolated value with new timestamps.
    void onScrollViewTimelinePlaybackTick(chrono::milliseconds deltaTIme);

private:

    // Forward declaration.
    class ScrollViewTimelinePlayback;

    /// Timeline which runs scroll view logic during animation ticks.
    class ScrollViewTimeline : public Timeline
    {
    public:

        /// Constructor.
        ///
        /// \param scrollView Scroll view the logic of which to run.
        explicit ScrollViewTimeline(TScrollView& scrollView) :
            Timeline(scrollView.getThisObject()->getDomain()),
            m_scrollView(scrollView)
        {
        }

        /// Timeline::createPlaybackOverride() implementation.
        virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& /*context*/) KZ_OVERRIDE
        {
            return make_polymorphic_shared_ptr<TimelinePlayback>(new ScrollViewTimelinePlayback(getDomain(), shared_from_this()));
        }

        /// Timeline::calculateContentDuration() implementation.
        virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE
        {
            // Scroll timeline is infinite.
            return nullopt;
        }

        /// Gets scroll view of the timeline.
        ///
        /// \return scrollView.
        TScrollView& getScrollView()
        {
            return m_scrollView;
        }

    private:

        /// Scroll view those logic to run.
        TScrollView& m_scrollView;
    };

    typedef shared_ptr<ScrollViewTimeline> ScrollViewTimelineSharedPtr;

    /// Playback of scroll view timeline. Runs scroll view logic during animation ticks.
    class ScrollViewTimelinePlayback : public TimelinePlayback
    {
    public:

        /// Constructor.
        ///
        /// \param domain Domain.
        /// \param timeline Timeline.
        explicit ScrollViewTimelinePlayback(Domain* domain, TimelineSharedPtr timeline) :
            TimelinePlayback(domain, timeline),
            m_scrollTimeline(dynamic_pointer_cast<ScrollViewTimeline>(timeline))
        {
        }

        /// TimelinePlayback::tickOverride() implementation.
        virtual void tickOverride(chrono::milliseconds deltaTime) KZ_OVERRIDE
        {
            m_scrollTimeline->getScrollView().onScrollViewTimelinePlaybackTick(deltaTime);
        }

        /// TimelinePlayback::onProgressTimeResetOverride() implementation.
        virtual void onProgressTimeResetOverride() KZ_OVERRIDE
        {
            m_scrollTimeline->getScrollView().onScrollViewTimelinePlaybackTick(chrono::milliseconds::zero());
        }

    private:

        /// Timeline of the playback.
        shared_ptr<ScrollViewTimeline> m_scrollTimeline;
    };

    /// Scrolling mode of a scroll view.
    enum ScrollViewMode
    {
        /// Represents the state when finger is no longer on the surface.
        ScrollViewModeSlide,
        /// Represents the state when finger is on the surface.
        ScrollViewModeDrag
    };

    // Timeline for performing scroll.
    ScrollViewTimelineSharedPtr m_scrollViewTimeline;
    // Playback for performing scroll.
    TimelinePlaybackSharedPtr m_scrollViewTimelinePlayback;

    /// Pan manipulator of scroll view. Stored so that threshold value can be changed.
    PanManipulatorSharedPtr m_panManipulator;

    /// Subscription for timer
    TimerSubscriptionToken m_panInertiaTimeoutSubscription;

    /// Pinch manipulator of scroll view. Stored so that it can be removed when disabling zoom.
    PinchManipulatorSharedPtr m_pinchManipulator;

    /// Measures scrolling speed in x-direction over time.
    SpeedMeasurer m_speedMeasurerX;
    /// Measures scrolling speed in y-direction over time.
    SpeedMeasurer m_speedMeasurerY;

    /// How fast scrolling accelerates when sliding.
    float m_slideAccelerationCoefficient;
    /// How much drag affects scrolling when sliding.
    float m_slideDragCoefficient;
    /// How fast scrolling accelerates when dragging.
    float m_dragAccelerationCoefficient;
    /// How much drag affects scrolling when dragging.
    float m_dragDragCoefficient;
    /// How much impulse is generated from pointing device movement when dragging.
    float m_dragImpulseFactor;
    /// How far a swipe sends the scroll value, relative to pointing device speed.
    float m_swipeDistance;

    /// Mode of scroll view.
    ScrollViewMode m_scrollingMode;

    /// Measured speed at end of pan, in X direction.
    float m_panEndMeasuredSpeedX;
    /// Measured speed at end of pan, in Y direction.
    float m_panEndMeasuredSpeedY;

    /// Last non-zero speed measured during pan, in X direction.
    float m_lastNonZeroSpeedX;
    /// Last non-zero speed measured during pan, in Y direction.
    float m_lastNonZeroSpeedY;

    /// Current pan state.
    PanState m_panState;

    /// Last position in panning. Used for calculating differences.
    Vector2 m_previousPanPosition;
    /// Current scroll position in x-direction.
    InterpolatedValue m_scrollPositionX;
    /// Current scroll position in y-direction.
    InterpolatedValue m_scrollPositionY;
    /// Last scroll position. Used for calculating differences.
    Vector2 m_previousScrollPosition;
    /// Last zoom value. Used for calculating differences.
    float m_previousZoom;
    /// Last position in pinching. Used for calculating differences.
    optional<Vector2> m_previousPinchPosition;

    /// Maximum number of speed measurements to use.
    static const size_t m_maxSpeedMeasurements;
    /// Minimum measurement time for speed. Samples newer than this will be dropped.
    static const chrono::milliseconds m_minMeasurementTime;
    /// Maximum measurement time for speed. Samples older than this will be dropped.
    static const chrono::milliseconds m_maxMeasurementTime;

    ClassPropertyDefaultValue<bool> m_classValueHitTestable;
    ClassPropertyDefaultValue<bool> m_classValueHitTestableContainer;
};

}

#endif
