/**
* \file
* Message dispatcher.
* Provides a system to exchange messages between different parts of an application.
* Messages can be used to notify of an event or request operations and data.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZU_MESSAGE_DISPATCHER_H
#define KZU_MESSAGE_DISPATCHER_H

#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/message/message_type.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#include <kanzi/core/cpp/memory.hpp>


/* Forward declarations. */
struct KzcMemoryManager;
struct KzuMessageType;
struct KzuTaskScheduler;

namespace kanzi
{

class InputManager;
class Node;
class MessageArguments;
class Scene;
}


/** Timer mode. */
enum KzuTimerMessageMode
{
    KZU_TIMER_MESSAGE_MODE_ONCE,        /**< Timer will be called once after the specified interval elapses. Unsubscribe still needed. */
    KZU_TIMER_MESSAGE_MODE_REPEAT,      /**< Timer will be called repeatedly at specified intervals. */
                                        /**< Timers in this mode should be disabled when the application update cycle is called infrequently, */
                                        /**< for example in low power situations, as this generates excessive number of messages. */
    KZU_TIMER_MESSAGE_MODE_REPEAT_BATCH /**< Same as KZU_TIMER_MESSAGE_MODE_REPEAT, but the system dispatches only the last message when a timer has several pending messages. */
};

/**
 * \struct KzuMessageDispatcher
 * Message dispatcher object.
 */
struct KzuMessageDispatcher;


/** Message callback prototype. */
typedef kzsError (*KzuMessageHandlerFunction)(kanzi::MessageArguments* message, void* userData);

/** Application message callback prototype. */
typedef kzsError (*KzuMessageDispatchFunction)(const kanzi::MessageArguments* message, void* userData);


/** Create a message dispatcher. */
KANZI_API kzsError kzuMessageDispatcherCreate(const struct KzcMemoryManager* memoryManager, struct KzuMessageDispatcher** out_messageDispatcher);
/** Destroy a message dispatcher. */
KANZI_API kzsError kzuMessageDispatcherDelete(struct KzuMessageDispatcher* messageDispatcher);


/** Adds a message handler.
 * \param messageDispatcher The message dispatcher to use.
 * \param subscriptionSiteNode Object node that is associated with the message subscription created by this function.
 * \param messageType Type of the message to match.
 * \param messageSource Source of the message (as returned by kzuMessageGetSource) to match.
 * \param handlerFunction Function to call when a matching message appears.
 * \param userData User data pointer passed to handlerFunction.
 */
KANZI_API kzsError kzuMessageDispatcherAddHandler(const struct KzuMessageDispatcher* messageDispatcher, kanzi::Node* subscriptionSiteNode,
                                                  const struct KzuMessageType* messageType, kanzi::Node* messageSource,
                                                  KzuMessageHandlerFunction handlerFunction, void* userData);

/** Adds a message handler for tunneling phase. */
KANZI_API kzsError kzuMessageDispatcherAddTunnellingHandler(const struct KzuMessageDispatcher* messageDispatcher, kanzi::Node* subscriptionSiteNode,
                                                            const struct KzuMessageType* messageType, kanzi::Node* messageSource,
                                                            KzuMessageHandlerFunction handlerFunction, void* userData);

/** Checks if a handler subscription is valid. */
KANZI_API kzsError kzuMessageDispatcherIsHandlerSubscriptionValid(const struct KzuMessageDispatcher* messageDispatcher, const kanzi::Node* subscriptionSiteNode,
                                                                  const struct KzuMessageType* messageType, KzuMessageHandlerFunction handlerFunction, const void* userData, kzBool* out_valid);

/** Removes a message handler. */
KANZI_API kzsError kzuMessageDispatcherRemoveHandler(const struct KzuMessageDispatcher* messageDispatcher, const kanzi::Node* subscriptionSiteNode,
                                                     const struct KzuMessageType* messageType, KzuMessageHandlerFunction handlerFunction, const void* userData);

/** Dispatches a message. The associated handlers are called immediately. */
KANZI_API kzsError kzuMessageDispatcherDispatchMessage(struct KzuMessageDispatcher* messageDispatcher, kanzi::MessageArguments* message, kanzi::Node* source);

/** Dispatches queued messages. Generally should be called once per frame. */
KANZI_API kzsError kzuMessageDispatcherDispatchQueuedMessages(struct KzuMessageDispatcher* messageDispatcher, kzUint elapsedTime = 0);

/** Notifies the message dispatcher that an object node is being destroyed.
 *  This will cancel all messages where the specified node is the source of the message or the current site during routing. */
