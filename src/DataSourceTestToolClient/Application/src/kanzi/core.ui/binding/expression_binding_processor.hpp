// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_EXPRESSION_VALIDATOR_H
#define KZU_EXPRESSION_VALIDATOR_H

#include "binding.hpp"
#include "binding_processor.hpp"
#include <kanzi/core.ui/property/variant.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


namespace kanzi
{

/* Forward declarations. */
class Domain;
class ExpressionBindingProcessor;
struct BindingExpressionOpCode;

/** Expression argument type. */
enum KzuExpressionValidatorArgumentType
{
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_SOURCE = 0,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_TARGET = 1,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_SOURCE_REGISTER_0 = 100,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_CONSTANT_REGISTER_0 = 200,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_TEMPORARY_REGISTER_0 = 300,
    KZU_EXPRESSION_VALIDATOR_ARGUMENT_TYPE_DATA_SOURCE_REGISTER_0 = 400
};


/** Expression operation. */
enum KzuExpressionValidatorOperation
{
    KZU_EXPRESSION_VALIDATOR_OPERATION_WRITE = 0,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ADD = 1,
    KZU_EXPRESSION_VALIDATOR_OPERATION_SUBTRACT = 2,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MULTIPLY = 3,
    KZU_EXPRESSION_VALIDATOR_OPERATION_DIVIDE = 4,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MODULO = 5,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ABS = 6,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MAX = 7,
    KZU_EXPRESSION_VALIDATOR_OPERATION_MIN = 8,
    KZU_EXPRESSION_VALIDATOR_OPERATION_CEIL = 9,
    KZU_EXPRESSION_VALIDATOR_OPERATION_FLOOR = 10,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ROUND = 11,
    KZU_EXPRESSION_VALIDATOR_OPERATION_POW = 12,
    KZU_EXPRESSION_VALIDATOR_OPERATION_SQRT = 13,
    KZU_EXPRESSION_VALIDATOR_OPERATION_STEP = 14,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_BOOL = 15,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_INT = 16,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_FLOAT = 17,
    KZU_EXPRESSION_VALIDATOR_OPERATION_TO_STRING = 18,
    KZU_EXPRESSION_VALIDATOR_OPERATION_REMAINDER = 19,
    KZU_EXPRESSION_VALIDATOR_OPERATION_CREATE_ROTATION = 20,
    KZU_EXPRESSION_VALIDATOR_OPERATION_CREATE_ROTATION_X = 21,
    KZU_EXPRESSION_VALIDATOR_OPERATION_CREATE_ROTATION_Y = 22,
    KZU_EXPRESSION_VALIDATOR_OPERATION_CREATE_ROTATION_Z = 23,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ROTATE = 24,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ROTATE_X = 25,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ROTATE_Y = 26,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ROTATE_Z = 27,
    KZU_EXPRESSION_VALIDATOR_OPERATION_EXTRACT_EULER_X = 28,
    KZU_EXPRESSION_VALIDATOR_OPERATION_EXTRACT_EULER_Y = 29,
    KZU_EXPRESSION_VALIDATOR_OPERATION_EXTRACT_EULER_Z = 30,
    KZU_EXPRESSION_VALIDATOR_OPERATION_POSITION_CONSTRAINT = 31,
    KZU_EXPRESSION_VALIDATOR_OPERATION_ORIENTATION_CONSTRAINT = 32,
    KZU_EXPRESSION_VALIDATOR_OPERATION_LOOK_AT_CONSTRAINT = 33,
    KZU_EXPRESSION_VALIDATOR_OPERATION_REVERSED_LOOK_AT_CONSTRAINT = 34,
    KZU_EXPRESSION_VALIDATOR_OPERATION_REVERSED_CYLINDRICAL_LOOK_AT_CONSTRAINT = 35
};


/// Expression function pointer type.
typedef bool (*BindingExpressionFunction)(BindingExpressionOpCode& expressionOpCode);


class ExpressionBindingProcessor;
typedef shared_ptr<ExpressionBindingProcessor> ExpressionBindingProcessorSharedPtr;

/// Expression validator.
class KANZI_API ExpressionBindingProcessor : public BindingProcessor
{
public:
#include "expression_binding_processor_properties.h"

