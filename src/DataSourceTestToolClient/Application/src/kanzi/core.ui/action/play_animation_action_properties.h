// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for PlayAnimationAction.
// Do not include this file directly. Include play_animation_action.hpp instead.



    /// AnimatedObjectPath property.
    /// 
    /// The default value is ".".
    /// \see setAnimatedObjectPath(), getAnimatedObjectPath()
    static PropertyType<string> AnimatedObjectPathProperty;

    /// Gets the value of #AnimatedObjectPathProperty.
    /// \see setAnimatedObjectPath()
    string getAnimatedObjectPath() const { return getProperty(AnimatedObjectPathProperty); }

    /// Sets the value of #AnimatedObjectPathProperty.
    /// \see getAnimatedObjectPath()
    void setAnimatedObjectPath(string value) { setProperty(AnimatedObjectPathProperty, value); }


    /// Animation property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setAnimation(), getAnimation()
    static PropertyType<ResourceSharedPtr> AnimationProperty;

    /// Gets the value of #AnimationProperty.
    /// \see setAnimation()
    ResourceSharedPtr getAnimation() const { return getProperty(AnimationProperty); }

    /// Sets the value of #AnimationProperty.
    /// \see getAnimation()
    void setAnimation(ResourceSharedPtr value) { setProperty(AnimationProperty, value); }


    /// PlaybackMode property.
    /// 
    /// The default value is KZU_TIME_LINE_ENTRY_PLAYBACK_MODE_NORMAL.
    /// \see setPlaybackMode(), getPlaybackMode()
    static PropertyType<KzuTimeLineEntryPlaybackMode> PlaybackModeProperty;

    /// Gets the value of #PlaybackModeProperty.
    /// \see setPlaybackMode()
    KzuTimeLineEntryPlaybackMode getPlaybackMode() const { return getProperty(PlaybackModeProperty); }

    /// Sets the value of #PlaybackModeProperty.
    /// \see getPlaybackMode()
    void setPlaybackMode(KzuTimeLineEntryPlaybackMode value) { setProperty(PlaybackModeProperty, value); }


    /// DurationScale property.
    /// 
    /// The default value is 1.0f.
    /// \see setDurationScale(), getDurationScale()
    static PropertyType<float> DurationScaleProperty;

    /// Gets the value of #DurationScaleProperty.
    /// \see setDurationScale()
    float getDurationScale() const { return getProperty(DurationScaleProperty); }

    /// Sets the value of #DurationScaleProperty.
    /// \see getDurationScale()
    void setDurationScale(float value) { setProperty(DurationScaleProperty, value); }


    /// RepeatCount property.
    /// 
    /// The default value is 1.
    /// \see setRepeatCount(), getRepeatCount()
    static PropertyType<int> RepeatCountProperty;

    /// Gets the value of #RepeatCountProperty.
    /// \see setRepeatCount()
    int getRepeatCount() const { return getProperty(RepeatCountProperty); }

    /// Sets the value of #RepeatCountProperty.
    /// \see getRepeatCount()
    void setRepeatCount(int value) { setProperty(RepeatCountProperty, value); }


    /// RestoreOriginalValuesAfterPlayback property.
    /// 
    /// The default value is false.
    /// \see setRestoreOriginalValuesAfterPlayback(), isRestoreOriginalValuesAfterPlayback()
    static PropertyType<bool> RestoreOriginalValuesAfterPlaybackProperty;

    /// Gets the value of #RestoreOriginalValuesAfterPlaybackProperty.
    /// \see setRestoreOriginalValuesAfterPlayback()
    bool isRestoreOriginalValuesAfterPlayback() const { return getProperty(RestoreOriginalValuesAfterPlaybackProperty); }

    /// Sets the value of #RestoreOriginalValuesAfterPlaybackProperty.
    /// \see isRestoreOriginalValuesAfterPlayback()
    void setRestoreOriginalValuesAfterPlayback(bool value) { setProperty(RestoreOriginalValuesAfterPlaybackProperty, value); }


    /// RelativePlayback property.
    /// 
    /// The default value is false.
    /// \see setRelativePlayback(), isRelativePlayback()
    static PropertyType<bool> RelativePlaybackProperty;

    /// Gets the value of #RelativePlaybackProperty.
    /// \see setRelativePlayback()
    bool isRelativePlayback() const { return getProperty(RelativePlaybackProperty); }

    /// Sets the value of #RelativePlaybackProperty.
    /// \see isRelativePlayback()
    void setRelativePlayback(bool value) { setProperty(RelativePlaybackProperty, value); }


