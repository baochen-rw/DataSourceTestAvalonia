// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_FRAME_TIME_QUEUE_HPP
#define KZU_FRAME_TIME_QUEUE_HPP

#include <kanzi/core/cpp/array.hpp>



/// The queue size defines the threshold (in FPS) for accurate measurement.
/// Keeping the queue size a power of two is recommended for optimization reasons.
#define KZU_FRAME_TIME_QUEUE_SIZE (64)


namespace kanzi
{


/// \class FrameTimeQueue
/// Queue specialization for calculating frame rate.
class FrameTimeQueue
{
public:
    /// Constructor.
    explicit FrameTimeQueue();

    /// Updates the frame time queue with a new frame time.
    /// \param frameTime Duration of the new frame in milliseconds.
    void update(unsigned int frameTime);

    /// Returns the current FPS.
    /// \return Current frame rate in frames per second.
    float getFPS() const
    {
        return m_fps;
    }

    /// Returns the last frame time.
    /// \return Last frame duration in milliseconds.
    unsigned int getLastFrameTime() const
    {
        return m_latestFrameTime;
    }

protected:
#ifdef KANZI_DEBUG
    /// Calculates the sum of the frame times in the queue.
    /// \return Total duration of all frames in milliseconds.
    unsigned int calculateMilliseconds() const;

    /// Calculates the current FPS.
    /// \return Current frame rate in frames per second.
    float calculateFPS() const;
#endif

    /// Frame time queue data.
    array<unsigned int, KZU_FRAME_TIME_QUEUE_SIZE> m_frames;

    /// Frame time queue front index.
    unsigned int m_firstFrame;

    /// Frame time queue size.
    unsigned int m_frameCount;

    /// Frame time queue content sum cache.
    unsigned int m_milliseconds;

    /// Duration of last frame in milliseconds.
    unsigned int m_latestFrameTime;

    /// Frame rate cache.
    float m_fps;
};

}

#endif