KANZI_API kzsError kzuMessageDispatcherNotifyObjectDeleted(const struct KzuMessageDispatcher* messageDispatcher, const kanzi::Node* objectNode);

/** Registers a timer handler.
 * \param messageDispatcher The message dispatcher to use.
 * \param interval timeout in milliseconds in case of a one-shot timer, and the interval in case of a repeating timer.
 * \param mode KZU_TIMER_MESSAGE_MODE_ONCE, KZU_TIMER_MESSAGE_MODE_REPEAT or KZU_TIMER_MESSAGE_MODE_REPEAT_BATCH. KZU_TIMER_MESSAGE_MODE_REPEAT_BATCH is
 *             recommended for a repeating timer because it calls handlerFunction only once when the interval has been exceeded several times over.
 * \param handlerFunction The function to call when the timer expires.
 * \param userData User data pointer passed to handlerFunction.
 */
KANZI_API kzsError kzuMessageDispatcherAddTimerHandler(KzuMessageDispatcher* messageDispatcher, kzUint interval, enum KzuTimerMessageMode mode,
                                                       KzuMessageHandlerFunction handlerFunction, void* userData);
/** Unregisters a timer handler. */
KANZI_API kzsError kzuMessageDispatcherRemoveTimerHandler(KzuMessageDispatcher* messageDispatcher, KzuMessageHandlerFunction handlerFunction, const void* userData);
/// Gets the proposed sleep time from message dispatcher.
/// This equals the smallest interval when a timer would be next executed.
/// If no timers are present, returns an empty optional.
/// \param messageDispatcher Message dispatcher to query.
/// \return Time until next timer handler should trigger (always nonnegative). Empty optional if no timer handlers present.
KANZI_API kanzi::optional<kanzi::chrono::milliseconds> kzuMessageDispatcherGetProposedSleepTime(const KzuMessageDispatcher* messageDispatcher);

/** Returns current time of message dispatcher in milliseconds. */
KANZI_API kzUint kzuMessageDispatcherGetTime(const struct KzuMessageDispatcher* messageDispatcher);

/** Return number of timer subscriptions of message dispatcher */
KANZI_API kzUint kzuMessageDispatcherGetTimerSubscriptionCount(const struct KzuMessageDispatcher* messageDispatcher);


namespace kanzi
{

struct TimerMessageArguments
{
    chrono::milliseconds timeStamp;
    chrono::milliseconds delta;
};

typedef function<void(const TimerMessageArguments&)> TimerFunction;
typedef shared_ptr<void> TimerSubscriptionToken;

KANZI_API TimerSubscriptionToken addTimerHandler(KzuMessageDispatcher* messageDispatcher, chrono::milliseconds interval, KzuTimerMessageMode mode, TimerFunction callback);
KANZI_API void removeTimerHandler(KzuMessageDispatcher* messageDispatcher, TimerSubscriptionToken token);


class KANZI_API MessageDispatcherProperties
{
public:

    /// \name Properties
    /// \{
#include "kzu_message_dispatcher_properties.h"
    /// \}

    class KANZI_API WriteLogMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(WriteLogMessageArguments, MessageArguments, "Kanzi.WriteLogMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(WriteLogMessageProperty)
        KZ_METACLASS_END()

        string getLogMessage() const { return getArgument(WriteLogMessageProperty); }
        void setLogMessage(string value) { setArgument(WriteLogMessageProperty, value); }
    };

    class KANZI_API TimerMessageArguments: public MessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(TimerMessageArguments, MessageArguments, "Kanzi.TimerMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(TimerBatchCountProperty)
            KZ_METACLASS_PROPERTY_TYPE(TimerValueProperty)
        KZ_METACLASS_END()

        int getBatchCount() const { return getArgument(TimerBatchCountProperty); }
        void setBatchCount(int value) { setArgument(TimerBatchCountProperty, value); }

        int getTimerValue() const { return getArgument(TimerValueProperty); }
        void setTimerValue(int value) { setArgument(TimerValueProperty, value); }
    };

    static MessageType<WriteLogMessageArguments> WriteLogMessage;
    static MessageType<TimerMessageArguments> TimerMessage;

    KZ_STATIC_METACLASS_BEGIN(MessageDispatcherProperties, "Kanzi.MessageDispatcherProperties")
        KZ_METACLASS_MESSAGE_TYPE(WriteLogMessage)
        KZ_METACLASS_MESSAGE_TYPE(TimerMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }
};

}

#endif
