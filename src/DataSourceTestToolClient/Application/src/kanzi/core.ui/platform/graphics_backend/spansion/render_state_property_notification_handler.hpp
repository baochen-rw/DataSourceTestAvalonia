// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SPANSION_RENDER_STATE_PROPERTY_NOTIFICATION_HANDLER_HPP
#define KZ_SPANSION_RENDER_STATE_PROPERTY_NOTIFICATION_HANDLER_HPP


//#include "gl_render_state.hpp"
#include "render_state_resource_container.hpp"

#include <kanzi/node/node_property_notification_handler.hpp>


// Forward declaration.

namespace kanzi
{

class RenderState;
class RenderStatePropertyNotificationHandler;
class Renderer;


/// Render state property container shared pointer.
typedef shared_ptr<RenderStatePropertyNotificationHandler> RenderStatePropertyContainerSharedPtr;


/// Property state and value container for render state.
class RenderStatePropertyNotificationHandler : public NodePropertyNotificationHandler
{
public:
    /// Empty constructor.
    explicit RenderStatePropertyNotificationHandler() {}

    /// Constructor
    ///
    /// Has no handle. Should only used for blend mode.
    ///
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    explicit RenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node) :
             NodePropertyNotificationHandler(propertyType, node),
             m_dirty(true) {}

    /// Constructor.
    ///
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    /// \param renderState Render state to extract extra information from.
    explicit RenderStatePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node, size_t handle) :
             NodePropertyNotificationHandler(propertyType, node),
             m_handle(handle),
             m_dirty(true) {}
#if 0
    /// Acquire default value for this handler.
    ///
    /// \param object Fallback object for property value.
    /// \param material Fallback material for property value.
    template<typename T> T acquirePropertyValue(Object& object, Material& material) const;
#endif
    /// AbstractPropertyNotificationHandler::onPropertyChanged() implementation.
    virtual void onPropertyChanged(KzuPropertyNotificationReason) KZ_OVERRIDE;

    /// Clear dirty flag.
    void clearDirtyFlag()
    {
        m_dirty = false;
    }
    /// Is the container dirty?
    ///
    /// \return True if dirty, false if not.
    bool isDirty() const
    {
        return m_dirty;
    }

    /// Access handle.
    ///
    /// \return Handle.
    size_t getHandle() const
    {
        return m_handle;
    }

    /// Set dirty flag.
    void setDirtyFlag()
    {
        m_dirty = true;
    }

private:
    size_t m_handle; ///< Handle into the render state.
    bool m_dirty;    ///< Is this property dirty and does it need updating.
};

#if 0

/// Update render state with new values acquirable from this.
///
/// \param renderState Render state to update.
/// \param object Fallback object for property value.
/// \param material Fallback material for property value.
template<typename T>
void updateRenderState(GlRenderState& renderState, RenderStatePropertyNotificationHandler& handler, Object& object, Material& material)
{
    if(!handler.isDirty())
    {
        return;
    }
    renderState.setValue(handler.getHandle(), handler.acquirePropertyValue<T>(object, material));
    handler.clearDirtyFlag();
}


template<> void updateRenderState<GraphicsBlendMode>(GlRenderState& renderState, RenderStatePropertyNotificationHandler& handler, Object& object, Material& material);
template<> void updateRenderState<RenderStateResourceContainer>(GlRenderState& renderState, RenderStatePropertyNotificationHandler& handler, Object& object, Material& material);


template<> bool RenderStatePropertyNotificationHandler::acquirePropertyValue<bool>(Object& object, Material& material) const;
template<> GraphicsBlendMode RenderStatePropertyNotificationHandler::acquirePropertyValue<GraphicsBlendMode>(Object& object, Material& material) const;
template<> int RenderStatePropertyNotificationHandler::acquirePropertyValue<int>(Object& object, Material& material) const;
template<> float RenderStatePropertyNotificationHandler::acquirePropertyValue<float>(Object& object, Material& material) const;
template<> KzcColorRGBA RenderStatePropertyNotificationHandler::acquirePropertyValue<KzcColorRGBA>(Object& object, Material& material) const;
template<> KzcVector2 RenderStatePropertyNotificationHandler::acquirePropertyValue<KzcVector2>(Object& object, Material& material) const;
template<> KzcVector3 RenderStatePropertyNotificationHandler::acquirePropertyValue<KzcVector3>(Object& object, Material& material) const;
template<> KzcVector4 RenderStatePropertyNotificationHandler::acquirePropertyValue<KzcVector4>(Object& object, Material& material) const;
template<> KzcMatrix3x3 RenderStatePropertyNotificationHandler::acquirePropertyValue<KzcMatrix3x3>(Object& object, Material& material) const;
template<> KzcMatrix4x4 RenderStatePropertyNotificationHandler::acquirePropertyValue<KzcMatrix4x4>(Object& object, Material& material) const;
template<> Texture* RenderStatePropertyNotificationHandler::acquirePropertyValue<Texture*>(Object& object, Material& material) const;
template<> RenderStateResourceContainer RenderStatePropertyNotificationHandler::acquirePropertyValue<RenderStateResourceContainer>(Object& object, Material& material) const;

#endif

}


#endif
