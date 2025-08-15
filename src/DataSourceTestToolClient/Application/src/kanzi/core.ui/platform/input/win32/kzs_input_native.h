/**
* \file
* Kanzi input, win32 specific implementation
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZS_INPUT_NATIVE_H
#define KZS_INPUT_NATIVE_H


#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/platform/cpp/win32/windows.hpp>


/* Forward declaration structures. */
struct KzsEventQueue;
struct KzsInputPointingDevice;
struct KzsWindow;


/** Message handler for native input. */
KANZI_API kzsError kzsInputNativeHandleMessage(struct KzsWindow* window, struct KzsEventQueue* queue, HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam, kzBool* out_handled);
/** Low-level message handler for native input. Expects g_activeEventQueue to be a valid input event queue. */
KANZI_API kzsError kzsWindowNativeWndProcHandler(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam, kzBool* out_handled);


#endif
