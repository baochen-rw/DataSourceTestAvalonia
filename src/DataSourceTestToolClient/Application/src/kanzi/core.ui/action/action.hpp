// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ACTION_HPP
#define KZ_ACTION_HPP

#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/string.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


struct KzcInputStream;
struct KzuBinaryFileInfo;

namespace kanzi
{

class Trigger;
class Domain;
class MessageArguments;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;


/** Action binding type. */
enum ActionArgumentType
{
    /// Value action binding type.
    ActionArgumentTypeValue            = 0,

    /// Argument action binding type.
    ActionArgumentTypeMessageArgument  = 1,

    /// Object property action binding type.
    ActionArgumentTypeObjectProperty   = 2,

    /// Value reference binding type.
    ActionArgumentTypeValueReference = 3
};


class Action;
typedef shared_ptr<Action> ActionSharedPtr;

/// Action is the base class for objects that execute something when the owning Trigger is activated.
class KANZI_API Action : public Object, public enable_shared_from_this<Action>
{
public:

    KZ_ABSTRACT_METACLASS_BEGIN(Action, Object, "Kanzi.Action")
        KZ_METACLASS_PROPERTY_TYPE(DelayProperty)
    KZ_METACLASS_END()

    string getName() const;

    /// Attaches the action to a trigger.
    void attach(Trigger* trigger);
    /// Detaches the action.
    void detach();
    /// Invokes the action.
    void invoke();

    /// Create a copy of the action.
    ActionSharedPtr copy() const;

    /// Returns the trigger the action is attached to.
    Trigger* getTrigger() const;

    /// \name Properties
    /// \{
#include "action_properties.h"
    /// \}

    chrono::milliseconds getDelay() const { return chrono::milliseconds(getProperty(DelayProperty)); }
    void setDelay(chrono::milliseconds delay) { setProperty(DelayProperty, static_cast<int>(delay.count())); }

    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file);
    virtual void load(KzbFile& kzbFile, KzbMemoryParser& parser);

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static ActionSharedPtr loadAction(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file);
    static ActionSharedPtr loadAction(Domain* domain, KzbFile& kzbFile, KzbMemoryParser& parser);

protected:

    explicit Action(Domain* domain, string_view name);

    /// Callback called during attach.
    virtual void onAttach();
    /// Callback called during detach.
    virtual void onDetach();
    /// Callback called during invoke.
    virtual void onInvoke();
    /// Callback called before delayed invoke.
    virtual void onPrepareDelayedInvoke();
    /// Callback called during delayed invoke.
    virtual void onDelayedInvoke();
    /// Callback called after delayed invoke.
    virtual void onUnprepareDelayedInvoke();

    virtual ActionSharedPtr clone() const = 0;

    void onCopy(const Action& other);

private:

    /// Delayed invocations handler callback.
    static kzsError delayHandlerCallback(MessageArguments* message, void* userData);

    /// Handles delayed invocations.
    void delayHandler(MessageArguments* message);

    /// Removes the delay handler subscription and unprepares the action if necessary.
    void unprepare();

    /// The name of the action.
    string m_name;
    /// Trigger the action is attached to.
    Trigger* m_trigger;
    /// Flag indicating whether the delayed action is being invoked.
    bool m_isInvokingDelayed;
};

}

#endif
