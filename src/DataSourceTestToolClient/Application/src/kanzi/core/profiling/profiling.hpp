// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROFILING_HPP
#define KZ_PROFILING_HPP

#include <kanzi/core/log/log_category.hpp>
#include <kanzi/core/profiling/default_profiler_registry.hpp>
#include <kanzi/core/profiling/profiling_detail.hpp>

/// \defgroup ProfilingMacros Profiling macros
///
/// Use profiling macros to instrument the code for runtime performance profiling.
///
/// \section TheKanziProfilingBuild Kanzi profiling build
/// The Kanzi profiling build includes profiled Kanzi libraries. Use the Kanzi profiling build to measure the performance of different
/// parts of Kanzi engine:
///  - For startup profiling, use \ref StartupProfiling
///  - For main loop task profiling, use \ref MainLoopTaskProfiling.
///
/// Use the #KANZI_PROFILING_BUILD macro to check whether the code is compiled with the Kanzi Profiling build configuration. The #KANZI_PROFILING_BUILD macro is defined for the Profiling build only.
///
/// For an example on how to extract profiler samples, see kanzi::AbstractProfiler.
///
/// \{

/// Gets the fully qualified, if possible, name of the enclosing function.
///
/// If you use this macro outside of the function or method body, the behavior is undefined.
///
/// \note Some compilers do not provide a way to obtain the name of the enclosing function.
/// When you use such a compiler, the value of this macro is undefined.
#define KZ_PROFILING_THIS_FUNCTION_NAME BOOST_CURRENT_FUNCTION

/// Default sample buffer size.
#define KZ_PROFILING_DEFAULT_SAMPLE_BUFFER_SIZE 128

/// Gets the reference to the default profiler registry.
/// \return The reference to the default profiler registry.
#define kzProfilingGetDefaultRegistry() ::kanzi::DefaultProfilerRegistry::get().getProfilerRegistry()

