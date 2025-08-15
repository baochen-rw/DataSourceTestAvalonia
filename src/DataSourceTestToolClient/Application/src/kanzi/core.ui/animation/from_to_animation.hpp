// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FROM_TO_ANIMATION_HPP
#define KZ_FROM_TO_ANIMATION_HPP


#include "value_animation.hpp"
#include "interpolation.hpp"
#include "easing_curve.hpp"


namespace kanzi
{

template <typename TValueType>
class FromToAnimationBase : public ValueAnimation<TValueType>
{
public:

    KZ_TEMPLATE_METACLASS_BEGIN(FromToAnimationBase, ValueAnimation<TValueType>)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }

    optional<TValueType> getFrom() const
    {
        return m_from;
    }

    void setFrom(optional<TValueType> from)
    {
        m_from = from;
    }

    bool hasFrom() const
    {
        return static_cast<bool>(m_from);
    }

    optional<TValueType> getTo() const
    {
        return m_to;
    }

    void setTo(optional<TValueType> to)
    {
        m_to = to;
    }

    bool hasTo() const
    {
        return static_cast<bool>(m_to);
    }

    void setDuration(chrono::milliseconds duration)
    {
        m_duration = duration;
    }

    void setEasingMode(AnimationEasingMode mode)
    {
        m_easingMode = mode;
    }

    AnimationEasingMode getEasingMode() const
    {
        return m_easingMode;
    }

protected:

    /// Constructor.
    explicit FromToAnimationBase(Domain* domain, chrono::milliseconds duration, optional<TValueType> from, optional<TValueType> to) : ValueAnimation<TValueType>(domain), m_duration(duration), m_from(from), m_to(to), m_easingMode(AnimationEaseIn)
    {
    }

    virtual optional<chrono::milliseconds> getDurationOverride() KZ_OVERRIDE
    {
        return m_duration;
    }

    /// Animation duration.
    chrono::milliseconds m_duration;
    /// "From" value of the animation.
    optional<TValueType> m_from;
    /// "To" value of the animation.
    optional<TValueType> m_to;
    /// Easing mode.
    AnimationEasingMode m_easingMode;
};


/// Template class for from-to animations.
/// \tparam TValueType Defines the type of the value you want to animate. For example, float, bool, int, ColorRGBA.
/// \tparam TEasingFunction defines the type of the easing function used for the animation. For example, LinearEasingFunction,
/// SmoothStepEasingFunction, BackEasingFunction. For a full list of easing functions see easing_curve.hpp
///
/// The Kanzi animation system consists animations and timelines: animations define how to animate a property,
/// and timelines map the animations to time and to objects you want to animate.
///
/// From-to animation defines from which to which value to change the value of a property. You can omit either
/// of these values to animate either from the current value or to the current value of the property.
///
/// From-to animations use an easing curve that defines the rate of change for the animation. You can use one of the
/// easing curves that comes with Kanzi, or define your own. With the easing mode you can control how the easing
/// function is applied to the animation:
/// - Ease in easing mode applies to the transition the easing function as it is.
/// - Ease out easing mode applies to the transition the negative value of the easing function.
/// - Ease in-out easing mode applies to the first half of the transition the easing function as it is, and to the
/// second half of the transition the negative value of the easing function.
///
/// Examples
/// ----
///
/// To create a from-to animation:
/// \snippet test_animation.cpp Create from-to animation
///
/// To animate a property value in a node using a from-to animation:
/// \snippet test_animation.cpp Add from-to animation to property timeline
///
/// To animate a property field value in a node using a from-to animation:
/// \snippet test_animation.cpp Add from-to animation to property field timeline
///
/// To create a float from-to animation that uses the back easing curve and the ease out easing mode:
/// \snippet test_animation.cpp Create from-to back easing function animation
///
/// To play an animation regardless of the timeline type:
/// \snippet test_animation.cpp Play animation


template <typename TValueType, typename TEasingFunction>
class FromToAnimation : public FromToAnimationBase<TValueType>
{
public:

    KZ_TEMPLATE_METACLASS_BEGIN(FromToAnimation, FromToAnimationBase<TValueType>)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo() { return PropertyTypeEditorInfoSharedPtr(); }

    static shared_ptr<FromToAnimation> create(Domain* domain, chrono::milliseconds duration, optional<TValueType> from, optional<TValueType> to)
    {
        return make_polymorphic_shared_ptr<AbstractAnimation>(new FromToAnimation(domain, duration, from, to));
    }

    TEasingFunction getEasingFunction() const
    {
        return m_easingFunction;
    }

    void setEasingFunction(TEasingFunction easingFunction)
    {
        m_easingFunction = easingFunction;
    }

    virtual TValueType getValue(const TValueType& currentValue, chrono::milliseconds time) KZ_OVERRIDE
    {
        if (!this->m_from && !this->m_to)
        {
            kzThrowException(logic_error("FromToAnimation with both from and to values unspecified."));
        }

        // Return exact values if possible.
        if (time <= chrono::milliseconds::zero())
        {
            return this->m_from.value_or(currentValue);
        }

        if (time >= this->m_duration)
        {
            return this->m_to.value_or(currentValue);
        }

        // Normalize time.
        const float normalizedTime = this->m_duration.count() ? static_cast<float>(time.count()) / static_cast<float>(this->m_duration.count()) : 0.0f;
        // Ease time.
        const float easedTime = easeTime(normalizedTime);

        // Get values and interpolate.
        TValueType from = this->m_from.value_or(currentValue);
        TValueType to = this->m_to.value_or(currentValue);
        TValueType value = animationInterpolate(from, to, easedTime);

        return value;
    }

protected:

    /// Constructor.
    explicit FromToAnimation(Domain* domain, chrono::milliseconds duration, optional<TValueType> from, optional<TValueType> to) : FromToAnimationBase<TValueType>(domain, duration, from, to)
    {
    }

    float easeTime(float normalizedTime) const
    {
        if (this->m_easingMode == AnimationEaseInOut)
        {
            return (normalizedTime < 0.5f) ? m_easingFunction(normalizedTime * 2.0f) * 0.5f : (1.0f - m_easingFunction((1.0f - normalizedTime) * 2.0f)) * 0.5f + 0.5f;
        }
        else if (this->m_easingMode == AnimationEaseOut)
        {
            return 1.0f - m_easingFunction(1.0f - normalizedTime);
        }

        return m_easingFunction(normalizedTime);
    }

private:
    
    /// Easing function of the animation.
    TEasingFunction m_easingFunction;
};


typedef FromToAnimation<bool, LinearEasingFunction> BoolLinearFromToAnimation;
typedef shared_ptr<BoolLinearFromToAnimation> BoolLinearFromToAnimationSharedPtr;

typedef FromToAnimation<float, LinearEasingFunction> FloatLinearFromToAnimation;
typedef shared_ptr<FloatLinearFromToAnimation> FloatLinearFromToAnimationSharedPtr;

typedef FromToAnimation<ColorRGBA, LinearEasingFunction> ColorRGBALinearFromToAnimation;
typedef shared_ptr<ColorRGBALinearFromToAnimation> ColorRGBALinearFromToAnimationSharedPtr;

typedef FromToAnimation<float, function<float(float)> > FloatCustomFromToAnimation;
typedef shared_ptr<FloatCustomFromToAnimation> FloatCustomFromToAnimationSharedPtr;


}


#endif
