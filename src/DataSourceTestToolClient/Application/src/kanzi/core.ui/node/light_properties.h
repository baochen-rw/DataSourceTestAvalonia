// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Light.
// Do not include this file directly. Include light.hpp instead.



    /// TypeName property.
    /// 
    /// The default value is "DirectionalLight".
    /// \see setTypeName(), getTypeName()
    static PropertyType<string> TypeNameProperty;

    /// Gets the value of #TypeNameProperty.
    /// \see setTypeName()
    string getTypeName() const { return getProperty(TypeNameProperty); }

    /// Sets the value of #TypeNameProperty.
    /// \see getTypeName()
    void setTypeName(string value) { setProperty(TypeNameProperty, value); }


    /// Enabled property.
    /// Whether the light is switched on or off. The light affects rendering only when the value is set to true.
    /// The default value is true.
    /// \see setEnabled(), isEnabled()
    static PropertyType<bool> EnabledProperty;

    /// Gets the value of #EnabledProperty.
    /// \see setEnabled()
    bool isEnabled() const { return getProperty(EnabledProperty); }

    /// Sets the value of #EnabledProperty.
    /// \see isEnabled()
    void setEnabled(bool value) { setProperty(EnabledProperty, value); }


    /// ColorScale property.
    /// Scales light color.
    /// The default value is 1.0f.
    /// \see setColorScale(), getColorScale()
    static PropertyType<float> ColorScaleProperty;

    /// Gets the value of #ColorScaleProperty.
    /// \see setColorScale()
    float getColorScale() const { return getProperty(ColorScaleProperty); }

    /// Sets the value of #ColorScaleProperty.
    /// \see getColorScale()
    void setColorScale(float value) { setProperty(ColorScaleProperty, value); }


    /// DirectionalLightColor property.
    /// Defines the color of a directional light.
    /// The default value is ColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f).
    /// \see setDirectionalLightColor(), getDirectionalLightColor()
    static PropertyType<ColorRGBA> DirectionalLightColorProperty;

    /// Gets the value of #DirectionalLightColorProperty.
    /// \see setDirectionalLightColor()
    ColorRGBA getDirectionalLightColor() const { return getProperty(DirectionalLightColorProperty); }

    /// Sets the value of #DirectionalLightColorProperty.
    /// \see getDirectionalLightColor()
    void setDirectionalLightColor(ColorRGBA value) { setProperty(DirectionalLightColorProperty, value); }


    /// DirectionalLightDirection property.
    /// Contains the direction vector of a directional light. Calculated automatically from a directional light's world transformation.
    /// The default value is Vector3(0.0f, 0.0f, 0.0f).
    /// \see setDirectionalLightDirection(), getDirectionalLightDirection()
    static PropertyType<Vector3> DirectionalLightDirectionProperty;

    /// Gets the value of #DirectionalLightDirectionProperty.
    /// \see setDirectionalLightDirection()
    Vector3 getDirectionalLightDirection() const { return getProperty(DirectionalLightDirectionProperty); }


    /// PointLightColor property.
    /// Defines the color of a point light.
    /// The default value is ColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f).
    /// \see setPointLightColor(), getPointLightColor()
    static PropertyType<ColorRGBA> PointLightColorProperty;

    /// Gets the value of #PointLightColorProperty.
    /// \see setPointLightColor()
    ColorRGBA getPointLightColor() const { return getProperty(PointLightColorProperty); }

    /// Sets the value of #PointLightColorProperty.
    /// \see getPointLightColor()
    void setPointLightColor(ColorRGBA value) { setProperty(PointLightColorProperty, value); }


    /// PointLightAttenuation property.
    /// Defines the effect of a point light on objects that are farther away. Define the attenuation value of a point light by setting constant, linear, and quadratic coefficients.
    /// The default value is Vector3(1.0f, 0.0f, 0.0f).
    /// \see setPointLightAttenuation(), getPointLightAttenuation()
    static PropertyType<Vector3> PointLightAttenuationProperty;

    /// Gets the value of #PointLightAttenuationProperty.
    /// \see setPointLightAttenuation()
    Vector3 getPointLightAttenuation() const { return getProperty(PointLightAttenuationProperty); }

    /// Sets the value of #PointLightAttenuationProperty.
    /// \see getPointLightAttenuation()
    void setPointLightAttenuation(Vector3 value) { setProperty(PointLightAttenuationProperty, value); }


    /// PointLightPosition property.
    /// Contains the position vector of a point light. Calculated automatically from a point light's world transformation.
    /// The default value is Vector3(0.0f, 0.0f, 0.0f).
    /// \see setPointLightPosition(), getPointLightPosition()
    static PropertyType<Vector3> PointLightPositionProperty;

    /// Gets the value of #PointLightPositionProperty.
    /// \see setPointLightPosition()
    Vector3 getPointLightPosition() const { return getProperty(PointLightPositionProperty); }


    /// PointLightRadius property.
    /// Sphere light radius.
    /// The default value is 0.0f.
    /// \see setPointLightRadius(), getPointLightRadius()
    static PropertyType<float> PointLightRadiusProperty;

    /// Gets the value of #PointLightRadiusProperty.
    /// \see setPointLightRadius()
    float getPointLightRadius() const { return getProperty(PointLightRadiusProperty); }

    /// Sets the value of #PointLightRadiusProperty.
    /// \see getPointLightRadius()
    void setPointLightRadius(float value) { setProperty(PointLightRadiusProperty, value); }


    /// SpotLightColor property.
    /// Defines the color of a spot light.
    /// The default value is ColorRGBA(0.4980392f, 0.4980392f, 0.4980392f, 1.0f).
    /// \see setSpotLightColor(), getSpotLightColor()
    static PropertyType<ColorRGBA> SpotLightColorProperty;

    /// Gets the value of #SpotLightColorProperty.
    /// \see setSpotLightColor()
    ColorRGBA getSpotLightColor() const { return getProperty(SpotLightColorProperty); }

    /// Sets the value of #SpotLightColorProperty.
    /// \see getSpotLightColor()
    void setSpotLightColor(ColorRGBA value) { setProperty(SpotLightColorProperty, value); }


    /// SpotLightAttenuation property.
    /// Defines the effect of a spot light on objects that are farther away. Define the attenuation value of a spot light by setting constant, linear, and quadratic coefficients.
    /// The default value is Vector3(1.0f, 0.0f, 0.0f).
    /// \see setSpotLightAttenuation(), getSpotLightAttenuation()
    static PropertyType<Vector3> SpotLightAttenuationProperty;

    /// Gets the value of #SpotLightAttenuationProperty.
    /// \see setSpotLightAttenuation()
    Vector3 getSpotLightAttenuation() const { return getProperty(SpotLightAttenuationProperty); }

    /// Sets the value of #SpotLightAttenuationProperty.
    /// \see getSpotLightAttenuation()
    void setSpotLightAttenuation(Vector3 value) { setProperty(SpotLightAttenuationProperty, value); }


    /// SpotLightCutoffAngle property.
    /// Defines the angle of the light cone in degrees.
    /// The default value is 90.0f.
    /// \see setSpotLightCutoffAngle(), getSpotLightCutoffAngle()
    static PropertyType<float> SpotLightCutoffAngleProperty;

    /// Gets the value of #SpotLightCutoffAngleProperty.
    /// \see setSpotLightCutoffAngle()
    float getSpotLightCutoffAngle() const { return getProperty(SpotLightCutoffAngleProperty); }

    /// Sets the value of #SpotLightCutoffAngleProperty.
    /// \see getSpotLightCutoffAngle()
    void setSpotLightCutoffAngle(float value) { setProperty(SpotLightCutoffAngleProperty, value); }


    /// SpotLightInnerAngle property.
    /// Defines the inner angle of the light cone in degrees.
    /// The default value is 80.0f.
    /// \see setSpotLightInnerAngle(), getSpotLightInnerAngle()
    static PropertyType<float> SpotLightInnerAngleProperty;

    /// Gets the value of #SpotLightInnerAngleProperty.
    /// \see setSpotLightInnerAngle()
    float getSpotLightInnerAngle() const { return getProperty(SpotLightInnerAngleProperty); }

    /// Sets the value of #SpotLightInnerAngleProperty.
    /// \see getSpotLightInnerAngle()
    void setSpotLightInnerAngle(float value) { setProperty(SpotLightInnerAngleProperty, value); }


    /// SpotLightDirection property.
    /// Contains the direction vector of a spot light. Calculated automatically from a spot light's world transformation.
    /// The default value is Vector3(0.0f, 0.0f, 0.0f).
    /// \see setSpotLightDirection(), getSpotLightDirection()
    static PropertyType<Vector3> SpotLightDirectionProperty;

    /// Gets the value of #SpotLightDirectionProperty.
    /// \see setSpotLightDirection()
    Vector3 getSpotLightDirection() const { return getProperty(SpotLightDirectionProperty); }


    /// SpotLightExponent property.
    /// Defines how fast a fully lit area at the center of the light cone turns into an unlit area.
    /// The default value is 1.0f.
    /// \see setSpotLightExponent(), getSpotLightExponent()
    static PropertyType<float> SpotLightExponentProperty;

    /// Gets the value of #SpotLightExponentProperty.
    /// \see setSpotLightExponent()
    float getSpotLightExponent() const { return getProperty(SpotLightExponentProperty); }

    /// Sets the value of #SpotLightExponentProperty.
    /// \see getSpotLightExponent()
    void setSpotLightExponent(float value) { setProperty(SpotLightExponentProperty, value); }


    /// SpotLightPosition property.
    /// Contains the position vector of a spot light. Calculated automatically from a spot light's world transformation.
    /// The default value is Vector3(0.0f, 0.0f, 0.0f).
    /// \see setSpotLightPosition(), getSpotLightPosition()
    static PropertyType<Vector3> SpotLightPositionProperty;

    /// Gets the value of #SpotLightPositionProperty.
    /// \see setSpotLightPosition()
    Vector3 getSpotLightPosition() const { return getProperty(SpotLightPositionProperty); }


