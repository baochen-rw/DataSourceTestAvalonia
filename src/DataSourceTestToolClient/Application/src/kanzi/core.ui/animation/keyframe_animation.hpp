// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_KEYFRAME_ANIMATION_HPP
#define KZ_KEYFRAME_ANIMATION_HPP


#include "value_animation.hpp"
#include "interpolation.hpp"
#include "easing_curve.hpp"
#include <kanzi/core/cpp/map.hpp>

#include <kanzi/core/cpp/map.hpp>

namespace kanzi
{



/// Template class for keyframe animations.
/// \tparam TValueType Defines the type of the value you want to animate. For example, float, bool, int, ColorRGBA.
///
/// The Kanzi animation system consists animations and timelines: animations define how to animate a property,
/// and timelines map the animations to time and to objects you want to animate.
///
/// Keyframe animation uses keyframes that define the property value and time at which the animation reaches
/// that value. In Kanzi you can create linear, step, and Bezier keyframes.
///
/// Examples
/// ----
///
/// To create a keyframe animation:
/// \snippet test_animation.cpp Create keyframe animation
///
/// To animate a property value in a node using a keyframe animation:
/// \snippet test_animation.cpp Add keyframe animation to property timeline
///
/// To animate a property field value in a node using a keyframe animation:
/// \snippet test_animation.cpp Add keyframe animation to property field timeline
///
/// To create a keyframe animation that uses Bezier keyframes to move an object on a sideways figure eight shaped path:
/// \snippet test_animation.cpp Create Bezier keyframe animation
///
/// To play an animation regardless of the timeline type:
/// \snippet test_animation.cpp Play animation


template <typename TValueType>
class KeyframeAnimation : public ValueAnimation<TValueType>
{
public:

    KZ_TEMPLATE_METACLASS_BEGIN(KeyframeAnimation, ValueAnimation<TValueType>)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo() { return PropertyTypeEditorInfoSharedPtr(); }

    static shared_ptr<KeyframeAnimation> create(Domain* domain)
    {
        return make_polymorphic_shared_ptr<AbstractAnimation>(new KeyframeAnimation(domain));
    }

    class Keyframe
    {
    public:
        /// Constructor.
        explicit Keyframe() :
            m_keyValue()
        {
        }

        /// Constructor.
        explicit Keyframe(TValueType value) :
            m_keyValue(value)
        {
        }

        virtual ~Keyframe()
        {
        }

        TValueType getKeyValue() const
        {
            return m_keyValue;
        }

        void setKeyValue(const TValueType& keyValue)
        {
            m_keyValue = keyValue;
        }

        virtual TValueType getValue(const TValueType& currentValue, float normalizedTime) = 0;

    private:

        TValueType m_keyValue;
    };

    typedef unique_ptr<Keyframe> KeyframePtr;

    typedef map<chrono::milliseconds, Keyframe*> KeyframeContainer;

    class StepKeyframe;
    typedef unique_ptr<StepKeyframe> StepKeyframePtr;

    class StepKeyframe : public Keyframe
    {
    public:
        /// Constructor.
        explicit StepKeyframe()
        {
        }

        /// Constructor.
        explicit StepKeyframe(TValueType value) :
            Keyframe(value)
        {
        }

        /// Creates step keyframe.
        static StepKeyframePtr create(float value)
        {
            return KZ_MOVE_RET(StepKeyframePtr, StepKeyframePtr(new StepKeyframe(value)));
        }

        virtual TValueType getValue(const TValueType& currentValue, float normalizedTime) KZ_OVERRIDE
        {
            return normalizedTime == 1.0f ? this->getKeyValue() : currentValue;
        }
    };

    class LinearKeyframe;
    typedef unique_ptr<LinearKeyframe> LinearKeyframePtr;

    class LinearKeyframe : public Keyframe
    {
    public:
        /// Constructor.
        explicit LinearKeyframe()
        {
        }

        /// Constructor.
        explicit LinearKeyframe(TValueType value) :
            Keyframe(value)
        {
        }

