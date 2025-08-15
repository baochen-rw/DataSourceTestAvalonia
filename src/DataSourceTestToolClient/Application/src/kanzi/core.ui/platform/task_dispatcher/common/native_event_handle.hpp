// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NATIVE_EVENT_HANDLE_HPP
#define KZ_NATIVE_EVENT_HANDLE_HPP


namespace kanzi
{

#if defined(_MSC_VER) || defined(__MINGW32__)

typedef void* NativeEventHandle;

#else

typedef int NativeEventHandle;

#endif

extern const NativeEventHandle invalidEventHandle;

}


#endif
