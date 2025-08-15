// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_UI_TRAJECTORY_LAYOUT_H
#define KZU_UI_TRAJECTORY_LAYOUT_H


#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/trajectory_layout.hpp>
#include <kanzi/core.ui/node/resource_reference.hpp>
#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core.ui/resource/trajectory.hpp>

namespace kanzi
{

// Forward declarations.
class TrajectoryLayout3D;

/// TrajectoryLayout shared pointer.
typedef shared_ptr<TrajectoryLayout3D> TrajectoryLayout3DSharedPtr;

/// Trajectory Layout 3D arranges its items along a trajectory.
///
/// You can use a line, a circle, or a spline as a trajectory for the trajectory layout. See #TrajectoryProperty,
/// setTrajectoryResourceID(), \ref using_resource_ids.
///
/// Based on the number of items in a trajectory layout, the layout by default arranges its items
/// so that they are separated by an equal amount of space. You can disable automatic positioning by
/// manually setting the distance between items. See setItemStaticOffset(), setFixedDistance().
///
/// \see For a 2D trajectory %layout component, see TrajectoryLayout2D.
///
/// Examples
/// ----
///
/// To create a Trajectory Layout 3D node:
/// \snippet test_trajectory_layout3d.cpp example
///
/// To create a trajectory and use it in a trajectory layout:
/// \snippet test_trajectory_layout3d.cpp resource example
///
/// To add items to a trajectory layout:
/// \snippet test_trajectory_layout3d.cpp items example
///
/// To manually position items in a trajectory layout:
/// \snippet test_trajectory_layout3d.cpp distance offset example


class KANZI_UI_API TrajectoryLayout3D : public Node3D, public TrajectoryLayoutConcept
{
public:

