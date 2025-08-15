// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROFILING_CATEGORY_HPP
#define KZ_PROFILING_CATEGORY_HPP

#include <boost/preprocessor/tuple/elem.hpp>
#include <kanzi/core/profiling/profiling_category_detail.hpp>

/// \ingroup ProfilingMacros
/// \{

/// The enabled profiling category state.
#define KZ_PROFILING_ENABLED_CATEGORY     1

/// The disabled profiling category state.
#define KZ_PROFILING_DISABLED_CATEGORY    0

/// Creates a new profiling category.
///
/// Use the \p compileTimeState parameter to set the compile-time state of the profiling category. The \ref ProfilingMacros use the compile-time state of the category.
/// The string literal you provide in \p name is a unique profiling category name.
///
/// \param compileTimeState The compile-time state of the profiling category: enabled (#KZ_LOG_ENABLED_CATEGORY) or disabled (#KZ_LOG_DISABLED_CATEGORY).
/// \param name Unique profiling category name. Must be string literal other than "*", which is used as wildcard name in category filter configuration.
/// \param sampleBufferSize The sample buffer size of the profiling category.
///
/// Example
/// -------
/// To create and register a profiling category:
/// \snippet snippets_profiling.cpp Create and register a profiling category
#define kzProfilingCreateCategory(compileTimeState, name, sampleBufferSize) (compileTimeState, name, sampleBufferSize)

/// Registers a new profiling category.
///
/// To be able to use a profiling category, you must first register it. To create a profiling category use #kzProfilingCreateCategory().
/// This macro must be called from the global namespace scope.
///
/// If the category you provide in the \p category parameter is disabled at compile time, this macro emits no code. The macro defines a unique type
/// to control the runtime state of the profiling category. You must provide the initial runtime state of the category through the \p initialRuntimeState parameter.
///
/// \param category The profiling category macro to register.
/// \param initialRuntimeState The initial runtime state of the category: enabled (#KZ_PROFILING_ENABLED_CATEGORY) or disabled (#KZ_PROFILING_DISABLED_CATEGORY).
///
/// Example
/// -------
/// To create and register a profiling category:
/// \snippet snippets_profiling.cpp Create and register a profiling category
#define kzProfilingRegisterCategory(category, initialRuntimeState) KZ_DETAIL_PROFILING_EVALUATE_IF_CATEGORY_IS_ENABLED(category, KZ_DETAIL_PROFILING_REGISTER_CATEGORY(KZ_DETAIL_EMPTY_EXPORT_IMPORT_PREFIX, category, category ## _ID, initialRuntimeState))

/// Registers a new profiling category that is exported/imported to/from shared library.
///
/// To be able to use a profiling category, you must first register it. To create a profiling category use #kzProfilingCreateCategory().
/// This macro must be called from the global namespace scope.
///
/// If the category you provide in the \p category parameter is disabled at compile time, this macro emits no code. The macro defines a unique type 
/// to control the runtime state of the profiling category. An export/import directive you provide in \p exportImportDirective parameter is added to 
/// profiling category type definition. This allows you to use profiling category registered in DLL or shared library which is linked to your application at runtime.
/// The export/import directive is operating system and toolchain dependent. For example MSVC provides __declspec(dllexport)/__declspec(dllimport) to export/import names.
///
/// \param exportImportDirective A directive to export/import registered category to/from shared library.
/// \param category The profiling category macro to register.
/// \param initialRuntimeState The initial runtime state of the category: enabled (#KZ_PROFILING_ENABLED_CATEGORY) or disabled (#KZ_PROFILING_DISABLED_CATEGORY).
///
/// Example
/// -------
/// To create and register an exported profiling category:
/// \snippet snippets_profiling.cpp Create and register an exported profiling category
#define kzProfilingRegisterExportedCategory(exportImportDirective, category, initialRuntimeState) KZ_DETAIL_PROFILING_EVALUATE_IF_CATEGORY_IS_ENABLED(category, KZ_DETAIL_PROFILING_REGISTER_CATEGORY(exportImportDirective, category, category ## _ID, initialRuntimeState))

/// Sets the runtime state of a profiling category.
///
/// If the category you provide in the \p category parameter is disabled at compile time, this macro emits no code.
///
/// \param category The profiling category macro.
/// \param newRuntimeState New runtime state of the category: enabled (#KZ_PROFILING_ENABLED_CATEGORY) or disabled (#KZ_PROFILING_DISABLED_CATEGORY).
#define kzProfilingCategorySetRuntimeState(category, newRuntimeState) KZ_DETAIL_PROFILING_EVALUATE_IF_CATEGORY_IS_ENABLED(category, KZ_DETAIL_PROFILING_SET_CATEGORY_RUNTIME_STATE(category ## _ID, newRuntimeState))

/// Sets the runtime state of all profiling categories.
///
/// \param newRuntimeState New runtime state for all categories: enabled (#KZ_PROFILING_ENABLED_CATEGORY) or disabled (#KZ_PROFILING_DISABLED_CATEGORY).
#define kzProfilingSetAllCategoriesRuntimState(newRuntimeState) KZ_DETAIL_PROFILING_SET_ALL_CATEGORIES_RUNTIME_STATE(newRuntimeState)

/// Gets the compile-time category state.
///
/// \param category The profiling category macro to fetch state.
/// \return The state of \p category: enabled (#KZ_PROFILING_ENABLED_CATEGORY) or disabled (#KZ_PROFILING_DISABLED_CATEGORY).
#define kzProfilingGetCategoryCompileTimeState(category)    BOOST_PP_TUPLE_ELEM(3, 0, category)

/// Gets the name of a profiling category.
///
/// \param category The profiling category macro to fetch name.
/// \return The name of the \p category.
#define kzProfilingGetCategoryName(category)      BOOST_PP_TUPLE_ELEM(3, 1, category)

