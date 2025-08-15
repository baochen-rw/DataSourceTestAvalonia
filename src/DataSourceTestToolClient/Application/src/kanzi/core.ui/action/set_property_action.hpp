// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_SET_PROPERTY_ACTION_H
#define KZU_SET_PROPERTY_ACTION_H

#include "forwarding_action.hpp"

#include <kanzi/core.ui/binding/binding.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

struct Variant;
class Domain;

class SetPropertyAction;
typedef shared_ptr<SetPropertyAction> SetPropertyActionSharedPtr;


/** Set property action. */
class KANZI_API SetPropertyAction : public ForwardingAction
{
public:

    /// \name Properties
    /// \{
#include "set_property_action_properties.h"
    /// \}

    /** Set a value as source. */
    void setSourceValue(const Variant& sourceValue);
    /** Set a message argument as patch message action. */
    void setSourceArgument(AbstractPropertyType sourceArgument, PropertyField sourceField);
    /** Set an object node property as source. */
    void setSourceProperty(string_view sourceObjectPath, AbstractPropertyType sourcePropertyType, PropertyField sourceField);
    /** Set target. */
    void setTarget(string_view targetObjectPath, AbstractPropertyType targetPropertyType, PropertyField targetField);

    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;
    virtual void load(KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

    KZ_METACLASS_BEGIN(SetPropertyAction, ForwardingAction, "Kanzi.SetPropertyAction")
        KZ_METACLASS_PROPERTY_TYPE(TargetObjectPathProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static SetPropertyActionSharedPtr create(Domain* domain, string_view name);

protected:

    /** Create a set property action. */
    explicit SetPropertyAction(Domain* domain, string_view name);

    /** Invoke set property action. */
    virtual void onInvoke() KZ_OVERRIDE;
    /** Prepare for delayed invoke of set property action. */
    virtual void onPrepareDelayedInvoke() KZ_OVERRIDE;
    /** Implementation of delayed invoke of set property action. */
    virtual void onDelayedInvoke() KZ_OVERRIDE;

    virtual ActionSharedPtr clone() const KZ_OVERRIDE;

    void onCopy(const SetPropertyAction& other);

    virtual void setTarget(BindingSharedPtr, AbstractPropertyType targetArgument, PropertyField targetField) KZ_OVERRIDE;

private:
    BindingSharedPtr bindingRule; /**< Binding rule. */
};

}

#endif
