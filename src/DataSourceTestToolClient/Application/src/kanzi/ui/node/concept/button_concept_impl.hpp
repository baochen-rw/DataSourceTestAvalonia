// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_BUTTON_CONCEPT_IMPL_HPP
#define KZ_BUTTON_CONCEPT_IMPL_HPP

#include "button.hpp"

#include <kanzi/core.ui/command/command.hpp>

namespace kanzi
{

template <typename TBaseClass, typename TDerivedClass>
bool ButtonConceptImpl<TBaseClass, TDerivedClass>::isPressed() const
{
    return getThisObject()->getProperty(IsPressedProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::setPressed(bool value)
{
    getThisObject()->setProperty(IsPressedProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
float ButtonConceptImpl<TBaseClass, TDerivedClass>::getLongPressInterval() const
{
    return getThisObject()->getProperty(LongPressIntervalProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::setLongPressInterval(float value)
{
    getThisObject()->setProperty(LongPressIntervalProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
bool ButtonConceptImpl<TBaseClass, TDerivedClass>::isPressOnHover() const
{
    return getThisObject()->getProperty(PressOnHoverProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::setPressOnHover(bool value)
{
    getThisObject()->setProperty(PressOnHoverProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
float ButtonConceptImpl<TBaseClass, TDerivedClass>::getAutoClickInterval() const
{
    return getThisObject()->getProperty(AutoClickIntervalProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::setAutoClickInterval(float value)
{
    getThisObject()->setProperty(AutoClickIntervalProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
unsigned int ButtonConceptImpl<TBaseClass, TDerivedClass>::getToggleStateCount() const
{
    return static_cast<unsigned int>(getThisObject()->getProperty(ToggleStateCountProperty));
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::setToggleStateCount(unsigned int value)
{
    getThisObject()->setProperty(ToggleStateCountProperty, static_cast<int>(value));
}

template <typename TBaseClass, typename TDerivedClass>
unsigned int ButtonConceptImpl<TBaseClass, TDerivedClass>::getToggleState() const
{
    return static_cast<unsigned int>(getThisObject()->getProperty(ToggleStateProperty));
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::setToggleState(unsigned int state)
{
    const unsigned int stateCount = getToggleStateCount();

    if (state == 0 || state < stateCount)
    {
        getThisObject()->setProperty(ToggleStateProperty, static_cast<int>(state));
    }
    else
    {
        kzThrowLegacyErrorFormat(KZS_ERROR_ILLEGAL_ARGUMENT, "Toggle state number %u too large (button '%s' has only %u states)",
                                 state, getThisObject()->getName().c_str(), stateCount);
    }
}

template <typename TBaseClass, typename TDerivedClass>
int ButtonConceptImpl<TBaseClass, TDerivedClass>::getIndexInGroup() const
{
    return getThisObject()->getProperty(IndexInGroupProperty);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::setIndexInGroup(int value)
{
    getThisObject()->setProperty(IndexInGroupProperty, value);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::configureMultiClickManipulator()
{
    bool multiClickManipulatorNeeded = getThisObject()->isEnableMultiClick();
    if (multiClickManipulatorNeeded && !m_multiClickManipulator)
    {
        m_multiClickManipulator = MultiClickManipulator::create(getThisObject()->getDomain());
        getThisObject()->addInputManipulator(m_multiClickManipulator);
        m_clickManipulator->requireToFail(m_multiClickManipulator);
    }
    else if (!multiClickManipulatorNeeded && m_multiClickManipulator)
    {
        getThisObject()->removeInputManipulator(*m_multiClickManipulator);
        m_multiClickManipulator.reset();
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::configureLongPressManipulator()
{
    // This is conversion from legacy property which is of type float
    const unsigned int longPressInterval = static_cast<unsigned int>(getLongPressInterval());
    if (longPressInterval > 0 && !m_longPressManipulator)
    {
        m_longPressManipulator = LongPressManipulator::create(getThisObject()->getDomain());
        m_longPressManipulator->setPressDuration(chrono::milliseconds(longPressInterval));

        getThisObject()->addInputManipulator(m_longPressManipulator);
    }
    else if (longPressInterval == 0 && m_longPressManipulator)
    {
        getThisObject()->removeInputManipulator(*m_longPressManipulator);
        m_longPressManipulator.reset();
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);

    if (propertyType == ToggleStateProperty)
    {
        const unsigned int stateCount = getToggleStateCount();
        unsigned int state = getToggleState();
        // Reflect the integer toggle state to the Boolean toggle state in toggle buttons.
        if (stateCount == 2)
        {
            // Toggle on/off messages
            if (state == 1)
            {
                ToggledOnMessageArguments toggledOnArguments;
                getThisObject()->dispatchMessage(ToggledOnMessage, toggledOnArguments);
            }
            else
            {
                ToggledOffMessageArguments toggledOffArguments;
                getThisObject()->dispatchMessage(ToggledOffMessage, toggledOffArguments);
            }
        }
        if (state > 0 && m_toggleButtonGroupMessageToken.isValid() &&
            // This avoids infinite recursion with the new synchronous message delivery.
            (!m_lastToggleState || state != *m_lastToggleState))
        {
            sendToggledMessage();
        }
        m_lastToggleState = state;

        ToggleStateChangedMessageArguments toggleStateChangedArguments;
        toggleStateChangedArguments.setToggleState(state);
        getThisObject()->dispatchMessage(ToggleStateChangedMessage, toggleStateChangedArguments);
    }
    else if (propertyType == IndexInGroupProperty)
    {
        optional<int> indexInGroup = getThisObject()->getOptionalProperty(IndexInGroupProperty);

        if (m_oldIndexInGroup != indexInGroup)
        {
            refreshButtonGroup();
            m_oldIndexInGroup = indexInGroup;
        }
    }

    if (getThisObject()->isAttached() && !getThisObject()->isDetaching())
    {
        if (propertyType == TDerivedClass::EnableMultiClickProperty)
        {
            configureMultiClickManipulator();
        }
        else if (propertyType == LongPressIntervalProperty)
        {
            configureLongPressManipulator();
        }
    }
}

template <typename TBaseClass, typename TDerivedClass>
ButtonConceptImpl<TBaseClass, TDerivedClass>::ButtonConceptImpl(Domain* domain, string_view name):
    TBaseClass(domain, name),
    m_hitTestableDefaultValue(*this, TDerivedClass::HitTestableProperty, true),
    m_hitTestableContainerDefaultValue(*this, TDerivedClass::HitTestableContainerProperty, true),
    m_pressedCounter(0),
    m_oldIndexInGroup(getThisObject()->getOptionalProperty(IndexInGroupProperty))
{
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::initialize()
{
    TBaseClass::initialize();

    setPressed(false);

    getThisObject()->setPropertyFlag(TDerivedClass::IsPressedProperty, KZU_PROPERTY_MANAGER_FLAG_KEEP_DURING_PATCHING);

    getThisObject()->addMessageHandler(ClickManipulator::ClickMessage, getThisObject(), &TDerivedClass::onClick);
    getThisObject()->addMessageHandler(ClickManipulator::ClickBeginMessage, getThisObject(), &TDerivedClass::onClickBegin);
    getThisObject()->addMessageHandler(ClickManipulator::ClickCancelMessage, getThisObject(), &TDerivedClass::onClickCancel);
    getThisObject()->addMessageHandler(ClickManipulator::ClickEnterMessage, getThisObject(), &TDerivedClass::onClickEnter);
    getThisObject()->addMessageHandler(ClickManipulator::ClickLeaveMessage, getThisObject(), &TDerivedClass::onClickLeave);
    getThisObject()->addMessageHandler(LongPressManipulator::LongPressMessage, getThisObject(), &TDerivedClass::onLongPress);
    getThisObject()->addMessageHandler(Keyboard::KeyDownMessage, getThisObject(), &TDerivedClass::onKeyDown);
    getThisObject()->addMessageHandler(Keyboard::KeyUpMessage, getThisObject(), &TDerivedClass::onKeyUp);

    // Force existence of property for bindings and state manager to work.
    setToggleState(getToggleState());

    getThisObject()->setPropertyFlag(TDerivedClass::ToggleStateProperty, KZU_PROPERTY_MANAGER_FLAG_KEEP_DURING_PATCHING);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onAttached()
{
    TBaseClass::onAttached();

    setPressed(false);

    m_clickManipulator = ClickManipulator::create(getThisObject()->getDomain());
    getThisObject()->addInputManipulator(m_clickManipulator);

    if (isPressOnHover())
    {
        m_clickManipulator->setHoverToBegin(true);
    }

    configureMultiClickManipulator();
    configureLongPressManipulator();

    refreshButtonGroup(true);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onDetached()
{
    kzsError result;

    if (m_clickManipulator)
    {
        getThisObject()->removeInputManipulator(*m_clickManipulator);
        m_clickManipulator.reset();
    }

    if (m_longPressManipulator)
    {
        getThisObject()->removeInputManipulator(*m_longPressManipulator);
        m_longPressManipulator.reset();
    }

    // TODO: replace with task scheduler functionality when available
    result = kzuMessageDispatcherRemoveTimerHandler(getThisObject()->getMessageDispatcher(), repeatHandler, getThisObject());
    kzThrowIfError(result);

    TBaseClass::onDetached();
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::enterPress()
{
    ++m_pressedCounter;
    if (m_pressedCounter == 1)
    {
        setPressed(true);
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::leavePress()
{
    --m_pressedCounter;
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::cancelPress()
{
    if (m_pressedCounter == 0)
    {
        setPressed(false);
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::processClick()
{
    if (m_pressedCounter == 0 && !m_clickManipulator->isPressed())
    {
        toggle();

        ClickedMessageArguments buttonClickArguments;
        getThisObject()->dispatchMessage(ClickedMessage, buttonClickArguments);

        string command = getThisObject()->getProperty(Command::CommandProperty);
        if (!command.empty())
        {

            Command::CommandMessageArguments commandArguments;
            commandArguments.setCommand(kanzi::move(command));
            getThisObject()->dispatchMessage(Command::CommandMessage, commandArguments);
        }
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onClickEnter(ClickManipulator::ClickEnterMessageArguments&)
{
    kzsError result;

    enterPress();

    // This is conversion from legacy property which is of type float
    unsigned int interval = static_cast<unsigned int>(getAutoClickInterval());
    if (interval > 0)
    {
        // Remove old timer subscription in case there is one.
        result = kzuMessageDispatcherRemoveTimerHandler(getThisObject()->getMessageDispatcher(), repeatHandler, getThisObject());
        kzThrowIfError(result);

        result = kzuMessageDispatcherAddTimerHandler(getThisObject()->getMessageDispatcher(), interval, KZU_TIMER_MESSAGE_MODE_REPEAT_BATCH,
            repeatHandler, getThisObject());
        kzThrowIfError(result);
    }

    PointerEnteredMessageArguments buttonEnterArguments;
    getThisObject()->dispatchMessage(PointerEnteredMessage, buttonEnterArguments);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onClickLeave(ClickManipulator::ClickLeaveMessageArguments&)
{
    leavePress();
    cancelPress();

    kzsError result;

    // In case we send repeat messages, stop sending them.
    result = kzuMessageDispatcherRemoveTimerHandler(getThisObject()->getMessageDispatcher(), repeatHandler, getThisObject());
    kzThrowIfError(result);

    PointerLeftMessageArguments buttonLeaveArguments;
    getThisObject()->dispatchMessage(PointerLeftMessage, buttonLeaveArguments);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onClickBegin(ClickManipulator::ClickBeginMessageArguments&)
{
    PressedMessageArguments buttonDownArguments;
    getThisObject()->dispatchMessage(PressedMessage, buttonDownArguments);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onClick(ClickManipulator::ClickMessageArguments&)
{
    cancelPress();
    processClick();
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onClickCancel(ClickManipulator::ClickCancelMessageArguments&)
{
    cancelPress();

    CanceledMessageArguments buttonCancelArguments;
    getThisObject()->dispatchMessage(CanceledMessage, buttonCancelArguments);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onLongPress(LongPressManipulator::LongPressMessageArguments&)
{
    LongPressMessageArguments buttonLongPressArguments;
    getThisObject()->dispatchMessage(LongPressMessage, buttonLongPressArguments);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onKeyDown(Keyboard::KeyDownMessageArguments& arguments)
{
    KzsInputKey button = arguments.getKey();
    if (button == KZS_KEY_ENTER ||
        button == KZS_KEY_SPACE ||
        button == KZS_KEY_NUM_ENTER)
    {
        enterPress();
    }
    else
    {
        arguments.setHandled(false);
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onKeyUp(Keyboard::KeyUpMessageArguments& arguments)
{
    KzsInputKey button = arguments.getKey();
    if (button == KZS_KEY_ENTER ||
        button == KZS_KEY_SPACE ||
        button == KZS_KEY_NUM_ENTER)
    {
        leavePress();
        cancelPress();
        processClick();
    }
    else
    {
        arguments.setHandled(false);
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::toggle()
{
    const unsigned int stateCount = getToggleStateCount();
    unsigned int oldState = getToggleState();

    // If the button is in a toggle button group and checked, don't react to the click.
    if (stateCount > 1 && !(oldState > 0 && m_toggleButtonGroupMessageToken.isValid()))
    {
        unsigned int newState = (oldState + 1) % stateCount;

        setToggleState(newState);
    }
}

template <typename TBaseClass, typename TDerivedClass>
kzsError ButtonConceptImpl<TBaseClass, TDerivedClass>::repeatHandler(MessageArguments* /*message*/, void* userData)
{
    TDerivedClass* node = static_cast<TDerivedClass*>(userData);

    if (node->isPressed())
    {
        ClickedMessageArguments buttonClickArguments;
        node->dispatchMessage(ClickedMessage, buttonClickArguments);
    }

    kzsSuccess();
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::removeFromButtonGroup()
{
    ToggleButtonGroupConcept* buttonGroup = 0;

    for (Node* parent = getThisObject()->getParent(); parent; parent = parent->getParent())
    {
        buttonGroup = dynamic_cast<ToggleButtonGroupConcept*>(parent);
        if (buttonGroup)
        {
            if (m_toggleButtonGroupMessageToken.isValid())
            {
                buttonGroup->getDerivedObject()->removeMessageHandler(m_toggleButtonGroupMessageToken);
            }
            buttonGroup->unregisterButton(getThisObject());
        }
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::refreshButtonGroup(bool forceSearch)
{
    if (getThisObject()->hasLocalValue(IndexInGroupProperty) && (!m_toggleButtonGroupMessageToken.isValid() || forceSearch))
    {
        int groupIndex = getIndexInGroup();
        ToggleButtonGroupConcept* buttonGroup = 0;

        for (Node* parent = getThisObject()->getParent(); parent && !buttonGroup; parent = parent->getParent())
        {
            buttonGroup = dynamic_cast<ToggleButtonGroupConcept*>(parent);
            if (buttonGroup)
            {
                break;
            }
        }

        if (buttonGroup)
        {
            m_effectiveButtonGroupId = groupIndex == -1 ? buttonGroup->m_nextFreeId++ : groupIndex;

            // Remove from any previous group.
            removeFromButtonGroup();

            m_toggleButtonGroupMessageToken = buttonGroup->getDerivedObject()->addMessageFilter(ToggleButtonGroupConcept::ToggledMessage,
                                                    getThisObject(), &ButtonConceptImpl::onButtonGroupToggled);
            // If we are toggled, send the toggled message so that other buttons can untoggle themselves.
            unsigned int value = getToggleState();
            if (value > 0)
            {
                sendToggledMessage();
            }
        }
        else
        {
            m_effectiveButtonGroupId = nullopt;
        }
    }
    else if (m_toggleButtonGroupMessageToken.isValid())
    {
        removeFromButtonGroup();
    }
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::sendToggledMessage()
{
    ToggleButtonGroupConcept::ToggledMessageArguments arguments;
    getThisObject()->dispatchMessage(ToggleButtonGroupConcept::ToggledMessage, arguments);
}

template <typename TBaseClass, typename TDerivedClass>
void ButtonConceptImpl<TBaseClass, TDerivedClass>::onButtonGroupToggled(ToggleButtonGroupConcept::ToggledMessageArguments& message)
{
    message.setHandled(false);
    if (!message.isFrom(*getThisObject()))
    {
        // Some other button in the group was toggled -- uncheck us.
        if (getToggleState() > 0)
        {
            setToggleState(0);
        }
    }
}

template <typename TBaseClass, typename TDerivedClass>
PropertyTypeEditorInfoSharedPtr ButtonConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary
            {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Button";

                return dict;
            }()
        ));
}

}

#endif