/// Gets the sample buffer size of a profiling category.
///
/// \param category The profiling category macro to fetch sample buffer size.
/// \return The sample buffer size of the \p category.
#define kzProfilingGetCategorySampleBufferSize(category)      BOOST_PP_TUPLE_ELEM(3, 2, category)

/// Gets the runtime profiling category reference.
///
/// The behavior of this macro is defined only if the category you provide in the \p category parameter is enabled at compile time.
/// Otherwise the behavior of this macro is undefined.
///
/// Use this macro to fetch a reference to profiling category object, associated with the profiling category you provide in the \p category parameter.
/// The profiling category object is an object of type #ProfilingCategory and is used by profiling subsystem to store of runtime category state.
/// You can use the reference provided by this macro to get or set the runtime state of the profiling.
///
/// \param category The profiling category macro to fetch category runtime reference.
/// \return Reference to \ref kanzi::ProfilingCategory.
#define kzProfilingGetCategoryRuntimeReference(category) KZ_DETAIL_PROFILING_GET_CATEGORY_RUNTIME_REFERENCE(category ## _ID)

/// Checks whether a profiling category is enabled at runtime.
///
/// Use this macro to get the runtime state of the category you provide in the \p category parameter. If the category is disabled at compile time,
/// this macro is evaluated to #KZ_PROFILING_DISABLED_CATEGORY. Otherwise the runtime state of the category is returned.
///
/// \param category The profiling category macro to fetch status.
/// \return #KZ_PROFILING_DISABLED_CATEGORY if the category is disabled at compile time, otherwise true/false, if profiling category is enabled/disabled at runtime.
#define kzProfilingIsCategoryEnabledAtRuntime(category) KZ_DETAIL_PROFILING_IS_CATEGORY_ENABLED_AT_RUNTIME(category, category ## _ID)

/// Checks whether a profiling category is enabled at compile time.
///
/// \param category The profiling category macro to test status.
/// \return #KZ_PROFILING_ENABLED_CATEGORY / #KZ_PROFILING_DISABLED_CATEGORY, when profiling category is enabled / disabled.
#define kzProfilingIsCategoryEnabledAtCompileTime(category)    kzProfilingGetCategoryCompileTimeState(category)

/// \}

namespace kanzi
{

/// \ingroup Profiling
/// Represents the runtime state of the profiling category.
class KANZI_API ProfilingCategory
{
public:

    /// Creates a new profiling category. Do not call this function directly.
    ///
    /// This function is used to create a new profiling category object. The name you provide in the \p name parameter should be unique for each category.
    /// The function raises an exception if a category with the given name already exists.
    ///
    /// \param name The name of the new category.
    /// \param initialEnabled The initial runtime state of the category.
    /// \return The reference to new profiling category.
    static ProfilingCategory& create(FixedString name, bool initialEnabled);

    /// Sets the category filter. Do not call this function directly.
    ///
    ///
    /// \param filterConfiguration Filter configuration string.
    static void setFilter(string_view filterConfiguration);

    /// Looks up a profiling category by its name.
    /// 
    /// Use profiling category name you provided in \p name to look up created profiling category.
    /// See #create() for details.
    ///
    /// \param name The name of the profiling category to lookup.
    /// \return Pointer to the profiling category object, 0 if category was not found.
    static ProfilingCategory* findByName(string_view name);

    /// Enables or disables the profiling category.
    ///
    /// \param enabled Whether to enable or disable the category.
    void setEnabled(bool enabled)
    {
        m_enabled = enabled;
    }

    /// Shows or hides the profiling category in the HUD.
    ///
    /// \param shownInHUD Whether to show or hide the category in the HUD.
    void setShownInHUD(bool shownInHUD)
    {
        m_shownInHUD = shownInHUD;
    }

    /// Resets the profiling category to its initial runtime state.
    void resetEnabledToInitial()
    {
        m_enabled = m_initialEnabled;
    }

    /// Enables or disables all profiling categories.
    ///
    /// \param enabled Whether to enable or disable all categories.
    static void setAllEnabled(bool enabled);

    /// Shows or hides all profiling categories in the HUD.
    ///
    /// \param shownInHUD Whether to show or hide all categories in the HUD.
    static void setAllShownInHUD(bool shownInHUD);

    /// Resets all profiling categories to their initial runtime state.
    static void resetAllEnabledToInitial();

    /// Gets the name of a profiling category.
    ///
    /// \return Category name.
    FixedString getName() const
    {
        return m_name;
    }

    /// Checks whether a profiling category is enabled.
    /// \return True if the category is enabled, otherwise false.
    bool isEnabled() const
    {
        return m_enabled;
    }

    /// To check if the category is shown in the HUD, use isShownInHUD().
    /// \return True if the category is shown in the HUD, otherwise false.
    bool isShownInHUD() const
    {
        return m_shownInHUD;
    }

private:

    /// Default constructor.
    ///
    /// \name Category name
    /// \name initialEnabled The initial runtime state of the category.
    explicit ProfilingCategory(FixedString name, bool initialEnabled);

    /// Deleted copy constructor.
    explicit ProfilingCategory(const ProfilingCategory& other) KZ_DELETED_FUNCTION;

    /// Deleted assignment operator
    ProfilingCategory& operator=(const ProfilingCategory& other) KZ_DELETED_FUNCTION;

    /// Name of the category.
    FixedString m_name;

    /// Initial state of the category: true - enabled, false - disabled.
    const bool m_initialEnabled;

    /// Current state of the category: true - enabled, false - disabled.
    bool m_enabled;

    /// Flags indicates if data this category assigned to is shown in HUD.
    bool m_shownInHUD;
};

}

#endif
