/**
 * \file
 * Error handling functions.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZS_ERROR_H
#define KZS_ERROR_H


#include <boost/preprocessor/cat.hpp>
#include <kanzi/core/debug/assert.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/cpp/string_view.hpp>


/** Error code type definition. */
typedef int kzsError;
/** Exception code type definition, extends error. */
typedef int kzsException;


#define KZS_EXCEPTION_MESSAGE_MAXIMUM_LENGTH 256 /**< Maximum length of exception. */


/*
      0 -  9999: Generic error codes
  10000 - 19999: System layer error codes
  20000 - 29999: Core layer error codes
  30000 - 39999: User layer error codes
  40000 - 49999: Framework error codes
 100000 -      : Application error codes
*/

/** Success code. */
#define KZS_SUCCESS (kzsError)0 /**< No error. */

/* Generic error codes. (1 - ) */
#define KZS_ERROR_ASSERTION_FAILED (kzsError)1 /**< Assertion failed. */
#define KZS_ERROR_NOT_IMPLEMENTED_YET (kzsError)2 /**< Functionality is not yet implemented. */
#define KZS_ERROR_ENUM_OUT_OF_RANGE (kzsError)3 /**< Invalid value for enum. */
#define KZS_ERROR_ILLEGAL_OPERATION (kzsError)4 /**< Trying to perform illegal operation. */
#define KZS_ERROR_ILLEGAL_ARGUMENT (kzsError)5 /**< An argument was invalid for the given context. */
#define KZS_ERROR_MALFORMED_DATA (kzsError)6 /**< Data is malformed. */
#define KZS_ERROR_ARRAY_OUT_OF_BOUNDS (kzsError)7 /**< Trying to access array with invalid index. */
#define KZS_ERROR_INVALID_STATE (kzsError)8 /**< Program is in invalid state. */

#define KZ_LOG_CATEGORY_LEGACY_EXCEPTIONS KZ_LOG_CREATE_CATEGORY(KZ_LOG_DISABLED_CATEGORY, "legacy exceptions")

/** Return from the function without any error code. */
#define kzsSuccess() return KZS_SUCCESS

#define KZ_UNIQUE_NAME_INTERNAL(name) BOOST_PP_CAT(name, __LINE__)

#define KZ_APPEND_MESSAGE_TO_STRING_LOGGER_INTERNAL(logger, logMessage) KZ_MULTILINE_MACRO \
    ::kanzi::detail::LogRecord KZ_UNIQUE_NAME_INTERNAL(record)(logger, ::kanzi::LogLevelInfo, "", "", "", 0); \
    KZ_UNIQUE_NAME_INTERNAL(record).appendMessage logMessage; \
    KZ_MULTILINE_MACRO_END

#define KZ_REPORT_ERROR_INTERNAL(new_error, logMessage) KZ_MULTILINE_MACRO \
    ::kanzi::detail::StringLogger KZ_UNIQUE_NAME_INTERNAL(messageLogger); \
    KZ_APPEND_MESSAGE_TO_STRING_LOGGER_INTERNAL(KZ_UNIQUE_NAME_INTERNAL(messageLogger), logMessage); \
    kzsErrorLog(new_error, KZ_UNIQUE_NAME_INTERNAL(messageLogger).c_str()); \
    kzsErrorThrow_private(new_error, KZ_UNIQUE_NAME_INTERNAL(messageLogger).c_str()); \
    KZ_MULTILINE_MACRO_END

#define KZ_REPORT_EXCEPTION_INTERNAL(error, logMessage) KZ_MULTILINE_MACRO \
    KZ_STATIC_ASSERT((error) < 0, "Tried to throw error code as an exception"); \
    ::kanzi::detail::StringLogger KZ_UNIQUE_NAME_INTERNAL(messageLogger); \
    KZ_APPEND_MESSAGE_TO_STRING_LOGGER_INTERNAL(KZ_UNIQUE_NAME_INTERNAL(messageLogger), logMessage); \
    kzsExceptionLog(error, KZ_UNIQUE_NAME_INTERNAL(messageLogger).c_str()); \
    kzsExceptionThrow_private(error, KZ_UNIQUE_NAME_INTERNAL(messageLogger).c_str()); \
    KZ_MULTILINE_MACRO_END

#ifndef SPANSION
/** Return from the function with the given error code. */
#define kzsErrorThrow(new_error, logMessage) KZ_MULTILINE_MACRO \
    KZ_REPORT_ERROR_INTERNAL(new_error, logMessage); \
    return new_error; \
KZ_MULTILINE_MACRO_END

#else

