// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_GRAPHICS_LOG_SCOPE_HPP
#define KZ_GL_GRAPHICS_LOG_SCOPE_HPP

// Forward declarations.
struct KzsGlGraphicsContext;

namespace kanzi
{

class Renderer;

/// Scoped OpenGL log enable/disabler.
/// When scope is left, earlier OpenGL logging status is restored.
class GlGraphicsLogScope
{
public:
    explicit GlGraphicsLogScope(Renderer& renderer, bool enable);
    ~GlGraphicsLogScope();

private:
    GlGraphicsLogScope(const GlGraphicsLogScope&);
    GlGraphicsLogScope& operator=(const GlGraphicsLogScope&);

private:
    KzsGlGraphicsContext* m_context;
    bool m_previousState;
    bool m_previousDump;
};

}

#endif
