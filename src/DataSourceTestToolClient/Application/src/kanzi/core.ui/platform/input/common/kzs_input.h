/**
 * \file
 * Input device handling. Keyboards, mice, touch screens, joysticks and similar devices.
 * 
 * Copyright 2008-2021 by Rightware. All rights reserved.
 */
#ifndef KZS_INPUT_H
#define KZS_INPUT_H


#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


/* Forward declarations. */
struct KzsWindow;
struct KzsEvent;
struct KzsEventQueue;
struct KzsEventQueueIterator;
struct KzsInputCursor;
struct KzsInputEventKey;
struct KzsInputEventPointer;
struct KzsInputEventTouch;
struct KzsWindowEventSimple;
struct KzsWindowEventResize;
struct KzsWindowEventOrientationChange;


/** List of window orientation. */
enum KzsWindowOrientation
{
    KZS_WINDOW_ORIENTATION_LANDSCAPE, /**< LANDSCAPE. */
    KZS_WINDOW_ORIENTATION_PORTRAIT, /**< PORTRAIT. */
    KZS_WINDOW_ORIENTATION_COUNT  /**< Last enum value for validation checks. */
};

/* TODO: Separate window events out from event type. */
/** Enumeration for different types of events. */
enum KzsEventType
{
    KZS_EVENT_NONE,                        /**< Should be handled as unused. */
    KZS_EVENT_KEY,                         /**< Key press or release. */
    KZS_EVENT_POINTER,                     /**< Pointer movement or press action. */
    KZS_EVENT_TOUCH,                       /**< Touch event. One finger or more. */
    KZS_EVENT_WINDOW_RESIZED,              /**< Window has been resized. */
    KZS_EVENT_WINDOW_RESIZE_REQUESTED,     /**< Window resize has been requested. */
    KZS_EVENT_WINDOW_FOCUS_LOST,           /**< Window has lost input focus but it may still be completely or partially visible. */
    KZS_EVENT_WINDOW_FOCUS_GAINED,         /**< Window has gained input focus and is fully visible. */
    KZS_EVENT_WINDOW_HIDDEN,               /**< Window has been minimized or completely hidden and/or a power saver or screen saver is enabled. Rendering should be disabled. */
    KZS_EVENT_WINDOW_RESOURCES_LOST,       /**< Window has lost the resources it has used. Application may need to be restarted or reinitialized. */
    KZS_EVENT_DISPLAY_ORIENTATION_CHANGED, /**< Display orientation has been changed. */
    KZS_EVENT_WINDOW_CLOSED,               /**< Window has been closed. */
    KZS_EVENT_APPLICATION_PAUSED,          /**< Application will be paused. */
    KZS_EVENT_APPLICATION_SLEEP,           /**< Application will be put to sleep by the operating system. */
    KZS_EVENT_APPLICATION_WAKEUP,          /**< Application has been waken up by the operating system. */
    KZS_EVENT_DEBUG_TOGGLE_HUD,            /**< Toggle HUD debug request. */
    KZS_EVENT_DEBUG_SET_HUD                /**< Set HUD debug request. */
};

/** Enumeration to select translation of events. */
enum KzsInputTranslation
{
    KZS_INPUT_TRANSLATE_NONE,                      /**< Do not translate anything, receive both touch and pointer events. */
    KZS_INPUT_TRANSLATE_POINTER_TO_TOUCH,          /**< Translate all pointer events to touch events. Disable pointer events. */
    KZS_INPUT_TRANSLATE_TOUCH_TO_POINTER,          /**< Translate all touch events to pointer events. Disable touch events. */
    KZS_INPUT_TRANSLATE_POINTER_TO_TOUCH_PRESERVE, /**< Translate all pointer events to touch events. Preserve pointer events. */
    KZS_INPUT_TRANSLATE_TOUCH_TO_POINTER_PRESERVE  /**< Translate all touch events to pointer events. Preserve pointer events. */
};

/** Enumeration for different states for a pointing device. */
enum KzsInputPointingDeviceState
{
    KZS_POINTING_DEVICE_STATE_DOWN,  /**< Pressed. */
    KZS_POINTING_DEVICE_STATE_MOVE,  /**< Pointer moved. Not all platforms support this, for example many touch screens. */
    KZS_POINTING_DEVICE_STATE_DRAG,  /**< Pointer dragged. */
    KZS_POINTING_DEVICE_STATE_UP,    /**< Released. */
    KZS_POINTING_DEVICE_STATE_SCROLL /**< Scrolled. Not all platforms support this, but can be used for example to mouse wheel. */
};

