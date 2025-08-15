/**
* \file
* Kanzi input, YunOS implementation
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_INPUT_NATIVE_H
#define KZS_INPUT_NATIVE_H

struct KzsEventQueue;

/// Sets the suspension manager event state to signaled.
void kzsInputDeviceNativeSignalEvent(struct KzsInputDeviceNative* device);

/// Clears the suspension manager event signaling state.
void kzsInputDeviceNativeClearEvent(struct KzsInputDeviceNative* device);

/// Returns a pointer to native input device's event queue. This function should only be called by InputEventListener.
KzsEventQueue* kzsInputDeviceNativeGetEventQueue(struct KzsInputDeviceNative* device);

#endif
