// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for DispatchMessageAction.
// Do not include this file directly. Include dispatch_message_action.hpp instead.



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


    /// DispatchMode property.
    /// 
    /// The default value is DispatchMessageAction::DispatchModePost.
    /// \see setDispatchMode(), getDispatchMode()
    static PropertyType<DispatchMessageAction::DispatchMode> DispatchModeProperty;

    /// Gets the value of #DispatchModeProperty.
    /// \see setDispatchMode()
    DispatchMessageAction::DispatchMode getDispatchMode() const { return getProperty(DispatchModeProperty); }

    /// Sets the value of #DispatchModeProperty.
    /// \see getDispatchMode()
    void setDispatchMode(DispatchMessageAction::DispatchMode value) { setProperty(DispatchModeProperty, value); }


    /// RoutingTarget property.
    /// 
    /// The default value is ".".
    /// \see setRoutingTarget(), getRoutingTarget()
    static PropertyType<string> RoutingTargetProperty;

    /// Gets the value of #RoutingTargetProperty.
    /// \see setRoutingTarget()
    string getRoutingTarget() const { return getProperty(RoutingTargetProperty); }

    /// Sets the value of #RoutingTargetProperty.
    /// \see getRoutingTarget()
    void setRoutingTarget(string value) { setProperty(RoutingTargetProperty, value); }


    /// RoutingTargetLookup property.
    /// 
    /// The default value is "".
    /// \see setRoutingTargetLookup(), getRoutingTargetLookup()
    static PropertyType<string> RoutingTargetLookupProperty;

    /// Gets the value of #RoutingTargetLookupProperty.
    /// \see setRoutingTargetLookup()
    string getRoutingTargetLookup() const { return getProperty(RoutingTargetLookupProperty); }

    /// Sets the value of #RoutingTargetLookupProperty.
    /// \see getRoutingTargetLookup()
    void setRoutingTargetLookup(string value) { setProperty(RoutingTargetLookupProperty, value); }


