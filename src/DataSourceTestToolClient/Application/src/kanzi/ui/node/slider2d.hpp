// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SLIDER2D_HPP
#define KZ_SLIDER2D_HPP

#include <kanzi/core.ui/node/node2d.hpp>
#include <kanzi/ui/node/concept/range.hpp>
#include <kanzi/ui/node/concept/slider2d_concept.hpp>
#include <kanzi/ui/node/slider_trajectory_presenter.hpp>
#include <kanzi/ui/node/trajectory_layout2d.hpp>


namespace kanzi
{

// Forward declarations.
class Slider2D;

/// Trajectory Slider shared pointer.
typedef shared_ptr<Slider2D> Slider2DSharedPtr;

typedef SliderTrajectoryPresenter<TrajectoryLayout2D, Slider2D, Trajectory2DInputHandler<TrajectoryLayout2D, Slider2D> > Slider2DPresenterType;
typedef Slider2DConceptImpl<RangeConceptImpl<Node2D, Slider2D>, Slider2DPresenterType, Slider2D> Slider2DConceptImplType;


/// Examples
/// ----
///
/// To create a Slider 2D node with a custom appearance:
/// \snippet test_slider2d.cpp Create custom Slider2D

class KANZI_UI_API Slider2D : public Slider2DConceptImplType
{
public:
    /// Slider concept implementation, defining the base class (Component) and presenter (TrajectoryLayout2D).
    typedef Slider2DConceptImplType ConceptClass;
    typedef Slider2DPresenterType PresenterClass;

    /// Creates a Slider3D node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the stack layout.
    static Slider2DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Slider2D, ConceptClass, "Kanzi.Slider2D")
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    //   kzsError onRenderLayer(Renderer3D* renderer, CompositionStack* compositionStack, KzuMaterial** out_material);

protected:
    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit Slider2D(Domain* domain, string_view name);
};
}

#endif
