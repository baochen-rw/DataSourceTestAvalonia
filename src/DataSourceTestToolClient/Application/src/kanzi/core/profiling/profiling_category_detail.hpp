// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROFILING_CATEGORY_DETAIL_HPP
#define KZ_PROFILING_CATEGORY_DETAIL_HPP

#include <boost/preprocessor/control/expr_if.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/string/fixed_string.hpp>

/// Evaluates a macro only when the provided profiling category is enabled.
/// 
/// If the profiling category you provide through the \p category parameter is disabled at compile time, this macro emits no code.
/// If the category is enabled at compile time, the macro is replaced with the \p macro you provide.
///
/// \param category The category macro to check status.
/// \param macro The text that this macro is replaced with when \p category is enabled at compile time.
#define KZ_DETAIL_PROFILING_EVALUATE_IF_CATEGORY_IS_ENABLED(category, macro) BOOST_PP_EXPR_IF(kzProfilingIsCategoryEnabledAtCompileTime(category), macro)

/// Generates profiling category type using a unique category ID.
///
/// \param uniqueId Unique category ID.
#define KZ_DETAIL_PROFILING_GET_CATEGORY_UNIQUE_TYPE(uniqueId) uniqueId ## _CategoryType

/// Gets runtime profiling category object reference associated with category, identified by \p uniqueId.
///
/// \param uniqueId Unique category ID.
#define KZ_DETAIL_PROFILING_GET_CATEGORY_RUNTIME_REFERENCE(uniqueId) ::kanzi::detail::KZ_DETAIL_PROFILING_GET_CATEGORY_UNIQUE_TYPE(uniqueId)::getProfilingCategorySingleton()

/// Empty export/import prefix used as a parameter to #KZ_DETAIL_PROFILING_REGISTER_CATEGORY to create regular profiling categories.
#define KZ_DETAIL_EMPTY_EXPORT_IMPORT_PREFIX

/// Converts category name string literal to fixed string.
#define KZ_DETAIL_CONVERT_CATEGORY_NAME_TO_FIXED_STRING(name) kzMakeFixedString(name)

/// Implementation of #kzProfilingRegisterCategory macro logic.
///
/// This macro defines structure which is unique for each profiling category and provides interface for \ref ProfilingMacros to access profiling category singleton object.
/// The ProfilingCategory singleton object associated with the profiling category is accessible through getProfilingCategorySingleton() function.
/// The singleton controls runtime state of category and is created with ProfilingCategory::create() function
/// which registers the profiling category in a global registry. This registry is used by ProfilingCategory::setFilter() function
/// to apply profiling category filter. It is required that all profiling categories are registered before ProfilingCategory::setFilter()
/// is called, so that the function can find them in the profiling registry by name. To achieve that static instance of
/// ProfilingCategorySingletonInitializer is defined which guarantees that the singleton is created at initialization of static variables,
/// which means all profiling categories are registered before ProfilingCategory::setFilter() is called by Kanzi.
#define KZ_DETAIL_PROFILING_REGISTER_CATEGORY(exportImportDirective, category, uniqueId, initialRuntimeState) \
    namespace kanzi \
    { \
    namespace detail \
    { \
        struct exportImportDirective KZ_DETAIL_PROFILING_GET_CATEGORY_UNIQUE_TYPE(uniqueId) \
        { \
            /** Returns reference to a profiling category singleton object. */ \
            /** Creates the singleton on first entry. This function is safe to call to initialize static profilers. */ \
            /** \return The reference to the profiling category singleton object. */ \
            static ProfilingCategory& getProfilingCategorySingleton() \
            { \
                static ProfilingCategory& categoryReference = ProfilingCategory::create(KZ_DETAIL_CONVERT_CATEGORY_NAME_TO_FIXED_STRING(kzProfilingGetCategoryName(category)), initialRuntimeState); \
                return categoryReference; \
            } \
        }; \
        /** Explicit instantiation of the profiling category singleton initializer. */ \
        template struct exportImportDirective ProfilingCategorySingletonInitializer<KZ_DETAIL_PROFILING_GET_CATEGORY_UNIQUE_TYPE(uniqueId)>; \
    } \
    }

/// Implementation of #kzProfilingIsCategoryEnabledAtRuntime macro logic.
///
/// \param category The profiling category macro to fetch runtime state.
/// \param uniqueId Unique profiling category ID.
#define KZ_DETAIL_PROFILING_IS_CATEGORY_ENABLED_AT_RUNTIME(category, uniqueId) \
    BOOST_PP_EXPR_IF(kzProfilingIsCategoryEnabledAtCompileTime(category), KZ_DETAIL_PROFILING_GET_CATEGORY_RUNTIME_REFERENCE(uniqueId).isEnabled()) \
    BOOST_PP_EXPR_IF(BOOST_PP_NOT(kzProfilingIsCategoryEnabledAtCompileTime(category)), KZ_PROFILING_DISABLED_CATEGORY)

/// Implementation of #kzProfilingCategorySetRuntimeState macro logic.
#define KZ_DETAIL_PROFILING_SET_CATEGORY_RUNTIME_STATE(uniqueId, newRuntimeState) KZ_DETAIL_PROFILING_GET_CATEGORY_RUNTIME_REFERENCE(uniqueId).setEnabled(newRuntimeState)

/// Implementation of #kzProfilingSetAllCategoriesRuntimState macro logic.
#define KZ_DETAIL_PROFILING_SET_ALL_CATEGORIES_RUNTIME_STATE(newRuntimeState) ::kanzi::ProfilingCategory::setAllEnabled(newRuntimeState)

#ifdef KANZI_DOXYGEN
/// This macro is defined in the Kanzi Profiling build configuration only.
/// \see \ref TheKanziProfilingBuild
#define KANZI_PROFILING_BUILD
#endif

#ifdef KANZI_PROFILING_BUILD
/// Do not use this macro directly
///
/// This macro is defined in Kanzi profiling builds. It is uses to disable all 
/// Kanzi profiling categories in all build types except profiling builds where #KANZI_PROFILING_BUILD is defined.
#define KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(categoryState) categoryState
#else
#define KZ_DETAIL_PROFILING_CATEGORY_STATE_FILTER(categoryState) KZ_PROFILING_DISABLED_CATEGORY
#endif

namespace kanzi
{

/// Forward profiling category declaration.
class ProfilingCategory;

namespace detail
{

/// Guarantees creation of profiling category singleton object associated with unique profiling category type defined with KZ_DETAIL_PROFILING_REGISTER_CATEGORY() and passed as template parameter.
///
/// The constructor of the class accesses singleton object associated with the unique profiling category type passed as template argument. That triggers the singleton creation
/// if it has not been created yet. The static instance of this class s_initializerInstance guarantees that the singleton is created during initialization of static variables.
template<typename UniqueProfilingCategoryType>
struct ProfilingCategorySingletonInitializer
{
    /// Accesses singleton object associated with the unique profiling category type passed as template argument.
    /// If access to singleton object happens first time, it will be created.
    explicit ProfilingCategorySingletonInitializer()
    {
        UniqueProfilingCategoryType::getProfilingCategorySingleton();
    }

    /// Static instance of this class guarantees that profiling category singleton is created no later than initialization of static variables is finished.
    static ProfilingCategorySingletonInitializer s_initializerInstance;
};

/// Initialize static instance of profiling category singleton initializer.
template<typename UniqueProfilingCategoryType> ProfilingCategorySingletonInitializer<UniqueProfilingCategoryType> ProfilingCategorySingletonInitializer<UniqueProfilingCategoryType>::s_initializerInstance;

}

}


#endif
