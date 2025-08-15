// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for ButtonConcept.
// Do not include this file directly. Include button.hpp instead.



    /// IsPressed property.
    /// Whether the button is in down state.
    /// The default value is false.
    /// \see setIsPressed(), isIsPressed()
    static PropertyType<bool> IsPressedProperty;


    /// LongPressInterval property.
    /// Occurs when the button is in down state for the set amount of milliseconds. Set to 0 to disable.
    /// The default value is 0.0f.
    /// \see setLongPressInterval(), getLongPressInterval()
    static PropertyType<float> LongPressIntervalProperty;


    /// PressOnHover property.
    /// Whether hovering the pointer over the button makes sets it into down state.
    /// The default value is false.
    /// \see setPressOnHover(), isPressOnHover()
    static PropertyType<bool> PressOnHoverProperty;


    /// AutoClickInterval property.
    /// An interval in milliseconds after which a held down button sends a button click message. Set to 0 to disable.
    /// The default value is 0.0f.
    /// \see setAutoClickInterval(), getAutoClickInterval()
    static PropertyType<float> AutoClickIntervalProperty;


    /// ToggleState property.
    /// The current toggle state of a toggle button.
    /// The default value is 0.
    /// \see setToggleState(), getToggleState()
    static PropertyType<int> ToggleStateProperty;


    /// ToggleStateCount property.
    /// The number of toggle states of a toggle button.
    /// The default value is 0.
    /// \see setToggleStateCount(), getToggleStateCount()
    static PropertyType<int> ToggleStateCountProperty;


    /// IndexInGroup property.
    /// 
    /// The default value is -1.
    /// \see setIndexInGroup(), getIndexInGroup()
    static PropertyType<int> IndexInGroupProperty;


