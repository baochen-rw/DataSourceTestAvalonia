// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_RENDER_CONTEXT_STACK_HPP
#define KZ_GL_RENDER_CONTEXT_STACK_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/renderer.hpp>
#include <kanzi/core/cpp/tuple.hpp>

#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/math/vector4.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core.ui/graphics2d/texture.hpp>
#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>

namespace kanzi
{

class Renderer3D;
class RenderPass;
class CompositionStack;
typedef shared_ptr<RenderPass> RenderPassSharedPtr;

/// Composition stack shared pointer.
typedef unique_ptr<CompositionStack> CompositionStackPtr;

/// Composition stack for managing current render context.
///
/// The stack has no ownership over the stored render targets - they will not be reserved or deleted.
class KANZI_API CompositionStack
{
public:

#ifndef SPANSION
    /// Composition target handle for OpenGL.
    typedef unsigned int NativeCompositionTargetHandle;
#else
    typedef Texture* NativeCompositionTargetHandle;
#endif

private:

    /// Template class for handling state arrays.
    template<typename T>
    class StateStack
    {
        /// Enumeration for keeping track with default state.
        enum DefaultState
        {
            /// No default state applied.
            DefaultStateNone = 0,

            /// 2D default state applied.
            DefaultState2D,

            /// 3D default state applied.
            DefaultState3D
        };

    public:
        explicit StateStack() :
            m_appliedState(0),
            m_defaultState(DefaultStateNone)
        {
        }

        /// Apply the topmost element.
        /// If no elements present, apply default 2D rendering state.
        void apply2D(Renderer& renderer)
        {
            // If stack is empty, apply default state.
            if (empty())
            {
                kzAssert(m_appliedState == 0);

                if (m_defaultState == DefaultState2D)
                {
                    return;
                }

                T::applyDefaultState2D(renderer);

                m_defaultState = DefaultState2D;
                return;
            }

            // Do not do anything if already applied.
            if (isApplied())
            {
                return;
            }

            T& currentState = back();

            currentState.apply(renderer);

            m_appliedState = &currentState;
            m_defaultState = DefaultStateNone;
        }

        /// Apply the topmost element.
        /// If no elements present, apply default 3D rendering state.
        void apply3D(Renderer& renderer)
        {
            // If stack is empty, apply default state.
            if (empty())
            {
                kzAssert(m_appliedState == 0);

                if (m_defaultState == DefaultState3D)
                {
                    return;
                }

                T::applyDefaultState3D(renderer);

                m_defaultState = DefaultState3D;
                return;
            }

            // Do not do anything if already applied.
            if (isApplied())
            {
                return;
            }

            T& currentState = back();

            currentState.apply(renderer);

            m_appliedState = &currentState;
            m_defaultState = DefaultStateNone;
        }

        /// Access last element.
        T& back()
        {
            kzAssert(!empty());

            return m_stack.back();
        }
        /// Access last element (const version).
        const T& back() const
        {
            kzAssert(!empty());

            return m_stack.back();
        }

        /// Tells if the stack is empty.
        bool empty() const
        {
            return m_stack.empty();
        }

        /// Invalidate state.
        /// Only be used when stack applies some other state than any of the default states.
        void invalidateState()
        {
            m_appliedState = 0;
            m_defaultState = DefaultStateNone;
        }

        /// Push new element into the stack.
        void push(T state)
        {
            m_stack.push_back(state);
        }

        /// Pop element from the stack.
        void pop()
        {
            if (isApplied())
            {
                m_appliedState = 0;
            }
            m_stack.pop_back();
        }

    private:
        /// Tell if the applied state is currently at the top of the stack.
        bool isApplied() const
        {
            return (&(back()) == m_appliedState);
        }

        /// Stack for holding 
        vector<T> m_stack;

        /// Pointer for last applied state.
        T* m_appliedState;

        /// Default state applied.
        DefaultState m_defaultState;
    };

    /// Blend state.
    struct ColorBlendState
    {
        /// Blend mode.
        GraphicsBlendMode blendMode;

        /// Graphics write mode.
        GraphicsColorWriteMode colorWriteMode;

        /// Constructor.
        ColorBlendState(GraphicsBlendMode blendMode, GraphicsColorWriteMode colorWriteMode) :
            blendMode(blendMode),
            colorWriteMode(colorWriteMode)
        {
        }

