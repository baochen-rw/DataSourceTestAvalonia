// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Page.
// Do not include this file directly. Include page.hpp instead.



    /// State property.
    /// The state of this Page node: false (inactive and invisible) or true (active and visible) (read-only).
    /// The default value is false.
    /// \see setState(), isState()
    static PropertyType<bool> StateProperty;

    /// Gets the value of #StateProperty.
    /// \see setState()
    bool isState() const { return getProperty(StateProperty); }

    /// Sets the value of #StateProperty.
    /// \see isState()
    void setState(bool value) { setProperty(StateProperty, value); }


    /// TransitionPhase property.
    /// The phase of the transition. For example, use for pixel-based effects.
    /// The default value is 0.0f.
    /// \see setTransitionPhase(), getTransitionPhase()
    static PropertyType<float> TransitionPhaseProperty;

    /// Gets the value of #TransitionPhaseProperty.
    /// \see setTransitionPhase()
    float getTransitionPhase() const { return getProperty(TransitionPhaseProperty); }

    /// Sets the value of #TransitionPhaseProperty.
    /// \see getTransitionPhase()
    void setTransitionPhase(float value) { setProperty(TransitionPhaseProperty, value); }


    /// AutoActivate property.
    /// Always activate this Page node when its parent is active.
    /// The default value is false.
    /// \see setAutoActivate(), isAutoActivate()
    static PropertyType<bool> AutoActivateProperty;

    /// Gets the value of #AutoActivateProperty.
    /// \see setAutoActivate()
    bool isAutoActivate() const { return getProperty(AutoActivateProperty); }

    /// Sets the value of #AutoActivateProperty.
    /// \see isAutoActivate()
    void setAutoActivate(bool value) { setProperty(AutoActivateProperty, value); }


    /// SlideOffset property.
    /// The offset to slide a Page node in horizontal or vertical direction:\nX [-1, 1] to move the Page node horizontally\nY [-1, 1] to move the Page node vertically
    /// The default value is Vector2(0.0f, 0.0f).
    /// \see setSlideOffset(), getSlideOffset()
    static PropertyType<Vector2> SlideOffsetProperty;

    /// Gets the value of #SlideOffsetProperty.
    /// \see setSlideOffset()
    Vector2 getSlideOffset() const { return getProperty(SlideOffsetProperty); }

    /// Sets the value of #SlideOffsetProperty.
    /// \see getSlideOffset()
    void setSlideOffset(Vector2 value) { setProperty(SlideOffsetProperty, value); }


    /// ScaleOffset property.
    /// The factor by which to scale a Page node.
    /// The default value is Vector2(1.0f, 1.0f).
    /// \see setScaleOffset(), getScaleOffset()
    static PropertyType<Vector2> ScaleOffsetProperty;

    /// Gets the value of #ScaleOffsetProperty.
    /// \see setScaleOffset()
    Vector2 getScaleOffset() const { return getProperty(ScaleOffsetProperty); }

    /// Sets the value of #ScaleOffsetProperty.
    /// \see getScaleOffset()
    void setScaleOffset(Vector2 value) { setProperty(ScaleOffsetProperty, value); }


    /// RotationOffset property.
    /// The angle in degrees by which to rotate a Page node.
    /// The default value is 0.0f.
    /// \see setRotationOffset(), getRotationOffset()
    static PropertyType<float> RotationOffsetProperty;

    /// Gets the value of #RotationOffsetProperty.
    /// \see setRotationOffset()
    float getRotationOffset() const { return getProperty(RotationOffsetProperty); }

    /// Sets the value of #RotationOffsetProperty.
    /// \see getRotationOffset()
    void setRotationOffset(float value) { setProperty(RotationOffsetProperty, value); }


