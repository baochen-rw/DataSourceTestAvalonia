// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BUTTON_HPP
#define KZ_BUTTON_HPP

#include <kanzi/ui/ui_api.hpp>
#include <kanzi/ui/node/concept/toggle_button_group.hpp>

#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/core.ui/input/click_manipulator.hpp>
#include <kanzi/core.ui/input/multi_click_manipulator.hpp>
#include <kanzi/core.ui/input/long_press_manipulator.hpp>
#include <kanzi/core.ui/input/keyboard.hpp>
#include <kanzi/core.ui/message/message_arguments.hpp>

#include <kanzi/core/message/message_type.hpp>


class KzTestButtons;

namespace kanzi
{

// Forward declarations.
class Domain;


/// Button concept class.
class KANZI_UI_API ButtonConcept
{
public:

    /// @name Properties
    /// @{
#include "button_properties.h"
    /// @}

    /// @name Message arguments
    /// @{
    class KANZI_UI_API ClickedMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ClickedMessageArguments, MessageArguments, "Kanzi.ButtonConcept.ClickedMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API PressedMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(PressedMessageArguments, MessageArguments, "Kanzi.ButtonConcept.PressedMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API CanceledMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(CanceledMessageArguments, MessageArguments, "Kanzi.ButtonConcept.CanceledMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API PointerEnteredMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(PointerEnteredMessageArguments, MessageArguments, "Kanzi.ButtonConcept.PointerEnteredMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API PointerLeftMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(PointerLeftMessageArguments, MessageArguments, "Kanzi.ButtonConcept.PointerLeftMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API LongPressMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(LongPressMessageArguments, MessageArguments, "Kanzi.ButtonConcept.LongPressMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ToggledOnMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ToggledOnMessageArguments, MessageArguments, "Kanzi.ButtonConcept.ToggledOnMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ToggledOffMessageArguments : public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ToggledOffMessageArguments, MessageArguments, "Kanzi.ButtonConcept.ToggledOffMessageArguments")
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ToggleStateChangedMessageArguments : public MessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ToggleStateChangedMessageArguments, MessageArguments, "Kanzi.ButtonConcept.ToggleStateChangedMessageArguments")
        KZ_METACLASS_END()

        unsigned int getToggleState() const { return static_cast<unsigned int>(getArgument(ToggleStateProperty)); }
        void setToggleState(unsigned int value) { setArgument(ToggleStateProperty, static_cast<int>(value)); }
    };
    /// @}

    /// @name Messages
    /// @{
    static MessageType<ClickedMessageArguments> ClickedMessage;
    static MessageType<PressedMessageArguments> PressedMessage;
    static MessageType<CanceledMessageArguments> CanceledMessage;
    static MessageType<PointerEnteredMessageArguments> PointerEnteredMessage;
    static MessageType<PointerLeftMessageArguments> PointerLeftMessage;
    static MessageType<LongPressMessageArguments> LongPressMessage;
    static MessageType<ToggledOnMessageArguments> ToggledOnMessage;
    static MessageType<ToggledOffMessageArguments> ToggledOffMessage;
    static MessageType<ToggleStateChangedMessageArguments> ToggleStateChangedMessage;
    /// @}

    KZ_MIXIN_METACLASS_BEGIN(ButtonConcept, "Kanzi.ButtonConcept")
        KZ_METACLASS_PROPERTY_TYPE(IsPressedProperty)
        KZ_METACLASS_PROPERTY_TYPE(LongPressIntervalProperty)
        KZ_METACLASS_PROPERTY_TYPE(PressOnHoverProperty)
        KZ_METACLASS_PROPERTY_TYPE(AutoClickIntervalProperty)
        KZ_METACLASS_PROPERTY_TYPE(ToggleStateProperty)
        KZ_METACLASS_PROPERTY_TYPE(ToggleStateCountProperty)
        KZ_METACLASS_PROPERTY_TYPE(IndexInGroupProperty)

