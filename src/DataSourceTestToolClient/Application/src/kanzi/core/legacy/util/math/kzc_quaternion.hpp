/**
* \file
* Quaternion operations.
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_QUATERNION_H
#define KZC_QUATERNION_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>


/* Forward declarations */
struct KzcVector3;
struct KzcMatrix4x4;


/**
* Structure of quaternion. Quaternion defines 3D orientation. 
*/
struct KzcQuaternion
{
    explicit KzcQuaternion() :
        w(1.0f),
        x(0.0f),
        y(0.0f),
        z(0.0f)
    {
    }

    explicit KzcQuaternion(float w, float x, float y, float z) :
        w(w),
        x(x),
        y(y),
        z(z)
    {
    }

    kzFloat w; /**< Angle. */
    kzFloat x; /**< X axis. */
    kzFloat y; /**< Y axis. */
    kzFloat z; /**< Z axis. */
};


/** Sets identity quaternion. */
KANZI_API void kzcQuaternionSetIdentity(KzcQuaternion* quaternion);
/** Creates quaternion from vector and and angle. */
KANZI_API void kzcQuaternionInitializeFromVector(const KzcVector3* axis, kzFloat angleInRadians, KzcQuaternion* out_quaternion);
/** Creates quaternion from matrix. */
KANZI_API void kzcQuaternionInitializeFromMatrix4x4(const KzcMatrix4x4* matrix, KzcQuaternion* out_quaternion);
/** Converts quaternion from 4x4 matrix. */
KANZI_API void kzcQuaternionConvertToMatrix4x4(const KzcQuaternion* quaternion, KzcMatrix4x4* out_matrix);
/** Multiplies 2 quaternions, resulting rotation. */
KANZI_API void kzcQuaternionMultiply(const KzcQuaternion* quaternion1, const KzcQuaternion* quaternion2, KzcQuaternion* out_quaternion);
/** Multiplies quaternion with vector, i.e. applies rotation to vector. */
KANZI_API void kzcQuaternionMultiplyVector3(const KzcQuaternion* quaternion, const KzcVector3* vector3, KzcVector3* out_vector3);
/** Normalizes a quaternion. */
KANZI_API void kzcQuaternionNormalize(KzcQuaternion* quaternion);
/** Creates normalized quaternion from specified quaternion and returns it. */
KANZI_API KzcQuaternion kzcQuaternionCreateNormalized(KzcQuaternion quaternion);
/** Inverses a quaternion. */
KANZI_API void kzcQuaternionInverse(KzcQuaternion* quaternion);
/** Spherical interpolation between two quaternions. t is the interpolation parameter from range [0, 1]. */
KANZI_API void kzcQuaternionSlerp(const KzcQuaternion* quaternion1, const KzcQuaternion* quaternion2, kzFloat t, KzcQuaternion* out_quaternion);
/** Spherical interpolation between two quaternions. Goes through the longer path (more than 180 degree turn). t is the interpolation parameter from range [0, 1]. */
KANZI_API void kzcQuaternionSlerpLongerPath(const KzcQuaternion* quaternion1, const KzcQuaternion* quaternion2, kzFloat t, KzcQuaternion* out_quaternion);

/** Creates quaternion from Euler rotation angles specified in radians. */
KANZI_API KzcQuaternion kzcQuaternionFromRotationAngles(struct KzcVector3 angles);

/** Creates quaternion from Euler rotation angles specified in radians. */
KANZI_API KzcQuaternion kzcQuaternionFromRotationAngles(float x, float y, float z);

KANZI_API KzcVector3 kzcQuaternionToEulerAngles(const KzcQuaternion& quaternion);

KANZI_API KzcQuaternion operator*(const KzcQuaternion& left, const KzcQuaternion& right);
KANZI_API KzcVector3 operator*(const KzcQuaternion& quaternion, const KzcVector3 vector);

KANZI_API bool operator==(const KzcQuaternion& q1, const KzcQuaternion& q2);
KANZI_API bool operator!=(const KzcQuaternion& q1, const KzcQuaternion& q2);


#endif
