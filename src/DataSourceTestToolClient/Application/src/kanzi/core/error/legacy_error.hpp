// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LEGACY_ERROR_HPP
#define KZ_LEGACY_ERROR_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/stdexcept.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/log/log_specialization.hpp>

#include <stdarg.h>


typedef int kzsError;
typedef int kzsException;

namespace kanzi
{

KANZI_API kzString kzErrorCodeToString(kzsError code);

class LegacyError : public runtime_error
{
public:

    explicit LegacyError(kzsError value, kzString message):
        runtime_error(message),
        value(value)
    {
    }

    kzsError value;
};

/// Used by logging system to convert legacy exception type objects to string.
///
/// See template logArgumentToString().
template <>
inline string logArgumentToString(const LegacyError& legacyError)
{
    return logArgumentToString<exception>(legacyError);
}

#ifdef SPANSION

#define kzThrowLegacyError(value) exceptionFail()
#define kzThrowLegacyErrorMessage(value, message) exceptionFail()
#define kzThrowLegacyErrorFormat(value, format, ...) exceptionFail()

#else

KANZI_API KZ_ATTRIBUTE_NO_RETURN void kzThrowLegacyError(kzsError value);
KANZI_API KZ_ATTRIBUTE_NO_RETURN void kzThrowLegacyErrorMessage(kzsError value, kzString message);
KANZI_API KZ_ATTRIBUTE_NO_RETURN void kzThrowLegacyErrorMessage(kzsError value, const string& message);
KANZI_API KZ_ATTRIBUTE_NO_RETURN void kzThrowLegacyErrorFormat(kzsError value, kzString format, ...);

KANZI_API string kzFormatVariadicLogMessage(kzString format, ...);
KANZI_API string kzFormatVariadicLogMessageList(kzString format, va_list arguments);

#endif

}

#define kzThrowIfErrorInner(x)                           if ((x) != KZS_SUCCESS) { kanzi::kzThrowLegacyError(x); }
#define kzThrowIfErrorMessageInner(x, message)           if ((x) != KZS_SUCCESS) { kanzi::kzThrowLegacyErrorMessage(x, message); }
#define kzThrowIfErrorFormatInner(x, variadicLogMessage) if ((x) != KZS_SUCCESS) { kanzi::kzThrowLegacyErrorFormat(x, variadicLogMessage); }

#define kzThrowIfError(x)                           KZ_MULTILINE_MACRO kzsError legacyErrorCode_ = (x); kzThrowIfErrorInner(legacyErrorCode_); KZ_MULTILINE_MACRO_END
#define kzThrowIfErrorMessage(x, message)           KZ_MULTILINE_MACRO kzsError legacyErrorCode_ = (x); kzThrowIfErrorMessageInner(legacyErrorCode_, message); KZ_MULTILINE_MACRO_END
#define kzThrowIfErrorFormat(x, variadicLogMessage) KZ_MULTILINE_MACRO kzsError legacyErrorCode_ = (x); kzThrowIfErrorFormatInner(legacyErrorCode_, variadicLogMessage); KZ_MULTILINE_MACRO_END

#define kzThrowIfErrorTest(test, error)                           if(!(test)) { kanzi::kzThrowLegacyError(error); }
#define kzThrowIfErrorTestMessage(test, error, message)           if(!(test)) { kanzi::kzThrowLegacyErrorMessage(error, message); }
#define kzThrowIfErrorTestFormat(test, error, variadicLogMessage) if(!(test)) { kanzi::kzThrowLegacyErrorMessage(error, kanzi::kzFormatVariadicLogMessage variadicLogMessage); }


#endif