        KZ_METACLASS_MESSAGE_TYPE(ClickedMessage)
        KZ_METACLASS_MESSAGE_TYPE(PressedMessage)
        KZ_METACLASS_MESSAGE_TYPE(CanceledMessage)
        KZ_METACLASS_MESSAGE_TYPE(PointerEnteredMessage)
        KZ_METACLASS_MESSAGE_TYPE(PointerLeftMessage)
        KZ_METACLASS_MESSAGE_TYPE(LongPressMessage)
        KZ_METACLASS_MESSAGE_TYPE(ToggledOnMessage)
        KZ_METACLASS_MESSAGE_TYPE(ToggledOffMessage)
        KZ_METACLASS_MESSAGE_TYPE(ToggleStateChangedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    optional<int> getEffectiveButtonGroupId() const { return m_effectiveButtonGroupId; }

protected:

    /// Measure function for a Node2D button.
    static Vector2 measure2D(Node2D* button, Vector2 availableSize);

    optional<int> m_effectiveButtonGroupId;
};


/// Base class for buttons.
template <typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API ButtonConceptImpl : public TBaseClass, public ButtonConcept
{
    friend class ::KzTestButtons;

    TDerivedClass* getThisObject()
    {
        return static_cast<TDerivedClass*>(this);
    }

    const TDerivedClass* getThisObject() const
    {
        return static_cast<const TDerivedClass*>(this);
    }

public:

    KZ_TEMPLATE_METACLASS_BEGIN(ButtonConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(ButtonConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    bool isPressed() const;
    void setPressed(bool value);

    // TODO change to chrono
    float getLongPressInterval() const;
    void setLongPressInterval(float value);

    bool isPressOnHover() const;
    void setPressOnHover(bool value);

    // TODO change to chrono
    float getAutoClickInterval() const;
    void setAutoClickInterval(float value);

    unsigned int getToggleStateCount() const;
    void setToggleStateCount(unsigned int value);

    unsigned int getToggleState() const;
    void setToggleState(unsigned int state);

    /// Gets the value of #ButtonGroupIndexProperty.
    /// \see setButtonGroupIndex()
    int getIndexInGroup() const;

    /// Sets the value of #ButtonGroupIndexProperty.
    /// \see getButtonGroupIndex()
    void setIndexInGroup(int value);

    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

protected:

    explicit ButtonConceptImpl(Domain* domain, string_view name);

    void initialize();

    virtual void onAttached() KZ_OVERRIDE;
    virtual void onDetached() KZ_OVERRIDE;

    void onClickEnter(ClickManipulator::ClickEnterMessageArguments&);
    void onClickLeave(ClickManipulator::ClickLeaveMessageArguments&);
    void onClickBegin(ClickManipulator::ClickBeginMessageArguments&);
    void onClick(ClickManipulator::ClickMessageArguments&);
    void onClickCancel(ClickManipulator::ClickCancelMessageArguments&);

    void onLongPress(LongPressManipulator::LongPressMessageArguments& arguments);
    void onKeyDown(Keyboard::KeyDownMessageArguments& arguments);
    void onKeyUp(Keyboard::KeyUpMessageArguments& arguments);

    void toggle();

    static kzsError repeatHandler(MessageArguments* message, void* userData);

private:

    void removeFromButtonGroup();

    void refreshButtonGroup(bool forceSearch = false);

    void sendToggledMessage();

    /// Called when the button starts being pressed by input method.
    /// Input method can be either keyboard or touch manipulator.
    ///
    /// Keeps track of how many input methods currently press the button.
    /// This should be called when input method starts pressing the button by
    /// entering its area or when pressing a keyboard key.
    void enterPress();

    /// Called when the button stops being pressed by input method.
    /// Input method can be either keyboard or touch manipulator.
    ///
    /// Keeps track of how many input methods currently press the button.
    /// This should be called when input method stops pressing the button by
    /// moving outside of its area or when releasing a previously pressed keyboard key.
    void leavePress();

    /// Unpresses the button if it's not being pressed by input method.
    /// Input method can be either keyboard or touch manipulator.
    ///
    /// This method should be called when input method unpresses the button by any means.
    void cancelPress();

    /// Sends a clicked message if the button is not being pressed by any input method.
    /// Input method can be either keyboard or touch manipulator.
    ///
    /// This method should be called when input method triggers a click.
    void processClick();

    void onButtonGroupToggled(ToggleButtonGroupConcept::ToggledMessageArguments& message);

    void configureMultiClickManipulator();
    void configureLongPressManipulator();

    optional<unsigned int> m_lastToggleState;
    ClassPropertyDefaultValue<bool> m_hitTestableDefaultValue;
    ClassPropertyDefaultValue<bool> m_hitTestableContainerDefaultValue;
    ClickManipulatorSharedPtr m_clickManipulator; /**< click manipulator */
    MultiClickManipulatorSharedPtr m_multiClickManipulator; /**< multiclick manipulator */
    LongPressManipulatorSharedPtr m_longPressManipulator; /**< long press manipulator */
    Node::MessageSubscriptionToken m_toggleButtonGroupMessageToken;
    size_t m_pressedCounter;

    /// Previous state of IndexInGroup property to determine if #refreshButtonGroup() needs to be called.
    optional<int> m_oldIndexInGroup;
};

}

#endif
