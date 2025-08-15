// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for TrajectoryListBox3D.
// Do not include this file directly. Include trajectory_list_box3d.hpp instead.



    /// Trajectory property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setTrajectory(), getTrajectory()
    static PropertyType<ResourceSharedPtr> TrajectoryProperty;

    /// Gets the value of #TrajectoryProperty.
    /// \see setTrajectory()
    ResourceSharedPtr getTrajectory() const { return getProperty(TrajectoryProperty); }

    /// Sets the value of #TrajectoryProperty.
    /// \see getTrajectory()
    void setTrajectory(ResourceSharedPtr value) { setProperty(TrajectoryProperty, value); }


    /// ItemAreaBegin property.
    /// 
    /// The default value is 0.0f.
    /// \see setItemAreaBegin(), getItemAreaBegin()
    static PropertyType<float> ItemAreaBeginProperty;

    /// Gets the value of #ItemAreaBeginProperty.
    /// \see setItemAreaBegin()
    float getItemAreaBegin() const { return getProperty(ItemAreaBeginProperty); }

    /// Sets the value of #ItemAreaBeginProperty.
    /// \see getItemAreaBegin()
    void setItemAreaBegin(float value) { setProperty(ItemAreaBeginProperty, value); }


    /// ItemAreaEnd property.
    /// 
    /// The default value is 1.0f.
    /// \see setItemAreaEnd(), getItemAreaEnd()
    static PropertyType<float> ItemAreaEndProperty;

    /// Gets the value of #ItemAreaEndProperty.
    /// \see setItemAreaEnd()
    float getItemAreaEnd() const { return getProperty(ItemAreaEndProperty); }

    /// Sets the value of #ItemAreaEndProperty.
    /// \see getItemAreaEnd()
    void setItemAreaEnd(float value) { setProperty(ItemAreaEndProperty, value); }


    /// AlignToTangent property.
    /// 
    /// The default value is false.
    /// \see setAlignToTangent(), isAlignToTangent()
    static PropertyType<bool> AlignToTangentProperty;

    /// Gets the value of #AlignToTangentProperty.
    /// \see setAlignToTangent()
    bool isAlignToTangent() const { return getProperty(AlignToTangentProperty); }

    /// Sets the value of #AlignToTangentProperty.
    /// \see isAlignToTangent()
    void setAlignToTangent(bool value) { setProperty(AlignToTangentProperty, value); }


    /// Spacing property.
    /// 
    /// The default value is 0.0f.
    /// \see setSpacing(), getSpacing()
    static PropertyType<float> SpacingProperty;

    /// Gets the value of #SpacingProperty.
    /// \see setSpacing()
    float getSpacing() const { return getProperty(SpacingProperty); }

    /// Sets the value of #SpacingProperty.
    /// \see getSpacing()
    void setSpacing(float value) { setProperty(SpacingProperty, value); }


    /// CursorOffset property.
    /// 
    /// The default value is 0.5f.
    /// \see setCursorOffset(), getCursorOffset()
    static PropertyType<float> CursorOffsetProperty;

    /// Gets the value of #CursorOffsetProperty.
    /// \see setCursorOffset()
    float getCursorOffset() const { return getProperty(CursorOffsetProperty); }

    /// Sets the value of #CursorOffsetProperty.
    /// \see getCursorOffset()
    void setCursorOffset(float value) { setProperty(CursorOffsetProperty, value); }


    /// ScrollAxis property.
    /// 
    /// The default value is Vector2(1.0f,  0.0f).
    /// \see setScrollAxis(), getScrollAxis()
    static PropertyType<Vector2> ScrollAxisProperty;

    /// Gets the value of #ScrollAxisProperty.
    /// \see setScrollAxis()
    Vector2 getScrollAxis() const { return getProperty(ScrollAxisProperty); }

    /// Sets the value of #ScrollAxisProperty.
    /// \see getScrollAxis()
    void setScrollAxis(Vector2 value) { setProperty(ScrollAxisProperty, value); }


    /// RecognitionThreshold property.
    /// 
    /// The default value is 5.0f.
    /// \see setRecognitionThreshold(), getRecognitionThreshold()
    static PropertyType<float> RecognitionThresholdProperty;

    /// Gets the value of #RecognitionThresholdProperty.
    /// \see setRecognitionThreshold()
    float getRecognitionThreshold() const { return getProperty(RecognitionThresholdProperty); }

    /// Sets the value of #RecognitionThresholdProperty.
    /// \see getRecognitionThreshold()
    void setRecognitionThreshold(float value) { setProperty(RecognitionThresholdProperty, value); }


    /// MinimumNumberOfTouches property.
    /// 
    /// The default value is 1.
    /// \see setMinimumNumberOfTouches(), getMinimumNumberOfTouches()
    static PropertyType<int> MinimumNumberOfTouchesProperty;

    /// Gets the value of #MinimumNumberOfTouchesProperty.
    /// \see setMinimumNumberOfTouches()
    int getMinimumNumberOfTouches() const { return getProperty(MinimumNumberOfTouchesProperty); }

    /// Sets the value of #MinimumNumberOfTouchesProperty.
    /// \see getMinimumNumberOfTouches()
    void setMinimumNumberOfTouches(int value) { setProperty(MinimumNumberOfTouchesProperty, value); }


    /// MaximumNumberOfTouches property.
    /// 
    /// The default value is 10.
    /// \see setMaximumNumberOfTouches(), getMaximumNumberOfTouches()
    static PropertyType<int> MaximumNumberOfTouchesProperty;

    /// Gets the value of #MaximumNumberOfTouchesProperty.
    /// \see setMaximumNumberOfTouches()
    int getMaximumNumberOfTouches() const { return getProperty(MaximumNumberOfTouchesProperty); }

    /// Sets the value of #MaximumNumberOfTouchesProperty.
    /// \see getMaximumNumberOfTouches()
    void setMaximumNumberOfTouches(int value) { setProperty(MaximumNumberOfTouchesProperty, value); }


    /// Sensitivity property.
    /// 
    /// The default value is 1.0f.
    /// \see setSensitivity(), getSensitivity()
    static PropertyType<float> SensitivityProperty;

    /// Gets the value of #SensitivityProperty.
    /// \see setSensitivity()
    float getSensitivity() const { return getProperty(SensitivityProperty); }

    /// Sets the value of #SensitivityProperty.
    /// \see getSensitivity()
    void setSensitivity(float value) { setProperty(SensitivityProperty, value); }


    /// SlidingAccelerationCoefficient property.
    /// 
    /// The default value is 40.0f.
    /// \see setSlidingAccelerationCoefficient(), getSlidingAccelerationCoefficient()
    static PropertyType<float> SlidingAccelerationCoefficientProperty;

    /// Gets the value of #SlidingAccelerationCoefficientProperty.
    /// \see setSlidingAccelerationCoefficient()
    float getSlidingAccelerationCoefficient() const { return getProperty(SlidingAccelerationCoefficientProperty); }

    /// Sets the value of #SlidingAccelerationCoefficientProperty.
    /// \see getSlidingAccelerationCoefficient()
    void setSlidingAccelerationCoefficient(float value) { setProperty(SlidingAccelerationCoefficientProperty, value); }


    /// SlidingDragCoefficient property.
    /// 
    /// The default value is 80.0f.
    /// \see setSlidingDragCoefficient(), getSlidingDragCoefficient()
    static PropertyType<float> SlidingDragCoefficientProperty;

    /// Gets the value of #SlidingDragCoefficientProperty.
    /// \see setSlidingDragCoefficient()
    float getSlidingDragCoefficient() const { return getProperty(SlidingDragCoefficientProperty); }

    /// Sets the value of #SlidingDragCoefficientProperty.
    /// \see getSlidingDragCoefficient()
    void setSlidingDragCoefficient(float value) { setProperty(SlidingDragCoefficientProperty, value); }


    /// DraggingAccelerationCoefficient property.
    /// 
    /// The default value is 80.0f.
    /// \see setDraggingAccelerationCoefficient(), getDraggingAccelerationCoefficient()
    static PropertyType<float> DraggingAccelerationCoefficientProperty;

    /// Gets the value of #DraggingAccelerationCoefficientProperty.
    /// \see setDraggingAccelerationCoefficient()
    float getDraggingAccelerationCoefficient() const { return getProperty(DraggingAccelerationCoefficientProperty); }

    /// Sets the value of #DraggingAccelerationCoefficientProperty.
    /// \see getDraggingAccelerationCoefficient()
    void setDraggingAccelerationCoefficient(float value) { setProperty(DraggingAccelerationCoefficientProperty, value); }


    /// DraggingDragCoefficient property.
    /// 
    /// The default value is 150.0f.
    /// \see setDraggingDragCoefficient(), getDraggingDragCoefficient()
    static PropertyType<float> DraggingDragCoefficientProperty;

    /// Gets the value of #DraggingDragCoefficientProperty.
    /// \see setDraggingDragCoefficient()
    float getDraggingDragCoefficient() const { return getProperty(DraggingDragCoefficientProperty); }

    /// Sets the value of #DraggingDragCoefficientProperty.
    /// \see getDraggingDragCoefficient()
    void setDraggingDragCoefficient(float value) { setProperty(DraggingDragCoefficientProperty, value); }


    /// DraggingImpulseFactor property.
    /// 
    /// The default value is 2.0f.
    /// \see setDraggingImpulseFactor(), getDraggingImpulseFactor()
    static PropertyType<float> DraggingImpulseFactorProperty;

    /// Gets the value of #DraggingImpulseFactorProperty.
    /// \see setDraggingImpulseFactor()
    float getDraggingImpulseFactor() const { return getProperty(DraggingImpulseFactorProperty); }

    /// Sets the value of #DraggingImpulseFactorProperty.
    /// \see getDraggingImpulseFactor()
    void setDraggingImpulseFactor(float value) { setProperty(DraggingImpulseFactorProperty, value); }


    /// SwipeDistance property.
    /// 
    /// The default value is 0.005f.
    /// \see setSwipeDistance(), getSwipeDistance()
    static PropertyType<float> SwipeDistanceProperty;

    /// Gets the value of #SwipeDistanceProperty.
    /// \see setSwipeDistance()
    float getSwipeDistance() const { return getProperty(SwipeDistanceProperty); }

    /// Sets the value of #SwipeDistanceProperty.
    /// \see getSwipeDistance()
    void setSwipeDistance(float value) { setProperty(SwipeDistanceProperty, value); }


    /// Gets the value of #LoopingProperty.
    /// \see setLooping()
    bool isLooping() const { return getProperty(LoopingProperty); }

    /// Sets the value of #LoopingProperty.
    /// \see isLooping()
    void setLooping(bool value) { setProperty(LoopingProperty, value); }

    /// LoopingProperty property.
    /// 
    /// The default value is false.
    /// \see setLooping(), isLooping()
    static PropertyType<bool> LoopingProperty;

    /// AllowedScrollAxis property
    /// Sets the axis on which you want to allow a Trajectory List Box node to scroll.
    /// The default value is \l ScrollViewConcept::AllAxes.
    /// \see ScrollViewConcept::AllowedScrollAxisProperty, getAllowedScrollAxis(), setAllowedScrollAxis()
    static PropertyType<ScrollViewConcept::AllowedScrollAxis> AllowedScrollAxisProperty;

    /// Returns the value of the #AllowedScrollAxisProperty.
    /// \see setAllowedScrollAxis()
    ScrollViewConcept::AllowedScrollAxis getAllowedScrollAxis() const { return getProperty(AllowedScrollAxisProperty); }

    /// Sets the #AllowedScrollAxisProperty value.
    /// \param axis The axis on which you want to allow scrolling.
    /// \see getAllowedScrollAxis()
    void setAllowedScrollAxis(ScrollViewConcept::AllowedScrollAxis axis) { setProperty(AllowedScrollAxisProperty, axis); }
