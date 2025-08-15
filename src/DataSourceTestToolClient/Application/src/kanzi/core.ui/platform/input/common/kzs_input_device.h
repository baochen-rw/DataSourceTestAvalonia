/**
* \file
* Kanzi input device implementation.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_INPUT_DEVICE_H
#define KZS_INPUT_DEVICE_H

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core.ui/input/event_source_properties.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>
#include <kanzi/core.ui/platform/windowing/common/kzs_desktop.h>
#include <kanzi/core.ui/platform/task_dispatcher/common/native_event_handle.hpp>


/**
 * \struct KzsInputDevice
 * Input device object.
 */
struct KzsInputDevice;


/** Creates an input device. */
kzsError kzsInputDeviceCreate(const struct KzsDesktop* desktop,  const kanzi::EventSourceProperties& properties, struct KzsInputDevice** device_out);

/** Deletes an input device. */
kzsError kzsInputDeviceDelete(struct KzsInputDevice* device);

/** Enqueues input data from input device. */
kzsError kzsInputDeviceGatherData(const struct KzsInputDevice* device, struct KzsEventQueue* queue);

/// Returns a waitable event handle for this input device.
kanzi::NativeEventHandle kzsInputDeviceGetEventHandle(const struct KzsInputDevice* device);

#endif
