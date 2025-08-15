// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_LIGHT_H
#define KZU_LIGHT_H


#include <kanzi/core.ui/node/node3d.hpp>


struct KzuStructPropertyType;


namespace kanzi
{

class Material;
typedef shared_ptr<Material> MaterialSharedPtr;

class Light;
typedef shared_ptr<Light> LightSharedPtr;


/// Light node is a source of light for a 3D scene.
///
/// Light nodes contain properties that are passed as uniforms to shaders when 3D nodes are rendered.
/// Note that lights affect only the rendering of nodes which use materials with shaders that use those lights.
///
/// Examples
/// ---
/// To create and set a directional light:
/// \snippet kz_test_light.cpp example directional
///
/// To create and set a point light:
/// \snippet kz_test_light.cpp example point
///
/// To create and set a spot light:
/// \snippet kz_test_light.cpp example spot


class KANZI_API Light : public Node3D
{
public:

    /// Light type enumeration.
    enum Type
    {
        /// Directional light.
        TypeDirectional = 0,

        /// Point light.
        TypePoint,

        /// Spotlight.
        TypeSpot,

        /// Number of light types.
        TypeCount,

        /// Invalid light type (or no light).
        TypeInvalid
    };

public:

    /// \name Properties
    /// \{
#include "light_properties.h"
    /// \}

    /// Creates a light node.
    /// \param domain The UI domain the new light node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static LightSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Light, Node3D, "Kanzi.Light")
        KZ_METACLASS_PROPERTY_TYPE(EnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(TypeNameProperty)
        KZ_METACLASS_PROPERTY_TYPE(DirectionalLightColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(DirectionalLightDirectionProperty)
        KZ_METACLASS_PROPERTY_TYPE(PointLightColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(PointLightAttenuationProperty)
        KZ_METACLASS_PROPERTY_TYPE(PointLightPositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(PointLightRadiusProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpotLightColorProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpotLightAttenuationProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpotLightCutoffAngleProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpotLightInnerAngleProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpotLightDirectionProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpotLightExponentProperty)
        KZ_METACLASS_PROPERTY_TYPE(SpotLightPositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ColorScaleProperty)
    KZ_METACLASS_END()

    /// Creates a directional light.
    /// \param domain The UI domain the new directional light node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static LightSharedPtr createDirectional(Domain* domain, string_view name);

    /// Creates a point light.
    /// \param domain The UI domain the new point light node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static LightSharedPtr createPoint(Domain* domain, string_view name);

    /// Creates a spot light.
    /// \param domain The UI domain the new spot light node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static LightSharedPtr createSpot(Domain* domain, string_view name);

    void setLightType(Type type);

    /// Gets the type of the light node.
    Light::Type getLightType() const;

    Matrix4x4 getWorldTransform() const;

    void setWorldTransform(const Matrix4x4& worldTransformation);

protected:
    virtual void onAttached() KZ_OVERRIDE;

    /// Constructor.
    /// \param domain The UI domain the new light node belongs to.
    /// \param name The name of the node.
    explicit Light(Domain* domain, string_view name);

private:
    Type m_type;
    Matrix4x4 m_worldTransformation;
};

}

#endif

#endif
