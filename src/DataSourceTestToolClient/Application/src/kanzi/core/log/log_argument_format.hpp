// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LOG_ARGUMENT_FORMAT_HPP
#define KZ_LOG_ARGUMENT_FORMAT_HPP

#include <kanzi/core/log/log_format_traits.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/cpp/sstream.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/cstdio.hpp>

/// \file
///
/// \section LogMessageFormattingSection Log message formatting
///
/// A log message is either a scalar value or a format specification string followed by the format arguments. 
/// For example:
/// \snippet test_log.cpp Simple log message formatting
///
/// The format specification string is a literal text that can contain the format argument references in curly braces: 
/// 
///     "Text {...} text {...} ... {...} ..."
///
/// When the logger writes the message, it replaces the argument references with a string representation of the values of the referred argument,
/// and keeps the rest of the literal text unchanged. This is the structure of the format argument reference:
///
///     {[argument index][:format specification]}
///
/// The format argument index and format specification are optional.
///
/// \note Place a colon ahead of the format specification part.
///
/// \note To prevent interpreting an opening brace '<b>{</b>' as the format argument reference, prefix it with two backslashes:
/// \verbatim \\{ \endverbatim
/// Note that if it is followed by a closing brace '<b>}</b>', it is not removed and remains in the log message output. 
/// The sole string literal is not considered a format string and is not parsed for format argument references.
///
/// For example:
/// \snippet test_log.cpp Figure brace logging example
///
///
/// The format argument index is a position of the format argument in the argument list. The first format argument has the index 0, followed by
/// the argument with index 1, and so on. The last format argument has the index N-1, where N is the total number of the format arguments.
///
/// The format specification part of the format argument reference describes how to convert the referenced argument to
/// the string when the reference is substituted with the string representation of the argument.
/// See \ref LogFormatSpecifiersSection section for details.
///
/// When the log message is written, the format argument references found in the message format string are replaced with a string representation 
/// of the corresponding arguments.
///
/// In the simplest case the format arguments are referenced by empty braces \b '{}':
/// \snippet test_log.cpp Simple log message format argument reference
///
/// You can also reference the format arguments using the argument index explicitly:
/// \snippet test_log.cpp Indexed log message argument reference
///
/// In the last example you can see that the indexed argument reference \b '{2}' is followed by argument reference without index \b '{}'.
/// In such a case the argument referenced without index is the one (#3 in this case) following the argument referenced with index (#2 in this case).
///
/// \section LogFormatSpecifiersSection Log message argument format specification
///
/// The log message format argument reference consists of argument index and format specification.
/// The format specification describes how the log message format argument value is converted to a string and how it is positioned when the message is written to the log.
/// The logging system takes the format argument value type into account when converting the value to the textual representation, making logging typesafe.
///
/// The format specification has this structure:
///
///     [align][sign][#][0][width][.precision][specifier]
///
/// The <b>align</b> format argument sets the positioning of the resulting text. This table lists the available values for <b>align</b>.
///
/// <table>
/// <tr>
/// <th>Align value
/// <th>Output
/// <tr>
/// <td><
/// <td>Text aligned to the left within the available space.
/// <tr>
/// <td>>
/// <td>Text aligned to the right within the available space. This is the default setting.
/// <tr>
/// <td>=
/// <td>Padding placed after the sign (if any) but before the digits. This is only valid for numeric types.
/// <tr>
/// <td>^
/// <td>Text aligned to the center within the available space.
/// </table>
///
/// The <b>sign</b> is valid for numeric types only. This table lists the available values for <b>sign</b>.
/// <table>
/// <tr>
/// <th>Sign value
/// <th>Output
/// <tr>
/// <td>+
/// <td>The sign of the number for both positive and negative numbers.
/// <tr>
/// <td>-
/// <td>The sign of the number for negative numbers. This is the default setting.
/// <tr>
/// <td>space
/// <td>Leading space for positive numbers, and a minus sign for negative numbers.
/// </table>
///
/// The <b>#</b> format argument is valid for octal or hexadecimal specifier of integer types. If present, the output is prefixed by '0' for the <b>o</b> specifier or by '0x'/'0X' for the <b>x</b>/<b>X</b> specifier.
///
/// The <b>0</b> format argument pads the number with zeroes to the left instead of spaces when the value converted to string consumes less characters than <b>width</b>.
/// 
/// The <b>width</b> format argument is an integer number describing the minimum width of the output text. If the text does not consume the whole width, the remaining space is padded with spaces or, if the <b>0</b> format argument is specified, with zeros.
///
/// The <b>precision</b> format argument is only valid for floating point types and describes how many digits to display after decimal point.
///
/// The <b>precision</b> format argument denotes the notation to use when converting the format argument value to a string. The available <b>specifier</b> values depend on the format argument type.
/// This table lists the available values for <b>specifier</b>.
///
/// <table>
/// <tr>
/// <th>Argument type
/// <th>Specifier
/// <th>Output
/// <tr>
/// <td rowspan = "6">Character
/// <td>c
/// <td>Single character. This is the default for signed characters.
/// <tr>
/// <td>d
/// <td>The number in base 10.
/// <tr>
/// <td>u
/// <td>Unsigned number in base 10. This is the default for unsigned characters.
/// <tr>
/// <td>o
/// <td>The number in base 8.
/// <tr>
/// <td>x
/// <td>The number in base 16 using lowercase letters a - f.
/// <tr>
/// <td>X
/// <td>The number in base 16 using uppercase letters A - F.
/// <tr>
/// <td rowspan = "5">Integer
/// <td>d
/// <td>The number in base 10. This is the default for signed integers.
/// <tr>
/// <td>u
/// <td>Unsigned number in base 10. This is the default for unsigned integers.
/// <tr>
/// <td>o
/// <td>The number in base 8.
/// <tr>
/// <td>x
/// <td>The number in base 16 using lower case letters a - f.
/// <tr>
/// <td>X
/// <td>The number in base 16 using upper case letters A - F.
/// <tr>
/// <td rowspan = "10">Floating point
/// <td>e
/// <td>The number in scientific notation. The letter 'e' denotes the exponent part.
/// <tr>
/// <td>E
/// <td>The number in scientific notation. The letter 'E' denotes the exponent part.<br>
/// <tr>
/// <td>f
/// <td>The number in decimal floating point notation, lowercase. This is the default for floating point numbers.
/// <tr>
/// <td>F
/// <td>The number in decimal floating point notation, upper case.
/// <tr>
/// <td>g
/// <td>The number in the shortest possible representation : 'e' or 'f'.
/// <tr>
/// <td>G
/// <td>The number in the shortest possible representation : 'E' or 'F'.
/// <tr>
/// <td>a
/// <td>The number in hexadecimal floating point notation, lower case.
/// <tr>
/// <td>A
/// <td>The number in hexadecimal floating point notation, upper case.
/// <tr>
/// <td>x
/// <td>The same as 'a'.
/// <tr>
/// <td>X
/// <td>The same as 'A'.
/// <tr>
/// <td>Pointer
/// <td>p
/// <td>The pointer address. This is the default for pointers.
/// </table>
///
///
/// \note If the argument type does not match the specifier field, the default specifier for the argument type is used to convert the argument value to a string.
///
/// If the type of the format argument is a pointer, the \ref LoggingSubsystemSection writes to the log the address stored in the pointer.
/// If the type of the format argument is array (T[]), the \ref LoggingSubsystemSection writes to the log the address of the first element of that array.
/// Only string literals of type const char[] or char[] are written to the log as text.
///
/// To write to the log the string pointed to by the const char* or char* pointer, you can use the string_view object. You can initialize the string_view
/// object with the pointer to the string that you want to log and then use that object as a log format argument. If you pass a pointer to the string as a format
/// argument, only the address of that string is written to the log.
///
/// You can use objects of user-defined type as log format arguments. The \ref LoggingSubsystemSection uses the \ref kanzi::logArgumentToString template function to convert 
/// objects of user-defined type to string. Only the \b align format argument is applicable for user-defined types. The \ref LoggingSubsystemSection specializes 
/// \ref kanzi::logArgumentToString for several user-defined types. See \ref SpecializedLogArgumentToString.
///
/// Examples
/// -------
///
/// To log a message using various argument specifiers:
/// \snippet test_log.cpp Log message with various argument specifiers
///
/// To use string format arguments:
/// \snippet test_log.cpp Use string format arguments