/** Enumeration for the state of a single cursor (as opposed to the state of the whole device. */
enum KzsInputCursorState
{
    KZS_CURSOR_STATE_DOWN,       /**< First finger down. */
    KZS_CURSOR_STATE_STATIONARY, /**< First finger down. */
    KZS_CURSOR_STATE_MOVE,       /**< First finger down. */
    KZS_CURSOR_STATE_UP          /**< First finger down. */
};

/** Enumeration for different states for a touch device. */
enum KzsInputTouchState
{
    KZS_TOUCH_STATE_BEGIN,    /**< First finger down. */
    KZS_TOUCH_STATE_CONTINUE, /**< Gesture or touch event in progress. */
    KZS_TOUCH_STATE_END       /**< Last finger up. */
};

/** Enumeration for different states for a key device. */
enum KzsInputKeyDeviceState
{
    KZS_KEY_DEVICE_STATE_DOWN,  /**< Pressed. */
    KZS_KEY_DEVICE_STATE_UP,    /**< Released. */
    KZS_KEY_DEVICE_STATE_REPEAT /**< Key is being held. */
};


/** Iterator for event queues. */
struct KzsEventQueueIterator
{
    kzInt index;                       /**< Index to current event. */
    const struct KzsEventQueue* queue; /**< Queue to iterate in. */
};


#define KZS_POINTING_DEVICE_BUTTON_PRIMARY   (1)      /**< Primary pointer button, e.g. usually mouse left on Windows. */
#define KZS_POINTING_DEVICE_BUTTON_SECONDARY (1 << 1) /**< Secondary pointer button, e.g. usually mouse right on Windows. */
#define KZS_POINTING_DEVICE_BUTTON_TERTIARY  (1 << 2) /**< Tertiary pointer button, e.g. usually mouse middle on Windows. */

/** Platform independent key enumeration */
enum KzsInputKey
{
    /* Unknown keys are used for unmapped keys. */
    KZS_KEY_UNKNOWN             = 0,

    /* Keys used for numeric input */   
    KZS_KEY_0                   = 1,
    KZS_KEY_1                   = 2,
    KZS_KEY_2                   = 3,
    KZS_KEY_3                   = 4,
    KZS_KEY_4                   = 5,
    KZS_KEY_5                   = 6,
    KZS_KEY_6                   = 7,
    KZS_KEY_7                   = 8,
    KZS_KEY_8                   = 9,
    KZS_KEY_9                   = 10,
    KZS_KEY_COMMA               = 11,
    KZS_KEY_PERIOD              = 12,
    KZS_KEY_DECIMAL_SEPARATOR   = 13,    /**< allows for locale specific separator key mapping */
    KZS_KEY_THOUSANDS_SEPARATOR = 14,    /**< allows for locale specific separator key mapping */

    /* Keys used for text input */
    KZS_KEY_A                   = 15,
    KZS_KEY_B                   = 16,
    KZS_KEY_C                   = 17,
    KZS_KEY_D                   = 18,
    KZS_KEY_E                   = 19,
    KZS_KEY_F                   = 20,
    KZS_KEY_G                   = 21,
    KZS_KEY_H                   = 22,
    KZS_KEY_I                   = 23,
    KZS_KEY_J                   = 24,
    KZS_KEY_K                   = 25,
    KZS_KEY_L                   = 26,
    KZS_KEY_M                   = 27,
    KZS_KEY_N                   = 28,
    KZS_KEY_O                   = 29,
    KZS_KEY_P                   = 30,
    KZS_KEY_Q                   = 31,
    KZS_KEY_R                   = 32,
    KZS_KEY_S                   = 33,
    KZS_KEY_T                   = 34,
    KZS_KEY_U                   = 35,
    KZS_KEY_V                   = 36,
    KZS_KEY_W                   = 37,
    KZS_KEY_X                   = 38,
    KZS_KEY_Y                   = 39,
    KZS_KEY_Z                   = 40,

