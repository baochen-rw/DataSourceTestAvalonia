// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RANGE_CONCEPT_HPP
#define KZ_RANGE_CONCEPT_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/node/node.hpp>


namespace kanzi
{

/// RangeConcept represents a number range with an optional step.
class KANZI_UI_API RangeConcept
{
public:
    /// \name Properties
    /// \{
#include "range_properties.h"
    /// \}

    class KANZI_UI_API CommonMessageArguments : public MessageArguments
    {
    public:
        /// Value property.
        ///
        /// The default value is 0.0f.
        static PropertyType<float> ValueProperty;

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(CommonMessageArguments, MessageArguments, "Kanzi.RangeConcept.CommonMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(ValueProperty)
        KZ_METACLASS_END()

        float getValue() const
        {
            return getArgument(ValueProperty);
        }

        void setValue(float value)
        {
            setArgument(ValueProperty, value);
        }

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    class KANZI_UI_API ValueChangeStartedMessageArguments : public CommonMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ValueChangeStartedMessageArguments, CommonMessageArguments, "Kanzi.RangeConcept.ValueChangeStartedMessageArguments")
            KZ_METACLASS_MIXIN(CommonMessageArguments)
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ValueChangeFinishedMessageArguments : public CommonMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ValueChangeFinishedMessageArguments, CommonMessageArguments, "Kanzi.RangeConcept.ValueChangeFinishedMessageArguments")
            KZ_METACLASS_MIXIN(CommonMessageArguments)
        KZ_METACLASS_END()
    };

    class KANZI_UI_API ValueChangedMessageArguments : public CommonMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(ValueChangedMessageArguments, CommonMessageArguments, "Kanzi.RangeConcept.ValueChangedMessageArguments")
            KZ_METACLASS_MIXIN(CommonMessageArguments)
        KZ_METACLASS_END()
    };

    static MessageType<ValueChangeStartedMessageArguments> ValueChangeStartedMessage;
    static MessageType<ValueChangeFinishedMessageArguments> ValueChangeFinishedMessage;
    static MessageType<ValueChangedMessageArguments> ValueChangedMessage;

    KZ_MIXIN_METACLASS_BEGIN(RangeConcept, "Kanzi.RangeConcept")
        KZ_METACLASS_PROPERTY_TYPE(MinimumValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(MaximumValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(StepProperty)
        KZ_METACLASS_PROPERTY_TYPE(ValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(NormalizedValueProperty)
        KZ_METACLASS_PROPERTY_TYPE(IsValueChangingProperty)

        KZ_METACLASS_MESSAGE_TYPE(ValueChangeStartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ValueChangeFinishedMessage)
        KZ_METACLASS_MESSAGE_TYPE(ValueChangedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

template <class TBaseClass, class TDerivedClass>
class KANZI_UI_TEMPLATE_API RangeConceptImpl : public TBaseClass, public RangeConcept
{
public:
    KZ_TEMPLATE_METACLASS_BEGIN(RangeConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(RangeConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    template <class MessageT>
    void sendRangeMessage(const MessageT& messageType);

    explicit RangeConceptImpl(Domain* domain, string_view name);

    /// Gets the value of #RangeMinimumProperty.
    /// \see setRangeMinimum()
    float getMinimumValue() const;

    /// Sets the value of #RangeMinimumProperty.
    /// \see getRangeMinimum()
    void setMinimumValue(float value);

    /// Gets the value of #RangeMaximumProperty.
    /// \see setRangeMaximum()
    float getMaximumValue() const;

    /// Sets the value of #RangeMaximumProperty.
    /// \see getRangeMaximum()
    void setMaximumValue(float value);

    /// Gets the value of #RangeStepProperty.
    /// \see setRangeStep()
    float getStep() const;

    /// Sets the value of #RangeStepProperty.
    /// \see getRangeStep()
    void setStep(float value);

    /// Gets the value of #RangeValueProperty.
    /// \see setRangeValue()
    float getValue() const;

    /// Sets the value of #RangeValueProperty.
    /// \see getRangeValue()
    void setValue(float value);

    /// Gets the value of #NormalizedValueProperty.
    /// \see setNormalizedValue()
    float getNormalizedValue() const;

    /// Sets the value of #NormalizedValueProperty.
    /// \see getNormalizedValue()
    void setNormalizedValue(float value);

    /// Gets the value of #ValueChangingProperty.
    bool isValueChanging() const;

    /// Increases the value by amount of #StepProperty.
    /// \see goToPreviousValue(), goToMinimumValue(), goToMaximumValue()
    void goToNextValue();

    /// Decreases the value by amount of #StepProperty.
    /// \see goToNextValue(), goToMinimumValue(), goToMaximumValue()
    void goToPreviousValue();

    /// Sets the value to #MinimumValue.
    /// \see goToMaximumValue(), goToPreviousValue(), goToNextValue()
    void goToMinimumValue();

    /// Sets the value to #MaximumValue.
    /// \see goToMinimumValue(), goToPreviousValue(), goToNextValue()
    void goToMaximumValue();

protected:
    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline TDerivedClass* getThisObject()
    {
        return static_cast<TDerivedClass*>(this);
    }

    /// Internal accessor for the Curiously Recurring Template Pattern.
    inline const TDerivedClass* getThisObject() const
    {
        return static_cast<const TDerivedClass*>(this);
    }

    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

private:
    // Updates the value and clamps it between #MinimumValue and #MaximumValue.
    void updateValue(float value);

    bool m_insideRangeValueCheck;
    bool m_insideNormalizedValueCheck;
};
}

#endif
