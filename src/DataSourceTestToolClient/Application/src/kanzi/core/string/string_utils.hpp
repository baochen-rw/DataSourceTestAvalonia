// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STRING_UTILS_HPP
#define KZ_STRING_UTILS_HPP


#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/vector.hpp>

namespace kanzi
{

/// Splits string to tokens.
///
/// Use this function to split string \p source to substrings using \p delimiter. This function returns vector of resulting substrings.
/// The substrings do not include delimiter.
///
/// Example:
/// --------
/// splitString(string("123;456;"), ";") returns vector of strings: { "123", "456", "" }
///
/// \param source The string that will be split.
/// \param delimiter The delimiter that is used for splitting.
/// \return The vector of substrings.
KANZI_API vector<string> splitString(const string& source, const string& delimiter);

/// Splits string view to tokens.
///
/// Use this function to split string view \p source to substrings using \p delimiter. This function returns vector of resulting substrings.
/// The substrings do not include delimiter.
///
/// Prefer this function over splitString function above to avoid extra cost.
///
/// Example:
/// --------
/// splitString(string_view("123;456;"), ";") returns vector of string views: { "123", "456", "" }
///
/// \param source The string view that will be split.
/// \param delimiter The delimiter that is used for splitting.
/// \return The vector of substrings.
KANZI_API vector<string_view> splitString(string_view source, string_view delimiter);

/// Wrapper for tolower() that returns unsigned char.
KANZI_API unsigned char toLower(unsigned char ch);

}

#endif
