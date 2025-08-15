// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPLASH_HPP
#define KZ_SPLASH_HPP

#ifndef SPANSION
#if 1 /* Set to 1 to enable splash screen. The splash screen is actually shown or not based on the Kanzi Studio license that was used when creating .KZB files. */
#define KZU_ENGINE_ENABLE_SPLASH_SCREEN /**< Enables the splash screen. */
#define KZU_ENGINE_SPLASH_DURATION 2000 /**< Splash screen duration in milliseconds. */
#endif
#endif

#ifdef KZU_ENGINE_ENABLE_SPLASH_SCREEN

#include <kanzi/core.ui/graphics2d/brush.hpp>
#include <kanzi/core.ui/graphics2d/brush_renderer.hpp>
#include <kanzi/core/cpp/chrono.hpp>

namespace kanzi
{

// Forward declarations.
class Domain;
class Renderer;
class Renderer3D;
class GraphicsOutput;
class SplashScreen;


/// Splash screen.
/// Handles rendering a splash screen and reserving associated resources.
class SplashScreen
{
public:

    /// Constructor.
    /// Creating a splash screen will implicitly reserve all resources.
    /// \param domain Domain.
    explicit SplashScreen(Domain* domain, chrono::milliseconds timeout);

    /// Update.
    /// \param deltaTime Duration since last call to update().
    void update(chrono::milliseconds deltaTime);

    /// Render.
    /// \param renderer Renderer to use.
    /// \param graphicsOutput Graphics output to render to.
    void render(Renderer3D& renderer, const GraphicsOutput& graphicsOutput);

    /// Clear remains, that might have been stayed from splash screen rendering.
    /// \param renderer Renderer to use.
    void clear(Renderer& renderer);

    /// Returns whether splash screen timeout has elapsed and splash screen could be removed.
    bool isFinished() const;

private:

    /// Perform actual clear.
    /// \param renderer Renderer to use.
    static void clearInternal(Renderer& renderer);

    /// Texture created from image.
    TextureSharedPtr m_texture;

    /// Brush.
    BrushSharedPtr m_brush;

    /// Brush renderer.
    BrushRendererPtr m_brushRenderer;

    /// Is clearing needed?
    bool m_needsClearing;

    /// Splash screen timer countdown.
    chrono::milliseconds m_timer;
};


} // namespace kanzi


#endif

#endif