/// Profiles the execution time of a scope.
///
/// Call this macro in the beginning of the scope that you want to profile. The behavior of this macro is controlled by the profiling 
/// category you provide through the \p category parameter.
/// When the compile time state of the profiling category is disabled, this macro produces no code. Otherwise, this macro creates a static profiler object of 
/// type IntervalProfiler to store profiling samples. Provide the name for that profiler through the \p scopeProfilerName parameter.
/// The profiler is registered within the default profiler registry. To access the default profiler registry use the #kzProfilingGetDefaultRegistry() macro.
///
/// The runtime state of the profiling category controls whether the profiler collects samples. If the runtime state of the category is disabled,
/// the profiler does not collect samples.
///
/// If the profiler collects samples, every time the enclosing scope is entered this macro measures the time spent executing
/// the scope and records the measurement in the sample of type #IntervalProfilerSampleData, which is after that added to the profiler.
///
/// The sample buffer size of the profiler is set to the value of the sample buffer size you assign to the profiling category through the \p category parameter.
/// To get the sample buffer size assigned to the profiling category, use the #kzProfilingGetCategorySampleBufferSize() macro.
///
/// \param category The profiling category. 
/// \param scopeProfilerName The name of the profiler.
/// \see kanzi::ProfilingCategory
///
/// Example
/// -------
/// To profile a scope:
/// \snippet snippets_profiling.cpp To profile the scope
#define kzProfileScope(category, scopeProfilerName) \
    KZ_DETAIL_EVALUATE_IF_PROFILING_IS_ENABLED(KZ_DETAIL_PROFILE_SCOPE_EXTENDED(category, category ## _ID, kzProfilingGetDefaultRegistry(), scopeProfilerName, kzProfilingGetCategorySampleBufferSize(category)))

/// Profiles the execution time of a scope using custom profiler registry and sample buffer size.
///
/// Call this macro in the beginning of the scope that you want to profile. The behavior of this macro is similar to the
/// behavior of the #kzProfileScope macro. This macro creates
/// a static profiler object which is registered within the profiler registry you provide through the \p profilerRegistry parameter.
/// The sample buffer size of the profiler is set to the value you provide through the \p sampleBufferSize parameter.
/// The profiling category you provide through the \p category parameter controls the behavior of this macro in the same way as
/// it does in the #kzProfileScope macro.
///
/// \param category The profiling category.
/// \param profilerRegistry The profiler registry to which you add the profiler.
/// \param scopeProfilerName The name of the profiler.
/// \param sampleBufferSize The sample buffer size of the profiler.
/// \see kanzi::ProfilingCategory
///
/// Example
/// -------
/// To profile the execution time of a scope using custom profiler registry and sample buffer size:
/// \snippet snippets_profiling.cpp To profile the scope
#define kzProfileScopeExtended(category, profilerRegistry, scopeProfilerName, sampleBufferSize) \
    KZ_DETAIL_EVALUATE_IF_PROFILING_IS_ENABLED(KZ_DETAIL_PROFILE_SCOPE_EXTENDED(category, category ## _ID, profilerRegistry, scopeProfilerName, sampleBufferSize))

/// Profiles the execution time of a function.
///
/// Call this macro in the beginning of the function that you want to profile. The behavior of this macro is similar to the
/// behavior of the #kzProfileScope macro. This macro creates a
/// static profiler object which is registered within the default profiler registry. The sample buffer size of the profiler is
/// set to the sample buffer size assigned to the profiling category you provide through the \p category parameter. The name
/// of the profiler is set to the value given by the #KZ_PROFILING_THIS_FUNCTION_NAME macro.
///
/// \param category The profiling category.
/// \see kanzi::ProfilingCategory
/// 
/// Example
/// -------
/// To profile the execution time of a function:
/// \snippet snippets_profiling.cpp To profile the function
#define kzProfileFunction(category) \
    KZ_DETAIL_EVALUATE_IF_PROFILING_IS_ENABLED(KZ_DETAIL_PROFILE_SCOPE_EXTENDED(category, category ## _ID, kzProfilingGetDefaultRegistry(), KZ_PROFILING_THIS_FUNCTION_NAME, kzProfilingGetCategorySampleBufferSize(category)))


/// Profiles the execution time of a scope using a sampler.
///
/// Call this macro in the beginning of the scope that you want to profile. Use this macro when you want to create a profiler outside of the scope that you want to profile.
/// Create the profiler before entering the scope and pass that profiler to this macro through the \p profiler parameter. The profiling category
/// you provide through the \p category parameter controls the behavior of this macro in the same way as it does in the #kzProfileScope macro.
/// Provide the sampler class type through the \p samplerClass parameter. The sampler class is used to collect samples and add them to the profiler.
/// The \ref ProfilingScopeHelper uses the sampler class to collect samples and add them to the profiler. The local sampler object is created every time
/// the enclosing scope is entered.
///
/// \param category The profiling category.
/// \param profiler The profiler.
/// \param samplerClass The profiling sampler class type.
/// \see kanzi::ProfilingCategory
///
/// Example
/// -------
/// To profile the execution time of a scope using a sampler:
/// \snippet snippets_profiling.cpp To profile with sampler
#define kzProfileScopeWithSampler(category, profiler, samplerClass) \
    KZ_DETAIL_EVALUATE_IF_PROFILING_IS_ENABLED(KZ_DETAIL_PROFILE_SCOPE_WITH_SAMPLER(category, category ## _ID, profiler, samplerClass))

/// Profiles the execution time of a scope using a sampler with constructor arguments.
///
/// Call this macro in the beginning of the scope that you want to profile. The behavior of this macro is similar to the behavior of
/// #kzProfileScopeWithSampler. Use this macro when the constructor of the sampler class that you provide through the \p samplerClass parameter
/// requires arguments. Pass the arguments enclosed in parentheses through the \p samplerConstructorArguments parameter of the macro.
/// Note that the local sampler object is created every time the enclosing scope is entered which means that the constructor arguments you provide
/// are passed to that local object every time the scope is entered.
///
/// \param category The profiling category.
/// \param profiler The profiler.
/// \param samplerClass The profiling sampler class type.
/// \param samplerConstructorArguments The sampler constructor arguments enclosed in parentheses.
/// \see kanzi::ProfilingCategory
///
/// Example
/// -------
/// To profile the execution time of a scope using a sampler with constructor arguments:
/// \snippet snippets_profiling.cpp To profile with sampler
#define kzProfileScopeWithSamplerExtended(category, profiler, samplerClass, samplerConstructorArguments) \
    KZ_DETAIL_EVALUATE_IF_PROFILING_IS_ENABLED(KZ_DETAIL_PROFILE_SCOPE_WITH_SAMPLER_EXTENDED(category, category ## _ID, profiler, samplerClass, samplerConstructorArguments))

#ifndef KZ_LOG_DEFAULT_CATEGORY_PROFILING_STATE
/// Defines profiling log category state.
///
/// The profiling log category is enabled by default.
/// \see KZ_LOG_CATEGORY_PROFILING
#define KZ_LOG_DEFAULT_CATEGORY_PROFILING_STATE KZ_LOG_ENABLED_CATEGORY
#endif

/// The profiling log category.
///
/// Use this log category to write profiling logs only. The #KZ_LOG_DEFAULT_CATEGORY_PROFILING_STATE defines the state of this log category.
#define KZ_LOG_CATEGORY_PROFILING KZ_LOG_CREATE_CATEGORY(KZ_LOG_DEFAULT_CATEGORY_PROFILING_STATE, "profiling")

/// \}

#ifndef KZ_PROFILING_DEFAULT_CATEGORY_GENERIC_STATE
/// \ingroup ProfilingMacros
/// Defines generic profiling category compile time state.
///
/// The generic profiling category is enabled by default.
/// \see KZ_PROFILING_CATEGORY_GENERIC
#define KZ_PROFILING_DEFAULT_CATEGORY_GENERIC_STATE KZ_PROFILING_ENABLED_CATEGORY
#endif

/// \ingroup ProfilingMacros
/// The generic profiling category to profile code not specific to other profiling categories. The #KZ_PROFILING_DEFAULT_CATEGORY_GENERIC_STATE defines the state of this category.
#define KZ_PROFILING_CATEGORY_GENERIC kzProfilingCreateCategory(KZ_PROFILING_DEFAULT_CATEGORY_GENERIC_STATE, "Generic", KZ_PROFILING_DEFAULT_SAMPLE_BUFFER_SIZE)

#ifndef KANZI_DOXYGEN
// Register generic profiling category.
kzProfilingRegisterExportedCategory(KANZI_API, KZ_PROFILING_CATEGORY_GENERIC, KZ_PROFILING_ENABLED_CATEGORY)
#endif

#endif
