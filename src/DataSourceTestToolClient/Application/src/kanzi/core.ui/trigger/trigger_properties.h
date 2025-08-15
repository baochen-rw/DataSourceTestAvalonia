// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Trigger.
// Do not include this file directly. Include trigger.hpp instead.



    /// ForwardedMessage property.
    /// 
    /// The default value is 0.
    /// \see setForwardedMessage(), getForwardedMessage()
    static PropertyType<void*> ForwardedMessageProperty;

    /// Gets the value of #ForwardedMessageProperty.
    /// \see setForwardedMessage()
    void* getForwardedMessage() const { return getProperty(ForwardedMessageProperty); }

    /// Sets the value of #ForwardedMessageProperty.
    /// \see getForwardedMessage()
    void setForwardedMessage(void* value) { setProperty(ForwardedMessageProperty, value); }


