// Copyright 2008-2021 by Rightware. All rights reserved.

/// \file
/// Include this file after including any header file that includes windows.h to reduce
/// the amount of macro pollution introduced by windows.h.
/// \see pre_windows.hpp

#ifndef KZ_DISABLE_WIN32_MEAN_AND_LEAN

#ifdef far
#undef far
#endif

#ifdef near
#undef near
#endif

#ifdef FAR
#undef FAR
#endif

#endif
