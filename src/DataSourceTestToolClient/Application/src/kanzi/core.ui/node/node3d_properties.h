// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Node3D.
// Do not include this file directly. Include node3d.hpp instead.



    /// FinalTransformation property.
    /// 
    /// The default value is Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f).
    /// \see setFinalTransformation(), getFinalTransformation()
    static PropertyType<Matrix4x4> FinalTransformationProperty;

    /// Gets the value of #FinalTransformationProperty.
    /// \see setFinalTransformation()
    Matrix4x4 getFinalTransformation() const { return getProperty(FinalTransformationProperty); }

    /// Sets the value of #FinalTransformationProperty.
    /// \see getFinalTransformation()
    void setFinalTransformation(Matrix4x4 value) { setProperty(FinalTransformationProperty, value); }


    /// FrustumCullMargin property.
    /// 
    /// The default value is 0.0f.
    /// \see setFrustumCullMargin(), getFrustumCullMargin()
    static PropertyType<float> FrustumCullMarginProperty;

    /// Gets the value of #FrustumCullMarginProperty.
    /// \see setFrustumCullMargin()
    float getFrustumCullMargin() const { return getProperty(FrustumCullMarginProperty); }

    /// Sets the value of #FrustumCullMarginProperty.
    /// \see getFrustumCullMargin()
    void setFrustumCullMargin(float value) { setProperty(FrustumCullMarginProperty, value); }


