// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for TrajectoryLayoutConcept.
// Do not include this file directly. Include trajectory_layout.hpp instead.



    /// Trajectory property.
    /// Defines the resource ID of the trajectory resource used by a trajectory layout.
    /// The default value is ResourceSharedPtr().
    /// \see setTrajectory(), getTrajectory()
    static PropertyType<ResourceSharedPtr> TrajectoryProperty;


    /// ItemAreaBegin property.
    /// Defines the starting point of the trajectory segment in which the layout items are considered fully visible. The value is in [0, 1] range where 0 is the beginning and 1 is the end of the trajectory. See use of the VisibleAmountInParent property. TODO Link to VisibleAmountInParent.
    /// The default value is 0.0f.
    /// \see setItemAreaBegin(), getItemAreaBegin()
    static PropertyType<float> ItemAreaBeginProperty;


    /// ItemAreaEnd property.
    /// Defines the ending point of the trajectory segment in which the layout items are considered fully visible. The value is in [0, 1] range where 0 is the beginning and 1 is the end of the trajectory. See use of the VisibleAmountInParent property. TODO Link to VisibleAmountInParent.
    /// The default value is 1.0f.
    /// \see setItemAreaEnd(), getItemAreaEnd()
    static PropertyType<float> ItemAreaEndProperty;


    /// OverrideDistance property.
    /// Defines the fixed distance between items in the trajectory layout. If not set, the trajectory layout calculates the distance and provides equal spacing between the items. TODO: clarify units
    /// The default value is 1.0f.
    /// \see setOverrideDistance(), getOverrideDistance()
    static PropertyType<float> OverrideDistanceProperty;


    /// StartOffset property.
    /// Defines the starting offset on the trajectory from where the items are laid out. The value is in [0, 1] range, where 0 is the beginning and 1 is the end of the trajectory spline (see, for example, TrajectoryLayoutClipEndOffsetProportional).
    /// The default value is 0.0f.
    /// \see setStartOffset(), getStartOffset()
    static PropertyType<float> StartOffsetProperty;


    /// AlignToTangent property.
    /// Whether the items in the trajectory layout are aligned to the tangent of the trajectory.
    /// The default value is false.
    /// \see setAlignToTangent(), isAlignToTangent()
    static PropertyType<bool> AlignToTangentProperty;


    /// CalculatedOffset property.
    /// Defines the value where the layout stores the current calculated offset along the trajectory calculated for an item. The value is in [0, 1] range, where 0 is the beginning and 1 is the end of the trajectory spline (see, for example, TrajectoryLayoutClipEndOffsetProportional).
    /// The default value is 0.0f.
    /// \see setCalculatedOffset(), getCalculatedOffset()
    static PropertyType<float> CalculatedOffsetProperty;


    /// OverrideOffset property.
    /// Defines the fixed offset on the trajectory, which the trajectory layout uses to position an item. If not set, the trajectory layout calculates the offset automatically. The value is in [0, 1] range, where 0 is the beginning and 1 is the end of the trajectory spline (see, for example, TrajectoryLayoutClipEndOffsetProportional).
    /// The default value is 0.0f.
    /// \see setOverrideOffset(), getOverrideOffset()
    static PropertyType<float> OverrideOffsetProperty;


    /// Stretch property.
    /// If true, scale the trajectory to match layout size.
    /// The default value is false.
    /// \see setStretch(), isStretch()
    static PropertyType<bool> StretchProperty;


