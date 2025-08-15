// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_EXPRESSION_CONDITION_H
#define KZU_EXPRESSION_CONDITION_H


#include "condition.hpp"

#include <kanzi/core.ui/binding/binding.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


namespace kanzi
{

class Binding;
struct Variant;
class Domain;
class ExpressionCondition;

typedef shared_ptr<ExpressionCondition> ExpressionConditionSharedPtr;

/// Use trigger conditions to set which conditions must be met for a Trigger to set off. For example, you can define
/// conditions to set off a trigger when the user navigates to a specific Page node, enable the user to click a button
/// only when that button is visible, or enable the user to scroll a Scroll View node only when a specific Page node is
/// active.
class KANZI_API ExpressionCondition : public Condition
{
public:

    /// Trigger condition operand position.
    enum Operand
    {
        /// Left-hand side operand.
        OperandLHS,
        /// Right-hand side operand.
        OperandRHS
    };

    /// Trigger condition operation.
    enum Operation
    {
        /// Invalid comparison.
        OperationInvalid = 0,
        /// Equality comparison.
        OperationEqual = 1,
        /// Inequality comparison.
        OperationNotEqual = 2,
        /// Less than comparison.
        OperationLess = 3,
        /// Greater than comparison.
        OperationGreater = 4,
        /// Less than or equal comparison.
        OperationLessOrEqual = 5,
        /// Greater than or equal comparison.
        OperationGreaterOrEqual = 6
    };

    KZ_METACLASS_BEGIN(ExpressionCondition, Condition, "Kanzi.ExpressionCondition")
    KZ_METACLASS_END()

    static ExpressionConditionSharedPtr create(Domain* domain, string_view name);

    /// Sets the comparisons operation for the condition. Not all property types support all operations. If the operation is not supported, the condition evaluates to KZ_FALSE.
    void setOperation(Operation operation);

    /// Sets an operand in the comparison to be read from a fixed value.
    kzsError setOperandValue(Operand operand, const Variant& value);

    /// Sets an operand in the comparison to be read from the forwarded message from the trigger.
    kzsError setOperandMessageArgument(Operand operand, AbstractPropertyType messageArgument, PropertyField argumentField);

    /// Sets an operand in the comparison to be read from an objects property.
    kzsError setOperandProperty(Operand operand, kzString objectPath, AbstractPropertyType propertyType, PropertyField propertyField);

    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;
    virtual void load(KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

protected:

    /// Creates a trigger condition that you can attach to a Trigger.
    ///
    /// The trigger condition compares two operands using a specified comparison #Operation.
    /// To use the trigger condition, you must set both the two operands and the operation.
    ///
    /// To set an operand to:
    /// - Fixed value, use setOperandValue().
    /// - Message argument from the message that the trigger forwards to the condition, use setOperandMessageArgument().
    /// - Property value of an object that you specify using a relative path to the trigger object, use setOperandProperty().
    ///
    /// To set the comparison operation, use setOperation().
    ///
    /// \see Trigger::addCondition
    explicit ExpressionCondition(Domain* domain);

    virtual bool onCheck() KZ_OVERRIDE;

    virtual ConditionSharedPtr clone() const KZ_OVERRIDE;
    void onCopy(ExpressionCondition const& other);

private:

    BindingSharedPtr m_lhsBindingRule; /**< Binding for fetching and storing the lhs operand. Not attached to any object. */
    BindingSharedPtr m_rhsBindingRule; /**< Binding for fetching and storing the rhs operand. Not attached to any object. */
    Operation m_operation; /**< Comparison operation. */
};

}


#endif
