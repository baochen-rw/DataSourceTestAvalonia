// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_CALLBACK_VALIDATOR_H
#define KZU_CALLBACK_VALIDATOR_H


#include <kanzi/core.ui/property/variant.hpp>
#include <kanzi/core.ui/binding/binding_processor.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

/* Forward declarations. */
class Domain;
class CallbackBindingProcessor;

typedef shared_ptr<CallbackBindingProcessor> CallbackBindingProcessorSharedPtr;


/** Callback validator. */
class KANZI_API CallbackBindingProcessor : public BindingProcessor
{
public:
    typedef function<bool (Variant& value)> CallbackFunctionType;

public:
    explicit CallbackBindingProcessor(Domain* domain, CallbackFunctionType callback);
    virtual ~CallbackBindingProcessor();

public: // protected
    virtual bool onValidate(Variant& value) KZ_OVERRIDE;

    virtual BindingProcessorSharedPtr clone() const KZ_OVERRIDE;

public:
    CallbackFunctionType callback;  /**< The callback. */
};

}


#endif
