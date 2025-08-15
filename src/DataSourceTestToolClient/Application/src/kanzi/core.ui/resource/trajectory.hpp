// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TRAJECTORY_HPP
#define KZ_TRAJECTORY_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/math/matrix4x4.hpp>
#include <kanzi/core/math/vector3.hpp>

#include <kanzi/core.ui/resource/resource.hpp>


#include <kanzi/core/legacy/util/math/kzc_matrix4x4.hpp>
#include <kanzi/core/legacy/util/math/kzc_vector3.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>

#include <kanzi/core/cpp/string.hpp>


struct KzcInputStream;
struct KzcReparametrization;
struct KzcSpline;
struct KzuBinaryFileInfo;

namespace kanzi
{

class Domain;
class Trajectory;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;

typedef shared_ptr<Trajectory> TrajectorySharedPtr;


class KANZI_API Trajectory : public Resource
{
public:
    KZ_ABSTRACT_METACLASS_BEGIN(Trajectory, Resource, "Kanzi.Trajectory")
    KZ_METACLASS_END()

    /// Type of trajectory.
    enum Type
    {
        /// Series of points. Spline.
        SplineTrajectory,
        /// Circle.
        CircleTrajectory,
        /// Line.
        LineTrajectory
    };

    /// Creates a trajectory with no data.
    static Trajectory* createEmpty(Domain* domain, string_view name);

    /// Creates a circle trajectory.
    /// \param origin Origin of the circle trajectory.
    /// \param up Normal vector for the plane where the circle exists. The vector will be normalized internally.
    /// \param angleInDegrees Rotation angle of the circle trajectory in its plane, in degrees.
    /// \param radius Radius of the circle.
    /// \param domain UI domain to use.
    /// \param name Node name.
    static TrajectorySharedPtr createCircle(Vector3 origin, Vector3 up, kzFloat angleInDegrees, kzFloat radius, kanzi::Domain* domain, string_view name);

    /// Creates a line trajectory.
    /// \param origin Origin of the line.
    /// \param direction Direction vector for the line. Direction will be normalized internally. 
    /// \param length Length of the line.
    /// \param domain UI domain to use.
    /// \param name Node name.
    static TrajectorySharedPtr createLine(Vector3 origin, Vector3 direction, kzFloat length, kanzi::Domain* domain, string_view name);

    /// Creates a spline trajectory.
    /// \param spline Spline structure to use as trajectory.
    static TrajectorySharedPtr createSpline(KzcSpline* spline, kanzi::Domain* domain, string_view name);

    virtual ~Trajectory() KZ_OVERRIDE;

    /// Gets a point on trajectory by using absolute coordinates ranging from 0.0 to trajectory length.
    /// \param lengthParameter Point on the trajectory.
    Vector3 getPointAbsolute(kzFloat lengthParameter) const;

    /// Gets a point on trajectory by using relative coordinates.
    /// \param phaseParameter Point on the trajectory. 0.0f start, 1.0f end.
    Vector3 getPointRelative(kzFloat phaseParameter) const;

    /// Gets length of trajectory.
    kzFloat getLength() const;

    /// Returns true if trajectory is complete and usable.
    bool isComplete() const;

    /// Returns spline in case of trajectory having the spline. 
    /// If type of the trajectory is not spline then NULL be returned.
    const KzcSpline* getSpline() const;

    /// Gets the number of counts recommended for visualizing the trajectory.
    kzUint getVisualizationPointCount() const;

    /// Gets a visualization point of the trajectory.
    Vector3 getVisualizationPoint(kzUint pointIndex, kzUint pointCount) const;

    /// Return the type of the trajectory.
    Type getType() const;

    /// Return radius of a circle trajectory.
    kzFloat getRadius() const;

    /// Return angle of a circle trajectory.
    kzFloat getAngle() const;

    /// Return direction vector of a line trajectory.
    Vector3 getLineDirection() const;

    /// Return normal vector for the plane of a circle trajectory.
    Vector3 getCircleNormal() const;

    /// Return origin point of a circle trajectory.
    Vector3 getCircleOrigin() const;

    Vector3 scalePoint(Vector3 point, const Matrix4x4& transform, Vector3 scaling) const;

    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Loads a trajectory from a file. Used internally by Kanzi Engine.
    ///
    /// \param domain Domain
    /// \param name Name
    /// \param kzbFile KZB file where to load from.
    /// \param file Trajectory file inside the KZB file where to load from.
    /// \param parser Parser pointing to the beginning of the file.
    static TrajectorySharedPtr loadFromKZB(Domain* domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

private:

    /// Type of the trajectory in kzb file.
    enum BinaryType
    {
        /// Spline trajectory binary type.
        BINARY_TYPE_POINT_SERIE = 0,
        /// Circle trajectory binary type.
        BINARY_TYPE_CIRCLE = 1,
        /// Line trajectory binary type.
        BINARY_TYPE_LINE = 2
    };

    explicit Trajectory(Domain* domain, string_view name);

    void initializeCircle(Vector3 originVector, Vector3 upVector, kzFloat angleInDegrees, kzFloat radius);
    void initializeLine(Vector3 origin, Vector3 direction, kzFloat length);
    void initializeSpline(KzcSpline* spline);
    void clearData();

    /// Type of the trajectory.
    Type m_type;

    /// Type specific data.
    union
    {
        struct
        {
            /// The spline of the trajectory.
            KzcSpline* spline;
        } spline;

        struct
        {
            /// The spline of the trajectory. Radius of the circle.
            kzFloat radius;
            /// The spline of the trajectory. Starting angle of the circle.
            kzFloat angle;
            /// The spline of the trajectory. Circle's transformation from unit circle in XY plane.
            KzcMatrix4x4 transform;
        } circle;

        struct
        {
            /// Length of the line.
            kzFloat length;
            /// Origin of the line.
            KzcVector3 origin;
            /// Normalized direction of the line.
            KzcVector3 direction;
        } line;
    } m_typeData;

    /// Curve length reparametrization for trajectory.
    KzcReparametrization* m_reparametrization;
};
}


#endif
