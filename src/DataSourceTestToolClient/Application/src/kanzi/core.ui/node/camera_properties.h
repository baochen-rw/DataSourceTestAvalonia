// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Camera.
// Do not include this file directly. Include camera.hpp instead.



    /// AspectRatio property.
    /// Defines the aspect ratio of a camera. This property has an effect only when the #DisableAspectRatioProperty is false.
    /// The default value is 1.666667f.
    /// \see setAspectRatio(), getAspectRatio()
    static PropertyType<float> AspectRatioProperty;

    /// Sets the value of #AspectRatioProperty.
    /// \see getAspectRatio()
    void setAspectRatio(float value) { setProperty(AspectRatioProperty, value); }


    /// DisableAspectRatio property.
    /// Whether to use the aspect ratio setting from the viewport in render pass. If the value is false, the aspect ratio is read from the #AspectRatioProperty of the camera.
    /// The default value is true.
    /// \see setDisableAspectRatio(), isDisableAspectRatio()
    static PropertyType<bool> DisableAspectRatioProperty;

    /// Gets the value of #DisableAspectRatioProperty.
    /// \see setDisableAspectRatio()
    bool isDisableAspectRatio() const { return getProperty(DisableAspectRatioProperty); }

    /// Sets the value of #DisableAspectRatioProperty.
    /// \see isDisableAspectRatio()
    void setDisableAspectRatio(bool value) { setProperty(DisableAspectRatioProperty, value); }


    /// ZNear property.
    /// Defines the distance of the camera near clipping plane. The camera shows only the objects that are farther away than the value set in this property.
    /// The default value is 0.01f.
    /// \see setZNear(), getZNear()
    static PropertyType<float> ZNearProperty;

    /// Gets the value of #ZNearProperty.
    /// \see setZNear()
    float getZNear() const { return getProperty(ZNearProperty); }

    /// Sets the value of #ZNearProperty.
    /// \see getZNear()
    void setZNear(float value) { setProperty(ZNearProperty, value); }


    /// ZFar property.
    /// Defines the distance of the camera far clipping plane. The camera shows only the objects that are closer than the value set in this property.
    /// The default value is 1000.0f.
    /// \see setZFar(), getZFar()
    static PropertyType<float> ZFarProperty;

    /// Gets the value of #ZFarProperty.
    /// \see setZFar()
    float getZFar() const { return getProperty(ZFarProperty); }

    /// Sets the value of #ZFarProperty.
    /// \see getZFar()
    void setZFar(float value) { setProperty(ZFarProperty, value); }


    /// ProjectionType property.
    /// Defines the camera type to either perspective or orthographic camera.
    /// The default value is Camera::ProjectionPerspective.
    /// \see setProjectionType(), getProjectionType()
    static PropertyType<Camera::ProjectionType> ProjectionTypeProperty;

    /// Gets the value of #ProjectionTypeProperty.
    /// \see setProjectionType()
    Camera::ProjectionType getProjectionType() const { return getProperty(ProjectionTypeProperty); }


    /// FovType property.
    /// Defines the direction of the field of view for the #FovProperty or the #OrthogonalPlaneHeight to either x or y.
    /// The default value is Camera::YFov.
    /// \see setFovType(), getFovType()
    static PropertyType<Camera::FieldOfViewType> FovTypeProperty;

    /// Gets the value of #FovTypeProperty.
    /// \see setFovType()
    Camera::FieldOfViewType getFovType() const { return getProperty(FovTypeProperty); }

    /// Sets the value of #FovTypeProperty.
    /// \see getFovType()
    void setFovType(Camera::FieldOfViewType value) { setProperty(FovTypeProperty, value); }


    /// Fov property.
    /// Defines the camera field of view angle in degrees. The #FovTypeProperty sets the direction of the angle.
    /// The default value is 45.0f.
    /// \see setFov(), getFov()
    static PropertyType<float> FovProperty;

    /// Gets the value of #FovProperty.
    /// \see setFov()
    float getFov() const { return getProperty(FovProperty); }

    /// Sets the value of #FovProperty.
    /// \see getFov()
    void setFov(float value) { setProperty(FovProperty, value); }


    /// OrthogonalCoordinateSystemType property.
    /// Defines the type of the orthogonal coordinate system. In the absolute mode, the camera uses pixel coordinates. In the relative mode, the camera displays an area whose width is -1..1 scaled with the value set by the #OrthogonalPlaneHeightProperty. The value is effective only when using an orthogonal projection.
    /// The default value is Camera::OrthogonalCoordinateSystemRelative.
    /// \see setOrthogonalCoordinateSystemType(), getOrthogonalCoordinateSystemType()
    static PropertyType<Camera::OrthogonalCoordinateSystem> OrthogonalCoordinateSystemTypeProperty;

    /// Gets the value of #OrthogonalCoordinateSystemTypeProperty.
    /// \see setOrthogonalCoordinateSystemType()
    Camera::OrthogonalCoordinateSystem getOrthogonalCoordinateSystemType() const { return getProperty(OrthogonalCoordinateSystemTypeProperty); }


    /// OrthogonalPlaneHeight property.
    /// Defines the half width or half height of the view plane of a relative orthographic camera. The #FovTypeProperty specifies whether the size is width or height.
    /// The default value is 1.0f.
    /// \see setOrthogonalPlaneHeight(), getOrthogonalPlaneHeight()
    static PropertyType<float> OrthogonalPlaneHeightProperty;

    /// Gets the value of #OrthogonalPlaneHeightProperty.
    /// \see setOrthogonalPlaneHeight()
    float getOrthogonalPlaneHeight() const { return getProperty(OrthogonalPlaneHeightProperty); }

    /// Sets the value of #OrthogonalPlaneHeightProperty.
    /// \see getOrthogonalPlaneHeight()
    void setOrthogonalPlaneHeight(float value) { setProperty(OrthogonalPlaneHeightProperty, value); }


