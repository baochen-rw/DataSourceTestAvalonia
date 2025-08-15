// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef SPANSION

#ifndef KZ_LOG_CATEGORY_HPP
#define KZ_LOG_CATEGORY_HPP

#include <boost/preprocessor/tuple/elem.hpp>

/// \file
///
///
/// \section LogCategorySection Log category
/// 
/// Use log categories to group log messages that contain information related to the same functionality. You can assign a dedicated log category to each log message group.
/// The log category is a macro that you pass to \ref LoggingMacros when you write log messages. To define a new log category, use the \ref KZ_LOG_CREATE_CATEGORY macro.
/// You can enable or disable the new log category by passing the \ref KZ_LOG_ENABLED_CATEGORY or \ref KZ_LOG_DISABLED_CATEGORY macro as the first parameter of the \ref KZ_LOG_CREATE_CATEGORY macro. 
/// To learn how the state of the log category is used in the log message filtering, see \ref LoggingMessageClassificationSection.
///
/// There are predefined log categories. For example, use \ref KZ_LOG_CATEGORY_GENERIC to log messages that you cannot assign to any other log category.
/// \ref KZ_LOG_CATEGORY_DEBUG is only used internally by the \ref kzLogDebug macro.

/// \defgroup LogCategoryMacros Log category utility macros
///
/// Use these macros to define new log categories and operate on existing ones.
///
/// \{

/// The enabled log category state.
#define KZ_LOG_ENABLED_CATEGORY     1

/// The disabled log category state.
#define KZ_LOG_DISABLED_CATEGORY    0

/// Use the KZ_LOG_CREATE_CATEGORY macro to create a log category.
///
/// Use the \p state parameter to determine the state of the log category. Use the log category state for log message filtering. 
/// See \ref LoggingMessageClassificationSection.
///
/// The \p name parameter is a short string identity of the log category that is passed to the logger when the log message is written.
/// You can implement a logger to include the category name in the log message. See kanzi::AbstractLogger.
///
/// \param state The state of the log category. To enable the log category, set the state to \ref KZ_LOG_ENABLED_CATEGORY, and to disable it, set the state to \ref KZ_LOG_DISABLED_CATEGORY.
/// \param name The name of the log category.
///
/// \see kanzi::AbstractLogger, \ref LoggingMessageClassificationSection, \ref KZ_LOG_CATEGORY_GENERIC.
#define KZ_LOG_CREATE_CATEGORY(state, name) (state, minimumLogLevel, name)

/// To get state of the log category, use KZ_LOG_GET_CATEGORY_STATE macro.
///
/// For detailed information on the log category state see \ref LogCategorySection.
///
/// \param category the log category.
/// \return State of log category.
#define KZ_LOG_GET_CATEGORY_STATE(category)    BOOST_PP_TUPLE_ELEM(3, 0, category)

/// To get the name of the log category, use KZ_LOG_GET_CATEGORY_NAME.
///
/// For detailed information on the log category name see \ref KZ_LOG_CREATE_CATEGORY.
///
/// \param category The log category.
/// \return The name of log category.
#define KZ_LOG_GET_CATEGORY_NAME(category)      BOOST_PP_TUPLE_ELEM(3, 2, category)

/// To check if the log category is enabled, use KZ_LOG_IS_CATEGORY_ENABLED.
///
/// \param category The log category.
/// \return If the category is enabled, 1, otherwise 0.
#define KZ_LOG_IS_CATEGORY_ENABLED(category)    KZ_LOG_GET_CATEGORY_STATE(category)

#ifndef KZ_LOG_CATEGORY_GENERIC_DEFAULT_STATE
/// Define this macro to \ref KZ_LOG_ENABLED_CATEGORY or \ref KZ_LOG_DISABLED_CATEGORY to enable or disable \ref KZ_LOG_CATEGORY_GENERIC category.
///
/// This macro is used to set the state of the \ref KZ_LOG_DISABLED_CATEGORY. If you do not define this macro before including this header then it 
/// will be defined to the value of \ref KZ_LOG_ENABLED_CATEGORY.
#define KZ_LOG_CATEGORY_GENERIC_DEFAULT_STATE         KZ_LOG_ENABLED_CATEGORY
#endif
/// \}

/// \defgroup LogCategories Log categories
///
/// Default log categories.
/// \{

/// Use the generic log category to log messages that you cannot assign to any other log category. Always prefer to assign log messages to existing log categories,
/// or define a new log category rather than use the generic log category. The state of this category is determined by \ref KZ_LOG_CATEGORY_GENERIC_DEFAULT_STATE.
#define KZ_LOG_CATEGORY_GENERIC                 KZ_LOG_CREATE_CATEGORY(KZ_LOG_CATEGORY_GENERIC_DEFAULT_STATE, "generic")

#ifndef KZ_LOG_CATEGORY_DEBUG_DEFAULT_STATE
/// Define this macro to \ref KZ_LOG_ENABLED_CATEGORY or \ref KZ_LOG_DISABLED_CATEGORY to enable or disable \ref KZ_LOG_CATEGORY_DEBUG category.
///
/// This macro is used to set the state of the \ref KZ_LOG_CATEGORY_DEBUG. If you do not define this macro before including this header then it 
/// will be defined to the value of \ref KZ_LOG_ENABLED_CATEGORY.
#define KZ_LOG_CATEGORY_DEBUG_DEFAULT_STATE   KZ_LOG_ENABLED_CATEGORY
#endif

/// Use the debug log category for debug messages only. The state of this category is determined by \ref KZ_LOG_CATEGORY_DEBUG_DEFAULT_STATE.
#define KZ_LOG_CATEGORY_DEBUG                    KZ_LOG_CREATE_CATEGORY(KZ_LOG_CATEGORY_DEBUG_DEFAULT_STATE, "debug")

/// The log category for extra graphics mesh log messages.
///
/// This category is disabled by default. To enable extra graphics mesh log messages, set the state of this category to \ref KZ_LOG_ENABLED_CATEGORY.
#define KZ_LOG_CATEGORY_GRAPHICS_MESH_EXTRA      KZ_LOG_CREATE_CATEGORY(KZ_LOG_DISABLED_CATEGORY, "graphics mesh extra")

/// The log category for extra EGL log messages.
///
/// This category is disabled by default. To enable extra EGL log messages, set the state of this category to \ref KZ_LOG_ENABLED_CATEGORY.
#define KZ_LOG_CATEGORY_EGL_EXTRA                KZ_LOG_CREATE_CATEGORY(KZ_LOG_DISABLED_CATEGORY, "egl extra")
/// \}

#endif

#endif