        /// Apply blend mode state.
        void apply(Renderer& renderer);

        /// Apply default state for 2D rendering (used when stack is empty).
        static void applyDefaultState2D(Renderer& renderer);

        /// Apply default state for 3D rendering (used when stack is empty).
        static void applyDefaultState3D(Renderer& renderer);
    };

    /// Composition target state.
    struct CompositionState
    {
        /// Composition target handle.
        NativeCompositionTargetHandle handle;

        /// Rendering context size.
        Vector2 size;

        /// Viewport.
        Vector4 viewport;

        /// Scissor rectangle.
        optional<Vector4> scissor;

        /// Viewport in device coordinates. Calculated upon apply.
        ViewportRectangle viewportDeviceCoordinates;

        /// Scissor in device coordinates. Calculated upon apply.
        optional<ViewportRectangle> scissorDeviceCoordinates;

        /// Flag for device coordinates being calculated or not.
        bool deviceCoordinatesCalculated;

        /// Constructor using specified composition target.
        /// \param handle Composition target handle.
        /// \param size Composition target size.
        /// \param viewport Viewport area.
        /// \param scissor Scissor area.
        explicit CompositionState(NativeCompositionTargetHandle handle, Vector2 size, Vector4 viewport, optional<Vector4> scissor) :
            handle(handle),
            size(size),
            viewport(viewport),
            scissor(scissor),
            deviceCoordinatesCalculated(false)
        {
        }

        /// Applies the state.
        void apply(Renderer& renderer);

        /// Apply default state for 2D rendering (used when stack is empty).
        static void applyDefaultState2D(Renderer& renderer);

        /// Apply default state for 3D rendering (used when stack is empty).
        static void applyDefaultState3D(Renderer& renderer);

        /// Calculates device coordinates for current topmost viewport and composition states.
        void calculateDeviceCoordinates();

    private:
        /// Convert viewport coordinates to device coordinates.
        /// \param viewport Viewport to convert.
        /// \param contextSize Current render context size.
        /// \param Tuple consisting of the viewport rectangle and a boolean indicating whether or not the whole contexts size is used.
        static tuple<ViewportRectangle, bool> convertViewportDeviceCoordinates(Vector4 viewport, Vector2 contextSize);
    };

    /// Depth/Stencil state.
    struct DepthStencilState
    {
        /// Depth testing mode. Use #GraphicsCompareFunctionDisabled for turning off depth test completely.
        GraphicsCompareFunction depthFunc;

        /// Depth write enabled or not.
        bool depthWrite;

        /// Stencil compare function. Use #GraphicsCompareFunctionDisabled for turning off stencil test completely.
        GraphicsCompareFunction stencilFunc;

        /// Stencil reference value.
        unsigned int referenceValue;

        /// Stencil mask value.
        unsigned int maskValue;

        /// Operation for stencil test failing.
        GraphicsStencilOperation stencilFail;

        /// Operation for stencil test passing but depth test failing.
        GraphicsStencilOperation stencilPassDepthFail;

        /// Operation for stencil and depth tests passing.
        GraphicsStencilOperation stencilPassDepthPass;

        /// Stencil write enabled or not.
        bool stencilWrite;

        /// Constructor.
        /// \param depthFunc Depth test function.
        /// \param depthWrite Depth write enabled?
        /// \param stencilFunc Stencil test function to use.
        /// \param referenceValue Stencil reference value.
        /// \param maskValue Stencil mask value.
        /// \param stencilFail Operation for stencil failing.
        /// \param stencilPassDepthFail Operation for stencil passing but depth failing.
        /// \param stencilPassDepthPass Operation for stencil and depth passing.
        /// \param stencilWrite Stencil write enabled?
        explicit DepthStencilState(GraphicsCompareFunction depthFunc, bool depthWrite, GraphicsCompareFunction stencilFunc, unsigned int referenceValue,
                                   unsigned int maskValue, GraphicsStencilOperation stencilFail, GraphicsStencilOperation stencilPassDepthFail,
                                   GraphicsStencilOperation stencilPassDepthPass, bool stencilWrite) :
            depthFunc(depthFunc),
            depthWrite(depthWrite),
            stencilFunc(stencilFunc),
            referenceValue(referenceValue),
            maskValue(maskValue),
            stencilFail(stencilFail),
            stencilPassDepthFail(stencilPassDepthFail),
            stencilPassDepthPass(stencilPassDepthPass),
            stencilWrite(stencilWrite)
        {
        }

