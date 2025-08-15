// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_SLIDER3D_HPP
#define KZ_SLIDER3D_HPP

#include <kanzi/core.ui/node/node3d.hpp>
#include <kanzi/ui/node/concept/range.hpp>
#include <kanzi/ui/node/concept/slider3d_concept.hpp>
#include <kanzi/ui/node/slider_trajectory_presenter.hpp>
#include <kanzi/ui/node/trajectory_layout3d.hpp>


namespace kanzi
{

// Forward declarations.
class Slider3D;

/// Trajectory Slider shared pointer.
typedef shared_ptr<Slider3D> Slider3DSharedPtr;

typedef SliderTrajectoryPresenter<TrajectoryLayout3D, Slider3D, Trajectory3DInputHandler<TrajectoryLayout3D, Slider3D> > Slider3DPresenterType;
typedef Slider3DConceptImpl<RangeConceptImpl<Node3D, Slider3D>, Slider3DPresenterType, Slider3D> Slider3DConceptImplType;


/// Examples
/// ----
///
/// To create a Slider 3D node with a custom appearance:
/// \snippet test_slider3d.cpp Create custom Slider3D
class KANZI_UI_API Slider3D : public Slider3DConceptImplType
{
public:
    /// Slider concept implementation, defining the base class (Component) and presenter (TrajectoryLayout3D).
    typedef Slider3DConceptImplType ConceptClass;
    typedef Slider3DPresenterType PresenterClass;

    /// Creates a Slider3D node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the stack layout.
    static Slider3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Slider3D, ConceptClass, "Kanzi.Slider3D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:
    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit Slider3D(Domain* domain, string_view name);

    /// KzuObjectNode::render() implementation for debugging.
    //  virtual void render(Renderer3D& renderer, const KzuTransformedObjectNode& transformedObjectNode, KzcMatrix4x4& worldTransformation);
};
}
#endif
#endif
