// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_GL_RENDER_VALUE_BINDING_HPP
#define KZ_GL_RENDER_VALUE_BINDING_HPP

#include "render_state_property_notification_handler.hpp"
#include <kanzi/core/cpp/vector.hpp>

#include "renderer.hpp"

namespace kanzi
{

class GlRenderState;
class Material;

/// GlRenderValueBinding is a binding from shaders/materials into values in GlRenderState.
struct GlRenderValueBinding
{
public:

    /// Add a listener for given property.
    ///
    /// \param propertyType Property type to listen.
    void addPropertyListener(Node* node, GlRenderState& renderState, AbstractPropertyType propertyType, ShaderProgram::UniformTransformation transformation);

    /// Attach to a combination of nodes.
    ///
    /// \param material Material to use.
    /// \param node Node to listen property changes on.
    /// \param renderState Render state that will be updated on changes.
    void attach(Material& material, Node* node, GlRenderState& renderState);

    /// Apply changes into render state.
    ///
    /// \param renderState Render state to write changes to.
    /// \param object Fallback object for property value.
    /// \param material Fallback material for property value.
    void update(GlRenderState& renderState, Object* object, Material& material);

    /// Invalidates the state of the notification handler.
    /// Use this function to invalidate a node that you destroyed before destroying the GlRenderValueBinding.
    void invalidate();

    /// Flag all properties as being dirty and needing an update.
    void setAllPropertiesDirty();

private:

    /// Singular property storage storing the blend mode.
    RenderStatePropertyNotificationHandlerPtr m_blendModeProperty;

    /// Property notifications connecting material and render state.
    vector<RenderStatePropertyNotificationHandlerPtr> m_materialProperties;
};

}

#endif // KZ_GL_RENDER_VALUE_BINDING_HPP