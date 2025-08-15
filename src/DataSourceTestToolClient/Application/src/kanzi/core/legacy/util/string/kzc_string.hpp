/**
 * \file
 * String utilities.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZC_STRING_H
#define KZC_STRING_H


#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/wrappers/kzs_arg.hpp>


/* Forward declarations */
struct KzcMemoryManager;


/** Constant for string termination character. */
#define KZC_STRING_TERMINATION_SYMBOL '\0'
/** Constant for unicode replacement character. */
#define KZC_STRING_UNICODE_REPLACEMENT_CHARACTER (kzUnicodeChar)0xFFFD


/** String iterator for unicode characters. */
struct KzcStringIterator
{
    kzString tail_private; /**< Tail of the string being iterated in UTF-8 format. */
    kzUnicodeChar codePoint_private; /**< Codepoint of the current string position. */
};


/**
 * Creates a new mutable string of given length and terminates it with '\0' from the start.
 * The string can contain length - 1 characters in addition to the terminating character.
 */
KANZI_API kzsError kzcStringCreate(kzUint length, kzMutableString* out_string);

/**
 * Creates a new string of given length. Terminating '\0' is not counted in the length.
 * The resulting string is not initialized and does not have terminating '\0'.
 */
KANZI_API kzsError kzcStringAllocate(kzUint length, kzMutableString* out_string);

/**
 * Creates a new string of given length using specified memory manager. Terminating '\0' is not counted in the length.
 * The resulting string is not initialized and does not have terminating '\0'.
 */
KANZI_API kzsError kzcStringAllocate(KzcMemoryManager* memoryManager, kzUint length, kzMutableString* out_string);

/** Deletes a string. */
KANZI_API kzsError kzcStringDelete(kzMutableString string);

/** Deletes a string using specified memory manager. */
KANZI_API kzsError kzcStringDelete(KzcMemoryManager* memoryManager, kzMutableString string);


/**
 * Returns the length of a string. Terminating '\0' is not counted.
 * Note that this function returns the number of UTF-8 bytes, not the number of unicode code points in it.
 */
KANZI_API kzUint kzcStringLength(kzString string);

/** Returns KZ_TRUE if the string is empty. */
KANZI_API kzBool kzcStringIsEmpty(kzString string);

/** Creates a copy of the given source string. */
KANZI_API kzsError kzcStringCopy(kzString source, kzMutableString* out_target);

/** Creates a copy of the given source string using specified memory manager. */
KANZI_API kzsError kzcStringCopy(KzcMemoryManager* memoryManager, kzString source, kzMutableString* out_target);

/** Concatenates two strings. */
KANZI_API kzsError kzcStringConcatenate(kzString front, kzString back,
                              kzMutableString* out_string);

/** Concatenates arbitrary number of strings. */
KANZI_API kzsError kzcStringConcatenateMultiple(kzUint numStrings,
                                      kzMutableString* out_string, ...);

/**
 * Returns a substring of the given string starting from the given index and length characters long.
 * If length would go out of bounds of the string it is silently clamped to the end of the string. 
 */
KANZI_API kzsError kzcStringSubstring(kzString string, kzUint start, kzUint length, kzMutableString* out_string);

/**
 * Finds the first position where given sub string is located in the given string.
 * Returns the index of the first letter which is part of the search string
 * Returns false if the pattern is not found.
 * \param out_index Index from the beginning of the string, KZ_NULL if not used.
 */
KANZI_API kzBool kzcStringFindSubstring(kzString string, kzString subString, kzUint* out_index);

/**
 * Finds the next position where given sub string is located in the given string. Search is started from the given index,
 * which must be smaller than the length of the string. Returns false if the pattern is not found.
 * \param out_index Index from the beginning of the string, KZ_NULL if not used.
 */
KANZI_API kzBool kzcStringFindNextSubstring(kzString string, kzString subString, kzUint startIndex, kzUint* out_index);

/** Returns the number of how many times given pattern exists as a substring in given string without overlapping. */
KANZI_API kzUint kzcStringGetSubstringCount(kzString string, kzString pattern);

/**
 * Finds the first position where given character is located in the given string.
 * Returns false if the character is not found.
 */
KANZI_API kzBool kzcStringFindCharacter(kzString string, kzChar ch, kzUint* out_index);

/** Checks if the given string starts with the given pattern. */
KANZI_API kzBool kzcStringStartsWith(kzString string, kzString pattern);

/** Checks if the given string ends with the given pattern. */
KANZI_API kzBool kzcStringEndsWith(kzString string, kzString pattern);

/** Replace instances of pattern in base. Return resulting string in out_string. 'out_string' is assigned new memory from heap. */
KANZI_API kzsError kzcStringReplace(kzString originalString, kzString pattern,
                          kzString patternReplacement, kzMutableString* out_string);

