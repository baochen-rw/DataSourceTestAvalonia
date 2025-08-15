// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PLATFORM_HPP
#define KZ_PLATFORM_HPP

#include "cstdint.hpp"

#if _MSC_VER // Visual Studio

// Boost includes windows.h so we have to disable extra headers included in windows.h
// to prevent pollution of global namespace with unnecessary symbols and typedefs.
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#if _MSC_VER >= 1900 // Visual Studio 2015 or higher

#define KZ_SUPPORTS_USER_DEFINED_LITERAL
#define KZ_SUPPORTS_EXPLICIT_OPERATOR
#define KZ_SUPPORTS_LAMBDA
#define KZ_CPP_NAMESPACE_TR1 std
#define KZ_CPP_SPECIALIZE_TR1_BEGIN \
    namespace std                   \
    {
#define KZ_CPP_SPECIALIZE_TR1_END }
#define KZ_CPP_OPERATOR_NEW_SPEC

#define KZ_FALLTHROUGH
#define KZ_STATIC_ASSERT static_assert
#define KZ_FINAL final
#define KZ_OVERRIDE override
#define KZ_DELETED_FUNCTION = delete

#elif _MSC_VER >= 1800 // Visual Studio 2013 or higher

#define KZ_EMULATE_CXX11_SNPRINTF
#define KZ_SUPPORTS_EXPLICIT_OPERATOR
#define KZ_SUPPORTS_LAMBDA
#define KZ_CPP_NAMESPACE_TR1 std
#define KZ_CPP_SPECIALIZE_TR1_BEGIN \
    namespace std                   \
    {
#define KZ_CPP_SPECIALIZE_TR1_END }
#define KZ_CPP_OPERATOR_NEW_SPEC

#define KZ_FALLTHROUGH
#define KZ_STATIC_ASSERT static_assert
#define KZ_FINAL final
#define KZ_OVERRIDE override
#define KZ_DELETED_FUNCTION = delete

// Visual Studio earlier than 2015 has substandard chrono implementation
#define KZ_USE_BOOST_CHRONO

#else // Visual Studio versions prior to 2013

#error Visual Studio version older than 2013 is not supported.

#endif

// Visual Studio common
#define KZ_ATTRIBUTE_NO_RETURN __declspec(noreturn)

#else // GCC

#if __cplusplus < 201402L
#define KZ_EMULATE_CXX14_STD

#if !defined(__INTEGRITY) || (__cplusplus < 201103L)
#define KZ_EMULATE_CXX14_ITERATOR_RANGE_FUNCTIONS
#endif

#endif

#if __cplusplus < 201103L

#define KZ_EMULATE_CXX11_STD
#define KZ_CPP_NAMESPACE_TR1 boost
#define KZ_CPP_SPECIALIZE_TR1_BEGIN \
    namespace boost                 \
    {
#define KZ_CPP_SPECIALIZE_TR1_END }
#define KZ_CPP_OPERATOR_NEW_SPEC throw(std::bad_alloc)

#define KZ_TOKEN_PASTE2(x, y) x##y
#define KZ_TOKEN_PASTE(x, y) KZ_TOKEN_PASTE2(x, y)
#define KZ_STATIC_ASSERT(x, s) typedef char KZ_TOKEN_PASTE(static_assertion_, __LINE__)[(!!(x)) * 2 - 1] __attribute__((unused))
#define KZ_FINAL
#define KZ_OVERRIDE
#define KZ_DELETED_FUNCTION

#else

#define KZ_SUPPORTS_USER_DEFINED_LITERAL
#define KZ_SUPPORTS_EXPLICIT_OPERATOR
#define KZ_SUPPORTS_LAMBDA
#define KZ_CPP_NAMESPACE_TR1 std
#define KZ_CPP_SPECIALIZE_TR1_BEGIN \
    namespace std                   \
    {
#define KZ_CPP_SPECIALIZE_TR1_END }
#define KZ_CPP_OPERATOR_NEW_SPEC

#define KZ_STATIC_ASSERT static_assert
#define KZ_FINAL final
#define KZ_OVERRIDE override
#define KZ_DELETED_FUNCTION = delete

#if defined(ANDROID) || defined(__ANDROID__)
#define KZ_EMULATE_CXX11_MATH
#define KZ_USE_C99_SNPRINTF
#endif

#endif

#if (__cplusplus >= 201103L) && defined(__has_cpp_attribute) && !defined(__INTEGRITY)
#if __has_cpp_attribute(clang::fallthrough)
#define KZ_FALLTHROUGH [[clang::fallthrough]]
#elif __has_cpp_attribute(gnu::fallthrough)
#define KZ_FALLTHROUGH [[gnu::fallthrough]]
#endif
#endif

#if !defined(KZ_FALLTHROUGH) && defined(__has_attribute)
#if __has_attribute(fallthrough)
#define KZ_FALLTHROUGH __attribute__((fallthrough))
#endif
#endif

#ifndef KZ_FALLTHROUGH
#define KZ_FALLTHROUGH
#endif

#if defined(QNX) || defined(__QNX__)

#if defined(__QNXNTO__)

#include <sys/neutrino.h>
#if _NTO_VERSION < 650
#error QNX versions prior to 6.5.0 are not supported.
#elif _NTO_VERSION < 700

#define KZ_EMULATE_CXX11_MATH
#define KZ_USE_C99_SNPRINTF
#define KZ_USE_SELECT

#if defined(__GLIBCXX__)

#define KZ_USE_BOOST_MAP
#define KZ_USE_BOOST_VECTOR
// Using std::mutex together with libstdc++ triggers crash on QNX660.
#define KZ_USE_BOOST_MUTEX
// Condition variable implementation must match mutex implementation.
#define KZ_USE_BOOST_CONDITION_VARIABLE
// Boost future required since std::async doesn't work on QNX660.
#define KZ_USE_BOOST_FUTURE
// Boost thread used in order to ensure compatibility with Boost mutex, conditional variable and future.
#define KZ_USE_BOOST_THREAD
// Using Boost bind in order to ensure compatibility with Boost thread, since boost::thread includes boost::bind.
#define KZ_USE_BOOST_BIND

#else

#if _NTO_VERSION == 660

#undef KZ_EMULATE_CXX14_ITERATOR_RANGE_FUNCTIONS

// Include yvals.h to make macro configurations without _ALT_NS.
#include <yvals.h>
// Define _ALT_NS to force ccomplex to use namespaces correctly. Otherwise it will give error if included after iostream.
#define _ALT_NS 2
// Included implicitly by some platform-headers so preemptively include and undefine I to avoid conflicts.
#include <ccomplex>
#undef I
#undef _ALT_NS

#define KZ_USE_BOOST_CHRONO
#ifndef _MSC_VER // Don't use Boost stdint on Windows/Visual Studio
#define KZ_USE_BOOST_STDINT
#endif

#endif

#endif

#endif

#else

#error QNX versions prior to 6.5.0 are not supported.

#endif

#endif

// GCC common
#define KZ_ATTRIBUTE_NO_RETURN __attribute__((__noreturn__))

// GCC support for diagnostic stack.
#ifndef __clang__
#define KZ_GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#define KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED (KZ_GCC_VERSION >= 40600)
#endif

// GCC 4.8.x does not support c++11 vectors
#if defined(__linux__) && (KZ_GCC_VERSION >= 40800) && (KZ_GCC_VERSION < 40900)

#define KZ_USE_BOOST_VECTOR

#endif

#endif

#include <kanzi/core/legacy/kzs_types.hpp>

#endif
