// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INTERPOLATED_VALUE_HPP
#define KZ_INTERPOLATED_VALUE_HPP

#include <kanzi/core.ui/coreui_api.hpp>

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/chrono.hpp>

namespace kanzi
{

/// Core component for smooth interpolation in code.
///
/// Uses Runge-Kutta methods and suitable differential equations to smoothly interpolate
/// between input data.
/// Supports multiple interpolation modes such as looping/non-looping.
/// Provides smooth and reactive interpolation towards a dynamic target value.

class KANZI_COREUI_API InterpolatedValue
{

public:

    /// Creates an interpolated value integrator.
    /// Larger acceleration coefficient leads to faster interpolation, larger drag coefficient lowers maximum speed.
    explicit InterpolatedValue(float startingValue,float accelerationCoefficient, float dragCoefficient);

    /// Initializes simulation variables.
    void initializeBoundMode(float accelerationCoefficient, float dragCoefficient);

    /// Sets minimum value for interpolator.
    void setMinimumValue(float minimumValue);

    /// Gets minimum value of interpolator.
    float getMinimumValue() const;

    /// Sets maximum value for interpolator.
    void setMaximumValue(float maximumValue);

    /// Gets maximum value of interpolator.
    float getMaximumValue() const;

    /// Sets maximum time step for the interpolator.
    /// Simulation time is split into time slices of at most this length.
    void setMaximumTimeStep(float maximumStep);

    /// Gets maximum time step of the interpolator.
    /// Simulation time is split into time slices of at most this length.
    float getMaximumTimeStep() const;

    /// Sets interpolator to loop between minimum and maximum value.
    void setLooping(bool state);

    /// Return interpolator's looping state.
    bool isLooping() const;

    /// Normalizes interpolator's value to [minimumValue, maximumValue].
    /// Calling this function manually is normally not required.
    void enforceBounds();

    /// Returns current value of the interpolator.
    /// The value is normalized to the allowed range if a looping interpolator is used.
    float getValue() const;

    /// Sets current value of the interpolator.
    /// If resetInterpolation is true, sets target to the new value and resets speed.
    void setValue(float value, bool resetInterpolation);

    /// Sets current speed of the interpolated value.
    void setSpeed(float speed);

    /// Returns current speed of the interpolated value.
    float getSpeed() const;

    /// Adds 'speedDelta' to current speed of the interpolated value.
    void modifySpeed(float speedDelta);

    /// Integrates simulation for 'timeDelta' milliseconds.
    void update(chrono::milliseconds timeDelta);

    /// Returns true if interpolation has ended for now, i.e. target reached and speed close to zero.
    bool interpolationEnded() const;

    /// Returns target value of the interpolator.
    ///
    /// The value is normalized to the allowed range if a looping interpolator is used.
    /// Function getTargetNonNormalized should be used instead if the target value will be set back with setTarget.
    float getTarget() const;

    /// Returns current non-normalized target value of the interpolator.
    ///
    /// If the interpolator is looping, the target value may be out of bounds to indicate direction and repetition.
    /// This call should be used instead of getTarget if the target value will be set back with setTarget.
    float getTargetNonNormalized() const;

    /// Sets target value of the interpolator.
    /// If the interpolator is looping, the target value may be out bounds to indicate direction and repetition.
    void setTarget(float target);

    /// Adds 'targetDelta' to target value of the interpolator.
    void modifyTarget(float targetDelta);

private:

    /// Current value in interpolation.
    float m_currentValue;

    /// Current speed in interpolation.
    float m_currentSpeed;

    /// Minimum value for interpolation target.
    float m_minimumValue;

    /// Maximum value for interpolation target.
    float m_maximumValue;

    /// Is interpolation looping.
    bool m_looping;

    /// Maximum length of a single integration step. More steps are used if necessary.
    float m_maximumStep;

    /// Current time step.
    float m_timeStep;

    /// Interpolation configuration for bound mode.

    /// Undamped angular frequency of harmonic oscillator, sqrt(k/m).
    float m_boundModeAngularFrequency;

    /// Drag coefficient for controlled interpolation. Additional drag to critically damped oscillator.
    float m_boundModeDragCoefficient;

    /// Interpolation goal value.
    float m_boundModeTargetValue;

private:

    /// Returns acceleration for the integrator at the given value and speed.
    float getAcceleration(float value, float speed);

    //Disabled since not currently needed. Can be enabled later.
    //Integrates simulation at most the given time step. Uses Runge-Kutta 4. Returns the used time step.
    //float integrateRK4(float maximumTimeStep);

    /// Integrates simulation at most the given time step. Uses Bogacki-Shampine with adaptive step size. Returns the used time step.
    float integrateBS(float maximumTimeStep);

    /// Returns 'value' normalized to [minimumValue, maximumValue[.
    float getNormalizedValue(float value) const;

    /// Normalizes values to [minimum value, maximum value[.
    void normalizeState();

private:

    /// Maximum allowed acceleration coefficient.
    static const float m_maximumAcceleration;

    /// Maximum allowed drag coefficient.
    static const float m_maximumDrag;

    /// Constants for Bogacki-Shampine sample calculation.

    /// Constant for Bogacki-Shampine.
    static const float m_BS_B21;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_B32;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_B41;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_B42;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_B43;

    /// Constants for Bogacki-Shampine lower order sample.

    /// Constant for Bogacki-Shampine.
    static const float m_BS_C1;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_C2;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_C3;

    /// Constants for Bogacki-Shampine higher order sample.

    /// Constant for Bogacki-Shampine.
    static const float m_BS_D1;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_D2;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_D3;

    /// Constant for Bogacki-Shampine.
    static const float m_BS_D4;

    /// Error tolerance for Bogacki-Shampine.

    /// Upper bound for maximum error estimate.
    static const float m_estimateError;

    /// Lower bound for maximum error estimate.
    static const float m_minEstimateError;

    /// Relative distance from convergence point where the interpolation is seen to have converged.
    static const float m_convergenceDistance;

    /// Relative maximum speed where the interpolation is seen to have converged.
    static const float m_convergenceSpeed;

    /// Minimum possible scale for calculations.
    static const float m_scaleMinimum;

    /// Minimum possible timestep.
    static const float m_timestepMinimum;
};

} // namespace

#endif