        /// Creates linear keyframe.
        static LinearKeyframePtr create(float value)
        {
            return KZ_MOVE_RET(LinearKeyframePtr, LinearKeyframePtr(new LinearKeyframe(value)));
        }

        virtual TValueType getValue(const TValueType& currentValue, float normalizedTime) KZ_OVERRIDE
        {
            return animationInterpolate(currentValue, this->getKeyValue(), normalizedTime);
        }
    };

    class BezierKeyframe;
    typedef unique_ptr<BezierKeyframe> BezierKeyframePtr;

    class BezierKeyframe : public Keyframe
    {
    public:
        /// Constructor.
        explicit BezierKeyframe()
        {
        }

        /// Constructor.
        explicit BezierKeyframe(TValueType value, const Vector2& p0, const Vector2& p1) :
            Keyframe(value),
            m_controlPoint0(p0),
            m_controlPoint1(p1)
        {
        }

        /// Creates bezier keyframe.
        static BezierKeyframePtr create(TValueType value, const Vector2& p0, const Vector2& p1)
        {
            return KZ_MOVE_RET(BezierKeyframePtr, BezierKeyframePtr(new BezierKeyframe(value, p0, p1)));
        }

        void setControlPoints(const Vector2& p0, const Vector2& p1)
        {
            m_controlPoint0 = p0;
            m_controlPoint1 = p1;
        }

        Vector2 getControlPoint0() const
        {
            return m_controlPoint0;
        }

        void setControlPoint0(Vector2 controlPoint)
        {
            m_controlPoint0 = controlPoint;
        }

        Vector2 getControlPoint1() const
        {
            return m_controlPoint1;
        }

        void setControlPoint1(Vector2 controlPoint)
        {
            m_controlPoint1 = controlPoint;
        }

        virtual TValueType getValue(const TValueType& currentValue, float normalizedTime) KZ_OVERRIDE
        {
            BezierEasingFunction easingCurve(currentValue, m_controlPoint0.getX(), m_controlPoint0.getY(),
                                             m_controlPoint1.getX(), m_controlPoint1.getY(), this->getKeyValue());

            return easingCurve(normalizedTime);
        }

    private:

        Vector2 m_controlPoint0;
        Vector2 m_controlPoint1;
    };

    ~KeyframeAnimation()
    {
        for (typename KeyframeContainer::const_iterator keyframe = m_keyframes.cbegin(); keyframe != m_keyframes.cend(); keyframe++)
        {
            delete keyframe->second;
        }
    }

    void addKeyframe(chrono::milliseconds time, KeyframePtr keyframePtr)
    {
        Keyframe* keyframe = keyframePtr.get();
        pair<typename KeyframeContainer::iterator, bool> result =
            m_keyframes.insert(typename KeyframeContainer::value_type(time, keyframe));
        if(!result.second)
        {
            kzThrowException(logic_error("Added two keyframes with the same time."));
        }
        keyframePtr.release();
    }

    void addStepKeyframe(chrono::milliseconds time, const TValueType& value)
    {
        KeyframePtr keyframe(new StepKeyframe(value));
        addKeyframe(time, kanzi::move(keyframe));
    }

    void addLinearKeyframe(chrono::milliseconds time, const TValueType& value)
    {
        KeyframePtr keyframe(new LinearKeyframe(value));
        addKeyframe(time, kanzi::move(keyframe));
    }

    void addBezierKeyframe(chrono::milliseconds time, const TValueType& value, const Vector2& p0, const Vector2& p1)
    {
        KeyframePtr keyframe(new BezierKeyframe(value, p0, p1));
        addKeyframe(time, kanzi::move(keyframe));
    }

