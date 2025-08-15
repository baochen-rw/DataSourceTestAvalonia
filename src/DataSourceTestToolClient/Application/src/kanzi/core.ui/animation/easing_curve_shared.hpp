// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_EASING_CURVE_SHARED_HPP
#define KZ_EASING_CURVE_SHARED_HPP


// Easing curves which do not require external dependencies for calculation.
// These curves can be used in other projects by including this header without
// including the rest of the engine or third-party libraries.

namespace kanzi
{

struct LinearEasingFunction
{
    float operator()(float v) const
    {
        return v;
    }
};

struct SmoothStepEasingFunction
{
    float operator()(float v) const
    {
        return v * v * (3.0f - 2.0f * v);
    }
};

struct BezierEasingFunction
{
    float fromValue;

    float tangentFromTime;
    float tangentFromValue;

    float tangentToTime;
    float tangentToValue;

    float toValue;

    explicit BezierEasingFunction(float fromValue, float tangentFromTime, float tangentFromValue,
                                  float tangentToTime, float tangentToValue, float toValue) :
        fromValue(fromValue),
        tangentFromTime(tangentFromTime),
        tangentFromValue(tangentFromValue),
        tangentToTime(tangentToTime),
        tangentToValue(tangentToValue),
        toValue(toValue)
    {
    }

    explicit BezierEasingFunction() :
        fromValue(0.0f),
        tangentFromTime(0.5f),
        tangentFromValue(0.0f),
        tangentToTime(0.5f),
        tangentToValue(1.0f),
        toValue(1.0f)
    {
    }

    float operator()(float v) const
    {
        // Bezier parameter.
        float t = 0.0f;

        // Find Bezier parameter from input time (v).
        {
            // Accepted value can be this far from correct value.
            const float approximationEpsilon = 1.0e-05f;
            const float maxError = approximationEpsilon;

            float from = 0.0f;
            float tangentFrom = tangentFromTime;
            float tangentTo = tangentToTime;
            float to = 1.0f;

            float left = 0.0f;
            float right = 1.0f;

            float error = to;
            bool binaryStep = false;

            for (int i = 0; i < 50; ++i)
            {
                // Regula falsi with De Casteljau subdivision, backed up with binary search.
                const float q = binaryStep ? 0.5f : ((v - from) / (to - from));

                const float a = from + (tangentFrom - from) * q;
                const float b = tangentFrom + (tangentTo - tangentFrom) * q;
                const float c = tangentTo + (to - tangentTo) * q;
                const float d = a + (b - a) * q;
                const float e = b + (c - b) * q;
                const float f = d + (e - d) * q;

                // Close enough to solution?
                const float difference = f - v;
                const float absoluteDifference = (difference >= 0.0f) ? difference : -difference;
                if (absoluteDifference < maxError)
                {
                    t = left + (right - left) * q;
                    t = (t < 0.0f) ? 0.0f : ((t > 1.0f) ? 1.0f : t);
                    break;
                }

                // Split Bezier.
                if (f < v)
                {
                    from = f;
                    tangentFrom = e;
                    tangentTo = c;
                    left = left + (right - left) * q;
                }
                else
                {
                    tangentFrom = a;
                    tangentTo = d;
                    to = f;
                    right = left + (right - left) * q;
                }

                // Select step mode.
                const float newError = to - from;
                binaryStep = (newError > (0.5f * error));
                error = newError;
            }
        }

        // Find value.
        const float A = fromValue;
        const float B = tangentFromValue;
        const float C = tangentToValue;
        const float D = toValue;

        return A + 3.0f * t * (B - A + t * (C - 2.0f * B + A + t * ((1.0f / 3.0f) * (D - A) + B - C)));
    }
};

}

#endif // KZ_EASING_CURVE_SHARED_HPP
