// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_EXCEPTION_HPP
#define KZ_EXCEPTION_HPP


#include <kanzi/core/cpp/platform.hpp>

#include <exception>
#include <kanzi/core/cpp/type_traits.hpp>
#include <kanzi/core/cpp/stdexcept.hpp>


#if defined(KANZI_NO_EXCEPTIONS)

#ifdef SPANSION
namespace kanzi
{
KZ_ATTRIBUTE_NO_RETURN void exceptionFail();
}

#define kzThrowException(e) exceptionFail()

#else

/// Throws an exception. User defined.
KZ_ATTRIBUTE_NO_RETURN void kzThrowException(const std::exception& e);

#endif

#else

/// Throws an exception.
template <typename TExceptionType>
KZ_ATTRIBUTE_NO_RETURN inline void kzThrowException(const TExceptionType& e)
{
    KZ_STATIC_ASSERT((::kanzi::is_base_of<std::exception, TExceptionType>::value), "Class of exception to be thrown must derive from std::exception.");
    throw e;
}

#endif


#endif
