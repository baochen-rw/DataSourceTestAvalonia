// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDER_VALUE_PROPERTY_NOTIFICATION_HANDLER_HPP
#define KZ_RENDER_VALUE_PROPERTY_NOTIFICATION_HANDLER_HPP

#include <kanzi/core/cpp/utility.hpp>

#include <kanzi/core.ui/platform/graphics_backend/gl/gl_render_value.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/render_value_property_notification_handler_base.hpp>

namespace kanzi
{

/// Render value updater for individual render values.
template<typename T>
class RenderValuePropertyNotificationHandler : public RenderValuePropertyNotificationHandlerBase
{
public:

    /// Empty constructor.
    explicit RenderValuePropertyNotificationHandler()
    {
    }

    /// Constructor
    ///
    /// Has no handle. Should only used for blend mode.
    ///
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    explicit RenderValuePropertyNotificationHandler(AbstractPropertyType propertyType, Node* node) :
        RenderValuePropertyNotificationHandlerBase(propertyType, node)
    {
    }

    /// Move constructor.
    /// \param other Source object.
    RenderValuePropertyNotificationHandler(KZ_RV_REF(RenderValuePropertyNotificationHandler) other) :
        RenderValuePropertyNotificationHandlerBase(KZ_MOVE_BASE(RenderValuePropertyNotificationHandlerBase, other))
    {
    }

    /// Update render value with new values acquirable from this.
    /// Do not update if dirty flag has not been set (property is not marked as dirty).
    /// \param renderState Render state to update.
    /// \param object Fallback object for property value. Can be 0.
    /// \param material Fallback material for property value.
    void update(GlRenderValue<T>& value, Object* object, Material& material)
    {
        // If not dirty, do nothing.
        if (!isDirty())
        {
            return;
        }

        // Call type-specific update.
        value.set(acquireRenderValueFromProperty<T>(getPropertyType(), getNode(), object, material, getTransformation()));

        // Clear dirty flag.
        setDirty(false);
    }

    /// Assignment operator.
    /// \param other Source object.
    RenderValuePropertyNotificationHandler& operator=(KZ_RV_REF(RenderValuePropertyNotificationHandler) other)
    {
        RenderValuePropertyNotificationHandlerBase::operator=(KZ_MOVE_BASE(RenderValuePropertyNotificationHandlerBase, other));
        return *this;
    }

private:

    KZ_MOVABLE_BUT_NOT_COPYABLE(RenderValuePropertyNotificationHandler)
};

}

#endif // KZ_RENDER_VALUE_PROPERTY_NOTIFICATION_HANDLER_HPP