namespace kanzi
{

/// The logging subsystem uses this function to convert a value to string.
///
/// The \ref LoggingSubsystemSection uses this function internally to convert log message format arguments to string, when the type of the format argument is user-defined.
/// See \ref LogFormatSpecifiersSection.
///
/// If you define your own type and want to use objects of that type as format arguments in formatted log messages, you must provide specialization of this function template 
/// for the type you defined, or provide overload of the operator<< for your type required by the default implementation of this template function.
///
/// \param value The value to be converted to string.
/// \return The string representation of \p value.
template<typename T>
string logArgumentToString(const T& value)
{   
    stringstream stream;
    stream << value;
    return stream.str();
}

namespace detail
{

/// Represents the log message argument formatting interface.

/// This class incapsulates interface used by \ref ::detail::kanzi::LogArgumentTypeEraser and \ref ::detail::LogRecord to convert
/// the log message format argument to string. For details, see \ref LogMessageFormattingSection.
class KANZI_API LogArgumentFormat
{
public:

    /// Declares pointer type to function used to convert void argument pointer to string.
    typedef string (*ConversionFunction)(string_view formatString, const void* value);

    /// Enumerates various presentation types supported by the formatting.
    enum PresentationTypeSpecifier
    {
        CharacterPresentationTypeSpecifier,
        UnsignedDecimalPresentationTypeSpecifier,
        DecimalPresentationTypeSpecifier,
        UnsignedOctalPresentationTypeSpecifier,
        UnsignedHexidecimalPresentationTypeSpecifier,
        UnsignedHexidecimalUppercasePresentationTypeSpecifier,
        StringPresentationTypeSpecifier,
        PointerPresentationTypeSpecifier,
        FloatingPointDecimalPresentationTypeSpecifier,
        FloatingPointDecimalUppercasePresentationTypeSpecifier,
        FloatingPointExponentPresentationTypeSpecifier,
        FloatingPointExponentUppercasePresentationTypeSpecifier,
        FloatingPointHexidecimalPresentationTypeSpecifier,
        FloatingPointHexidecimalUppercasePresentationTypeSpecifier,
        FloatingPointAdaptivePresentationTypeSpecifier,
        FloatingPointAdaptiveUppercasePresentationTypeSpecifier
    };

