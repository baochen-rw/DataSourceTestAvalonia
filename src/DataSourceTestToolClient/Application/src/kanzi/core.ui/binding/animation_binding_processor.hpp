// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_ANIMATION_VALIDATOR_H
#define KZU_ANIMATION_VALIDATOR_H


#include "binding.hpp"
#include "binding_processor.hpp"
#include "expression_binding_processor.hpp"

#include <kanzi/core.ui/animation/value_animation.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


namespace kanzi
{

class AnimationBindingProcessor;
typedef shared_ptr<AnimationBindingProcessor> AnimationBindingProcessorSharedPtr;


/** Animation validator. */
class KANZI_API AnimationBindingProcessor : public BindingProcessor
{
public:
#include "animation_binding_processor_properties.h"

    KZ_METACLASS_BEGIN(AnimationBindingProcessor, BindingProcessor, "Kanzi.AnimationBindingProcessor")
        KZ_METACLASS_PROPERTY_TYPE(AnimationProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    virtual ~AnimationBindingProcessor();

    static AnimationBindingProcessorSharedPtr create(Domain* domain, string_view name);

protected:
    explicit AnimationBindingProcessor(Domain* domain);

    virtual void onAttach() KZ_OVERRIDE;
    virtual void onDetach() KZ_OVERRIDE;

    virtual bool onValidate(Variant& value) KZ_OVERRIDE;

    virtual BindingProcessorSharedPtr clone() const KZ_OVERRIDE;

public:
    /// Value animation.
    FloatAnimationSharedPtr m_valueAnimation;

    const Variant* m_sourceRegister; /**< Register for source argument to validator function. */
    Variant* m_outputRegister;       /**< Register for output argument of validator function. */
};


/// Animation binding operation.
///
/// When adding new animation operation to binding, create instance
/// of BindingAnimationOpCode, leave its fields to default values,
/// set fields of its Settings to appropriate values and add the
/// BindingAnimationOpCode instance to a binding.
struct KANZI_API BindingAnimationOpCode : BindingOperation
{
    /// BindingOperation::attach() implementation.
    virtual void attach(Binding& binding) KZ_OVERRIDE;

    /// BindingOperation::detach() implementation.
    virtual void detach() KZ_OVERRIDE;

    /// BindingOperation::execute() implementation.
    virtual void execute() KZ_OVERRIDE;

    /// BindingOperation::clone() implementation.
    virtual BindingOperationSharedPtr clone() KZ_OVERRIDE;

    /// Settings contain information about animation binding operation, i.e.
    /// which animation should be applied, where result is written, etc.
    ///
    ///Settings are used by operation after is it added to a binding.
    struct Settings
    {
        /// Constructor.
        explicit Settings();

        /// Animation which should be applied by the operation.
        ResourceID animationId;

        /// Output where result of the operation should be written.
        KzuExpressionValidatorArgumentType argument;
        /// Field of output where result of the operation should be written.
        unsigned int output;
    };

    /// Constructor.
    explicit BindingAnimationOpCode():
        argument(),
        output()
    {
    }

    /// Information about animation operation.
    Settings settings;

    /// Value animation which is applied by operation.
    FloatAnimationSharedPtr animation;

    /// Register for output argument of operation function.
    const Variant* argument;
    /// Cached output argument field.
    Variant* output;
};
}

#endif
