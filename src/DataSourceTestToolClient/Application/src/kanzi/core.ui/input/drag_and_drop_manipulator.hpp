// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DRAG_AND_DROP_MANIPULATOR_HPP
#define KZ_DRAG_AND_DROP_MANIPULATOR_HPP

#include <kanzi/core.ui/input/input_manipulator.hpp>
#include <kanzi/core.ui/input/input_manager.hpp>
#include <kanzi/core.ui/message/kzu_message_dispatcher.h>

namespace kanzi
{

// Forward declarations.
class Node;
class DragAndDropManipulator;

typedef shared_ptr<DragAndDropManipulator> DragAndDropManipulatorSharedPtr;

/// Drag and drop input manipulator recognizes the drag and drop gesture from incoming touch events. It generates messages required to 
/// implement the logic for objects which react to the drag and drop gesture. For example, use the drag and drop input manipulator to
/// move objects in an application.
///
/// \see ClickManipulator, LongPressManipulator, MultiClickManipulator, PanManipulator, PinchManipulator
///
/// Examples
/// ----
///
/// To receive the drag moved events, add the message handler for the MovedMessage message.
///
/// First create a handler method:
/// \snippet test_input_manipulators.cpp Drag moved message handler
///
/// Then add a message handler for your node:
/// \snippet test_input_manipulators.cpp Subscribe drag moved
class KANZI_API DragAndDropManipulator : public InputManipulator
{
public:

    /// Message arguments for drag and drop started message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API StartedMessageArguments : public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StartedMessageArguments, InputMessageArguments, "Kanzi.DragAndDropManipulator.StartedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for drag and drop moved message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API MovedMessageArguments : public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(MovedMessageArguments, InputMessageArguments, "Kanzi.DragAndDropManipulator.MovedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for drag and drop finished message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API FinishedMessageArguments : public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(FinishedMessageArguments, InputMessageArguments, "Kanzi.DragAndDropManipulator.FinishedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message type for notifying the beginning of the drag and drop gesture.
    /// StartedMessage is generated after successful long press over the node area.
    static MessageType<StartedMessageArguments> StartedMessage;
    /// Message type for notifying update on position for the recognized gesture.
    /// MovedMessage is generated when the tracked touch has moved while the drag is active.
    static MessageType<MovedMessageArguments> MovedMessage;
    /// Message type for notifying end of the recognized drag and drop gesture.
    /// FinishedMessage is generated when the tracked touch is released while the drag is active.
    static MessageType<FinishedMessageArguments> FinishedMessage;

    KZ_METACLASS_BEGIN(DragAndDropManipulator, InputManipulator, "Kanzi.DragAndDropManipulator")
        KZ_METACLASS_MESSAGE_TYPE(StartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(MovedMessage)
        KZ_METACLASS_MESSAGE_TYPE(FinishedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static DragAndDropManipulatorSharedPtr create(Domain* domain, string_view /*name*/ = "")
    {
        return make_polymorphic_shared_ptr<InputManipulator>(new DragAndDropManipulator(domain));
    }

    /// Set the duration in milliseconds of the long press before drag and drop starts. The default duration is 500ms.
    void setPressDuration(chrono::milliseconds pressDuration);

protected:
    /// Constructor
    explicit DragAndDropManipulator(Domain* domain);

    /// InputManipulator::notifyTouchInside implementation.
    virtual void notifyTouchInside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// InputManipulator::notifyTouchOutside implementation.
    virtual void notifyTouchOutside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// InputManipulator::onReset implementation.
    virtual void onReset() KZ_OVERRIDE;

    /// Update the drag and drop gesture state with touch event.
    void trackDragAndDrop(const TouchInfo& touchInfo);

    /// Timer callback for successful long press.
    void onLongPressCompleted(const TimerMessageArguments& arguments);

private:
    /// Press delay.
    chrono::milliseconds m_pressDuration;
    /// Touch ID.
    unsigned int m_touchId;
    /// Has dragging started.
    bool m_dragging;
    /// Last touch point.
    KzuInputTouchPoint m_lastTouchPoint;
    /// Timer handle for initial long press.
    TimerSubscriptionToken m_longPressTimerSubscription;
};

}


#endif
