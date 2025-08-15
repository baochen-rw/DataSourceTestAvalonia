
#ifdef KANZI_FEATURE_3D

/**
* \file
* Specifies frustum cull filter.
* Frustum cull filter accepts objects whose bounding volume is at least partially inside current view frustum.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_FRUSTUM_CULL_FILTER_H
#define KZU_FRUSTUM_CULL_FILTER_H

#include "kzu_object_source_base.h"

#include <kanzi/core/legacy/util/math/kzc_plane.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>

#include <kanzi/core/math/matrix4x4.hpp>


/* Forward declarations */
struct KzcMemoryManager;
struct KzuObjectSource;

namespace kanzi
{
    class Domain;
}



/** Structure for frustum cull filter. */
struct KANZI_API KzuFrustumCullFilter: public KzuFilterObjectSource
{
    /// Frustum plane indices.
    enum FrustumPlaneIndex
    {
        /// Near frustum plane.
        FrustumPlaneNear,

        /// Far frustum plane.
        FrustumPlaneFar,

        /// Top frustum plane.
        FrustumPlaneTop,

        /// Bottom frustum plane.
        FrustumPlaneBottom,

        /// Left frustum plane.
        FrustumPlaneLeft,

        /// Right frustum plane.
        FrustumPlaneRight,

        /// Number of frustum planes.
        FrustumPlaneCount
    };

    KzuFrustumCullFilter(kanzi::Domain* domain, kanzi::string_view name);

    static void calculateFrustumPlanes(const kanzi::Matrix4x4&, const kanzi::Matrix4x4&, KzcPlane out_frustumPlanes[KzuFrustumCullFilter::FrustumPlaneCount]);

    kzBool valid; /**< Is the frustum cull filter in valid state. Non-invertible matrix can make it invalid. */
    KzcPlane frustumPlanes[FrustumPlaneCount]; /**< List of frustum planes. */
    kanzi::Matrix4x4 projectionMatrix;
    
};

/** Creates frustum cull filter. */
KANZI_API KzuFrustumCullFilter* kzuFrustumCullFilterCreate(kanzi::Domain* domain, kanzi::ObjectSourceSharedPtr input, kanzi::string_view name);




#endif

#endif
