// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GRAPHICS_OUTPUT_HPP
#define KZ_GRAPHICS_OUTPUT_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core.ui/platform/windowing/common/window_properties.hpp>


struct KzsEventQueue;


namespace kanzi
{

class GraphicsOutput;
class Renderer;


typedef shared_ptr<GraphicsOutput> GraphicsOutputSharedPtr;


/// GraphicsOutput class.
///
/// Base class for graphics outputs.
class KANZI_API GraphicsOutput
{
public:
    /// Constructor.
    explicit GraphicsOutput();

    /// Destructor.
    virtual ~GraphicsOutput() {}

    /// Posts rendering results.
    ///
    /// Implicitly flushes the rendering pipeline and executes all received rendering commands before posting.
    virtual void present() = 0;
    
    /// Returns the width of rendering area in pixels.
    unsigned int getWidth() const
    {
        return m_width;
    }

    /// Returns the height of rendering area in pixels.
    unsigned int getHeight() const
    {
        return m_height;
    }

    /// Returns the orientations of the rendering area.
    enum KzsDisplayOrientationAngle getOrientationAngle() const
    {
        return m_orientationAngle;
    }

    /// Resizes the rendering area.
    void resize(unsigned int width, unsigned int height);

    /// Handles appropriate events.
    virtual void handleEvents(const struct KzsEventQueue* eventQueue) = 0;

protected:
    /// Override function for resize().
    virtual void resizeOverride(unsigned int width, unsigned int height)
    {
        updateSize(width, height);
    }

    /// Updates the rendering area size.
    void updateSize(unsigned int width, unsigned int height)
    {
        m_width = width;
        m_height = height;
    }

private:
    /// Width (in pixels) of the graphics output.
    unsigned int m_width;

    /// Height (in pixels) of the graphics output.
    unsigned int m_height;

    /// Orientation of the rendering area.
    enum KzsDisplayOrientationAngle m_orientationAngle;
};

}

#endif
