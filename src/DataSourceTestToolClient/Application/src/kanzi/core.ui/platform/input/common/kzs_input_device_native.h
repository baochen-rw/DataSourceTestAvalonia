/**
* \file
* Kanzi native input device implementation
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_INPUT_DEVICE_NATIVE_H
#define KZS_INPUT_DEVICE_NATIVE_H

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core.ui/input/event_source_properties.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>
#include <kanzi/core.ui/platform/windowing/common/kzs_desktop.h>
#include <kanzi/core.ui/platform/task_dispatcher/common/native_event_handle.hpp>


/**
 * \struct KzsInputDeviceNative
 * Native implementation of input device.
 */
struct KzsInputDeviceNative;


#if defined _MSC_VER || defined __MINGW32__
extern struct KzsEventQueue* g_activeEventQueue; /**< Context parameter for Win32 message handler callback functions. */
#endif

/// SYN_DROPPED is not defined in some toolchains,
/// as old Linux kernels don't implement it.
#if !defined(SYN_DROPPED)
#define SYN_DROPPED 3
#endif

/** Creates an input device. */
kzsError kzsInputDeviceNativeCreate(const struct KzsDesktop* desktop, const kanzi::EventSourceProperties& properties, struct KzsInputDeviceNative** device_out);

/** Deletes an input device. */
kzsError kzsInputDeviceNativeDelete(struct KzsInputDeviceNative* device);

/** Enqueues input data from input device. */
kzsError kzsInputDeviceNativeGatherData(struct KzsInputDeviceNative* device, struct KzsEventQueue* queue);

/// Returns a waitable event handle for this input device or a platform-specific invalid-handle if not supported.
kanzi::NativeEventHandle kzsInputDeviceNativeGetEventHandle(const struct KzsInputDeviceNative* device);


#endif
