// Copyright 2008-2021 by Rightware. All rights reserved.

/// \file
/// Include this file before including any header file that includes windows.h to reduce
/// the amount of macro pollution and to fix some issues introduced by windows.h.
/// \see post_windows.hpp

// Define this macro before including <kanzi/core/platform/cpp/win32/windows.hpp> to include 
// all headers included by windows.h
#ifdef KZ_DISABLE_WIN32_MEAN_AND_LEAN

#ifdef WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#endif

#ifdef VC_EXTRALEAN
#undef VC_EXTRALEAN
#endif

#ifdef NOMINMAX
#undef NOMINMAX
#endif

#else

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN 1
#endif

#ifndef NOMINMAX
#define NOMINMAX 1
#endif

#endif

// Workaround for "combaseapi.h(229): error C2187: syntax error: 'identifier' was unexpected here" when using /permissive-
struct IUnknown;
