/// \file
/// Platform-specific globals and constants for Android platform.
///
/// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ANDROID_HPP
#define KZ_ANDROID_HPP

#include <jni.h>


/// Globally available Java Virtual Machine object.
extern JavaVM* g_kzsJavaVM;

/// User-defined Android view class derived from com.rightware.kanzi.KanziView.
extern jclass g_kzsViewClass; 

/// Instance of the user-defined Android view class currently in use.
extern jobject g_kzsView; 

/// User-defined Android activity class derived from com.rightware.kanzi.KanziActivity.
extern jclass g_kzsActivityClass; 

/// Instance of the user-defined Android activity class.
extern jobject g_kzsActivity; 


#endif
