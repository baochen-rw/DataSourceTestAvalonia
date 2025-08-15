// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TRIGGER_TEMPLATE_HPP
#define KZ_TRIGGER_TEMPLATE_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core.ui/template/node_component_template.hpp>

#include <kanzi/core/legacy/util/io/kzc_input_stream.hpp>
#include <kanzi/core.ui/kzb/kzu_binary_directory.h>

namespace kanzi
{

// Forward declarations.
class Action;
class Condition;
class KzbMemoryParser;
class NodeComponent;
class Trigger;
class TriggerTemplate;
typedef shared_ptr<Action> ActionSharedPtr;
typedef shared_ptr<Condition> ConditionSharedPtr;

// Trigger template shared pointer types.
typedef shared_ptr<TriggerTemplate> TriggerTemplateSharedPtr;
typedef shared_ptr<TriggerTemplate const> TriggerTemplateConstSharedPtr;

/// TriggerTemplate is the base class for trigger templates.
class KANZI_API TriggerTemplate : public NodeComponentTemplate
{
public:

    /// Creates instance of trigger template.
    /// \param domain Domain.
    /// \param name Name to assign to every instanced trigger.
    /// \param metaclass Metaclass to create trigger from.
    /// \return Trigger template.
    static TriggerTemplateSharedPtr create(Domain* domain, string_view name, const Metaclass* metaclass);

    /// Destructor.
    virtual ~TriggerTemplate();

    /// NodeComponentTemplate::load() implementation.
    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// NodeComponentTemplate::load() implementation.
    virtual void load(KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param name Name to use for instantiated triggers.
    /// \param triggerMetaclass Metaclass to create trigger component from.
    explicit TriggerTemplate(Domain* domain, string_view name, const Metaclass* triggerMetaclass);

    /// NodeComponentTemplate::onInstantiate() implementation.
    virtual void onInstantiate(NodeComponent& nodeComponent) KZ_OVERRIDE;

private:

    typedef vector<ActionSharedPtr> ActionContainer;
    typedef ActionContainer::const_iterator ActionIterator;

    typedef vector<ConditionSharedPtr> ConditionContainer;
    typedef ConditionContainer::const_iterator ConditionIterator;

    /// Actions to copy to instantiated trigger.
    ActionContainer m_actions;

    /// Conditions to copy to instantiated trigger.
    ConditionContainer m_conditions;
};

}

#endif
