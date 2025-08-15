// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STRING_CONVERSION_HPP
#define KZ_STRING_CONVERSION_HPP

#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>

namespace kanzi
{

/// Converts a given UTF-8 string view into a Win32-compatible wide character string.
/// \param utf8 String to convert. Must be UTF-8.
/// \return Corresponding wide character string.
KANZI_API wstring convertUTF8ToWideChar(string_view utf8);

/// Converts a given Win32-compatible wide character string view into a UTF-8 string.
/// \param wchar Wide character string to convert.
/// \return Corresponding UTF-8 string.
KANZI_API string convertWideCharToUTF8(wstring_view wchar);

#ifdef UNICODE

typedef wstring Win32String;
typedef wstring_view Win32StringView;

inline Win32String convertUTF8ToWin32(string_view utf8)
{
    return convertUTF8ToWideChar(utf8);
}

inline Win32String convertWideCharToWin32(wstring_view wchar)
{
    return Win32String(wchar);
}

inline string convertWin32ToUTF8(Win32StringView win32)
{
    return convertWideCharToUTF8(win32);
}

inline wstring convertWin32ToWideChar(Win32StringView win32)
{
    return wstring(win32);
}

#else

typedef string Win32String;
typedef string_view Win32StringView;

inline Win32String convertUTF8ToWin32(string_view utf8)
{
    return Win32String(utf8);
}

inline Win32String convertWideCharToWin32(wstring_view wchar)
{
    return convertWideCharToUTF8(wchar);
}

inline string convertWin32ToUTF8(Win32StringView win32)
{
    return string(win32);
}

inline wstring convertWin32ToWideChar(Win32StringView win32)
{
    return convertUTF8ToWideChar(win32);
}

#endif


}

#endif