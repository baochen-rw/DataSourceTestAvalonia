// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPEED_MEASURER_HPP
#define KZ_SPEED_MEASURER_HPP

#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/optional.hpp>

namespace kanzi
{

/// Implements an object that calculates average speed from its measurement data.

class KANZI_API SpeedMeasurer
{

public:

    /// Creates a speed measurer with the given properties.
    explicit SpeedMeasurer(size_t maxMeasurements, chrono::milliseconds minMeasurementWindow, chrono::milliseconds maxMeasurementWindow);

    /// Resets measurement data.
    void reset();

    /// Adds a new measurement to the measurer.
    void addMeasurement(chrono::milliseconds timestamp, float value);

    /// Calculates average speed from measurements in units / second.
    /// Returns nullopt if there were not enough measurements.
    optional<float> getSpeed(chrono::milliseconds measurementTime) const;

private:
    /// Contains a value and a time for measuring speed.
    struct Measurement
    {
        /// Value of the measurement.
        float value;

        /// Time of the measurement.
        chrono::milliseconds timestamp;
    };

    typedef vector<Measurement> Measurements;

    /// An array of speed measurements.
    Measurements m_measurements;

    /// Index of the first element.
    size_t m_index;

    /// Minimum measurement window.
    chrono::milliseconds m_minMeasurementWindow;

    /// Maximum measurement window.
    chrono::milliseconds m_maxMeasurementWindow;

    /// Maximum number of measurements to use.
    size_t m_maxMeasurements;

};

} // namespace

#endif

