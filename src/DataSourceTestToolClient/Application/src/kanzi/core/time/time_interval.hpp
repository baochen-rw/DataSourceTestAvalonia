// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIME_INTERVAL_HPP
#define KZ_TIME_INTERVAL_HPP


#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/optional.hpp>


namespace kanzi
{

/// Interval in time specified as start and end timestamps.
struct TimeInterval
{
public:

    /// Default constructor.
    /// Initializes start of interval to negative infinity and 
    /// end of interval to negative infinity.
    explicit TimeInterval();

    /// Constructor.
    /// If start and end are both defined and start in bigger than end,
    /// interval will switch start and end.
    /// \param start Start timestamp of interval. Empty optional specifies negative infinity.
    /// \param end End timestamp of interval. Empty optional specifies positive infinity.
    explicit TimeInterval(optional<chrono::milliseconds> start, optional<chrono::milliseconds> end);

    /// Gets start timestamp. Empty optional specifies negative infinity.
    /// \return start timestamp.
    optional<chrono::milliseconds> getStart() const;

    /// Gets end timestamp. Empty optional specifies positive infinity.
    /// \return end timestamp.
    optional<chrono::milliseconds> getEnd() const;

    /// Gets the duration of interval. Empty optional specifies infinite duration.
    /// \return end timestamp.
    optional<chrono::milliseconds> getDuration() const;

    /// Determines whether the interval contains specified timestamp.
    /// \time time Timestamp to test.
    /// \return true if the timestamp is within interval, false otherwise.
    bool contains(chrono::milliseconds time) const;

    /// Determines whether specified timestamp equals to start of interval.
    /// \param time Timestamp to test.
    /// \return true if the timestamp equals to start of interval.
    bool isStart(chrono::milliseconds time) const;

    /// Determines whether specified timestamp equals to end of interval.
    /// \param time Timestamp to test.
    /// \return true if the timestamp equals to end of interval.
    bool isEnd(chrono::milliseconds time) const;

    /// Clamps time to interval.
    /// \param time Timestamp to clamp.
    /// \return clamped timestamp.
    chrono::milliseconds clampToInterval(chrono::milliseconds time) const;

    /// Creates interval from start time and duration.
    /// \param start Start timestamp of interval.
    /// \param duration Duration of interval. Empty optional specifies infinite duration.
    static TimeInterval createFromStartTimeAndDuration(chrono::milliseconds start, optional<chrono::milliseconds> duration);

private:

    /// Start timestamp of interval.
    /// Empty optional specifies negative infinity.
    optional<chrono::milliseconds> m_start;

    /// End timestamp of interval.
    /// Empty optional specifies positive infinity.
    optional<chrono::milliseconds> m_end;
};


/// Gets intersection of two intervals.
/// \param first First interval.
/// \param second Second interval.
/// \return Intersection interval or empty optional if intervals are not intersecting.
optional<TimeInterval> getIntersection(const TimeInterval& first, const TimeInterval& second);

}

#endif
