// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LONG_PRESS_MANIPULATOR_HPP
#define KZ_LONG_PRESS_MANIPULATOR_HPP


#include <kanzi/core.ui/input/input_manipulator.hpp>
#include <kanzi/core/message/message_type.hpp>
#include <kanzi/core.ui/input/input_manager.hpp>
#include <kanzi/core.ui/message/kzu_message_dispatcher.h>

namespace kanzi
{

class LongPressManipulator;

typedef shared_ptr<LongPressManipulator> LongPressManipulatorSharedPtr;

/// Long press input manipulator recognizes the long press gesture from the incoming touch events. It generates the required messages to 
/// implement logic for objects which react to the long press gesture. For example, use the long press input manipulator to open a context menu.
///
/// \see ClickManipulator, DragAndDropManipulator, MultiClickManipulator, PanManipulator, PinchManipulator
///
/// Examples
/// ---
/// 
/// To receive the long press event, add message handler for the LongPressMessage message.
///
/// First create a handler method:
/// \snippet test_input_manipulators.cpp Long press message handler
///
/// Then add a message handler for your node:
/// \snippet test_input_manipulators.cpp Subscribe long press
class KANZI_API LongPressManipulator : public InputManipulator
{
public:
    /// Message arguments for long press gesture recognized message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API LongPressMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(LongPressMessageArguments, InputMessageArguments, "Kanzi.LongPressManipulator.LongPressMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message type for notifying recognition of long press gesture.
    /// LongPressMessage message is generated when the tracked touch has remained in the node area for the press duration.
    static MessageType<LongPressMessageArguments> LongPressMessage;

    KZ_METACLASS_BEGIN(LongPressManipulator, InputManipulator, "Kanzi.LongPressManipulator")
        KZ_METACLASS_MESSAGE_TYPE(LongPressMessage)
    KZ_METACLASS_END()

    static LongPressManipulatorSharedPtr create(Domain* domain, string_view /*name*/ = "")
    {
        return make_polymorphic_shared_ptr<InputManipulator>(new LongPressManipulator(domain));
    }

    /// Set the duration in milliseconds of the long press. The default duration is 500ms.
    void setPressDuration(chrono::milliseconds pressDuration);

protected:
    /// Constructor
    explicit LongPressManipulator(Domain* domain);

    /// InputManipulator::notifyTouchInside implementation
    virtual void notifyTouchInside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// InputManipulator::notifyTouchOutside implementation
    virtual void notifyTouchOutside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// InputManipulator::onReset implementation
    virtual void onReset() KZ_OVERRIDE;

    /// Timer callback for successful long press
    void onLongPressCompleted(const TimerMessageArguments& arguments);

public:
    /// Press delay.
    chrono::milliseconds m_pressDuration;
    /// Touch ID.
    unsigned int m_touchId;
    /// Last touch point.
    struct KzuInputTouchPoint m_lastTouchPoint;
    /// Timer handle for initial long press.
    TimerSubscriptionToken m_longPressTimerSubscription;
};

}

#endif
