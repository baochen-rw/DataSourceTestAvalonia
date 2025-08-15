// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_BINDING_VALIDATOR_H
#define KZU_BINDING_VALIDATOR_H


#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/metadata/metaclass.hpp>


/* Forward declarations. */
struct KzuBinaryFileInfo;

namespace kanzi
{

class Binding;
struct Variant;
class Domain;
class BindingProcessor;

typedef shared_ptr<BindingProcessor> BindingProcessorSharedPtr;

/** Binding validator. */
class KANZI_API BindingProcessor : public Object
{
public:

    KZ_ABSTRACT_METACLASS_BEGIN(BindingProcessor, Object, "Kanzi.BindingProcessor")
    KZ_METACLASS_END()

    /** Attach binding processor. */
    void attach(Binding* rule);
    /** Detach binding processor. */
    void detach();
    /**
    * Reattach a binding validator to the rule it already was in.
    * This must be done if the binding validator properties were changed. The properties are cached upon attach.
    */
    void reattach();

    /** Validates binding processor. */
    bool validate(Variant& value);

    /** Copy a validator. */
    BindingProcessorSharedPtr copy();

    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

protected:

    explicit BindingProcessor(Domain* domain);

    /** Base attach implementation. */
    virtual void onAttach();
    /** Detach function for binding validators. */
    virtual void onDetach();

    /** Validate function. */
    virtual bool onValidate(Variant& value) = 0;

    virtual BindingProcessorSharedPtr clone() const = 0;

    virtual void onCopy(BindingProcessor const& other);

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        // TODO provide info
        return PropertyTypeEditorInfoSharedPtr();
    }

public:
    Binding* m_rule; /**< Binding rule. */
};


/** Loads a binding validator from stream. */
BindingProcessorSharedPtr loadBindingValidator(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file);

}


#endif
