// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for MessageTrigger.
// Do not include this file directly. Include message_trigger.hpp instead.



    /// MessageType property.
    /// 
    /// The default value is "".
    /// \see setMessageType(), getMessageType()
    static PropertyType<string> MessageTypeProperty;

    /// Gets the value of #MessageTypeProperty.
    /// \see setMessageType()
    string getMessageType() const { return getProperty(MessageTypeProperty); }

    /// Sets the value of #MessageTypeProperty.
    /// \see getMessageType()
    void setMessageType(string value) { setProperty(MessageTypeProperty, value); }


    /// SetHandled property.
    /// 
    /// The default value is true.
    /// \see setSetHandled(), isSetHandled()
    static PropertyType<bool> SetHandledProperty;

    /// Gets the value of #SetHandledProperty.
    /// \see setSetHandled()
    bool isSetHandled() const { return getProperty(SetHandledProperty); }

    /// Sets the value of #SetHandledProperty.
    /// \see isSetHandled()
    void setSetHandled(bool value) { setProperty(SetHandledProperty, value); }


    /// RoutingMode property.
    /// 
    /// The default value is MessageRoutingBubbling.
    /// \see setRoutingMode(), getRoutingMode()
    static PropertyType<MessageRouting> RoutingModeProperty;

    /// Gets the value of #RoutingModeProperty.
    /// \see setRoutingMode()
    MessageRouting getRoutingMode() const { return getProperty(RoutingModeProperty); }

    /// Sets the value of #RoutingModeProperty.
    /// \see getRoutingMode()
    void setRoutingMode(MessageRouting value) { setProperty(RoutingModeProperty, value); }


    /// MessageSource property.
    /// 
    /// The default value is ".".
    /// \see setMessageSource(), getMessageSource()
    static PropertyType<string> MessageSourceProperty;

    /// Gets the value of #MessageSourceProperty.
    /// \see setMessageSource()
    string getMessageSource() const { return getProperty(MessageSourceProperty); }

    /// Sets the value of #MessageSourceProperty.
    /// \see getMessageSource()
    void setMessageSource(string value) { setProperty(MessageSourceProperty, value); }


