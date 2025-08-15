// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_FPS_CONSTRAINTS
#define KZ_FPS_CONSTRAINTS

#include <kanzi/core.ui/coreui_api.hpp>

#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/math/rational.hpp>

namespace kanzi
{

/// Constraint for limiting the number of frames per second the Engine is rendering.
class KANZI_COREUI_API FPSConstraints
{
public:

    /// Constructor
    /// Sets desired framerate to 60.
    explicit FPSConstraints();

    /// Sets desired framerate as frames per second.
    /// The desired framerate represents the number of frames per second the program should render.
    /// In heavy load, framerate may be smaller if rendering frames takes too long.
    /// In practice the framerate may also be very slightly higher (due to time measurement inaccuracies).
    /// This is the reason it's called desired framerate - the system is aiming to the framerate but cannot guarantee exact numbers.
    /// \param frameRate Framerate to aim for.
    void setDesiredFrameRate(unsigned int frameRate);

    /// Gets the time main thread can sleep in milliseconds, supposing given duration would have passed from the start of the frame.
    /// The time passed is used to determine the remaining sleep time this frame, for example when called after rendering.
    /// \param deltaTime Time passed since the frame started.
    /// \return Maximum time the main thread should sleep. Always nonnegative.
    chrono::milliseconds getProposedSleepTime(chrono::milliseconds deltaTime) const;

    /// Update constraints tracking with frame time.
    /// \param delta Time delta since last frame.
    void update(chrono::milliseconds delta);

    /// Gets the target frame time in milliseconds.
    /// This is the number of milliseconds each rendering of a frame should take.
    /// This number is rounded down if exact frame time is not an integer.
    /// \return Frame time in milliseconds, rounded down.
    chrono::milliseconds getTargetFrameTime() const
    {
        return m_frameTimeLowerLimit;
    }

    /// Tells if frame rate limiting is enabled.
    /// \return True if framerate is limited, false if unlimited.
    bool isEnabled() const
    {
        return m_enabled;
    }
    /// Turn frame rate limit on or off.
    /// \param enable New state.
    void setEnabled(bool enable)
    {
        m_enabled = enable;
    }

private:

    /// Type for rational contents.
    typedef long long RationalIntegerType;

    /// Type for timestamps that is not affected by floating point errors.
    typedef rational<RationalIntegerType> RationalType;

    /// Fractional time remaining from previous frames.
    /// If frame time is not exact milliseconds, this represents the 'leap' milliseconds from previous frames.
    /// When leap milliseconds add to more than one millisecond, the next frame should take one millisecond longer.
    RationalType m_fractionalTime;

    /// Frame time lower in whole (non-fractional) milliseconds.
    chrono::milliseconds m_frameTimeLowerLimit;

    /// Frame time upper limit in whole (non-fractional) milliseconds.
    /// This represents the comparison number that the current frame time is checked against, to determine if time demands were met or not.
    /// When frame time lower limit is exact milliseconds, this limit equals the frame time.
    /// Otherwise it's frame time in milliseconds rounded up.
    chrono::milliseconds m_frameTimeUpperLimit;

    /// Desired framerate the system is aiming for.
    unsigned int m_desiredFrameRate;

    /// Flag telling whether or not frame rate limiter is enabled.
    bool m_enabled;
};

}

#endif // KZ_FPS_CONSTRAINTS