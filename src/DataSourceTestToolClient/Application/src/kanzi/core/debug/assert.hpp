// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ASSERT_HPP
#define KZ_ASSERT_HPP

#include <kanzi/core/debug/assert_detail.hpp>

/// \defgroup AssertionMacros Assertion macros
///
/// In the debug build, use assertion macros to terminate the application and log the error message when the assertion is failed.
///
/// To assert expressions use \ref kzAssert and \ref kzAssertMessage macros.
///
/// To assert unreachable code paths use \ref kzAssertUnreachable and \ref kzAssertUnreachableMessage.
///
/// To insert a breakpoint use \ref kzDebugBreak.
///
/// \note The assertion macros use the \ref LoggingSubsystemSection to log the errors.
/// 
/// \{

/// In the debug build, if assertion expression evaluates to false, use this macro to terminate the application and log the error message.
///
/// The error message includes the file name and the line number where the assertion failed. 
///
/// If you want to include in the error message the description, which makes it easier to understand why assertion failed, use \ref kzAssertMessage.
///
/// For compile-time assertion, use \ref KZ_STATIC_ASSERT.
///
/// \note In the release build the calls to this macro are removed during preprocessing.
///
/// \param expression The assertion expression.
///
/// Example
/// --------
///
/// To terminate an application when assertion fails:
/// \snippet test_assert.cpp Simple assertion
#define kzAssert(expression) KZ_ASSERT_IF_KANZI_DEBUG_ENABLED_INTERNAL(KZ_ASSERT_INTERNAL(expression))

/// In the debug build, if the assertion expression evaluates to false, use this macro to terminate the application and log the error message including the description message you provided.
///
/// The error message includes the description \p message you provided and the file name and the line number where the assertion failed.
///
/// For compile-time assertion, use \ref KZ_STATIC_ASSERT.
///
/// \note In the release build the calls to this macro are removed during preprocessing.
///
/// \param expression The assertion expression.
/// \param message The description message you want to include in the error message. For the format description see \ref LogMessageFormattingSection.
///
/// Example
/// -------
///
/// To terminate an application when assertion fails and include in the log message a description of why the assertion failed:
/// \snippet test_assert.cpp Assertion with description
#define kzAssertMessage(expression, message) KZ_ASSERT_IF_KANZI_DEBUG_ENABLED_INTERNAL(KZ_ASSERT_MESSAGE_INTERNAL(expression, message))

/// In the debug build, use this macro to terminate the application and log the error message.
///
/// Use this macro to assert the execution of the code which must not be reached by any valid code path.
/// The error message includes the file name and the line number where the assertion failed.
/// 
/// If you want to include in the error message additional description message, which makes it easier to understand why the assertion failed,
/// use \ref kzAssertUnreachableMessage.
///
/// \note In the release build the behavior of this macro is undefined.
///
/// Example
/// -------
/// 
/// To terminate an application and write an error message:
/// \snippet test_assert.cpp Code unreachable assertion
#define kzAssertUnreachable() KZ_ASSERT_IF_KANZI_DEBUG_ENABLED_INTERNAL(KZ_ASSERT_UNREACHABLE_INTERNAL())

/// In the debug build, use this macro to terminate the application and log the error message including the description message you provided.
///
/// The error message includes the description \p message you provided and the file name and the line number where the assertion failed.
///
/// \note In the release build the behavior of this macro is undefined.
///
/// \param message The description message you want to include in the error message. For the format description see \ref LogMessageFormattingSection.
///
/// Example
/// -------
///
/// To terminate an application when assertion fails and include in the log message a description of why the assertion failed:
/// \snippet test_assert.cpp Unreachable assertion with message
#define kzAssertUnreachableMessage(message) KZ_ASSERT_IF_KANZI_DEBUG_ENABLED_INTERNAL(KZ_ASSERT_UNREACHABLE_MESSAGE_INTERNAL(message))

/// In the debug build, when you attach the debugger, use this macro to trigger a breakpoint.
///
/// If you do not attach the debugger, the execution continues without interruption.
///
/// \note In the release build the calls to this macro are removed during preprocessing.
#define kzDebugBreak() KZ_ASSERT_IF_KANZI_DEBUG_ENABLED_INTERNAL(::kanzi::detail::debugBreak())
/// \}

#endif
