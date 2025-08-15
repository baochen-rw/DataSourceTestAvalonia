/**
 * \file
 * Kanzi types - integers, floats, doubles, strings, inlines
 *
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZS_TYPES_H
#define KZS_TYPES_H


#include <kanzi/core/legacy/kzs_stdint.hpp>


/** Boolean type. */
typedef int kzBool;

#define KZ_FALSE (kzBool)0 /**< False boolean value. */
#define KZ_TRUE (kzBool)1 /**< True boolean value. */

/** Char type. */
typedef char kzChar;
/** Unsigned char type. */
typedef unsigned int kzUnicodeChar;
/** Constant string type. */
typedef kzChar const* kzString;
/** Non-const string type. */
typedef kzChar* kzMutableString;

/** Signed integer type. */
typedef int kzInt;
/** Unsigned integer type. */
typedef unsigned int kzUint;

/** Float type. */
typedef float kzFloat;
/** Double precision float type. */
typedef double kzDouble;

/** Byte type. */
typedef unsigned char kzByte;

/** Pointer to anything type. */
typedef void* kzPointer;


/** Null pointer value. */
#define KZ_NULL 0


/** Inline function definition. */
#ifndef KZ_INLINE
#define KZ_INLINE inline
#endif


/// Macro for flagging parameter as potentially unused depending on configuration.
/// Add statements defining parameters as potentially unused at end of function if necessary.
/// Only use this for parameters that really require it. If a parameter is never used, omit the name from definition.
#define KZ_MAYBE_UNUSED(param) (void)param

/** Macro for flagging unused return value. */
#define KZ_UNUSED_RETURN_VALUE(param) (void)param

/** Macro for flagging a function as a call-back function. */
#define KZ_CALLBACK

/** Beginning of a multiline macro. */
#define KZ_MULTILINE_MACRO do {
/** End of a multiline macro. */
#define KZ_MULTILINE_MACRO_END } while ((void)0, 0)

/** Macro to use in empty source file to allow compilation. */
#define KZ_EMPTY_SOURCE_FILE static void* const unusedVariable = KZ_NULL

#if defined(_MSC_VER)
// Disable warning C4251: 'MyClass::m_member' : class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 'MyClass'
// See http://msdn.microsoft.com/en-us/library/esew7y1w.aspx
#pragma warning(disable: 4251)
#endif

// Use Microsoft toolchain specific storage-class attribute.
#if defined(_MSC_VER)
#if defined(KANZI_API_IMPORT) && defined(KANZI_API_EXPORT)
#error "Both KANZI_API_IMPORT and KANZI_API_EXPORT defined"
#elif defined(KANZI_API_IMPORT)
#define KANZI_API __declspec(dllimport)
#elif defined(KANZI_API_EXPORT)
#define KANZI_API __declspec(dllexport)
#else
#define KANZI_API
#endif

// Other toolchains
#else
#define KANZI_API
#endif

#endif