        /// Apply blend mode state.
        void apply(Renderer& renderer);

        /// Apply default state for 2D rendering (used when stack is empty).
        static void applyDefaultState2D(Renderer& renderer);

        /// Apply default state for 3D rendering (used when stack is empty).
        static void applyDefaultState3D(Renderer& renderer);
    };

    /// Rasterization state.
    struct RasterizationState
    {
        /// Culling mode.
        GraphicsCullMode cullMode;

        /// Constructor.
        explicit RasterizationState(GraphicsCullMode cullMode) :
            cullMode(cullMode)
        {
        }

        /// Apply rasterization state.
        void apply(Renderer& renderer);

        /// Apply default state for 2D rendering (used when stack is empty).
        static void applyDefaultState2D(Renderer& renderer);

        /// Apply default state for 3D rendering (used when stack is empty).
        static void applyDefaultState3D(Renderer& renderer);
    };

public:
    /// Constructor.
    explicit CompositionStack()
    {
    }

    /// Constructor.
    ///
    /// \param handle Composition target handle.
    /// \param size Composition target size.
    explicit CompositionStack(NativeCompositionTargetHandle handle, Vector2 size)
    {
        pushComposition(handle, size);
    }

    /// Constructor.
    ///
    /// \param handle Composition target handle.
    /// \param size Composition target size.
    /// \param viewport Viewport area.
    /// \param scissor Scissor area.
    explicit CompositionStack(NativeCompositionTargetHandle handle, Vector2 size, Vector4 viewport, optional<Vector4> scissor)
    {
        pushComposition(handle, size, viewport, scissor);
    }

    /// Tells if composition stack is empty.
    /// Empty composition stack has no states whatsoever.
    bool isCompositionStackEmpty() const
    {
        return m_compositionStack.empty();
    }

    /// Push blend state into the blend stack.
    /// Using nullopt with any parameter will take the default value or the last value pushed.
    /// \param blendMode Blend mode.
    /// \param colorWriteMode Color write mode.
    void pushColorBlend(optional<GraphicsBlendMode> blendMode, optional<GraphicsColorWriteMode> colorWriteMode);
    /// Pop blend state from blend stack.
    void popColorBlend()
    {
        m_colorBlendStack.pop();
    }

    /// Push a composition target into the composition stack.
    /// \param handle Composition target handle.
    /// \param size Composition target size.
    void pushComposition(NativeCompositionTargetHandle handle, Vector2 size);
    /// Push a composition target into the composition stack.
    /// \param texture Composition target.
    void pushComposition(Texture& texture);
    /// Push a composition target into the composition stack.
    /// \param texture Composition target.
    /// \param size Composition target size.
    void pushComposition(Texture& texture, Vector2 size);
    /// Push a framebuffer into the composition stack.
    /// \param framebuffer Framebuffer.
    /// \param size Composition target size.
    void pushComposition(Framebuffer& framebuffer, Vector2 size);
    /// Push a viewport and/or scissor onto composition stack.
    /// \param viewport optional viewport area.
    /// \param scissor optional scissor area.
    void pushComposition(optional<Vector4> viewport, optional<Vector4> scissor);
    /// Push a composition target and a viewport into the composition stack.
    /// \param texture Composition target.
    /// \param viewport Viewport area.
    /// \param scissor Scissor area.
    void pushComposition(Texture& texture, Vector4 viewport, optional<Vector4> scissor);
    /// Push a composition target and a viewport into the composition stack.
    /// \param handle Composition target handle.
    /// \param size Composition target size.
    /// \param viewport Viewport area.
    /// \param scissor Scissor area.
    void pushComposition(NativeCompositionTargetHandle handle, Vector2 size, Vector4 viewport, optional<Vector4> scissor)
    {
        m_compositionStack.push(CompositionState(handle, size, viewport, scissor));
    }
    /// Pop a composition target state from the stack.
    void popComposition()
    {
        m_compositionStack.pop();
    }

