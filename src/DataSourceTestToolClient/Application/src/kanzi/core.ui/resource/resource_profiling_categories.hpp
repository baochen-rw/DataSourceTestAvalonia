// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_CATEGORIES_HPP
#define KZ_RESOURCE_PROFILING_CATEGORIES_HPP

#include <kanzi/core/profiling/profiling_category.hpp>

// Profiling category for resource loading is compile-time enabled only in the Profiling build.
#ifdef KANZI_PROFILING_BUILD
/// \ingroup ResourceProfiling
// Defines the compile-time state of the #KZ_PROFILING_RESOURCE_LOADING_CATEGORY profiling category.
#define KZ_PROFILING_DEFAULT_RESOURCE_LOADING_CATEGORY_STATE KZ_PROFILING_ENABLED_CATEGORY
#else
#define KZ_PROFILING_DEFAULT_RESOURCE_LOADING_CATEGORY_STATE KZ_PROFILING_DISABLED_CATEGORY
#endif

/// \ingroup ResourceProfiling
/// Kanzi uses this category to profile resource loading.
///
/// The compile-time state of this category is defined by #KZ_PROFILING_DEFAULT_RESOURCE_LOADING_CATEGORY_STATE.
#define KZ_PROFILING_RESOURCE_LOADING_CATEGORY kzProfilingCreateCategory(KZ_PROFILING_DEFAULT_RESOURCE_LOADING_CATEGORY_STATE, "ResourceLoading", 0)

#ifndef KANZI_DOXYGEN

// Registration of resource profiling category defined above.
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_RESOURCE_LOADING_CATEGORY, KZ_PROFILING_DISABLED_CATEGORY)

#endif
#endif
