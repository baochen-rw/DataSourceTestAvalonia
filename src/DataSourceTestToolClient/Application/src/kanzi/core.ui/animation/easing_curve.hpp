// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_EASING_CURVE_HPP
#define KZ_EASING_CURVE_HPP

#include <kanzi/core.ui/animation/easing_curve_shared.hpp>
#include <kanzi/core/cpp/math.hpp>
#include <kanzi/core/legacy/wrappers/kzs_math.hpp>
#include <kanzi/core/cpp/cstddef.hpp>


// All kinds of animation easing curves

namespace kanzi
{

enum AnimationEasingMode
{
    AnimationEaseIn,
    AnimationEaseOut,
    AnimationEaseInOut
};

struct StepEasingFunction
{
    float operator()(float v) const
    {
        return v >= 1.0f ? 1.0f : 0.0f;
    }
};

struct SmootherStepEasingFunction
{
    float operator()(float v) const
    {
        return v * v * v * (v * (v * 6.0f - 15.0f) + 10.0f);
    }
};

struct BackEasingFunction
{
    float amplitude;

    explicit BackEasingFunction(float amplitude) : amplitude(amplitude)
    {
    }

    BackEasingFunction() : amplitude(1.0f)
    {
    }

    float operator()(float v) const
    {
        return v * v * v - v * amplitude * sin(v * KZS_PI);
    }
};

struct BounceEasingFunction
{
    BounceEasingFunction()
    {
    }

    float operator()(float t) const
    {
        float a = 1.70158f;
        float c = 1.0f;
        // Invert t for consistent behavior with other easing functions regarding in-out mode.
        t = 1.0f - t;
        if (t < (4.0f / 11.0f))
        {
            return 1.0f - c * (7.5625f * t * t);
        }
        else if (t < (8.0f / 11.0f))
        {
            t -= (6.0f / 11.0f);
            return 1.0f - (-a * (1.0f - (7.5625f * t * t + 0.75f)) + c);
        }
        else if (t < (10.0f / 11.0f))
        {
            t -= (9.0f / 11.0f);
            return 1.0f - (-a * (1.0f - (7.5625f * t * t + 0.9375f)) + c);
        }
        else
        {
            t -= (21.0f / 22.0f);
            return 1.0f - (-a * (1.0f - (7.5625f * t * t + 0.984375f)) + c);
        }
    }
};

struct CircleEasingFunction
{
    float operator()(float v) const
    {
        return 1.0f - sqrt(1.0f - v * v);
    }
};

struct QuadraticEasingFunction
{
    float operator()(float v) const
    {
        return v * v;
    }
};

struct CubicEasingFunction
{
    float operator()(float v) const
    {
        return v * v * v;
    }
};

struct QuarticEasingFunction
{
    float operator()(float v) const
    {
        return v * v * v * v;
    }
};

struct QuinticEasingFunction
{
    float operator()(float v) const
    {
        return v * v * v * v * v;
    }
};

struct PowerEasingFunction
{
    float power;

    explicit PowerEasingFunction(float power) : power(power)
    {
    }

    PowerEasingFunction() : power(6.0f)
    {
    }

    float operator()(float v) const
    {
        return pow(v, power);
    }
};

struct ExponentialEasingFunction
{
    float exponent;

    explicit ExponentialEasingFunction(float exponent) : exponent(exponent)
    {
    }

    ExponentialEasingFunction() : exponent(2.0f)
    {
    }

    float operator()(float v) const
    {
        return (exp(exponent * v) - 1.0f) / (exp(exponent) - 1.0f);
    }
};

struct SineEasingFunction
{
    float operator()(float v) const
    {
        return 1.0f - sin(KZS_PI * 0.5f * (1.0f - v));
    }
};

struct ElasticEasingFunction
{
    float oscillations;
    float springiness;

    explicit ElasticEasingFunction(float oscillations, float springiness) : oscillations(oscillations), springiness(springiness)
    {
    }

    ElasticEasingFunction() : oscillations(3.0f), springiness(3.0f)
    {
    }

    float operator()(float v) const
    {
        float expo;
        if (v == 0.0f)
        {
            expo = v;
        }
        else
        {
            expo = (exp(springiness * v) - 1.0f) / (exp(springiness) - 1.0f);
        }

        return expo * (sin((KZS_PI * 2.0f * oscillations + KZS_PI * 0.5f) * v));

    }
};


}


#endif
