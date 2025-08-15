// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDER_VALUE_PROPERTY_NOTIFICATION_HANDLER_BASE_HPP
#define KZ_RENDER_VALUE_PROPERTY_NOTIFICATION_HANDLER_BASE_HPP

#include <kanzi/core.ui/graphics3d/graphics_enums.hpp>
#include <kanzi/core.ui/graphics3d/material.hpp>
#include <kanzi/core.ui/node/node_property_notification_handler.hpp>
#include <kanzi/core.ui/platform/graphics_backend/gl/shader.hpp>

namespace kanzi
{

/// Base class for notification handlers for render values and render state values (through handles).
class RenderValuePropertyNotificationHandlerBase : public NodePropertyNotificationHandler
{
public:

    /// Is the container dirty?
    ///
    /// \return True if dirty, false if not.
    bool isDirty() const
    {
        return m_dirty;
    }
    /// Set dirty flag state.
    /// \param enabled New dirty flag state.
    void setDirty(bool enabled)
    {
        m_dirty = enabled;
    }

    /// Assignment operator.
    /// \param other Source object.
    RenderValuePropertyNotificationHandlerBase& operator=(KZ_RV_REF(RenderValuePropertyNotificationHandlerBase) other)
    {
        NodePropertyNotificationHandler::operator=(kanzi::move(other));
        m_dirty = other.m_dirty;
        return *this;
    }

private:

    KZ_MOVABLE_BUT_NOT_COPYABLE(RenderValuePropertyNotificationHandlerBase)

protected:

    /// Empty constructor.
    explicit RenderValuePropertyNotificationHandlerBase() :
        m_transformation(ShaderProgram::UniformTransformationPassThrough),
        m_dirty(true)
    {
    }

    /// Constructor.
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    explicit RenderValuePropertyNotificationHandlerBase(AbstractPropertyType propertyType, Node* node) :
        NodePropertyNotificationHandler(propertyType, node),
        m_transformation(ShaderProgram::UniformTransformationPassThrough),
        m_dirty(true)
    {
    }

    /// Constructor.
    /// \param propertyType Property type to listen on.
    /// \param node Node to listen for changes on.
    /// \param transformation Uniform transformation.
    explicit RenderValuePropertyNotificationHandlerBase(AbstractPropertyType propertyType, Node* node, ShaderProgram::UniformTransformation transformation) :
        NodePropertyNotificationHandler(propertyType, node),
        m_transformation(transformation),
        m_dirty(true)
    {
    }

    /// Move constructor.
    /// \param other Source object.
    RenderValuePropertyNotificationHandlerBase(KZ_RV_REF(RenderValuePropertyNotificationHandlerBase) other) :
        NodePropertyNotificationHandler(kanzi::move(other)),
        m_transformation(other.m_transformation),
        m_dirty(other.m_dirty)
    {
    }

    /// AbstractPropertyNotificationHandler::onPropertyChanged() implementation.
    virtual void onPropertyChanged(PropertyNotificationReason) KZ_OVERRIDE;

    /// Gets the uniform transformation.
    /// \return Uniform transformation for this 
    ShaderProgram::UniformTransformation getTransformation() const
    {
        return m_transformation;
    }

private:

    /// Shader transformation.
    ShaderProgram::UniformTransformation m_transformation;

    /// Is this property dirty and does it need updating.
    bool m_dirty;
};

/// Default implementation for acquiring value for property notification handlers.
/// \param handler Handler to access node from.
/// \param object Fallback object for property value.
/// \param material Fallback material for property value.
template<typename T> T acquireRenderValueFromPropertyDefault(AbstractPropertyType abstractProperty, Node* node, Object* object, Material& material)
{
    const DynamicPropertyType<T> propertyType(abstractProperty);

    if (node)
    {
        optional<T> value = node->getOptionalProperty(propertyType);
        if (value)
        {
            return *value;
        }
    }

    if (object)
    {
        optional<T> value = object->getOptionalProperty(propertyType);
        if (value)
        {
            return *value;
        }
    }

    return material.getProperty(propertyType);
}

/// Default implementation for acquiring value for property notification handlers.
/// \param handler Handler to access node from.
/// \param object Fallback object for property value.
/// \param material Fallback material for property value.
/// \param transformation Shader transformation for uniform values.
template<typename T> T acquireRenderValueFromProperty(AbstractPropertyType abstractProperty, Node* node, Object* object, Material& material, ShaderProgram::UniformTransformation /*transformation*/)
{
    return acquireRenderValueFromPropertyDefault<T>(abstractProperty, node, object, material);
}

/// #acquireRenderValueFromProperty() specialization.
template<> GraphicsBlendMode acquireRenderValueFromProperty(AbstractPropertyType abstractProperty, Node* node, Object* object, Material& material, ShaderProgram::UniformTransformation transformation);

/// #acquireRenderValueFromProperty() specialization.
template<> ColorRGBA acquireRenderValueFromProperty(AbstractPropertyType abstractProperty, Node* node, Object* object, Material& material, ShaderProgram::UniformTransformation transformation);

/// #acquireRenderValueFromProperty() specialization.
template<> TextureSharedPtr acquireRenderValueFromProperty(AbstractPropertyType abstractProperty, Node* node, Object* object, Material& material, ShaderProgram::UniformTransformation transformation);

}

#endif // KZ_RENDER_VALUE_PROPERTY_NOTIFICATION_HANDLER_BASE_HPP