    KZS_KEY_SPACE               = 41,
    KZS_KEY_BACKSPACE           = 42,
    KZS_KEY_ENTER               = 43,
    KZS_KEY_TAB                 = 44,
    KZS_KEY_ESC                 = 45,
    
    KZS_KEY_CAPS_LOCK           = 46,
    KZS_KEY_NUM_LOCK            = 47,
    KZS_KEY_PRINT_SCREEN        = 48,
    KZS_KEY_SCROLL_LOCK         = 49,
    KZS_KEY_BREAK               = 50,

    KZS_KEY_INSERT              = 51,
    KZS_KEY_DELETE              = 52,
    KZS_KEY_HOME                = 53,
    KZS_KEY_END                 = 54,
    KZS_KEY_PAGE_UP             = 55,
    KZS_KEY_PAGE_DOWN           = 56,

    KZS_KEY_PLUS                = 57,
    KZS_KEY_MINUS               = 58,
    KZS_KEY_MULTIPLY            = 59,
    KZS_KEY_DIVIDE              = 60,

    /* Arrow keys for navigation (8-directional on some devices?) */
    KZS_KEY_ARROW_UP            = 61,
    KZS_KEY_ARROW_DOWN          = 62,
    KZS_KEY_ARROW_LEFT          = 63,
    KZS_KEY_ARROW_RIGHT         = 64,
    
    /* Numpad keys on a common IBM keyboard */
    KZS_KEY_NUM_0               = 65,
    KZS_KEY_NUM_1               = 66,
    KZS_KEY_NUM_2               = 67,
    KZS_KEY_NUM_3               = 68,
    KZS_KEY_NUM_4               = 69,
    KZS_KEY_NUM_5               = 70,
    KZS_KEY_NUM_6               = 71,
    KZS_KEY_NUM_7               = 72,
    KZS_KEY_NUM_8               = 73,
    KZS_KEY_NUM_9               = 74,
    KZS_KEY_NUM_DIVIDE          = 75,
    KZS_KEY_NUM_MULTIPLY        = 76,
    KZS_KEY_NUM_PLUS            = 77,
    KZS_KEY_NUM_MINUS           = 78,
    KZS_KEY_NUM_COMMA           = 79,
    KZS_KEY_NUM_ENTER           = 80,
    
    /* Function keys on a common IBM keyboard */
    KZS_KEY_F1                  = 81,
    KZS_KEY_F2                  = 82,
    KZS_KEY_F3                  = 83,
    KZS_KEY_F4                  = 84,
    KZS_KEY_F5                  = 85,
    KZS_KEY_F6                  = 86,
    KZS_KEY_F7                  = 87,
    KZS_KEY_F8                  = 88,
    KZS_KEY_F9                  = 89,
    KZS_KEY_F10                 = 90,
    KZS_KEY_F11                 = 91,
    KZS_KEY_F12                 = 92,

    /* Sound volume control keys */
    KZS_KEY_VOLUME_UP           = 93,
    KZS_KEY_VOLUME_DOWN         = 94,

    /* Unnamed buttons, usually on phones etc */
    KZS_KEY_SOFTKEY1            = 95,  
    KZS_KEY_SOFTKEY2            = 96,
    KZS_KEY_SOFTKEY3            = 97,
    KZS_KEY_SOFTKEY4            = 98,
    
    /* Generic names for modifier keys such as shift, ctrl, alt, Fn, command, super, etc. */
    KZS_KEY_MODIFIER1           = 99, 
    KZS_KEY_MODIFIER2           = 100,
    KZS_KEY_MODIFIER3           = 101,
    
    /* Specific modifier key names on a common IBM keyboard */
    KZS_KEY_RIGHT_ALT           = 102,
    KZS_KEY_RIGHT_CONTROL       = 103,
    KZS_KEY_RIGHT_SHIFT         = 104,
    KZS_KEY_RIGHT_WINDOWS_KEY   = 105,
    KZS_KEY_LEFT_ALT            = 106,
    KZS_KEY_LEFT_CONTROL        = 107,
    KZS_KEY_LEFT_SHIFT          = 108,
    KZS_KEY_LEFT_WINDOWS_KEY    = 109,
    KZS_KEY_MENU_KEY            = 110,
    
