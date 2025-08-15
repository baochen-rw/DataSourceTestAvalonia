// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Constraints.
// Do not include this file directly. Include constraints.hpp instead.



    /// Position property.
    /// 
    /// The default value is "".
    /// \see setPosition(), getPosition()
    static PropertyType<string> PositionProperty;


    /// Orientation property.
    /// 
    /// The default value is "".
    /// \see setOrientation(), getOrientation()
    static PropertyType<string> OrientationProperty;


    /// InWorldCoordinates property.
    /// 
    /// The default value is false.
    /// \see setInWorldCoordinates(), isInWorldCoordinates()
    static PropertyType<bool> InWorldCoordinatesProperty;


    /// FaceToCamera property.
    /// 
    /// The default value is false.
    /// \see setFaceToCamera(), isFaceToCamera()
    static PropertyType<bool> FaceToCameraProperty;


    /// FaceToCameraIsBillboarding property.
    /// 
    /// The default value is true.
    /// \see setFaceToCameraIsBillboarding(), isFaceToCameraIsBillboarding()
    static PropertyType<bool> FaceToCameraIsBillboardingProperty;


    /// FaceToCameraCylindral property.
    /// 
    /// The default value is false.
    /// \see setFaceToCameraCylindral(), isFaceToCameraCylindral()
    static PropertyType<bool> FaceToCameraCylindralProperty;


    /// FaceToCameraTargetCamera property.
    /// 
    /// The default value is "".
    /// \see setFaceToCameraTargetCamera(), getFaceToCameraTargetCamera()
    static PropertyType<string> FaceToCameraTargetCameraProperty;


    /// LookAt property.
    /// 
    /// The default value is "".
    /// \see setLookAt(), getLookAt()
    static PropertyType<string> LookAtProperty;


