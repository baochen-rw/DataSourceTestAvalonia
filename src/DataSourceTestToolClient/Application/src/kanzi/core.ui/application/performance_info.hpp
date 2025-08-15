// Copyright 2015-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_PERFORMANCE_INFO_HPP
#define KZ_PERFORMANCE_INFO_HPP

#include <kanzi/core.ui/domain/domain.hpp>
#include <kanzi/core.ui/font/kzu_font_base.h>
#include <kanzi/core.ui/node/camera.hpp>
#include <kanzi/core.ui/application/performance_info_properties.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/brush_renderer.hpp>
#include <kanzi/core/profiling/profiling.hpp>

// Forward declarations.
struct KzuMaterial;
struct KzuTextFormat;
struct KzuTextRenderer;
struct KzuEngine;

namespace kanzi
{

class Domain;
class MaterialBrush;
class Renderer;
class Screen;
class ResourceManager;
typedef shared_ptr<MaterialBrush> MaterialBrushSharedPtr;
typedef shared_ptr<Screen> ScreenSharedPtr;

/// HUD class allows drawing information on top of tests.
class KANZI_API PerformanceInfo
{
public:
    /// Constructor for HUD.
    explicit PerformanceInfo(Domain* domain, KzuEngine* engine, ScreenSharedPtr screen, const PerformanceInfoProperties& properties);

    /// Draws the FPS information on the screen.
    void drawFps();

    /// Draws performance related information on the screen.
    void drawInfo();

    /// Draws profiling graphs.
    void drawProfilingInfo();

    /// Sets the font color for drawing the HUD info
    /// \param fontColor The ColorRGBA color value of the font
    void setFontColor(const ColorRGBA& fontColor);

    /// Sets the color of the lines used to draw the performance graphs
    /// \param lineColor The ColorRGBA color value for the graph lines
    void setLineColor(const ColorRGBA& lineColor);

    /// Sets the border color of the HUD info boxes
    /// \param borderColor The ColorRGBA color value for the graph borders
    void setBorderColor(const ColorRGBA& borderColor);

    /// Set the text top-left corner position.
    /// \param x Text x-position on the screen.
    /// \param y Text y-position on the screen.
    void setTextTopLeft(int x, int y);

private:
    void drawText(Renderer3D* renderer3D, const char* text);

    /// Domain.
    Domain* m_domain;

    /// Engine.
    KzuEngine* m_engine;

    /// Text format for FPS text.
    shared_ptr<KzuTextFormat> m_textFormat;

    /// Text format for graph text.
    shared_ptr<KzuTextFormat> m_graphTextFormat;

    /// Material brush for rendering the text.
    BrushSharedPtr m_textBrush;

    /// Brush renderer for rendering the text.
    BrushRendererPtr m_textBrushRenderer;

    /// Font for rendering.
    FontSharedPtr m_font;

    /// Material for rendering the graphs
    MaterialSharedPtr m_graphMaterial;

    /// Graph line color
    ColorRGBA m_lineColor;

    /// Graph border color
    ColorRGBA m_borderColor;

    /// Text offset in x-direction.
    int m_textOffsetX;

    /// Text offset in y-direction.
    int m_textOffsetY;
};

}

#endif // KZ_PERFORMANCE_INFO_HPP

#endif