    /* Key names for Finnish 105-key IBM keyboard */
    KZS_KEY_SECTION             = 111,  /**< left of 1 */
    KZS_KEY_QUOTE               = 112,  /**< left of enter, below */
    KZS_KEY_LESS_THAN           = 113,  /**< left of Z */
    KZS_KEY_UMLAUT              = 114,  /**< left of enter, above */
    KZS_KEY_AUML                = 115,  /**< right of OUML */
    KZS_KEY_OUML                = 116,  /**< right of L */   
    KZS_KEY_ARING               = 117,  /**< right of P */
    KZS_KEY_ACCENT              = 118,  /**< left of backspace */

    /* Key names for game controller */
    KZS_KEY_BUTTON_A            = 119,
    KZS_KEY_BUTTON_B            = 120,
    KZS_KEY_BUTTON_C            = 121,
    KZS_KEY_BUTTON_X            = 122,
    KZS_KEY_BUTTON_Y            = 123,
    KZS_KEY_BUTTON_Z            = 124,
    KZS_KEY_BUTTON_L1           = 125,
    KZS_KEY_BUTTON_L2           = 126,
    KZS_KEY_BUTTON_R1           = 127,
    KZS_KEY_BUTTON_R2           = 128,
    KZS_KEY_BUTTON_SELECT       = 129,
    KZS_KEY_BUTTON_START        = 130,
    KZS_KEY_BUTTON_THUMBL       = 131,
    KZS_KEY_BUTTON_THUMBR       = 132,
    KZS_KEY_BUTTON_MODE         = 133,

    KZS_KEY_COUNT               = 134
};


/** Callback function type for event handling. */ 
typedef kzsError (*KzsEventHandleFunction)(const struct KzsEventQueue* queue, void* userData);


/** Creates a new event queue. */
KANZI_API kzsError kzsEventQueueCreate(struct KzsEventQueue** queue_out);
/** Frees memory allocated for a input event queue. */
KANZI_API void kzsEventQueueDelete(struct KzsEventQueue* queue);

/** Get an iterator over an event queue. */
KANZI_API struct KzsEventQueueIterator kzsEventQueueGetIterator(const struct KzsEventQueue* queue);
/** Internal iteration. */
KANZI_API kzBool kzsEventQueueIteratorIterate_private(struct KzsEventQueueIterator* it);
/** Iterate an event queue iterator.
*
* Return true if this value is still valid.
*/
#define kzsEventQueueIteratorIterate(it) kzsEventQueueIteratorIterate_private(&it)
/** Internal iteration get value. */
KANZI_API struct KzsEvent* kzsEventQueueIteratorGetValue_private(const struct KzsEventQueueIterator* it);
/** Get the current value of an event queue iterator. */
#define kzsEventQueueIteratorGetValue(it) kzsEventQueueIteratorGetValue_private(&it)

/** Get nth event from an event queue. */
KANZI_API struct KzsEvent* kzsEventQueueGetEvent(const struct KzsEventQueue* queue, kzUint index);
/** Get the number of events in an event queue. */
KANZI_API kzUint kzsEventQueueGetEventCount(const struct KzsEventQueue* queue);

/** Clear all events from an event queue. */
KANZI_API void kzsEventQueueClear(struct KzsEventQueue* queue);

/** Swap contents of two queues. */
KANZI_API void kzsEventQueueSwap(struct KzsEventQueue* queue1, struct KzsEventQueue* queue2);

/** Renders an event idempotent. */
KANZI_API void kzsEventInvalidate(struct KzsEvent* event);

/** Creates a new key event with input values. */
KANZI_API struct KzsEvent* kzsEventCreateKeyEvent(kzUint button, enum KzsInputKeyDeviceState state);

/** Frees memory allocated for a input event. */
KANZI_API void kzsEventDeleteKeyEvent(struct KzsEvent* event);

/** Adds a new event into the queue. */
KANZI_API struct KzsEvent* kzsEventQueueAddRawEvent(struct KzsEventQueue* queue, const struct KzsEvent* event);

/** Adds a new key event into the queue with input values. */
KANZI_API struct KzsEvent* kzsEventQueueAddKeyEvent(struct KzsEventQueue* queue, kzUint button,
                                          enum KzsInputKeyDeviceState state);

