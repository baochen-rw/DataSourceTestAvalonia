// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_RENDER_STATE_PROPERTY_NOTIFICATION_HANDLER_HPP
#define KZ_GL_RENDER_STATE_PROPERTY_NOTIFICATION_HANDLER_HPP

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_render_state.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/render_value_property_notification_handler_base.hpp>

namespace kanzi
{

// Forward declarations.
class RenderStatePropertyNotificationHandler;

/// Render state property container shared pointer.
typedef unique_ptr<RenderStatePropertyNotificationHandler> RenderStatePropertyNotificationHandlerPtr;

/// Render value updater for render state.
/// This is an abstract class that is inherited and specialized by property value type.
class RenderStatePropertyNotificationHandler : public RenderValuePropertyNotificationHandlerBase
{
public:
    /// Update render state with new values acquirable from this.
    /// Do not update if dirty flag has not been set (property is not marked as dirty).
    /// \param renderState Render state to update.
    /// \param object Fallback object for property value. Can be 0.
    /// \param material Fallback material for property value.
    void update(GlRenderState& renderState, Object* object, Material& material);

    /// Access handle.
    /// \return Handle.
    int getHandle() const
    {
        return m_handle;
    }

protected:

    /// Empty constructor.
    explicit RenderStatePropertyNotificationHandler() :
        m_handle(0)
    {
    }

    /// Constructor
    /// Has no handle. Should only used for blend mode.
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    explicit RenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node) :
        RenderValuePropertyNotificationHandlerBase(propertyType, node),
        m_handle(0)
    {
    }

    /// Constructor.
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    /// \param handle Handle into the render state.
    /// \param transformation Uniform transformation.
    explicit RenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node, GlRenderState::HandleType handle, ShaderProgram::UniformTransformation transformation) :
        RenderValuePropertyNotificationHandlerBase(propertyType, node, transformation),
        m_handle(handle)
    {
    }

    /// Perform type-specific update.
    /// \param renderState Render state to update.
    /// \param object Fallback object for property value, may be 0 for no object.
    /// \param material Fallback material for property value.
    virtual void updateOverride(GlRenderState& renderState, Object* object, Material& material) = 0;

private:

    /// Handle into the render state.
    GlRenderState::HandleType m_handle;
};

/// Specialized property state and value container for render state.
template <typename T>
class TypedRenderStatePropertyNotificationHandler : public RenderStatePropertyNotificationHandler
{
public:

    /// Empty constructor.
    explicit TypedRenderStatePropertyNotificationHandler()
    {
    }

    /// Constructor
    /// Has no handle. Should only used for blend mode.
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    explicit TypedRenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node) :
        RenderStatePropertyNotificationHandler(propertyType, node)
    {
    }

    /// Constructor.
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    /// \param handle Handle into the render state.
    /// \param transformation Uniform transformation.
    explicit TypedRenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node, GlRenderState::HandleType handle, ShaderProgram::UniformTransformation transformation) :
        RenderStatePropertyNotificationHandler(propertyType, node, handle, transformation)
    {
    }

    /// Create a new render state property notification handler.
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    /// \param handle Handle into the render state.
    /// \param transformation Uniform transformation.
    static RenderStatePropertyNotificationHandlerPtr create(AbstractPropertyType propertyType, Node* node, GlRenderState::HandleType handle, ShaderProgram::UniformTransformation transformation)
    {
        RenderStatePropertyNotificationHandlerPtr notificationHandler(new TypedRenderStatePropertyNotificationHandler<T>(propertyType, node, handle, transformation));

        return KZ_MOVE_RET(RenderStatePropertyNotificationHandlerPtr, notificationHandler);
    }

protected:

    /// RenderStatePropertyNotificationHandler::updateOverride() implementation.
    virtual void updateOverride(GlRenderState& renderState, Object* object, Material& material) KZ_OVERRIDE
    {
        renderState.setValue(getHandle(), acquireRenderValueFromProperty<T>(getPropertyType(), getNode(), object, material, getTransformation()));
    }
};

/// TypedRenderStatePropertyNotificationHandler specialization.
template<>
class TypedRenderStatePropertyNotificationHandler<GraphicsBlendMode> : public RenderStatePropertyNotificationHandler
{
public:
    explicit TypedRenderStatePropertyNotificationHandler()
    {
    }

    explicit TypedRenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node) :
        RenderStatePropertyNotificationHandler(propertyType, node)
    {
    }

    explicit TypedRenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node, GlRenderState::HandleType handle, ShaderProgram::UniformTransformation transformation) :
        RenderStatePropertyNotificationHandler(propertyType, node, handle, transformation)
    {
    }

    static RenderStatePropertyNotificationHandlerPtr create(AbstractPropertyType propertyType, Node* node)
    {
        RenderStatePropertyNotificationHandlerPtr notificationHandler(new TypedRenderStatePropertyNotificationHandler<GraphicsBlendMode>(propertyType, node));

        return KZ_MOVE_RET(RenderStatePropertyNotificationHandlerPtr, notificationHandler);
    }

protected:
    virtual void updateOverride(GlRenderState& renderState, Object* object, Material& material) KZ_OVERRIDE
    {
        renderState.setValue(acquireRenderValueFromProperty<GraphicsBlendMode>(getPropertyType(), getNode(), object, material, getTransformation()));
    }
};

/// TypedRenderStatePropertyNotificationHandler specialization.
template<>
class TypedRenderStatePropertyNotificationHandler<TextureSharedPtr> : public RenderStatePropertyNotificationHandler
{
public:
    explicit TypedRenderStatePropertyNotificationHandler()
    {
    }

    explicit TypedRenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node) :
        RenderStatePropertyNotificationHandler(propertyType, node)
    {
    }

    explicit TypedRenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node, GlRenderState::HandleType handle, ShaderProgram::UniformTransformation transformation) :
        RenderStatePropertyNotificationHandler(propertyType, node, handle, transformation)
    {
    }

    static RenderStatePropertyNotificationHandlerPtr create(AbstractPropertyType propertyType, Node* node, GlRenderState::HandleType handle, ShaderProgram::UniformTransformation transformation)
    {
        RenderStatePropertyNotificationHandlerPtr notificationHandler(new TypedRenderStatePropertyNotificationHandler<TextureSharedPtr>(propertyType, node, handle, transformation));

        return KZ_MOVE_RET(RenderStatePropertyNotificationHandlerPtr, notificationHandler);
    }

protected:
    virtual void updateOverride(GlRenderState& renderState, Object* object, Material& material) KZ_OVERRIDE
    {
        renderState.setValue(getHandle(), acquireRenderValueFromProperty<TextureSharedPtr>(getPropertyType(), getNode(), object, material, getTransformation()));
    }
};

}

#endif
