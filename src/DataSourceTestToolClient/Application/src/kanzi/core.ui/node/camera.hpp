// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_CAMERA_H
#define KZU_CAMERA_H


#include <kanzi/core.ui/node/node3d.hpp>

#include <kanzi/core/legacy/util/math/kzc_plane.hpp>
#include <kanzi/core/legacy/util/math/kzc_matrix4x4.hpp>

namespace kanzi
{

class Camera;

/// CameraNode shared pointer.
typedef shared_ptr<Camera> CameraSharedPtr;


/// Camera node defines a view transform that is used to render the 3D scene.
///
/// Each scene can have multiple cameras. Set the camera that is used for rendering in the #Scene node.
///
/// Examples
/// ----
/// Create a camera with a perspective projection:
/// \snippet kz_test_camera_node.cpp Camera node example perspective
///
/// Create a camera with an orthographic projection:
/// \snippet kz_test_camera_node.cpp Camera node example orthographic


class KANZI_API Camera : public Node3D
{
public:

    /// Field of view type of a camera.
    enum FieldOfViewType
    {
        XFov = 0, ///< Field of view is specified in x direction.
        YFov = 1  ///< Field of view is specified in y direction.
    };

    /// Projection type of a camera.
    enum ProjectionType
    {
        ProjectionPerspective  = 0, ///< Perspective projection.
        ProjectionOrthographic = 1  ///< Orthogonal projection.
    };

    /// Type of the orthogonal coordinate system.
    enum OrthogonalCoordinateSystem
    {
        OrthogonalCoordinateSystemAbsolute = 0, ///< Absolute orthogonal projection.
        OrthogonalCoordinateSystemRelative = 1  ///< Relative orthogonal projection.
    };


    /// Creates a camera node.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    /// \return The created node.
    static CameraSharedPtr create(Domain* domain, string_view name);

    /// \name Properties
    /// \{
#include "camera_properties.h"
    /// \}

    KZ_METACLASS_BEGIN(Camera, Node3D, "Kanzi.Camera")
        KZ_METACLASS_PROPERTY_TYPE(AspectRatioProperty)
        KZ_METACLASS_PROPERTY_TYPE(DisableAspectRatioProperty)
        KZ_METACLASS_PROPERTY_TYPE(ZNearProperty)
        KZ_METACLASS_PROPERTY_TYPE(ZFarProperty)
        KZ_METACLASS_PROPERTY_TYPE(ProjectionTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(FovTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(FovProperty)
        KZ_METACLASS_PROPERTY_TYPE(OrthogonalCoordinateSystemTypeProperty)
        KZ_METACLASS_PROPERTY_TYPE(OrthogonalPlaneHeightProperty)
    KZ_METACLASS_END()

    /// Sets the orthogonal projection mode.
    /// \param coordinateSystem The type of the orthogonal coordinate system.
    void setOrthogonalProjection(OrthogonalCoordinateSystem coordinateSystem);

    /// Sets the perspective projection mode.
    void setPerspectiveProjection();

    /// Gets the current aspect ratio of a camera.
    /// \return Depending on the #DisableAspectRatioProperty, either the value of the #AspectRatioProperty or the value set with setInheritedAspectRatio().
    float getAspectRatio() const;

    /// Sets the inherited aspect ratio value.
    /// \param inheritedAspectRatio The new inherited aspect ratio.
    /// \see getInheritedAspectRatio(), getAspectRatio()
    void setInheritedAspectRatio(float inheritedAspectRatio);

    /// Gets the value of the inherited aspect ratio of a camera.
    /// \return The inherited aspect ratio.
    /// \see setInheritedAspectRatio(), getAspectRatio()
    float getInheritedAspectRatio() const;

    /// Creates a projection matrix for a camera.
    /// \param viewportWidth Width of the current viewport in pixels. Used only when the camera uses the absolute orthogonal system.
    /// \param viewportHeight Height of the current viewport in pixels. Used only when the camera uses the absolute orthogonal system.
    /// \return Perspective or orthogonal projection matrix calculated from the camera values.
    Matrix4x4 calculateProjectionMatrix(float viewportWidth, float viewportHeight) const;


protected:

    /// Constructor.
    /// \param domain The UI domain the new node belongs to.
    /// \param name The name of the node.
    explicit Camera(Domain* domain, string_view name);

private:

    /// Aspect ratio inherited from outside camera.
    float m_inheritedAspectRatio;
};


// TODO: do these function need ..FromValues in their names?
/// Creates an orthogonal projection matrix for a symmetrical viewing volume.
/// \param near Camera near value.
/// \param far Camera far value.
/// \param fovType Tells whether the orthoSize parameter is the width or height of the viewing box.
/// \param orthoSize Specifies the size of the viewing box (either width of height).
/// \param aspectRatio Specifies the aspect ratio of the viewing box.
/// \return Orthogonal projection matrix.
/// \see Matrix4x4::createOrthogonalProjection
KANZI_API Matrix4x4 calculateRelativeOrthogonalProjectionMatrixFromValues(float near, float far, Camera::FieldOfViewType fovType, float orthoSize, float aspectRatio);


/// Creates a perspective projection matrix for a symmetrical viewing volume.
/// \param near Camera near value.
/// \param far Camera far value.
/// \param fovType Tells whether the fovInDegrees parameter is xfov or yfov.
/// \param fovInDegrees Field of view in degrees.
/// \param aspectRatio The aspect ratio of the viewport.
/// \return Perspective projection matrix.
KANZI_API Matrix4x4 calculatePerspectiveProjectionMatrixFromValues(float near, float far, Camera::FieldOfViewType fovType, float fovInDegrees, float aspectRatio);

/// Calculate sub-quad projection of an existing projection matrix.
///
/// This is a specific solution for an axis-aligned case.
///
/// Old projection matrix =
/// [P00    0  P02  P03]
/// [  0  P11  P12  P13]
/// [  0    0  P22  P23]
/// [  0    0   -1    0]
///
/// Traslated and scaled: (x, y) |--> (Ox, Oy) + (Sx * x, Sy * y)
/// [Sx P00,       0,  Ox P22 + Sx P02,  Ox P23]
/// [     0,  Sy P11,  Oy P22 + Sy P12,  Oy P23]
/// [     0,       0,              P22,     P23]
/// [     0,       0,               -1,       0]
///
/// \param projection Projection matrix.
/// \param relativeOffsetX X offset of sub-quad as portion of the size of the projection area.
/// \param relativeOffsetY Y offset of sub-quad as portion of the size of the projection area.
/// \param relativeSizeX Projection area X size in regard to sub-quad area size.
/// \param relativeSizeY Projection area Y size in regard to sub-quad area size.
/// \return Modified projection matrix.
KANZI_API Matrix4x4 calculateSubProjection(Matrix4x4 projection, float relativeOffsetX, float relativeOffsetY, float relativeSizeX, float relativeSizeY);

}


#endif

#endif