    virtual TValueType getValue(const TValueType& currentValue, chrono::milliseconds time) KZ_OVERRIDE
    {
        if (m_keyframes.empty())
        {
            return currentValue;
        }

        const typename KeyframeContainer::const_iterator it = m_keyframes.lower_bound(time);
        if (it == cend(m_keyframes))
        {
            // Past last keyframe.
            const typename KeyframeContainer::value_type& lastKeyframeEntry = *crbegin(m_keyframes);
            return lastKeyframeEntry.second->getKeyValue();
        }

        if (time == it->first)
        {
            // Exact key match.
            const typename KeyframeContainer::value_type& keyframeEntry = *it;
            return keyframeEntry.second->getKeyValue();
        }

        if (it == cbegin(m_keyframes))
        {
            // Before the first keyframe.
            if (time < chrono::milliseconds::zero())
            {
                // Negative time and a keyframe at 0.
                if (it->first == chrono::milliseconds::zero())
                {
                    // Exact key match.
                    const typename KeyframeContainer::value_type& keyframeEntry = *it;
                    return keyframeEntry.second->getKeyValue();
                }

                // Negative time and no keyframe at 0.
                return currentValue;
            }

            const typename KeyframeContainer::value_type& firstKeyframeEntry = *it;
            const float normalizedTime = static_cast<float>(time.count()) / static_cast<float>(firstKeyframeEntry.first.count());
            return firstKeyframeEntry.second->getValue(currentValue, normalizedTime);
        }

        // Between keyframes.
        const typename KeyframeContainer::value_type& afterKeyframeEntry = *it;
        const typename KeyframeContainer::value_type& beforeKeyframeEntry = *prev(it);
        const chrono::milliseconds timeSinceBeforeKeyframe = time - beforeKeyframeEntry.first;
        const chrono::milliseconds timeBetweenKeyframes = afterKeyframeEntry.first - beforeKeyframeEntry.first;
        const float normalizedTime = static_cast<float>(timeSinceBeforeKeyframe.count()) / static_cast<float>(timeBetweenKeyframes.count());
        return afterKeyframeEntry.second->getValue(beforeKeyframeEntry.second->getKeyValue(), normalizedTime);
    }

protected:

    /// Constructor.
    explicit KeyframeAnimation(Domain* domain) : ValueAnimation<TValueType>(domain)
    {
    }

    virtual optional<chrono::milliseconds> getDurationOverride() KZ_OVERRIDE
    {
        if (m_keyframes.empty())
        {
            return chrono::milliseconds::zero();
        }

        const typename KeyframeContainer::const_reverse_iterator lastKeyframe = crbegin(m_keyframes);
        return lastKeyframe->first;
    }

private:

    KeyframeContainer m_keyframes;
};


typedef KeyframeAnimation<bool> BoolKeyframeAnimation;
typedef shared_ptr<BoolKeyframeAnimation> BoolKeyframeAnimationSharedPtr;

typedef KeyframeAnimation<int> IntKeyframeAnimation;
typedef shared_ptr<IntKeyframeAnimation> IntKeyframeAnimationSharedPtr;

typedef KeyframeAnimation<float> FloatKeyframeAnimation;
typedef shared_ptr<FloatKeyframeAnimation> FloatKeyframeAnimationSharedPtr;

typedef KeyframeAnimation<Vector2> Vector2KeyframeAnimation;
typedef shared_ptr<Vector2KeyframeAnimation> Vector2KeyframeAnimationSharedPtr;

typedef KeyframeAnimation<Vector3> Vector3KeyframeAnimation;
typedef shared_ptr<Vector3KeyframeAnimation> Vector3KeyframeAnimationSharedPtr;

typedef KeyframeAnimation<Vector4> Vector4KeyframeAnimation;
typedef shared_ptr<Vector4KeyframeAnimation> Vector4KeyframeAnimationSharedPtr;

typedef KeyframeAnimation<ColorRGBA> ColorRGBAKeyframeAnimation;
typedef shared_ptr<ColorRGBAKeyframeAnimation> ColorRGBAKeyframeAnimationSharedPtr;

typedef KeyframeAnimation<string> StringKeyframeAnimation;
typedef shared_ptr<StringKeyframeAnimation> StringKeyframeAnimationSharedPtr;

typedef KeyframeAnimation<ResourceID> ResourceIDKeyframeAnimation;
typedef shared_ptr<ResourceIDKeyframeAnimation> ResourceIDKeyframeAnimationSharedPtr;


}


#endif