    /// Optional presentation type specifier.
    typedef optional<PresentationTypeSpecifier> OptionalPresentationTypeSpecifier;

    /// The pointer type to the function that converts type presentation specifier to printf specifier.
    typedef string_view (*PresentationTypeSpecifierToStringConversionFunction)(OptionalPresentationTypeSpecifier presentationTypeSpecifier);

    /// Uses type information of the argument to convert pointer to the value to string representation of the value.
    ///
    /// The argument value is converted according to the supplied format string. This template function is only instantiated for the types that support formatting, that is
    /// integral types, pointers, and arrays, but not user-defined types.
    ///
    /// \param formatString The format specification.
    /// \param valueVoidReference The pointer to the argument value.
    /// \return The argument value converted to string using the supplied format specification.
    template <typename T>
    static typename enable_if<LogArgumentSupportsFormatting<T>::value, string>::type convertToString(string_view formatString, const void* valueVoidReference)
    {
        typedef T ValueType;

        const ValueType& valueReference = *static_cast<const ValueType*>(valueVoidReference);

        LogArgumentFormat format(formatString, LogArgumentSupportsPrecisionFormatting<ValueType>::value, &PresentationTypeSpecifierConverter<ValueType>::convert);

        const char* printfFormatString = format.getFormatString();

        int count = snprintf(0, 0, printfFormatString, valueReference);
        string result;

        if (count <= 0)
        {
            return result;
        }

        result.resize(count);
        (void)snprintf(&(*result.begin()), count + 1, printfFormatString, valueReference);

        return result;
    }