    KZ_METACLASS_BEGIN(ExpressionBindingProcessor, BindingProcessor, "Kanzi.ExpressionBindingProcessor")
        KZ_METACLASS_PROPERTY_TYPE(Argument1Property)
        KZ_METACLASS_PROPERTY_TYPE(Argument1FieldProperty)
        KZ_METACLASS_PROPERTY_TYPE(Argument2Property)
        KZ_METACLASS_PROPERTY_TYPE(Argument2FieldProperty)
        KZ_METACLASS_PROPERTY_TYPE(Argument3Property)
        KZ_METACLASS_PROPERTY_TYPE(Argument3FieldProperty)
        KZ_METACLASS_PROPERTY_TYPE(OperationProperty)
        KZ_METACLASS_PROPERTY_TYPE(OutputFieldProperty)
        KZ_METACLASS_PROPERTY_TYPE(OutputProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static ExpressionBindingProcessorSharedPtr create(Domain* domain, string_view name);

    virtual ~ExpressionBindingProcessor();

protected:
    explicit ExpressionBindingProcessor(Domain* domain);

    virtual void onAttach() KZ_OVERRIDE;

    virtual bool onValidate(Variant& sourceValue) KZ_OVERRIDE;

    virtual BindingProcessorSharedPtr clone() const KZ_OVERRIDE;

public: // Should be protected.
    /// Target value.
    Variant targetValue;

    /// Register for first argument to validator function.
    const Variant* firstArgumentRegister;
    /// Register for second argument to validator function.
    const Variant* secondArgumentRegister;
    /// Register for third argument to validator function.
    const Variant* thirdArgumentRegister;
    /// Register for output argument of validator function.
    Variant* outputRegister;
    /// Cached first argument field.
    PropertyField firstArgumentField;
    /// Cached second argument field.
    PropertyField secondArgumentField;
    /// Cached third argument field.
    PropertyField thirdArgumentField;
    /// Cached output field.
    PropertyField outputField;

    /// Validator function pointer.
    BindingExpressionFunction validatorFunction;

    /// Does target value need to be read when evaluating.
    bool requiresTargetRead;
};


/// Expression binding operation.
///
/// When adding new expression operation to binding, create instance
/// of BindingExpressionOpCode, leave its fields to default values,
/// set fields of its Settings to appropriate values and add the
/// BindingExpressionOpCode instance to a binding.
struct KANZI_API BindingExpressionOpCode : public BindingOperation
{
    /// BindingOperation::attach() implementation.
    virtual void attach(Binding& binding) KZ_OVERRIDE;

    /// BindingOperation::detach() implementation.
    virtual void detach() KZ_OVERRIDE;

    /// BindingOperation::execute() implementation.
    virtual void execute() KZ_OVERRIDE;

    /// BindingOperation::clone() implementation.
    virtual BindingOperationSharedPtr clone() KZ_OVERRIDE;

    /// Settings contain information about expression binding operation, i.e.
    /// which operation should be executed, which arguments this operation
    /// should have, etc.
    ///
    ///Settings are used by operation after is it added to a binding.
    struct Settings
    {
        /// Constructor.
        explicit Settings();

        /// Id of expression operation.
        KzuExpressionValidatorOperation operation;

        /// First argument of the operation.
        KzuExpressionValidatorArgumentType argument1;
        /// Field of first argument.
        PropertyField argument1Field;

        /// Second argument of the operation.
        KzuExpressionValidatorArgumentType argument2;
        /// Field of second argument.
        PropertyField argument2Field;

        /// Third argument of the operation.
        KzuExpressionValidatorArgumentType argument3;
        /// Field of third argument.
        PropertyField argument3Field;

        /// Output where result of the operation should be written.
        unsigned int output;
        /// Field of output where result of the operation should be written.
        PropertyField outputField;
    };

    /// Constructor.
    explicit BindingExpressionOpCode() :
        operation(),
        firstArgumentRegister(),
        firstArgumentField(PropertyFieldWhole),
        secondArgumentRegister(),
        secondArgumentField(PropertyFieldWhole),
        thirdArgumentRegister(),
        thirdArgumentField(PropertyFieldWhole),
        outputRegister(),
        outputField(PropertyFieldWhole)
    {
    }

    /// Information about expression operation.
    Settings settings;

    /// Operation function pointer.
    BindingExpressionFunction operation;

    /// Register for first argument to operation function.
    const Variant* firstArgumentRegister;
    /// Cached first argument field.
    PropertyField firstArgumentField;

    /// Register for second argument to operation function.
    const Variant* secondArgumentRegister;
    /// Cached second argument field.
    PropertyField secondArgumentField;

    /// Register for third argument to operation function.
    const Variant* thirdArgumentRegister;
    /// Cached third argument field.
    PropertyField thirdArgumentField;

    /// Register for output argument of operation function.
    Variant* outputRegister;
    /// Cached output argument field.
    PropertyField outputField;
};


/** Get expression validator argument. */
const Variant* kzuExpressionValidatorGetArgument(Binding* rule, KzuExpressionValidatorArgumentType argumentType);
}


#endif
