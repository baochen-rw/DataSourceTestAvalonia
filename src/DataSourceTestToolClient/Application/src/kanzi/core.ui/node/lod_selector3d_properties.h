// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for LevelOfDetail3D.
// Do not include this file directly. Include lod_selector3d.hpp instead.



    /// MinimumArea property.
    /// When using #LodTypeScreenArea, the constraint that sets the minimum screen area covered by the level of detail in proportion to the screen size in range [0, 1].
    /// The default value is 0.0f.
    /// \see setMinimumArea(), getMinimumArea()
    static PropertyType<float> MinimumAreaProperty;


    /// MinimumDistance property.
    /// When using #LodTypeDistance, the constraint that sets the minimum z distance from the camera to the level of detail in range [0, Inf].
    /// The default value is 0.0f.
    /// \see setMinimumDistance(), getMinimumDistance()
    static PropertyType<float> MinimumDistanceProperty;


    /// Type property.
    /// Defines the type of the level of detail. LevelOfDetail3D::LodTypeDistance sets the level of detail to use the minimum z distance from the camera to the level of detail. LevelOfDetail3D::LodTypeScreenArea sets the level of detail to use the minimum screen area covered by the child node in proportion to the screen size.
    /// The default value is LevelOfDetail3D::LodTypeDistance.
    /// \see setType(), getType()
    static PropertyType<LevelOfDetail3D::LODType> TypeProperty;

    /// Gets the value of #TypeProperty.
    /// \see setType()
    LevelOfDetail3D::LODType getType() const { return getProperty(TypeProperty); }

    /// Sets the value of #TypeProperty.
    /// \see getType()
    void setType(LevelOfDetail3D::LODType value) { setProperty(TypeProperty, value); }