    /// Uses type information of the argument to convert a pointer to the value to string representation of the value.
    ///
    /// The argument value is converted according to the supplied format string. This template function is instantiated for types that do not support formatting, that is,
    /// user defined types.
    ///
    /// \param formatString The format specification.
    /// \param valueVoidReference The pointer to the argument value.
    /// \return The argument value converted to string using the supplied format specification.
    template <typename T>
    static typename enable_if<!LogArgumentSupportsFormatting<T>::value, string>::type convertToString(string_view formatString, const void* valueVoidReference)
    {
        typedef T ValueType;

        typedef char StringLiteralType[1];

        const ValueType& valueReference = *static_cast<const ValueType*>(valueVoidReference);
        
        string userConvertedValue = logArgumentToString<ValueType>(valueReference);        
        string result;

        if (userConvertedValue.empty())
        {
            return result;
        }

        LogArgumentFormat format(formatString, LogArgumentSupportsPrecisionFormatting<StringLiteralType>::value, &PresentationTypeSpecifierConverter<StringLiteralType>::convert);
        const char* printfFormatString = format.getFormatString();
        
        int count = snprintf(0, 0, printfFormatString, userConvertedValue.c_str());

        if (count <= 0)
        {
            return result;
        }

        result.resize(count);
        (void)snprintf(&(*result.begin()), count + 1, printfFormatString, userConvertedValue.c_str());

        return result;
    }

    /// Returns printf format string that is used with sprintf to convert the value to string.
    ///
    /// For details, see LogArgumentFormat().
    /// \return printf compatible format string
    const char* getFormatString() const
    {
        return m_formatStringBuffer.c_str();
    }

private:

    /// Used to convert presentation type specifier to printf type specifier in a context of type used to instantiate this template. 
    template <typename T>
    struct PresentationTypeSpecifierConverter
    {
        /// Converts presentation type specifier found in format string to printf type specifier compatible with type used to instantiate this template.
        ///
        /// The presentation type specifier found in the format string is converted to appropriate printf format specifier compatible with type used to instantiate this template. 
        /// If the presentation type specifier is not compatible with the instantiation type or the format string is missing the presentation type, this function returns default printf presentation type specifier for the instantiation type.
        static string_view convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier);
    };

    /// Used to convert presentation type specifier to printf type specifier in a context of array type used to instantiate this template. 
    template <typename T, size_t N>
    struct PresentationTypeSpecifierConverter<T[N]>
    {
        /// Converts presentation type specifier to printf type specifier for array type.
        ///
        /// See PresentationTypeSpecifierConverter<T>::convert() for details for general description. This function always returns pointer type specifier. 
        static string_view convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier);
    };