/** Adds a new pointer event into the queue with input values.
*
* If translating to touch events, add a touch event with one cursor instead. */
KANZI_API struct KzsEvent* kzsEventQueueAddPointerEvent(struct KzsEventQueue* queue, kzInt x, kzInt y,
                                              kzU32 buttons, kzInt scroll, enum KzsInputPointingDeviceState state);

/** Adds a new touch event
*
* The touch event generated will have a specified number of cursors. The cursors must be filled separately to the
* event structure returned from this function. */
KANZI_API struct KzsEvent* kzsEventQueueAddTouchEvent(struct KzsEventQueue* queue, kzUint numCursors);
/** As add touch event, but with a state already set now. */
KANZI_API struct KzsEvent* kzsEventQueueAddTouchEventWithState(struct KzsEventQueue* queue, kzUint numCursors,
                                                     enum KzsInputTouchState state);
/** As add touch event with details. Useful in testing. */
KANZI_API struct KzsEvent* kzsEventQueueAddTouchEventWithDetails(struct KzsEventQueue* queue, enum KzsInputTouchState state,
                                                       enum KzsInputCursorState cursorState, kzFloat x, kzFloat y);
/** Adds a new window event into the queue. */
KANZI_API struct KzsEvent* kzsEventQueueAddSimpleWindowEvent(struct KzsEventQueue* queue, enum KzsEventType type, struct KzsWindow* window);
/** Adds a new window resize event into the queue. */
KANZI_API struct KzsEvent* kzsEventQueueAddWindowResizeEvent(struct KzsEventQueue* queue, struct KzsWindow* window, kzUint width, kzUint height);
/** Adds a new window resize request event into the queue. */
KANZI_API struct KzsEvent* kzsEventQueueAddWindowResizeRequestedEvent(struct KzsEventQueue* queue, struct KzsWindow* window, kzUint width, kzUint height);

/** Adds a new orientation change event into the queue. */
KANZI_API struct KzsEvent* kzsEventQueueAddWindowOrientationChangeEvent(struct KzsEventQueue* queue, struct KzsWindow* window, enum KzsWindowOrientation orientation);

/** Adds a new application paused event. */
KANZI_API struct KzsEvent* kzsEventQueueAddApplicationPausedEvent(struct KzsEventQueue* queue);
/** Adds a new application sleep event. */
KANZI_API struct KzsEvent* kzsEventQueueAddApplicationSleepEvent(struct KzsEventQueue* queue);
/** Adds a new application wakeup event. */
KANZI_API struct KzsEvent* kzsEventQueueAddApplicationWakeupEvent(struct KzsEventQueue* queue);

/** Adds a new toggle HUD debug event into the queue. */
KANZI_API struct KzsEvent* kzsEventQueueAddToggleHUDDebugEvent(struct KzsEventQueue* queue);
/** Adds a new set HUD debug event into the queue. */
KANZI_API struct KzsEvent* kzsEventQueueAddSetHUDDebugEvent(struct KzsEventQueue* queue, kzInt onoff);

/** Get the pointer event from an input event. */
KANZI_API const struct KzsInputEventPointer* kzsInputEventGetPointingDeviceData(const struct KzsEvent* event);
/** Get key event from an input event. */
KANZI_API const struct KzsInputEventKey* kzsInputEventGetKeyDeviceData(const struct KzsEvent* event);
/** Get touch event from an input event. */
KANZI_API const struct KzsInputEventTouch* kzsInputEventGetTouchData(const struct KzsEvent* event);
/** Get the event type. */
KANZI_API enum KzsEventType kzsEventGetType(const struct KzsEvent* event);

/** Get the identifier of the touch cursor. */
KANZI_API kzUint kzsInputCursorGetId(const struct KzsInputCursor* inputdata);
/** Gets the pressure of the touch cursor. */
KANZI_API kzFloat kzsInputCursorGetPressure(const struct KzsInputCursor* inputData);
/** Gets the radius of the touch cursor. */
KANZI_API kzFloat kzsInputCursorGetRadius(const struct KzsInputCursor* inputData);
/** Get the x coordinate of touch cursor. */
KANZI_API kzFloat kzsInputCursorGetX(const struct KzsInputCursor* inputData);
/** Get the y coordinate of touch cursor. */
KANZI_API kzFloat kzsInputCursorGetY(const struct KzsInputCursor* inputData);
/** Get the state of the touch cursor. */
KANZI_API enum KzsInputCursorState kzsInputCursorGetState(const struct KzsInputCursor* inputdata);