    /// Push depth stencil state.
    /// Using nullopt with any parameter will take the default value or the last value pushed.
    /// \param depthFunc Depth testing function.
    /// \param depthWrite Depth write enabled?
    /// \param stencilfunc Stencil function.
    /// \param referenceValue Stencil reference value.
    /// \param maskValue Stencil mask value.
    /// \param stencilFail Operation for stencil fail.
    /// \param stencilPassDepthFail Operation for stencil pass but depth fail.
    /// \param stencilPassDepthPass Operation for stencil and depth pass.
    /// \param stencilWrite Stencil write enabled?
    void pushDepthStencil(optional<GraphicsCompareFunction> depthFunc, optional<bool> depthWrite,
        optional<GraphicsCompareFunction> stencilFunc, optional<unsigned int> referenceValue,
        optional<unsigned int> maskValue, optional<GraphicsStencilOperation> stencilFail,
        optional<GraphicsStencilOperation> stencilPassDepthFail, optional<GraphicsStencilOperation> stencilPassDepthPass,
        optional<bool> stencilWrite);
    /// Pop a depth stencil state from the stack.
    void popDepthStencil()
    {
        m_depthStencilStack.pop();
    }

    /// Push rasterization state.
    /// Using nullopt with any parameter will take the default value or the last value pushed.
    /// \param cullMode Culling mode.
    void pushRasterization(optional<GraphicsCullMode> cullMode);
    /// Pop a rasterization state from the stack.
    void popRasterization()
    {
        m_rasterizationStack.pop();
    }

#ifndef SPANSION
    /// Get the debug composer used by this render context stack.
    RenderPassSharedPtr getDebugComposer() const
    {
        return m_debugComposer;
    }
    /// Set the debug composer to be used by this render context stack.
    void setDebugComposer(RenderPassSharedPtr debugComposer)
    {
        m_debugComposer = debugComposer;
    }
#endif

    /// Apply the topmost render context for 2D rendering.
    /// \param renderer Renderer to use.
    void apply2D(Renderer3D& renderer);

    /// Apply 3D rendering state.
    /// Default values will be used for those states with empty stacks.
    void apply3D(Renderer3D& renderer);

    /// Apply for 2D perspective rendering.
    ///
    /// TODO: fix everything about this.
    ///
    /// \param renderer Renderer to use.
    /// \param worldPerspectiveOffset World perspective offset provided by 2D rendering.
    void applyPerspective2D(Renderer3D& renderer, const Vector4* worldPerspectiveOffset);

    /// Get current composition target handle.
    /// This function exists for tests.
    /// \return Framebuffer handle.
    optional<NativeCompositionTargetHandle> peekCompositionTargetHandle() const
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        return m_compositionStack.back().handle;
    }

