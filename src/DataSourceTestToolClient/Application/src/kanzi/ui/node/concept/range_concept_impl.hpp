// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RANGE_CONCEPT_IMPL_HPP
#define KZ_RANGE_CONCEPT_IMPL_HPP

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/ui/node/concept/range.hpp>

namespace kanzi
{

template <class TBaseClass, class TDerivedClass>
template <class MessageT>
void RangeConceptImpl<TBaseClass, TDerivedClass>::sendRangeMessage(const MessageT& messageType)
{
    typename MessageT::ArgumentsType arguments;
    arguments.setValue(getValue());
    getThisObject()->dispatchMessage(messageType, arguments);
}

template <class TBaseClass, class TDerivedClass>
RangeConceptImpl<TBaseClass, TDerivedClass>::RangeConceptImpl(Domain* domain, string_view name) :
    TBaseClass(domain, name),
    m_insideRangeValueCheck(false),
    m_insideNormalizedValueCheck(false)
{
}

template <class TBaseClass, class TDerivedClass>
float RangeConceptImpl<TBaseClass, TDerivedClass>::getMinimumValue() const
{
    return getThisObject()->getProperty(MinimumValueProperty);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::setMinimumValue(float value)
{
    getThisObject()->setProperty(MinimumValueProperty, value);
}

template <class TBaseClass, class TDerivedClass>
float RangeConceptImpl<TBaseClass, TDerivedClass>::getMaximumValue() const
{
    return getThisObject()->getProperty(MaximumValueProperty);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::setMaximumValue(float value)
{
    getThisObject()->setProperty(MaximumValueProperty, value);
}

template <class TBaseClass, class TDerivedClass>
float RangeConceptImpl<TBaseClass, TDerivedClass>::getStep() const
{
    return getThisObject()->getProperty(StepProperty);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::setStep(float value)
{
    getThisObject()->setProperty(StepProperty, value);
}

template <class TBaseClass, class TDerivedClass>
float RangeConceptImpl<TBaseClass, TDerivedClass>::getValue() const
{
    return getThisObject()->getProperty(ValueProperty);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::setValue(float value)
{
    getThisObject()->setProperty(ValueProperty, value);
}

template <class TBaseClass, class TDerivedClass>
float RangeConceptImpl<TBaseClass, TDerivedClass>::getNormalizedValue() const
{
    return getThisObject()->getProperty(NormalizedValueProperty);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::setNormalizedValue(float value)
{
    getThisObject()->setProperty(NormalizedValueProperty, value);
}

template <class TBaseClass, class TDerivedClass>
bool RangeConceptImpl<TBaseClass, TDerivedClass>::isValueChanging() const
{
    return getThisObject()->getProperty(IsValueChangingProperty);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::updateValue(float newValue)
{
    const float minimum = getMinimumValue();
    const float maximum = getMaximumValue();
    if (minimum != maximum)
    {
        newValue = clamp(newValue, minimum, maximum);
    }

    if (newValue == getValue())
    {
        return;
    }

    setValue(newValue);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::goToNextValue()
{
    const float step = getStep();
    if (step == 0.0f)
    {
        return;
    }

    updateValue(getValue() + step);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::goToPreviousValue()
{
    const float step = getStep();
    if (step == 0.0f)
    {
        return;
    }

    updateValue(getValue() - step);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::goToMinimumValue()
{
    const float minimum = getMinimumValue();
    const float maximum = getMaximumValue();

    if (minimum == maximum)
    {
        return;
    }

    setValue(minimum);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::goToMaximumValue()
{
    const float minimum = getMinimumValue();
    const float maximum = getMaximumValue();

    if (minimum == maximum)
    {
        return;
    }

    setValue(maximum);
}

template <class TBaseClass, class TDerivedClass>
void RangeConceptImpl<TBaseClass, TDerivedClass>::onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason)
{
    TBaseClass::onNodePropertyChanged(propertyType, reason);

    if (propertyType == ValueProperty)
    {
        sendRangeMessage(RangeConcept::ValueChangedMessage);
    }

    if (!m_insideRangeValueCheck && propertyType == ValueProperty)
    {
        m_insideRangeValueCheck = true;
        float value = getValue();
        float minimum = getMinimumValue();
        float maximum = getMaximumValue();

        if (value < minimum)
        {
            setValue(minimum);
        }
        else if (value > maximum)
        {
            setValue(maximum);
        }

        float step = getStep();
        if (std::abs(step) > 0.0f)
        {
            int n = static_cast<int>(value / step);
            float product = n * step;
            float remainder = value - product;

            if (remainder > 0.0f)
            {
                if (remainder >= step / 2.0f)
                {
                    float newValue = product + step;
                    setValue(newValue > maximum ? maximum : newValue);
                }
                else
                {
                    float newValue = product;
                    setValue(newValue < minimum ? minimum : newValue);
                }
            }
            else if (remainder < 0.0f)
            {
                if (remainder >= -step / 2.0f)
                {
                    float newValue = product;
                    setValue(newValue > maximum ? maximum : newValue);
                }
                else
                {
                    float newValue = product - step;
                    setValue(newValue < minimum ? minimum : newValue);
                }
            }
        }

        setNormalizedValue((getValue() - minimum) / (maximum - minimum));
        m_insideRangeValueCheck = false;
    }
    else if (propertyType == MaximumValueProperty ||
             propertyType == MinimumValueProperty)
    {
        float value = getValue();
        float maximum = getMaximumValue();
        float minimum = getMinimumValue();

        if (maximum < minimum)
        {
            setMaximumValue(minimum);
        }
        if (value > maximum)
        {
            setValue(maximum);
        }
        else if (value < minimum)
        {
            setValue(minimum);
        }
    }
    else if (!m_insideNormalizedValueCheck && !m_insideRangeValueCheck && propertyType == NormalizedValueProperty)
    {
        m_insideNormalizedValueCheck = true;
        // Normalized value changed. Update RangeValue.
        float maximum = getMaximumValue();
        float minimum = getMinimumValue();
        float normalized = getNormalizedValue();

        setValue(normalized * (maximum - minimum) + minimum);
        m_insideNormalizedValueCheck = false;
    }
}

template <class TBaseClass, class TDerivedClass>
PropertyTypeEditorInfoSharedPtr RangeConceptImpl<TBaseClass, TDerivedClass>::makeEditorInfo()
{
    return PropertyTypeEditorInfoSharedPtr(
        KZ_PROPERTY_TYPE_EDITOR_INFO(
            []() -> PropertyTypeEditorInfo::AttributeDictionary {
                PropertyTypeEditorInfo::AttributeDictionary dict;

                dict.displayName = "Range";

                return dict;
            }()));
}
}

#endif
