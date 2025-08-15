// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FORWARDING_ACTION_HPP
#define KZ_FORWARDING_ACTION_HPP

#include "action.hpp"

#include <kanzi/core.ui/binding/binding.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

class Domain;

class ForwardingAction;
typedef shared_ptr<ForwardingAction> ForwardingActionSharedPtr;


/** 
* A class that is able to read arguments from message and translates them to action arguments. 
* It is then possible for the action to decide what to do with the arguments. It is possible for example
* to utilize the action arguments to set a property of a node or to dispatch a message containing a value of
* the action argument.
*/
class KANZI_API ForwardingAction : public Action
{
public:
    KZ_METACLASS_BEGIN(ForwardingAction, Action, "Kanzi.ForwardingAction")
    KZ_METACLASS_END()

    static ForwardingActionSharedPtr create(Domain* domain, string_view name);

    /// Add binding from value to object node or message argument.
    /// \param sourceValue Source value.
    /// \param targetArgument Target argument property type for the forwarded value.
    /// \return The created binding object.
    BindingSharedPtr addValueBinding(const Variant& sourceValue, AbstractPropertyType targetArgument);

    /// Add binding from value to object node or message argument.
    /// \param sourceValue Source value.
    /// \param targetArgument Target argument property type for the forwarded value.
    /// \param targetField Target field of the argument property type.
    /// \return The created binding object.
    BindingSharedPtr addValueBinding(const Variant& sourceValue, AbstractPropertyType targetArgument, PropertyField targetField);

    /// Add binding from message argument to object node or message argument.
    /// \param sourceArgument Source message argument.
    /// \param targetArgument Target argument property type for the forwarded value.
    /// \return The created binding object.
    BindingSharedPtr addArgumentBinding(AbstractPropertyType sourceArgument, AbstractPropertyType targetArgument);

    /// Add binding from message argument to object node or message argument.
    /// \param sourceArgument Source message argument.
    /// \param targetArgument Target argument property type for the forwarded value.
    /// \param targetField Target field of the argument property type.
    /// \return The created binding object.
    BindingSharedPtr addArgumentBinding(AbstractPropertyType sourceArgument, PropertyField sourceField, AbstractPropertyType targetArgument, PropertyField targetField);

    /// Add binding from property to object node or message argument.
    /// \param sourceObjectPath Path to source object.
    /// \param sourcePropertyType Source property.
    /// \param targetArgument Target argument property type for the forwarded value.
    /// \return The created binding object.
    BindingSharedPtr addPropertyBinding(string_view sourceObjectPath, AbstractPropertyType sourcePropertyType, AbstractPropertyType targetArgument);

    /// Add binding from property to object node or message argument.
    /// \param sourceObjectPath Path to source object.
    /// \param sourcePropertyType Source property.
    /// \param targetArgument Target argument property type for the forwarded value.
    /// \param targetField Target field of the argument property type.
    /// \return The created binding object.
    BindingSharedPtr addPropertyBinding(string_view sourceObjectPath, AbstractPropertyType sourcePropertyType, PropertyField sourceField, AbstractPropertyType targetArgument, PropertyField targetField);

    typedef map<AbstractPropertyType, BindingSharedPtr> BindingContainer;
    typedef BindingContainer::const_iterator BindingConstIterator;

    BindingConstIterator beginBindings() const;
    BindingConstIterator endBindings() const;

    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;
    virtual void load(KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

protected:

    /** Create a set property action. */
    explicit ForwardingAction(Domain* domain, string_view name);

    /// Loads binding object from binary.
    /// \param inputStream The input stream.
    /// \param file The binary file.
    /// \return The binding object that was loaded.
    BindingSharedPtr loadBinding(KzcInputStream* inputStream, const KzuBinaryFileInfo* file);
    BindingSharedPtr loadBinding(KzbFile& kzbFile, KzbMemoryParser& parser);

    /// Adds binding object to action.
    /// \param argumentType Type of the argument. 
    /// \param binding Binding object to add.
    void addBinding(AbstractPropertyType argumentType, BindingSharedPtr binding);

    /// Removes binding object from action.
    /// \param argumentType Type of the argument to remove. 
    void removeBinding(AbstractPropertyType argumentType);

    /// Removes all binding objects from this action.
    void removeAllBindings();

    void onCopy(const ForwardingAction& other);

    Variant getArgument(AbstractPropertyType argumentType);

protected:

    /// Called when value binding is added.
    void setSource(BindingSharedPtr binding, const Variant& sourceValue);
    /// Called when argument binding is added.
    void setSource(BindingSharedPtr binding, AbstractPropertyType sourceArgument, PropertyField sourceField);
    /// Called when property binding is added.
    void setSource(BindingSharedPtr binding, string_view sourceObjectPath, AbstractPropertyType sourcePropertyType, PropertyField sourceField);
    /// Called when binding is added, does nothing by default but allows derived classes to set the binding target.
    virtual void setTarget(BindingSharedPtr, AbstractPropertyType targetArgument, PropertyField targetField);

private:
    BindingContainer m_bindings; ///< Binding rules.
};

}

#endif
