// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CLICK_MANIPULATOR_HPP
#define KZ_CLICK_MANIPULATOR_HPP

#include <kanzi/core.ui/input/input_manipulator.hpp>

namespace kanzi
{

// Forward declarations.
class ClickManipulator;

typedef shared_ptr<ClickManipulator> ClickManipulatorSharedPtr;

/// Click input manipulator recognizes the click and tap gestures from incoming touch events. It generates the messages required to 
/// implement the logic for objects which users can click or tap the object. For example, use the click input manipulator to a create button.
///
/// \see DragAndDropManipulator, LongPressManipulator, MultiClickManipulator, PanManipulator, PinchManipulator
///
/// Examples
/// ----
///
/// To receive the click event, add a message handler for the ClickMessage message.
/// 
/// First create a handler method:
/// \snippet test_input_manipulators.cpp Click message handler
///
/// Then add a message handler for your node:
/// \snippet test_input_manipulators.cpp Subscribe click
///
/// To configure the click manipulator to work together with the multi-click manipulator, you need to configure the click manipulator
/// to wait for the failure of the multi-click:
/// \snippet test_input_manipulators.cpp requireToFail
class KANZI_API ClickManipulator : public InputManipulator
{
public:
    /// Message arguments for click gesture recognized message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API ClickMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ClickMessageArguments, InputMessageArguments, "Kanzi.ClickManipulator.ClickMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for click gesture began message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API ClickBeginMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ClickBeginMessageArguments, InputMessageArguments, "Kanzi.ClickManipulator.ClickBeginMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for click canceled message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API ClickCancelMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ClickCancelMessageArguments, InputMessageArguments, "Kanzi.ClickManipulator.ClickCancelMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for pointer entering the node area message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API ClickEnterMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ClickEnterMessageArguments, InputMessageArguments, "Kanzi.ClickManipulator.ClickEnterMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for pointer leaving the node area message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API ClickLeaveMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ClickLeaveMessageArguments, InputMessageArguments, "Kanzi.ClickManipulator.ClickLeaveMessageArguments")
        KZ_METACLASS_END()
    };
    
    /// Message type for notifying recognition of click gesture.
    /// Click message is generated when the tracked touch is released over the attached node or when the fail manipulator fails (see InputManipulator::requireToFail).
    static MessageType<ClickMessageArguments> ClickMessage;
    /// Message type for notifying the beginning of a click gesture.
    /// There are two scenarios for ClickBeginMessage to be generated:
    /// 1) When touch is pressed over the attached node. This is the default behavior. 
    /// 2) If the gesture is set to start on hover with the setHoverToBegin function, click gesture begins when the touch arrives in 
    /// the node area while being pressed.
    static MessageType<ClickBeginMessageArguments> ClickBeginMessage;
    /// Message type for notifying cancellation of click gesture.
    /// Click gesture is canceled when the tracked touch is released outside the node area, or when the fail manipulator succeeds (see InputManipulator::requireToFail).
    static MessageType<ClickCancelMessageArguments> ClickCancelMessage;
    /// Message type for notifying the tracked touch entering the node area.
    /// Click enter message is generated when touch is pressed over the node area or when the touch returns to the node area after leaving it.
    static MessageType<ClickEnterMessageArguments> ClickEnterMessage;
    /// Message type for notifying the tracked touch leaving the node area.
    /// Click leave message is generated when the pointer leaves the area or when the click gesture is completed or canceled.
    static MessageType<ClickLeaveMessageArguments> ClickLeaveMessage;

    KZ_METACLASS_BEGIN(ClickManipulator, InputManipulator, "Kanzi.ClickManipulator")
        KZ_METACLASS_MESSAGE_TYPE(ClickMessage)
        KZ_METACLASS_MESSAGE_TYPE(ClickBeginMessage)
        KZ_METACLASS_MESSAGE_TYPE(ClickCancelMessage)
        KZ_METACLASS_MESSAGE_TYPE(ClickEnterMessage)
        KZ_METACLASS_MESSAGE_TYPE(ClickLeaveMessage)
    KZ_METACLASS_END()

    static ClickManipulatorSharedPtr create(Domain* domain, string_view /*name*/ = "")
    {
        return make_polymorphic_shared_ptr<InputManipulator>(new ClickManipulator(domain));
    }

    /// Enable or disable the gesture to begin on pressed touch point arriving to the node area.
    void setHoverToBegin(bool hoverToBegin);

    /// Returns true if manipulator is in the pressed state.
    bool isPressed() const;

protected:
    /// Constructor
    explicit ClickManipulator(Domain* domain);

    /// InputManipulator::notifyTouchInside implementation
    virtual void notifyTouchInside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// InputManipulator::notifyTouchOutside implementation.
    virtual void notifyTouchOutside(const TouchInfo& touchInfo) KZ_OVERRIDE;

    /// InputManipulator::onReset implementation.
    virtual void onReset() KZ_OVERRIDE;

    /// InputManipulator::onFail implementation.
    virtual void onFail() KZ_OVERRIDE;

private:
    /// Touch ID.
    unsigned int m_touchId;
    /// Is the touch inside the node attached to the manipulator.
    bool m_touchInside;
    /// Is in the pressed state.
    bool m_pressed;
    /// Is the click handling delayed by other input manipulator.
    bool m_delayed; 
    /// Is begin on hovering enabled.
    bool m_hoverToBegin;
};

}

#endif
