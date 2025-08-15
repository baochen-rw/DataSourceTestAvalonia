// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_THREAD_HANDLE_HPP
#define KZ_THREAD_HANDLE_HPP

#include <kanzi/core/cpp/platform.hpp>

// Visual Studio's <thread> is not supported when compiling with /clr or /clr:pure.
// So we have a separate header for exposing the thread::native_handle_type, and avoiding the inclusion of <thread>.
//
// Note: You can include \a <kanzi/core/cpp/thread.hpp>, along with this header in your source, for complete thread functionality.

#if defined(_MSC_VER)

// In Visual Studio <thread>, the std::thread::native_handle_type resolves to a void pointer.
namespace kanzi
{
typedef void* ThreadNativeHandleType;
}

#elif defined(KZ_EMULATE_CXX11_STD) || defined(KZ_USE_BOOST_THREAD)

#if defined(__GNUC__)
#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic push
#endif
#pragma GCC diagnostic ignored "-Wtype-limits"
#endif

#include <boost/thread/thread.hpp>

#if KZ_GCC_DIAGNOSTIC_STACK_SUPPORTED
#pragma GCC diagnostic pop
#endif

namespace kanzi
{
typedef boost::thread::native_handle_type ThreadNativeHandleType;
}

#else

#include <thread>

namespace kanzi
{
typedef std::thread::native_handle_type ThreadNativeHandleType;
}

#endif

#endif // KZ_THREAD_HANDLE_HPP.