    /// Specialization of PresentationTypeSpecifierConverter<T,S> for character array types. 
    template <size_t N>
    struct PresentationTypeSpecifierConverter<char[N]>
    {
        /// Converts presentation type specifier to printf type specifier for character array type.
        ///
        /// See PresentationTypeSpecifierConverter<T>::convert() for details for general description. In other cases this function returns literal type specifier.
        static string_view convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier);
    };

    /// Specialization of PresentationTypeSpecifierConverter<T,S> for constant character array types. 
    template <size_t N>
    struct PresentationTypeSpecifierConverter<const char[N]>
    {
        /// Converts presentation type specifier to printf type specifier for constant character array type.
        ///
        /// See PresentationTypeSpecifierConverter<T>::convert() for details for general description. In other cases this function returns literal type specifier.
        static string_view convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier);
    };

    /// Specialization of PresentationTypeSpecifierConverter<T> for pointer types. 
    template <typename T>
    struct PresentationTypeSpecifierConverter<T*>
    {
        /// Converts presentation type specifier found in format string to printf type specifier compatible with pointer type.
        ///
        /// See PresentationTypeSpecifierConverter<T>::convert() for details for general description. This function Always returns pointer type specifier.
        static string_view convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier);
    };

    /// Constructs object by parsing format string tokens and converting it to printf compatible format string, that can be accessed with getFormatString().
    ///
    /// \param formatString format specification.
    /// \param supportsPrecision flag indicating if precision makes sense for argument type.
    /// \param presentationTypeSpecifierConverter function pointer to convert presentation type specifier to printf type specifier compatible with argument type
    explicit LogArgumentFormat(string_view formatString, bool supportsPrecision, PresentationTypeSpecifierToStringConversionFunction presentationTypeSpecifierConverter);

    string m_formatStringBuffer; /// printf compatible format string.
};

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<char>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "c";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case CharacterPresentationTypeSpecifier:
            return "c";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "u";

        case DecimalPresentationTypeSpecifier:
            return "d";

        case UnsignedOctalPresentationTypeSpecifier:
            return "o";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "x";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "X";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<unsigned char>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "u";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case CharacterPresentationTypeSpecifier:
            return "c";
    
        case UnsignedDecimalPresentationTypeSpecifier:
            return "u";

        case DecimalPresentationTypeSpecifier:
            return "d";

        case UnsignedOctalPresentationTypeSpecifier:
            return "o";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "x";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "X";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<short int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "hd";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "hd";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "hu";

        case UnsignedOctalPresentationTypeSpecifier:
            return "ho";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "hx";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "hX";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<unsigned short int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "hu";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "hd";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "hu";

        case UnsignedOctalPresentationTypeSpecifier:
            return "ho";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "hx";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "hX";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "d";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "d";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "u";

        case UnsignedOctalPresentationTypeSpecifier:
            return "o";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "x";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "X";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<unsigned int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "u";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "d";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "u";

        case UnsignedOctalPresentationTypeSpecifier:
            return "o";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "x";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "X";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<long int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "ld";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "ld";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "lu";

        case UnsignedOctalPresentationTypeSpecifier:
            return "lo";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "lx";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "lX";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<unsigned long int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "lu";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "ld";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "lu";
    
        case UnsignedOctalPresentationTypeSpecifier:
            return "lo";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "lx";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "lX";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<long long int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "lld";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "lld";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "llu";

        case UnsignedOctalPresentationTypeSpecifier:
            return "llo";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "llx";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "llX";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<unsigned long long int>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "llu";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case DecimalPresentationTypeSpecifier:
            return "lld";

        case UnsignedDecimalPresentationTypeSpecifier:
            return "llu";

        case UnsignedOctalPresentationTypeSpecifier:
            return "llo";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "llx";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "llX";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<float>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "f";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case FloatingPointDecimalPresentationTypeSpecifier:
            return "f";

        case FloatingPointDecimalUppercasePresentationTypeSpecifier:
            return "F";

        case FloatingPointExponentPresentationTypeSpecifier:
            return "e";

        case FloatingPointExponentUppercasePresentationTypeSpecifier:
            return "E";

        case FloatingPointHexidecimalPresentationTypeSpecifier:
            return "a";

        case FloatingPointHexidecimalUppercasePresentationTypeSpecifier:
            return "A";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "a";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "A";

        case FloatingPointAdaptivePresentationTypeSpecifier:
            return "g";

        case FloatingPointAdaptiveUppercasePresentationTypeSpecifier:
            return "G";

        default:
            return defaultValue;
    }
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<double>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    return PresentationTypeSpecifierConverter<float>::convert(presentationTypeSpecifier);
}

template <>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<long double>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    const char* defaultValue = "Lf";

    if (!presentationTypeSpecifier)
    {
        return defaultValue;
    }

    switch (presentationTypeSpecifier.value())
    {
        case FloatingPointDecimalPresentationTypeSpecifier:
            return "Lf";

        case FloatingPointDecimalUppercasePresentationTypeSpecifier:
            return "LF";

        case FloatingPointExponentPresentationTypeSpecifier:
            return "Le";

        case FloatingPointExponentUppercasePresentationTypeSpecifier:
            return "LE";

        case FloatingPointHexidecimalPresentationTypeSpecifier:
            return "La";

        case FloatingPointHexidecimalUppercasePresentationTypeSpecifier:
            return "LA";

        case UnsignedHexidecimalPresentationTypeSpecifier:
            return "La";

        case UnsignedHexidecimalUppercasePresentationTypeSpecifier:
            return "LA";

        case FloatingPointAdaptivePresentationTypeSpecifier:
            return "Lg";

        case FloatingPointAdaptiveUppercasePresentationTypeSpecifier:
            return "LG";

        default:
            return defaultValue;
    }
}

template <typename T>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<T*>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    KZ_MAYBE_UNUSED(presentationTypeSpecifier);
    return "p";
}

template <typename T, size_t N>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<T[N]>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    return PresentationTypeSpecifierConverter<T*>::convert(presentationTypeSpecifier);
}

template <size_t N>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<char[N]>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    KZ_MAYBE_UNUSED(presentationTypeSpecifier);
    return "s";
}

template <size_t N>
inline string_view LogArgumentFormat::PresentationTypeSpecifierConverter<const char[N]>::convert(OptionalPresentationTypeSpecifier presentationTypeSpecifier)
{
    return PresentationTypeSpecifierConverter<char[N]>::convert(presentationTypeSpecifier);
}

}
}

#endif