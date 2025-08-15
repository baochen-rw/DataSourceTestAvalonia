// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MULTI_CLICK_MANIPULATOR_HPP
#define KZ_MULTI_CLICK_MANIPULATOR_HPP

#include <kanzi/core.ui/input/input_manipulator.hpp>
#include <kanzi/core.ui/message/kzu_message_dispatcher.h>

namespace kanzi
{


class MultiClickManipulator;

typedef shared_ptr<MultiClickManipulator> MultiClickManipulatorSharedPtr;

/// Multi-click input manipulator recognizes double click and tap gestures from incoming touch events. It generates the messages required to
/// implement the logic for objects that change the state when users multi-click or multi-tap the object. For example, use the multi-click input
/// manipulator to zoom in and out a map.
///
/// \see ClickManipulator, DragAndDropManipulator, LongPressManipulator, PanManipulator, PinchManipulator
///
/// Examples
/// ----
///
/// To receive the multi click event, add message handler for the MultiClickMessage message.
///
/// First create a handler method:
/// \snippet test_input_manipulators.cpp Multi click message handler
///
/// Then add a message handler for your node:
/// \snippet test_input_manipulators.cpp Subscribe multi click
class KANZI_API MultiClickManipulator : public InputManipulator
{
public:
    /// Message arguments for the multi-click gesture recognized message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API MultiClickMessageArguments: public InputMessageArguments
    {
    public:
        /// The amount of clicks that were required to trigger this message.
        static PropertyType<int> ClickCountProperty;

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(MultiClickMessageArguments, InputMessageArguments, "Kanzi.MultiClickManipulator.MultiClickMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(ClickCountProperty)
        KZ_METACLASS_END()

        /// Returns the value of the ClickCountProperty property.
        int getClickCount() const;

        /// Sets the value of the ClickCountProperty property.
        void setClickCount(int count);
    };

    /// Message type for notifying recognition of multi-click gesture.
    /// MultiClickMessage message is generated when the second touch press and release sequence is recognized in the attached node area within the timeout duration.
    /// MultiClick fails if some other gesture succeeds before it.
    static MessageType<MultiClickMessageArguments> MultiClickMessage;

    /// The property that determines how many clicks are required to trigger
    /// the MultiClickMessage message.
    static PropertyType<int> ExpectedClicksProperty;

    /// If the property is set to true, the manipulator will send MultiClickMessage
    /// for each click up to ExpectedClicksProperty value. If the property is
    /// set to false, Only the final click will trigger the message.
    static PropertyType<bool> SendIntermediateClickMessagesProperty;

    KZ_METACLASS_BEGIN(MultiClickManipulator, InputManipulator, "Kanzi.MultiClickManipulator")
        KZ_METACLASS_MESSAGE_TYPE(MultiClickMessage)
        KZ_METACLASS_PROPERTY_TYPE(ExpectedClicksProperty)
        KZ_METACLASS_PROPERTY_TYPE(SendIntermediateClickMessagesProperty)
    KZ_METACLASS_END()

    static MultiClickManipulatorSharedPtr create(Domain* domain, string_view /*name*/ = "")
    {
        return make_polymorphic_shared_ptr<InputManipulator>(new MultiClickManipulator(domain));
    }

    /// Set multi-click timeout in milliseconds. The default timeout is 250ms.
    void setTimeout(chrono::milliseconds timeout);

    /// Set the amount of clicks required to emit the MultiClickMessage message.
    void setExpectedClicks(int clicks);

    /// Get the amount of clicks required to emit the MultiClickMessage message.
    int getExpectedClicks() const;

    /// Set SendIntermediateClickMessagesProperty.
    void setSendIntermediateClickMessages(bool value);

    /// Get SendIntermediateClickMessagesProperty.
    bool getSendIntermediateClickMessages() const;

protected:
    /// Constructor
    explicit MultiClickManipulator(Domain* domain);

    /// InputManipulator::notifyTouchInside implementation
    virtual void notifyTouchInside(const TouchInfo& touchInfo) KZ_OVERRIDE;
    /// InputManipulator::notifyTouchOutside implementation
    virtual void notifyTouchOutside(const TouchInfo& touchInfo) KZ_OVERRIDE;
    /// InputManipulator::onReset implementation
    virtual void onReset() KZ_OVERRIDE;
    /// InputManipulator::onFail implementation.
    virtual void onFail() KZ_OVERRIDE;

    void onTimeout(const TimerMessageArguments& arguments);

private:
    /// Timeout duration.
    chrono::milliseconds m_timeout;
    /// Touch ID.
    unsigned int m_touchId;
    /// Number of clicks.
    unsigned int m_numberOfClicks;
    /// Timer handle for initial long press.
    TimerSubscriptionToken m_timeoutTimerSubscription;
    /// Is the click handling delayed by other input manipulator.
    bool m_delayed;
    /// The touch point stored when the message is delayed
    KzuInputTouchPoint m_touchPoint;
};

}

#endif
