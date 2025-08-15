// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for PageTransitionCollection.
// Do not include this file directly. Include page_transition_collection.hpp instead.



    /// PageTransitionDuration property.
    /// The duration of a Page node transition (in milliseconds).
    /// The default value is 500.
    /// \see setPageTransitionDuration(), getPageTransitionDuration()
    static PropertyType<int> PageTransitionDurationProperty;


    /// PageTransitionFrom property.
    /// The selection criteria for the source Page node. Use * for any Page node.
    /// The default value is "".
    /// \see setPageTransitionFrom(), getPageTransitionFrom()
    static PropertyType<string> PageTransitionFromProperty;


    /// PageTransitionTo property.
    /// The selection criteria for the target Page node. Use * for any Page node.
    /// The default value is "".
    /// \see setPageTransitionTo(), getPageTransitionTo()
    static PropertyType<string> PageTransitionToProperty;


    /// PageTransitionDirection property.
    /// Defines whether the transition is unidirectional (one way) or bidirectional (two way).
    /// The default value is PageTransitionCollection::Transition::Bidirectional.
    /// \see setPageTransitionDirection(), getPageTransitionDirection()
    static PropertyType<PageTransitionCollection::Transition::Direction> PageTransitionDirectionProperty;


    /// PageTransitionAnimationPropertyType property.
    /// Defines which property to animate.
    /// The default value is "".
    /// \see setPageTransitionAnimationPropertyType(), getPageTransitionAnimationPropertyType()
    static PropertyType<string> PageTransitionAnimationPropertyTypeProperty;


    /// PageTransitionAnimationAnimationTarget property.
    /// Defines the animation target, either page transitioning in or page transitioning out.
    /// The default value is PageTransitionCollection::Transition::PageIn.
    /// \see setPageTransitionAnimationAnimationTarget(), getPageTransitionAnimationAnimationTarget()
    static PropertyType<PageTransitionCollection::Transition::AnimationTarget> PageTransitionAnimationAnimationTargetProperty;


    /// PageTransitionAnimationStartValue property.
    /// The starting value for the animation.
    /// The default value is "".
    /// \see setPageTransitionAnimationStartValue(), getPageTransitionAnimationStartValue()
    static PropertyType<string> PageTransitionAnimationStartValueProperty;


    /// PageTransitionAnimationEndValue property.
    /// The ending value for the animation.
    /// The default value is "".
    /// \see setPageTransitionAnimationEndValue(), getPageTransitionAnimationEndValue()
    static PropertyType<string> PageTransitionAnimationEndValueProperty;