#define kzsErrorThrow(new_error, logMessage) ::kanzi::detail::exceptionFail()

#endif

/** Return from the function with the given exception code. */
#define kzsExceptionThrow(new_exception, logMessage) KZ_MULTILINE_MACRO \
    KZ_STATIC_ASSERT((new_exception) < 0, "Tried to throw error code as an exception"); \
    KZ_REPORT_EXCEPTION_INTERNAL(new_exception, logMessage); \
    return new_exception; \
KZ_MULTILINE_MACRO_END

/** Return from the function with the given exception code. */
#define kzsExceptionRethrow(param_exception) KZ_MULTILINE_MACRO                            \
    KZ_STATIC_ASSERT((param_exception) < 0, "Tried to rethrow error code as an exception"); \
    return exception;                                                            \
KZ_MULTILINE_MACRO_END

/** Return from the function with the given error code, if the test is false. Otherwise continue. */
#define kzsErrorTest(test, new_error, logMessage) KZ_MULTILINE_MACRO \
    if (!(test)) \
    { \
        kzsErrorThrow(new_error, logMessage); \
    } \
    KZ_MULTILINE_MACRO_END

/** Return from the function with the given exception code, if the test is false. Otherwise continue. */
#define kzsExceptionTest(test, new_exception, logMessage) KZ_MULTILINE_MACRO \
    if (!(test)) \
    { \
        kzsExceptionThrow(new_exception, logMessage); \
    } \
    KZ_MULTILINE_MACRO_END

/**
* Return from the function with the given error code, if it is one.
* If the error code is an exception, the code may or may not return (use ::kzsExceptionForward instead).
*/
#define kzsErrorForward(error) KZ_MULTILINE_MACRO \
    if ((error) != KZS_SUCCESS) \
    { \
        if ((error) < KZS_SUCCESS) \
        { \
            kzsErrorThrow(error, (::kanzi::string_view(kzsErrorGetLastExceptionMessage(("Unhandled exception"))))); \
        } \
        return error; \
    } \
    KZ_MULTILINE_MACRO_END

/** Return from the function with the given exception or error code, if it is one. Otherwise continue. */
#define kzsExceptionForward(exception) KZ_MULTILINE_MACRO   \
    if ((exception) != KZS_SUCCESS)                         \
    {                                                       \
        return exception;                                   \
    }                                                       \
KZ_MULTILINE_MACRO_END

/**
 * If the given exception code is an error, pass it forward. If it is an exception, substitute it with the given error.
 * Otherwise continue.
 */
#define kzsExceptionForwardAsError(exception, new_error, logMessage) KZ_MULTILINE_MACRO \
    if ((exception) < KZS_SUCCESS)                                                      \
    {                                                                                   \
        kzsErrorThrow(new_error, logMessage);                                           \
    }                                                                                   \
    else if ((exception) > KZS_SUCCESS)                                                 \
    {                                                                                   \
        return (kzsError)(exception);                                                   \
    }                                                                                   \
KZ_MULTILINE_MACRO_END

/**
 * Return from the function with the given new error code,
 * if the given old code is also an error. Otherwise continue.
 */
#define kzsErrorSubstitute(error, new_error, logMessage) KZ_MULTILINE_MACRO \
    if ((error) != KZS_SUCCESS) \
    { \
        kzsErrorThrow(new_error, logMessage); \
    } \
    KZ_MULTILINE_MACRO_END

/**
 * Return from the function with the given new exception code,
 * if the given old code is also an exception. Otherwise continue.
 */
#define kzsExceptionSubstitute(error, new_exception, logMessage) KZ_MULTILINE_MACRO \
    if ((error) != KZS_SUCCESS)                                                     \
    {                                                                               \
        return new_exception;                                                       \
    }                                                                               \
KZ_MULTILINE_MACRO_END

/** Test if the given error is an error. */
#define kzsErrorIf(error) if ((error) != KZS_SUCCESS)

/** Test if the given exception matches the specified exception code. */
#define kzsExceptionCatch(exception, exception_code) if ((exception) == (exception_code))

/** Test if the given exception is an actual exception and not success or error. */
#define kzsExceptionCatchAll(exception) if ((exception) < 0)

/** Macro to use to indicate that some code is not yet implemented. */
#define KZS_NOT_IMPLEMENTED_YET kzsErrorLog(KZS_ERROR_NOT_IMPLEMENTED_YET, ("Not implemented yet."))

