// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_OUTPUT_HPP
#define KZ_GL_GRAPHICS_OUTPUT_HPP

#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core.ui/graphics/graphics_output.hpp>
#include <kanzi/core.ui/platform/windowing/common/kzs_native_handles.h>
#include <kanzi/core.ui/platform/graphics_context/common/kzs_surface_configuration.h>



// Forward declaration.
struct KzsDesktop;
struct KzsDisplay;
struct KzsWindow;
struct KzsSurface;
struct NativeDesktopProperties;

namespace kanzi
{

class Domain;

// Forward declarations.
class GlGraphicsOutput;

/// GlGraphicsOutput shared pointer type.
typedef shared_ptr<GlGraphicsOutput> GlGraphicsOutputSharedPtr;

/// GlGraphicsOutput class.
///
/// A graphics output implementation that provides basic GL rendering output.
class KANZI_API GlGraphicsOutput : public GraphicsOutput
{
public:
    /// Constructor.
    explicit GlGraphicsOutput(const struct KzsSurfaceProperties* surfaceProperties, const NativeWindowProperties* windowProperties, const NativeDesktopProperties* desktopProperties);

    /// Constructor.
    explicit GlGraphicsOutput(NativeWindowHandle handle, const struct KzsSurfaceProperties* surfaceProperties, const NativeWindowProperties* windowProperties, const NativeDesktopProperties* desktopProperties);

    /// Destructor.
    virtual ~GlGraphicsOutput() KZ_OVERRIDE;

    /// Posts rendering results.
    ///
    /// Implicitly flushes the rendering pipeline and executes all received rendering commands before posting.
    /// \seealso setSwapInterval().
    virtual void present() KZ_OVERRIDE;

    /// Sets the swap interval of the underlying graphics implementation.
    ///
    /// \param interval Specifies the minimum number of video frame periods per buffer swap.
    /// Negative interval values are reserved for platform-specific special cases.
    /// \seealso swapBuffers().
    void setSwapInterval(int interval);

    /// Handles the window resize event.
    virtual void handleEvents(const struct KzsEventQueue* eventQueue) KZ_OVERRIDE;

    /// Logs the properties of the graphics output.
    void logProperties() const;

    /// Logs the extensions of the graphics context.
    void logExtensions() const;

    /// Sets the window title, if possible.
    void setWindowTitle(const string& title);

    struct KzsDesktop* getDesktop() const;
    struct KzsWindow* getWindow() const;
    struct KzsSurface* getSurface() const;

    /// Access display by index.
    /// \param index Display index to access.
    /// \return Display at given index or 0.
    struct KzsDisplay* getDisplay(size_t index) const;

    KzsGraphicsContextAPI getGraphicsContextAPI() const;

    /// Replaces the native window associated to the graphics output.
    /// \param handle Handle to the native window.
    void replaceNativeWindow(NativeWindowHandle handle);

    /// Removes the native window associated to the graphics output.
    /// Leaves the graphics output to unusable state. This function is only needed when a native
    /// window is lost temporarily and will be replaced later.
    void deleteNativeWindow();

    /// Gets the handle of the GL context associated to the graphics output.
    /// \return The handle of associated graphics context object.
    void* getContextHandle() const;

    /// Gets the handle of display associated to the the graphics output.
    /// \return The handle of display associated to the graphics output.
    void* getDisplayHandle() const;

protected:
    /// Resizes the rendering area.
    virtual void resizeOverride(unsigned int width, unsigned int height) KZ_OVERRIDE;

private:
    /// Constructor delegatee.
    void initialize(const struct KzsSurfaceProperties* surfaceProperties, const struct NativeDesktopProperties* desktopProperties);

    /// Destructor delegatee.
    void uninitialize();

    /// Resizes the surface and rendering area to match window size.
    void updateSizeFromWindow();

    struct KzsSurfaceConfiguration* m_surfaceConfiguration; ///< Surface configuration for application.
    struct KzsDesktop* m_desktop;       ///< Desktop for application.

    /// Display container.
    typedef vector<struct KzsDisplay*> DisplayContainer;

    /// List of application displays.
    DisplayContainer m_displays;

    /// System-dependent window implementation.
    struct KzsWindow* m_window;

    /// System-dependent surface implementation.
    struct KzsSurface* m_surface;
};

}

#endif
