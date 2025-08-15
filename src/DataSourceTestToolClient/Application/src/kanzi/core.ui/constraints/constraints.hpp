// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_CONSTRAINTS_HPP
#define KZ_CONSTRAINTS_HPP


#include <kanzi/core.ui/binding/binding.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

namespace kanzi
{

/**
 * Contains property types of Constraints.
 */
class KANZI_API Constraints
{
public:
    /// \name Properties
    /// \{
#include "constraints_properties.h"
    /// \}

    KZ_STATIC_METACLASS_BEGIN(Constraints, "Kanzi.Constraints")
        KZ_METACLASS_PROPERTY_TYPE(PositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(OrientationProperty)
        KZ_METACLASS_PROPERTY_TYPE(InWorldCoordinatesProperty)
        KZ_METACLASS_PROPERTY_TYPE(FaceToCameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(FaceToCameraIsBillboardingProperty)
        KZ_METACLASS_PROPERTY_TYPE(FaceToCameraCylindralProperty)
        KZ_METACLASS_PROPERTY_TYPE(FaceToCameraTargetCameraProperty)
        KZ_METACLASS_PROPERTY_TYPE(LookAtProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of InWorldCoordinates property of object.
    /// \param object An object.
    /// \return Returns value of the InWorldCoordinates property.
    static bool isInWorldCoordinates(const Object& object)
    {
        return object.getProperty(InWorldCoordinatesProperty);
    }

    /// Sets the value of InWorldCoordinates property of object.
    /// \param object An object.
    /// \param value Value of InWorldCoordinatesColor property.
    static void setInWorldCoordinates(Object& object, bool value)
    {
        object.setProperty(InWorldCoordinatesProperty, value);
    }

    /// Gets the value of FaceToCamera property of object.
    /// \param object An object.
    /// \return Returns value of the FaceToCamera property.
    static bool isFaceToCamera(const Object& object)
    {
        return object.getProperty(FaceToCameraProperty);
    }

    /// Sets the value of FaceToCamera property of object.
    /// \param object An object.
    /// \param value Value of FaceToCameraColor property.
    static void setFaceToCamera(Object& object, bool value)
    {
        object.setProperty(FaceToCameraProperty, value);
    }

    /// Gets the value of FaceToCameraIsBillboarding property of object.
    /// \param object An object.
    /// \return Returns value of the FaceToCameraIsBillboarding property.
    static bool isFaceToCameraBillboarding(const Object& object)
    {
        return object.getProperty(FaceToCameraIsBillboardingProperty);
    }

    /// Sets the value of FaceToCameraIsBillboarding property of object.
    /// \param object An object.
    /// \param value Value of FaceToCameraIsBillboardingColor property.
    static void setFaceToCameraIsBillboarding(Object& object, bool value)
    {
        object.setProperty(FaceToCameraIsBillboardingProperty, value);
    }

    /// Gets the value of FaceToCameraIsCylindral property of object.
    /// \param object An object.
    /// \return Returns value of the FaceToCameraIsCylindral property.
    static bool isFaceToCameraCylindral(const Object& object)
    {
        return object.getProperty(FaceToCameraCylindralProperty);
    }

    /// Sets the value of FaceToCameraIsCylindral property of object.
    /// \param object An object.
    /// \param value Value of FaceToCameraIsCylindralColor property.
    static void setFaceToCameraIsCylindral(Object& object, bool value)
    {
        object.setProperty(FaceToCameraCylindralProperty, value);
    }

    static BindingSharedPtr createPositionBinding(Domain* domain, string_view targetRelativePath);
    static BindingSharedPtr createOrientationBinding(Domain* domain, string_view targetRelativePath);
    static BindingSharedPtr createLookAtBinding(Domain* domain, string_view targetRelativePath);

    static BindingSharedPtr createReversedLookAtBinding(Domain* domain, string_view targetRelativePath);
    static BindingSharedPtr createReversedCylindricalLookAtBinding(Domain* domain, string_view targetRelativePath);

    static BindingSharedPtr createLocalPositionBinding(Domain* domain, string_view targetRelativePath);
    static BindingSharedPtr createLocalOrientationBinding(Domain* domain, string_view targetRelativePath);
};
}


#endif

#endif