    /// Get current composition target size.
    /// This function exists for tests.
    /// \return Composition target size.
    optional<Vector2> peekRenderContextSize() const
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        return m_compositionStack.back().size;
    }

    /// Get current scissor.
    /// \return Scissor in Node2D coordinates or an empty optional if no scissor is set.
    optional<Vector4> peekScissor() const
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        return m_compositionStack.back().scissor;
    }

    /// Get current viewport.
    /// \return Viewport in Node2D coordinates or an empty optional if composition stack is empty.
    optional<Vector4> peekViewport() const
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        return m_compositionStack.back().viewport;
    }

    /// Get current viewport offset.
    /// \return Offset of topmost viewport or an empty optional if composition stack is empty.
    optional<Vector2> peekViewportOffset() const
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        const CompositionState& state = m_compositionStack.back();

        return Vector2(state.viewport.getX(), state.viewport.getY());
    }

    /// Get current viewport size.
    /// Disregards scissor.
    /// \return Size of topmost viewport or an empty optional if composition stack is empty.
    optional<Vector2> peekViewportSize() const
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        const CompositionState& state = m_compositionStack.back();

        return Vector2(state.viewport.getZ(), state.viewport.getW());
    }

    /// Get current viewport in device coordinates.
    /// This function exists for tests.
    /// \return Device coordinate viewport.
    optional<ViewportRectangle> peekViewportDeviceCoordinates()
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        // Recalculating device coordinates is expensive, but this function shouldn't be called outside tests in any case.
        CompositionState& state = m_compositionStack.back();

        state.calculateDeviceCoordinates();

        return state.viewportDeviceCoordinates;
    }

    /// Get current device coordinate scissor.
    /// This function exists for tests.
    /// \return Device coordinate viewport.
    optional<ViewportRectangle> peekScissorDeviceCoordinates()
    {
        if (m_compositionStack.empty())
        {
            return nullopt;
        }

        // Recalculating device coordinates is expensive, but this function shouldn't be called outside tests in any case.
        CompositionState& state = m_compositionStack.back();

        state.calculateDeviceCoordinates();

        return state.scissorDeviceCoordinates;
    }

    /// Apply blend stack.
    /// If stack is empty, default 2D blend settings are used.
    /// \param renderer Renderer to use.
    void applyColorBlend2D(Renderer& renderer)
    {
        m_colorBlendStack.apply2D(renderer);
    }
    /// Apply blend stack.
    /// If stack is empty, default 3D blend settings are used.
    /// \param renderer Renderer to use.
    void applyColorBlend3D(Renderer& renderer)
    {
        m_colorBlendStack.apply3D(renderer);
    }
    /// Invalidate color/blend stack state.
    /// Should only be called when manually modifying color/blend state so that applying again will not assume no changes.
    void invalidateColorBlend()
    {
        m_colorBlendStack.invalidateState();
    }

    /// Apply composition stack.
    /// Default composition state for 2D is not defined.
    /// \param renderer Renderer to use.
    void applyComposition2D(Renderer& renderer)
    {
        m_compositionStack.apply2D(renderer);
    }
    /// Apply composition stack.
    /// Default composition state for 2D is not defined.
    /// \param renderer Renderer to use.
    void applyComposition3D(Renderer& renderer)
    {
        m_compositionStack.apply3D(renderer);
    }
    /// Invalidate composition stack state.
    /// Should only be called when manually modifying composition state so that applying again will not assume no changes.
    void invalidateComposition()
    {
        m_compositionStack.invalidateState();
    }

    /// Apply depth/stencil stack
    /// If stack is empty, default depth/stencil settings are used.
    /// \param renderer Renderer to use.
    void applyDepthStencil2D(Renderer& renderer)
    {
        m_depthStencilStack.apply2D(renderer);
    }
    /// Apply depth/stencil stack
    /// If stack is empty, default depth/stencil settings are used.
    /// \param renderer Renderer to use.
    void applyDepthStencil3D(Renderer& renderer)
    {
        m_depthStencilStack.apply3D(renderer);
    }
    /// Invalidate depth/stencil stack state.
    /// Should only be called when manually modifying depth/stencil state so that applying again will not assume no changes.
    void invalidateDepthStencil()
    {
        m_depthStencilStack.invalidateState();
    }

    /// Apply rasterization stack.
    /// If stack is empty, default rasterization settings are used.
    /// \param renderer Renderer to use.
    void applyRasterization2D(Renderer& renderer)
    {
        m_rasterizationStack.apply2D(renderer);
    }
    /// Apply rasterization stack.
    /// If stack is empty, default rasterization settings are used.
    /// \param renderer Renderer to use.
    void applyRasterization3D(Renderer& renderer)
    {
        m_rasterizationStack.apply3D(renderer);
    }
    /// Invalidate rasterization stack state.
    /// Should only be called when manually modifying rasterization state so that applying again will not assume no changes.
    void invalidateRasterization()
    {
        m_rasterizationStack.invalidateState();
    }

    /// Invalidate all distinct stacks.
    /// User should not need to call this function.
    /// Intended to be called along #Renderer3D::reset() to signify context change.
    void invalidateAllState()
    {
        invalidateColorBlend();
        invalidateComposition();
        invalidateDepthStencil();
        invalidateRasterization();
    }

private:
    /// Stack for blend information.
    StateStack<ColorBlendState> m_colorBlendStack;

    /// Stack for composition information.
    StateStack<CompositionState> m_compositionStack;

    /// Stack for depth/stencil information.
    StateStack<DepthStencilState> m_depthStencilStack;

    /// Stack for rasterization information.
    StateStack<RasterizationState> m_rasterizationStack;

#ifndef SPANSION
    /// Debug composer to use (if set).
    RenderPassSharedPtr m_debugComposer;
#endif
};

}

#endif