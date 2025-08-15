// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_PROPERTY_CHANGED_TRIGGER_H
#define KZU_PROPERTY_CHANGED_TRIGGER_H

#include "trigger.hpp"
#include <kanzi/core.ui/binding/binding.hpp>

namespace kanzi
{

struct Variant;
class OnPropertyChangedTrigger;
typedef shared_ptr<OnPropertyChangedTrigger> OnPropertyChangedTriggerSharedPtr;

/** Property change Trigger. */
class KANZI_API OnPropertyChangedTrigger : public Trigger
{
public:

#include "on_property_changed_trigger_properties.h"

    KZ_METACLASS_BEGIN(OnPropertyChangedTrigger, Trigger, "Kanzi.OnPropertyChangedTrigger")
        KZ_METACLASS_PROPERTY_TYPE(SourceNodeProperty)
        KZ_METACLASS_PROPERTY_TYPE(SourcePropertyTypeProperty)
    KZ_METACLASS_END()

    static OnPropertyChangedTriggerSharedPtr create(Domain* domain, string_view name)
    {
        return make_polymorphic_shared_ptr<Trigger>(new OnPropertyChangedTrigger(domain, name));
    }

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

protected:

    bool bindingHandler(Variant&);

    explicit OnPropertyChangedTrigger(Domain* domain, string_view name);
    
    /// NodeComponent::attachOverride() implementation.
    virtual void attachOverride() KZ_OVERRIDE;
    /// NodeComponent::detachOverride() implementation.
    virtual void detachOverride() KZ_OVERRIDE;

private:

    BindingSharedPtr m_binding;
};

}

#endif