    /// Creates a trajectory layout node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name Name of the trajectory layout.
    static TrajectoryLayout3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(TrajectoryLayout3D, Node3D, "Kanzi.TrajectoryLayout3D")
        KZ_METACLASS_MIXIN(TrajectoryLayoutConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the offset calculated for an item.
    /// \param item The item that is a child of trajectory layout.
    /// \return Returns the offset calculated for a child node. If the layout has not been calculated, it returns the previous value. If the item is not a child node of the trajectory layout, it returns 0.0f.
    float getCalculatedOffset(const Node3DSharedPtr& item) const;
    
    /// Gets the position calculated for an item.
    /// \param item The item that is a child of trajectory layout.
    /// \return Returns the position calculated for an item. If the layout has not been calculated, it returns the previous value. If the item is not a child node of the trajectory layout, it returns the starting position.
    Vector3 getCalculatedPosition(const Node3DSharedPtr& item) const;

    /// Gets the tangent calculated for an item.
    /// \param item The item that is a child of trajectory layout.
    /// \return Returns the tangent calculated for an item. If the layout has not been calculated, it returns the previous value. If the item is not a child node of the trajectory layout, it returns Vector3(-1.0f, 0.0f, 0.0f).
    Vector3 getCalculatedTangent(const Node3DSharedPtr& item) const;

    /// Gets the length of the trajectory used by the trajectory layout.
    /// \return Returns the length of the trajectory.
    /// \see KzuTrajectory
    float getCurveLength() const;

    /// Converts a proportional offset to a length offset.
    /// \param proportionalOffset Offset in [0, 1] range.
    /// \return Returns the offset mapped to the length of the trajectory.
    float proportionalToLength(float proportionalOffset) const;
    /// Converts a length offset to a proportional offset.
    /// \param lengthOffset Offset on the trajectory.
    /// \return Returns the offset mapped to [0, 1] range.
    float lengthToProportional(float lengthOffset) const;

    /// Gets the offset of an item.
    /// \param item A node that is or can become an item of a trajectory layout.
    /// \return Returns the last offset calculated for the item by trajectory layout.
    static float getItemOffset(const Node& item);

    /// Gets static offset of an item.
    /// \param item A node that is or can become an item of a trajectory layout.
    /// \return #StaticTrajectoryOffsetProperty or an empty optional if not set on the item.
    static optional<float> getOverrideOffset(const Node& item);

    /// Sets static offset of an item.
    /// \param item A node that is or can become an item of a trajectory layout.
    /// \param staticOffset Static offset to use for the item on a trajectory.
    ///
    /// Examples
    /// ----
    ///
    /// To manually position items in a trajectory layout:
    /// \snippet test_trajectory_layout3d.cpp distance offset example
    static void setOverrideOffset(Node& item, float staticOffset);
    
    /// Gets the value of #TrajectoryProperty.
    /// \see setTrajectory()
    TrajectorySharedPtr getTrajectory() const { return dynamic_pointer_cast<Trajectory>(getProperty(TrajectoryProperty)); }

    /// Sets the value of #TrajectoryProperty.
    /// \see getTrajectory()
    void setTrajectory(TrajectorySharedPtr value) { setProperty(TrajectoryProperty, value); }

    /// Gets the value of #ClipStartOffsetProportionalProperty.
    /// \see setClipStartOffsetProportional()
    float getItemAreaBegin() const { return getProperty(ItemAreaBeginProperty); }

    /// Sets the value of #ClipStartOffsetProportionalProperty.
    /// \see getClipStartOffsetProportional()
    void setItemAreaBegin(float value) { setProperty(ItemAreaBeginProperty, value); }

    /// Gets the value of #ClipEndOffsetProportionalProperty.
    /// \see setClipEndOffsetProportional()
    float getItemAreaEnd() const { return getProperty(ItemAreaEndProperty); }

    /// Sets the value of #ClipEndOffsetProportionalProperty.
    /// \see getClipEndOffsetProportional()
    void setItemAreaEnd(float value) { setProperty(ItemAreaEndProperty, value); }

    /// Gets the value of #FixedDistanceProperty.
    /// \see setFixedDistance()
    float getOverrideDistance() const { return getProperty(OverrideDistanceProperty); }

    /// Sets the value of #FixedDistanceProperty.
    /// \see getFixedDistance()
    void setOverrideDistance(float value) { setProperty(OverrideDistanceProperty, value); }

    /// Gets the value of #ScrollOffsetProportionalProperty.
    /// \see setScrollOffsetProportional()
    float getStartOffset() const { return getProperty(StartOffsetProperty); }

    /// Sets the value of #ScrollOffsetProportionalProperty.
    /// \see getScrollOffsetProportional()
    void setStartOffset(float value) { setProperty(StartOffsetProperty, value); }

    /// Gets the value of #AlignToTangentProperty.
    /// \see setAlignToTangent()
    bool isAlignToTangent() const { return getProperty(AlignToTangentProperty); }

    /// Sets the value of #AlignToTangentProperty.
    /// \see isAlignToTangent()
    void setAlignToTangent(bool value) { setProperty(AlignToTangentProperty, value); }

    /// Gets the value of #EnableTrajectoryScalingProperty.
    /// \see setEnableTrajectoryScaling()
    bool isStretch() const { return getProperty(StretchProperty); }

    /// Sets the value of #EnableTrajectoryScalingProperty.
    /// \see isEnableTrajectoryScaling()
    void setStretch(bool value) { setProperty(StretchProperty, value); }

    /// Return scaling factor.
    Vector3 getScaling() const { return m_scaling; }

    void refreshScaling(const Vector3& availableSize);

protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit TrajectoryLayout3D(Domain* domain, string_view name);

    /// KzuUiComponent::measureOverride() implementation.
    virtual Vector3 measureOverride(Vector3 availableSize) KZ_OVERRIDE;
    /// KzuUiComponent::arrangeOverride() implementation.
    virtual void arrangeOverride(Vector3 actualSize) KZ_OVERRIDE;
    /// Node::onPropertyChanged implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Updates the offset property value of an item, which the user of the layout can later retrieve from #TrajectoryOffsetProperty.
    /// \param item The item that is a child of trajectory layout.
    void updateItemOffsetProperty(const Node3DSharedPtr& item) const;
    /// Updates the visible amount value for an item, which the user of the layout can later retrieve from #VisibleAmountInParentProperty.
    /// \param item The item that is a child of trajectory layout.
    /// \see #VisibleAmountInParentProperty
    void updateItemAmountVisibleInParentProperty(const Node3DSharedPtr& item) const;

private:

    /// Container of offsets for items.
    typedef map<Node3DWeakPtr, float, owner_less<Node3DWeakPtr> > OffsetContainer;

    /// Calculated offsets for items.
    OffsetContainer m_itemOffsets;
    /// Cached trajectory.
    TrajectorySharedPtr m_cachedTrajectory;
    /// Scaling for spline.
    Vector3 m_scaling;
    /// Biggest child for spline measurement.
    Vector3 m_biggestChild;
};

}

#endif
#endif