/** Gets the raw button code of the key device. */
KANZI_API kzUint kzsInputEventKeyGetButtonRaw(const struct KzsInputEventKey* inputData);
/** Gets the translated button of the key device. */
KANZI_API enum KzsInputKey kzsInputEventKeyGetButton(const struct KzsInputEventKey* inputData);
/** Gets the state of the key device. */
KANZI_API enum KzsInputKeyDeviceState kzsInputEventKeyGetState(const struct KzsInputEventKey* inputData);

/** Gets the bitfield of the buttons of the active pointing device.
 * \param inputData Input data pointer.
 * \return Bitmask of pointing device buttons, defined as KZS_POINTING_DEVICE_BUTTON_ *.
 */
KANZI_API kzU32 kzsInputEventPointerGetButtons(const struct KzsInputEventPointer* inputData);
/** Gets the scroll amount of the active pointing device. */
KANZI_API kzInt kzsInputEventPointerGetScroll(const struct KzsInputEventPointer* inputData);
/** Gets the state of the active pointing device. */
KANZI_API enum KzsInputPointingDeviceState kzsInputEventPointerGetState(const struct KzsInputEventPointer* inputData);
/** Gets the x coordinate of the active pointing device. */
KANZI_API kzInt kzsInputEventPointerGetX(const struct KzsInputEventPointer* inputData);
/** Gets the y coordinate of the active pointing device. */
KANZI_API kzInt kzsInputEventPointerGetY(const struct KzsInputEventPointer* inputData);

/** Get the nth cursor form a touch event. */
KANZI_API struct KzsInputCursor* kzsInputEventTouchGetCursor(const struct KzsInputEventTouch* inputData, kzUint cursorIdx);
/** Get the number of cursors in this event. */
KANZI_API kzUint kzsInputEventTouchGetCursorCount(const struct KzsInputEventTouch* inputData);
/** Get the touch state.
*
* Note that touch state goes DOWN when the first finger touches the screen and UP when the last finger leaves.
* Everything in-between is drag. */
KANZI_API enum KzsInputTouchState kzsInputEventTouchGetState(const struct KzsInputEventTouch* inputData);
/** Add a cursor to a touch event.
*
* The queue is needed for potential mirroring of the event.
*
* Returns true if there was space for the cursor, false otherwise.
*
* If translating pointer events, add a pointer event instead and mark the touch event as unusable.
*
* If the event is not a touch event, do nothing unless translating. */
KANZI_API kzBool kzsInputEventTouchSetCursor(struct KzsEventQueue* queue, struct KzsEvent* event, kzUint cursorIndex,
                                   kzUint cursorId, kzFloat x, kzFloat y, kzFloat pressure, kzFloat radius, enum KzsInputCursorState state);
/** Set the state of touch event.
*
* This function takes a generic event structure for consistency.
*
* If the event is not a touch event, do nothing. */
KANZI_API void kzsInputEventTouchSetState(struct KzsEvent* event, enum KzsInputTouchState state);

/** Get the target window of the event. */
KANZI_API struct KzsWindow* kzsWindowEventGetTarget(const struct KzsEvent* event);
/** Get the window width of a resize event. */
KANZI_API kzUint kzsWindowEventResizeGetWidth(const struct KzsEvent* event);
/** Get the window height of a resize event. */
KANZI_API kzUint kzsWindowEventResizeGetHeight(const struct KzsEvent* event);
/** Get the window orientation of a orientation change event. */
KANZI_API enum KzsWindowOrientation kzsWindowEventOrientationChangeGetOrientation(const struct KzsEvent* event);

/** Returns the translated key. */
KANZI_API enum KzsInputKey kzsInputNativeGetTranslatedKey(kzUint button);

/** Get set HUD event data from an event. */
KANZI_API const struct KzsDebugEventSetHUD* kzsEventGetSetHUDData(const struct KzsEvent* event);

/** Returns set HUD debug event parameter. */
KANZI_API kzInt kzsSetHUDDebugEventGetOnOff(const struct KzsDebugEventSetHUD* inputData);

#endif