/** Macro to use to indicate and throw error that some code is not yet implemented. */
#define KZS_NOT_IMPLEMENTED_YET_ERROR kzsErrorThrow(KZS_ERROR_NOT_IMPLEMENTED_YET, ("Not implemented yet."))
/** Macro to use to indicate and throw error with an explanation, that some code is not yet implemented. */
#define KZS_NOT_IMPLEMENTED_YET_ERROR_TEXT(message) kzsErrorThrow(KZS_ERROR_NOT_IMPLEMENTED_YET, (message))

/** Logs the given error code with given message. */
#define kzsErrorLog(errorCode, message) KZ_MULTILINE_MACRO \
    kzsStoreErrorMessage(errorCode, message); \
    KZ_LOG_FILTER_MESSAGES_INTERNAL(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_ERROR, KZ_LOG_CATEGORY_GENERIC, KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(1, ((::kanzi::string_view(message))))); \
    KZ_MULTILINE_MACRO_END

/** Logs exception with given error code with given message. */
#define kzsExceptionLog(errorCode, message) KZ_MULTILINE_MACRO \
    kzsStoreExceptionMessage(message); \
    KZ_LOG_FILTER_MESSAGES_INTERNAL(::kanzi::DefaultLogger::get(), KZ_LOG_LEVEL_ERROR, KZ_LOG_CATEGORY_LEGACY_EXCEPTIONS, KZ_LOG_BUNDLE_MULTIPLE_MESSAGES_INTERNAL(1, ((::kanzi::string_view(message))))); \
    KZ_MULTILINE_MACRO_END

namespace kanzi
{

#ifdef SPANSION
KZ_ATTRIBUTE_NO_RETURN void exceptionFail();
#endif

namespace detail
{

/// Stores log messages in a string for later retrieval by the error reporting subsystem.
///
/// The error subsystem uses this class internally to convert formatted error messages to string for later use for logging and for creating exception error objects. The error reporting
/// subsystem keeps the latest exception or error message to be retrieved later by tool module through kzsErrorGetLastExceptionMessage().
class StringLogger : public AbstractLogger
{
public:
    
    /// Returns C string representation of logged messages.
    const char* c_str() const
    {
        return m_log.c_str();
    }

protected:
    virtual void writeOverride(LogLevel level, string_view levelName, string_view categoryName, string_view fileName, size_t lineNumber, string_view message)
    {
        KZ_MAYBE_UNUSED(level);
        KZ_MAYBE_UNUSED(levelName);
        KZ_MAYBE_UNUSED(categoryName);
        KZ_MAYBE_UNUSED(fileName);
        KZ_MAYBE_UNUSED(lineNumber);

        m_log.append(message.data(), message.length());
    }

private:   
    /// Placeholder for log messages.
    string m_log;
};

}
}

/** Wrapper for kzsErrorThrow() to share more code. */
KANZI_API void kzsErrorThrow_private(kzsError error, kzString message);

/** Wrapper for kzsExceptionThrow() to share more code. */
KANZI_API void kzsExceptionThrow_private(kzsError error, kzString message);

/// Stores error message in global storage area.
KANZI_API void kzsStoreErrorMessage(kzsError errorCode, kzString message);

/// Stores exception message in per-thread data area.
KANZI_API void kzsStoreExceptionMessage(kzString message);

/** Initializes error handling for thread. */
KANZI_API kzsError kzsErrorInitializeThread(kzMutableString* storage);
/** De-initializes error handling for thread. */
KANZI_API kzsError kzsErrorDeinitializeThread(void);

/** Initialize a global variable for error message storage. */
KANZI_API kzsError kzsErrorInitialize(void);
/** De-initialize a global variable for error message storage. */
KANZI_API kzsError kzsErrorUninitialize(void);

/** Callback that is triggered in error situations. */
typedef void (*KzsErrorCallback)(kzsError errorCode, kzString message);
/** Sets error callback. */
KANZI_API void kzsErrorSetErrorCallback(KzsErrorCallback callback);

/** Callback that is triggered in exception situations. */
typedef void (*KzsExceptionCallback)(kzsError errorCode, kzString message);
/** Sets exception callback. */
KANZI_API void kzsErrorSetExceptionCallback(KzsExceptionCallback callback);

/** Gets last error message stored in a global buffer or empty string if there are no errors have being reported yet. */
KANZI_API kzString kzsErrorGetLastErrorMessage();

/** Gets the last exception message for the thread or empty string if there are no exceptions have being reported yet. */
KANZI_API kzString kzsErrorGetLastExceptionMessage();

/** Gets the last exception message for the thread. Returns fallbackMessage if are no exceptions have being reported yet. */
KANZI_API kzString kzsErrorGetLastExceptionMessage(kzString fallbackMessage);

/** Gets last error code.
*/
KANZI_API kzsError kzsErrorGetLastErrorCode();

#endif
