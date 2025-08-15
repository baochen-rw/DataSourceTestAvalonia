// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_LOD_SELECTOR_H
#define KZU_LOD_SELECTOR_H

#include <kanzi/core.ui/node/node3d.hpp>


namespace kanzi
{

class LevelOfDetail3D;

/// LODSelectorNode shared pointer.
typedef shared_ptr<LevelOfDetail3D> LevelOfDetail3DSharedPtr;


/// Level of detail selector node is a 3D node that changes the appearance of its child nodes based on
/// the viewing distance.
///
/// Level of detail selector node is a collection of multiple appearances of a single 3D object. Each child of
/// a level of detail selector node sets a single appearance and a constraint when that appearance is selected
/// and shown. The constraint can be either a minimum distance from the preview camera or a minimum coverage
/// of the screen. Lower values set the child object to be selected when the preview camera is closer to
/// the object. Higher values set the child object to be selected when the preview camera is further away
/// from the object.
///
/// Note that the level of detail selector nodes affect only rendering, which is why you cannot use them in layouts.
/// The size of the level of detail selector node is the size of its largest child, even if that child is not
/// visible at the current level of detail.
///
/// Examples
/// ---
///
/// To create a distance level of detail selector node with three levels of detail:
/// \snippet kz_test_lod_selector.cpp example


class KANZI_API LevelOfDetail3D : public Node3D
{
public:

    /// Level of detail node selector types.
    enum LODType
    {
        LodTypeDistance,  ///< The level of detail is measured using the z distance from the camera to the level of detail selector node.
        LodTypeScreenArea ///< The level of detail is measured using the ratio of the screen area covered by the level of detail selector node to the whole screen area.
    };

    /// \name Properties
    /// \{
#include "lod_selector3d_properties.h"
    /// \}

    /// Creates a level of detail selector node.
    /// \param domain The UI domain the new level of detail selector node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static LevelOfDetail3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(LevelOfDetail3D, Node3D, "Kanzi.LevelOfDetail3D")
        KZ_METACLASS_PROPERTY_TYPE(MinimumAreaProperty)
        KZ_METACLASS_PROPERTY_TYPE(MinimumDistanceProperty)
        KZ_METACLASS_PROPERTY_TYPE(TypeProperty)
    KZ_METACLASS_END()

    /// Gets the minimum area constraint of an item.
    /// \param item A node that is or can become an item of a level of detail selector node.
    /// \return The value of the #LevelOfDetailMinimumAreaProperty.
    static float getMinimumArea(const Node3D& item);

    /// Sets the minimum area constraint of an item. The constraint is effective when #LodTypeScreenArea is used.
    /// \param item A node that is or can become an item of a level of detail selector node.
    /// \param value The new value for the #LevelOfDetailMinimumAreaProperty.
    static void setMinimumArea(Node3D& item, float value);

    /// Gets the minimum distance constraint for an item.
    /// \param item A node that is or can become an item of a level of detail selector node.
    /// \return The value of the #LevelOfDetailMinimumDistanceProperty.
    static float getMinimumDistance(const Node3D& item);

    /// Sets the minimum distance constraint of an item. The constraint is effective when #LodTypeDistance is used.
    /// \param item A node that is or can become an item of a level of detail selector node.
    /// \param value The new value for the #LevelOfDetailMinimumDistanceProperty.
    static void setMinimumDistance(Node3D& item, float value);

    /// Gets the number of available level of details levels.
    /// \return The number of child nodes this level of detail selector node has.
    size_t getLevelCount() const;

    /// Gets the item that best matches the current level of detail. It returns the item that has the largest
    /// satisfied constraint.
    /// \param levelOfDetail The desired level of detail value (either distance or area size).
    /// \return The child node that has the largest satisfied constraint. If no node has a satisfied constraint, returns nullptr. TODO Is nullptr enough, or should we be more specific?
    Node3DConstSharedPtr getNodeAtConstraint(float levelOfDetail) const;

    /// Gets the object node at a given index. TODO This index is not used anywhere in LOD. What is it? What does this return if there's no object node at the requested index?
    /// \return The child at the given index.
    Node3DConstSharedPtr getNodeAtLevel(size_t index) const;

protected:

    /// Constructor.
    /// \param domain The UI domain the new level of detail selector node belongs to.
    /// \param name The name of the node.
    explicit LevelOfDetail3D(Domain* domain, string_view name);
};

}


#endif

#endif  // KANZI_FEATURE_3D