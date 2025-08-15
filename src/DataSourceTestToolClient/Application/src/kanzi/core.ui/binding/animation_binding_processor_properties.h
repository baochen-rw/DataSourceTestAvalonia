// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for AnimationBindingProcessor.
// Do not include this file directly. Include animation_binding_processor.hpp instead.



    /// Animation property.
    /// 
    /// The default value is "".
    /// \see setAnimation(), getAnimation()
    static PropertyType<string> AnimationProperty;

    /// Gets the value of #AnimationProperty.
    /// \see setAnimation()
    string getAnimation() const { return getProperty(AnimationProperty); }

    /// Sets the value of #AnimationProperty.
    /// \see getAnimation()
    void setAnimation(string value) { setProperty(AnimationProperty, value); }


