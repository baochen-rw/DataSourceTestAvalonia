// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for GridListBoxConcept.
// Do not include this file directly. Include grid_list_box.hpp instead.



    /// Direction property.
    /// 
    /// The default value is GridListBoxConcept::GridDirectionRight.
    /// \see setDirection(), getDirection()
    static PropertyType<GridListBoxConcept::GridDirection> DirectionProperty;


    /// CellWidth property.
    /// 
    /// The default value is 1.0f.
    /// \see setCellWidth(), getCellWidth()
    static PropertyType<float> CellWidthProperty;


    /// CellHeight property.
    /// 
    /// The default value is 1.0f.
    /// \see setCellHeight(), getCellHeight()
    static PropertyType<float> CellHeightProperty;


    /// ItemAreaBegin property.
    /// 
    /// The default value is 0.0f.
    /// \see setItemAreaBegin(), getItemAreaBegin()
    static PropertyType<float> ItemAreaBeginProperty;


    /// ItemAreaEnd property.
    /// 
    /// The default value is 1.0f.
    /// \see setItemAreaEnd(), getItemAreaEnd()
    static PropertyType<float> ItemAreaEndProperty;


    /// ScrollAxis property.
    /// 
    /// The default value is Vector2(1.0f,  0.0f).
    /// \see setScrollAxis(), getScrollAxis()
    static PropertyType<Vector2> ScrollAxisProperty;


    /// RecognitionThreshold property.
    /// 
    /// The default value is 5.0f.
    /// \see setRecognitionThreshold(), getRecognitionThreshold()
    static PropertyType<float> RecognitionThresholdProperty;


    /// MinimumNumberOfTouches property.
    /// 
    /// The default value is 1.
    /// \see setMinimumNumberOfTouches(), getMinimumNumberOfTouches()
    static PropertyType<int> MinimumNumberOfTouchesProperty;


    /// MaximumNumberOfTouches property.
    /// 
    /// The default value is 10.
    /// \see setMaximumNumberOfTouches(), getMaximumNumberOfTouches()
    static PropertyType<int> MaximumNumberOfTouchesProperty;


    /// Sensitivity property.
    /// 
    /// The default value is 1.0f.
    /// \see setSensitivity(), getSensitivity()
    static PropertyType<float> SensitivityProperty;


    /// SlidingAccelerationCoefficient property.
    /// 
    /// The default value is 40.0f.
    /// \see setSlidingAccelerationCoefficient(), getSlidingAccelerationCoefficient()
    static PropertyType<float> SlidingAccelerationCoefficientProperty;


    /// SlidingDragCoefficient property.
    /// 
    /// The default value is 80.0f.
    /// \see setSlidingDragCoefficient(), getSlidingDragCoefficient()
    static PropertyType<float> SlidingDragCoefficientProperty;


    /// DraggingAccelerationCoefficient property.
    /// 
    /// The default value is 80.0f.
    /// \see setDraggingAccelerationCoefficient(), getDraggingAccelerationCoefficient()
    static PropertyType<float> DraggingAccelerationCoefficientProperty;


    /// DraggingDragCoefficient property.
    /// 
    /// The default value is 150.0f.
    /// \see setDraggingDragCoefficient(), getDraggingDragCoefficient()
    static PropertyType<float> DraggingDragCoefficientProperty;


    /// DraggingImpulseFactor property.
    /// 
    /// The default value is 2.0f.
    /// \see setDraggingImpulseFactor(), getDraggingImpulseFactor()
    static PropertyType<float> DraggingImpulseFactorProperty;


    /// SwipeDistance property.
    /// 
    /// The default value is 0.01f.
    /// \see setSwipeDistance(), getSwipeDistance()
    static PropertyType<float> SwipeDistanceProperty;


    /// CalculatedOffset property.
    /// 
    /// The default value is 0.0f.
    /// \see setCalculatedOffset(), getCalculatedOffset()
    static PropertyType<float> CalculatedOffsetProperty;


    /// ScrollPosition property.
    /// 
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see setScrollPosition(), getScrollPosition()
    static PropertyType<Vector2> ScrollPositionProperty;


    /// ScrollTargetPosition property.
    /// 
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see setScrollTargetPosition(), getScrollTargetPosition()
    static PropertyType<Vector2> ScrollTargetPositionProperty;


    /// ScrollSpeed property.
    /// 
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see setScrollSpeed(), getScrollSpeed()
    static PropertyType<Vector2> ScrollSpeedProperty;


    /// Scrolling property.
    /// 
    /// The default value is false.
    /// \see setScrolling(), isScrolling()
    static PropertyType<bool> ScrollingProperty;