/**
* Parse input string to an integer value.
* \param string String to parse.
* \return Integer value parsed from string or 0 if the string contains an invalid number. */
KANZI_API kzInt kzcStringToInt(kzString string);

/**
* Parse input string to a floating point value.
* \param string String to parse.
* \return Floating-point value parsed from string or 0.0f if the string contains an invalid number. */
KANZI_API kzFloat kzcStringToFloat(kzString string);

/**
 * Splits the string by the given separator into an array of strings.
 * The separator symbol is not included in the output string.
 * The returned string array must be released with delete[].
 */
KANZI_API kzsError kzcStringSplit(kzString string, kzString separator,
                        kzUint* out_stringCount, kzMutableString** out_strings);

/**
 * Creates string that contains lower case letters from source string.
 * This function only modifies characters in the range A-Z.
 */
KANZI_API kzsError kzcStringAsciiToLowerCase(kzString sourceString,
                                   kzMutableString* out_string);

/**
 * vsnprintf()-like string formatter.
 * Format parameter specifies how the resulting string is formatted.
 * Arguments parameter provides the formatting arguments as variable arguments list.
 * \param out_string Newly allocated, formatted string. Free with kzcStringDelete().
 * \see kzcStringFormat for format information.
 */
KANZI_API kzsError kzcStringFormatList(kzString format, KZ_CONST_ARGLIST kzArgList* arguments, kzMutableString* out_string);

/**
 * Formats the given string with given parameters.
 * Format parameter specifies how the resulting string is formatted.
 * Formatting arguments are given as variable arguments.
 *
 * Format flags:
 *
 * %[flags][width][.precision]type
 * Alternatively %% produces a single % character.
 *
 * flags:  - Use left alignment for output
 *         + Use sign for non-negative numbers also
 *         0 Use leading zeros for padding, when width is specified
 *
 *         Flags must appear in the order listed above.
 *
 * width: Any positive number. Output will be padded with spaces until it is at least this number of characters wide.
 *        Output will then be right-aligned by default.
 *
 * precision: Precision is available only for floating point types.
 *            Exactly this number of decimal digits will be outputted.
 *
 * Type char  Actual type     Format
 *   i/d        kzInt           Signed integer
 *   u          kzUint          Unsigned integer
 *   f          kzFloat         printed in scientific notation if not enough space for decimal notation
 *   x          kzUint          Lowercase hexadecimal integer (badf00d)
 *   X          kzUint          Uppercase hexadecimal integer (BADF00D)
 *   s          kzString        String
 *   c          kzChar          ASCII character
 *   C          kzUnicodeChar   Unicode character
 *   b          kzBool          Lowercase boolean string (true or false)
 *   B          kzBool          Boolean string with first letter uppercase (True or False)
 *   p          void*           Memory pointer
 *
 * An error is thrown, if the format is not meaningful (eg. %+b, %5.5i or %-i).
 */
KANZI_API kzsError kzcStringFormat(kzString format, kzMutableString* out_string, ...);

/** Compare two strings. Return -1 if first < second, 0 if first == second and 1 if first > second. */ 
KANZI_API kzInt kzcStringCompare(kzString first, kzString second);

/** Compare two strings. Return KZ_TRUE if the strings are equal. */ 
KANZI_API kzBool kzcStringIsEqual(kzString first, kzString second);

/** Returns the number of unicode characters in given UTF-8 encoded string. */
KANZI_API kzUint kzcStringGetUnicodeLength(kzString string);

/**
 * Decodes the given UTF-8 encoded string to an array of unicode code points.
 * New memory is allocated for out_unicodeArray, which must be manually freed.
 */
KANZI_API kzsError kzcStringToUnicodeArray(const struct KzcMemoryManager* memoryManager, kzString string,
                                 kzUint* out_characterCount, kzUnicodeChar** out_unicodeCharacters);

/** Get unicode iterator for given UTF-8 string. */
KANZI_API struct KzcStringIterator kzcStringGetIterator(kzString string);

/** Finds the next entry in the attached hash map. Returns KZ_TRUE if next entry is found, otherwise KZ_FALSE. */
#define kzcStringIterate(iterator_param) kzcStringIterate_private(&iterator_param)

/** Returns the value of the hash map entry pointed by the iterator. */
#define kzcStringIteratorGetValue(iterator_param) kzcStringIteratorGetValue_private(&iterator_param)


/** \see kzcStringIterate */
KANZI_API kzBool kzcStringIterate_private(struct KzcStringIterator* iterator);
/** \see kzcStringIteratorGetValue */
KANZI_API kzUnicodeChar kzcStringIteratorGetValue_private(const struct KzcStringIterator* iterator);

/** Test whether or not a certain character is whitespace. */
KANZI_API kzBool kzcStringAsciiCharIsSpace(kzChar character);


#endif
