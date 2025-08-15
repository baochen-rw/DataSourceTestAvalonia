/**
* \file
* Variable argument list wrapper
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_ARG_H
#define KZS_ARG_H


#include <kanzi/core/legacy/kzs_types.hpp>

#include <stdarg.h>


/**
 * Variable argument iterator type. kzArgList may not be passed by value
 * to a function nor copied without using kzArgListCopy().
 */
typedef va_list kzArgList;

/**
 * Variable argument iterator constant modifier.
 */
#if defined __GNUC__ && defined __LP64__
#define KZ_CONST_ARGLIST /* 64-bit GCC doesn't allow passing kzArgList as const pointer. */
#else
#define KZ_CONST_ARGLIST const
#endif

/** Makes a copy of a variable argument list. */
void kzArgListCopy(kzArgList* target, KZ_CONST_ARGLIST kzArgList* source);
/** Deletes a copy of a variable argument list. Must be called once for every kzArgListCopy(). */
void kzArgListEnd(kzArgList* list);

/* In major implementations, when passed through the variable argument
 list '...' - construct, chars are promoted to ints and floats to doubles*/

/** Reads a float from variable argument iterator. */
#define KZ_READ_FLOAT_FROM_ARGLIST(list_param)(kzFloat)va_arg((list_param), double)
/** Reads an integer from variable argument iterator. */
#define KZ_READ_INT_FROM_ARGLIST(list_param)(kzInt)va_arg((list_param), int)
/** Reads an unsigned integer from variable argument iterator. */
#define KZ_READ_UINT_FROM_ARGLIST(list_param)(kzUint)va_arg((list_param), unsigned int)
/** Reads a boolean from variable argument iterator. */
#define KZ_READ_BOOL_FROM_ARGLIST(list_param)(kzBool)va_arg((list_param), int)
/** Reads a character from variable argument iterator. */
#define KZ_READ_CHAR_FROM_ARGLIST(list_param)(kzChar)va_arg((list_param), int)
/** Reads a string from variable argument iterator. */
#define KZ_READ_STRING_FROM_ARGLIST(list_param)(kzString)va_arg((list_param), char*)
/** Reads a pointer from variable argument iterator. */
#define KZ_READ_POINTER_FROM_FROM_ARGLIST(list_param)(void*)va_arg((list_param), void*)


#endif
