// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROFILING_DETAIL_HPP
#define KZ_PROFILING_DETAIL_HPP

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/cat.hpp>

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/profiling/profiling_category.hpp>
#include <kanzi/core/profiling/profiling_category_detail.hpp>
#include <kanzi/core/profiling/interval_profiler.hpp>
#include <kanzi/core/profiling/profiler_registration_helper.hpp>
#include <kanzi/core/profiling/profiling_scope_helper.hpp>

#define KZ_DETAIL_UNIQUE_PROFILER_VAR_NAME(variable)    BOOST_PP_CAT(kanzi, BOOST_PP_CAT(variable, __LINE__))
#define KZ_DETAIL_PROFILING_SAMPLER_VAR                 KZ_DETAIL_UNIQUE_PROFILER_VAR_NAME(sampler)
#define KZ_DETAIL_PROFILING_SCOPE_GUARD_VAR             KZ_DETAIL_UNIQUE_PROFILER_VAR_NAME(scopeGuard)
#define KZ_DETAIL_PROFILER_VAR                          KZ_DETAIL_UNIQUE_PROFILER_VAR_NAME(profiler)

/// Implementation of #kzProfileScopeWithSamplerExtended() macro.
#define KZ_DETAIL_PROFILE_SCOPE_WITH_SAMPLER_EXTENDED(category, categoryUniqueId, profiler, samplerClassName, samplerConstructorArguments) \
    BOOST_PP_EXPR_IF(kzProfilingIsCategoryEnabledAtCompileTime(category), \
        samplerClassName KZ_DETAIL_PROFILING_SAMPLER_VAR samplerConstructorArguments; \
        ::kanzi::ProfilingScopeHelper KZ_DETAIL_PROFILING_SCOPE_GUARD_VAR(profiler, KZ_DETAIL_PROFILING_SAMPLER_VAR))

/// Implementation of #kzProfileScopeWithSampler().
#define KZ_DETAIL_PROFILE_SCOPE_WITH_SAMPLER(category, categoryUniqueId, profiler, samplerClassName) \
    BOOST_PP_EXPR_IF(kzProfilingIsCategoryEnabledAtCompileTime(category), \
        samplerClassName KZ_DETAIL_PROFILING_SAMPLER_VAR; \
        ::kanzi::ProfilingScopeHelper KZ_DETAIL_PROFILING_SCOPE_GUARD_VAR(profiler, KZ_DETAIL_PROFILING_SAMPLER_VAR))

/// Implementation of #kzProfileScopeExtended().
#define KZ_DETAIL_PROFILE_SCOPE_EXTENDED(category, categoryUniqueId, profilerRegistry, profilerName, sampleBufferSize) \
    BOOST_PP_EXPR_IF(kzProfilingIsCategoryEnabledAtCompileTime(category), \
        static ::kanzi::detail::ProfilerRegistrationHelper< ::kanzi::IntervalProfiler > KZ_DETAIL_PROFILER_VAR(profilerRegistry, ::kanzi::IntervalProfiler::create(profilerName, KZ_DETAIL_PROFILING_GET_CATEGORY_RUNTIME_REFERENCE(categoryUniqueId), sampleBufferSize)); \
        KZ_DETAIL_PROFILE_SCOPE_WITH_SAMPLER(category, categoryUniqueId, KZ_DETAIL_PROFILER_VAR.m_profiler, ::kanzi::IntervalProfilingSampler))

#ifdef KZ_DISABLE_PROFILING
/// To disable profiling define KZ_DISABLE_PROFILING.
///
/// To evaluate a macro only when profiling is enabled, use the KZ_DETAIL_PROFILING_EVALUATE_IF_CATEGORY_IS_ENABLED() macro.
///
/// If profiling is disabled, this macro emits no code. If profiling is enabled,
/// this macro is replaced with the \p macro you provided.
///
/// \param macro The text that this macro is replaced with when profiling is enabled.
#define KZ_DETAIL_EVALUATE_IF_PROFILING_IS_ENABLED(macro)
#else
#define KZ_DETAIL_EVALUATE_IF_PROFILING_IS_ENABLED(macro) macro
#endif

#endif
