// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for InputManipulator::InputMessageArguments.
// Do not include this file directly. Include input_manipulator.hpp instead.



    /// ManipulatorPoint property.
    /// 
    /// The default value is Vector2(0.0f, 0.0f).
    /// \see setManipulatorPoint(), getManipulatorPoint()
    static PropertyType<Vector2> ManipulatorPointProperty;


    /// ManipulatorRayOrigin property.
    /// 
    /// The default value is Vector3(0.0f, 0.0f, 0.0f).
    /// \see setManipulatorRayOrigin(), getManipulatorRayOrigin()
    static PropertyType<Vector3> ManipulatorRayOriginProperty;


    /// ManipulatorRayDirection property.
    /// 
    /// The default value is Vector3(0.0f, 0.0f, -1.0f).
    /// \see setManipulatorRayDirection(), getManipulatorRayDirection()
    static PropertyType<Vector3> ManipulatorRayDirectionProperty;


    /// HitTestPoint property.
    /// 
    /// The default value is Vector2(KZS_NAN, KZS_NAN).
    /// \see setHitTestPoint(), getHitTestPoint()
    static PropertyType<Vector2> HitTestPointProperty;


    /// HitTestRayOrigin property.
    /// 
    /// The default value is Vector3(0.0f, 0.0f, 0.0f).
    /// \see setHitTestRayOrigin(), getHitTestRayOrigin()
    static PropertyType<Vector3> HitTestRayOriginProperty;


    /// HitTestRayDirection property.
    /// 
    /// The default value is Vector3(0.0f, 0.0f, -1.0f).
    /// \see setHitTestRayDirection(), getHitTestRayDirection()
    static PropertyType<Vector3> HitTestRayDirectionProperty;


    /// HitTestObject property.
    /// 
    /// The default value is 0.
    /// \see setHitTestObject(), getHitTestObject()
    static PropertyType<void*> HitTestObjectProperty;


