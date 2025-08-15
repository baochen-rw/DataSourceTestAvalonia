// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NULL_GRAPHICS_OUTPUT_HPP
#define KZ_NULL_GRAPHICS_OUTPUT_HPP


#include <kanzi/core.ui/graphics/graphics_output.hpp>


namespace kanzi
{

/// NullGraphicsOutput class.
///
/// A graphics output implementation that provides a width and a height, but no actual rendering output.
/// This graphics output can be used as a placeholder, as it works on all platforms.
class KANZI_API NullGraphicsOutput : public GraphicsOutput
{
public:
    /// Constructor.
    explicit NullGraphicsOutput(unsigned int width = 320, unsigned height = 200);

    /// Destructor.
    virtual ~NullGraphicsOutput() KZ_OVERRIDE;

    /// Does nothing.
    virtual void present() KZ_OVERRIDE;

    /// Does nothing.
    void setSwapInterval(int interval);

    /// Does nothing.
    virtual void handleEvents(const struct KzsEventQueue* eventQueue) KZ_OVERRIDE;
};

}

#endif // KZ_NULL_GRAPHICS_OUTPUT_HPP
