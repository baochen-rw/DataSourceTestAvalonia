/**
* \file
* Interpolation functions
* 
* Copyright 2008-2021 by Rightware. All rights reserved.
*/
#ifndef KZC_INTERPOLATION_H
#define KZC_INTERPOLATION_H


#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations */
struct KzcVector2;
struct KzcVector3;
struct KzcVector4;


/** Returns linearly interpolated value between given two values. t is clamped in the range [0,1]. */
kzFloat kzcInterpolateLinear(kzFloat value1, kzFloat value2, kzFloat t);

/** Returns linearly interpolated point between given two n-dimensional points. t is clamped in the range [0,1]. */
void kzcInterpolateLinearVector(kzUint dimension, const kzFloat* point1, const kzFloat* point2, kzFloat t, kzFloat* out_point);

/** Returns linearly interpolated vector between given two 3-dimensional vectors. t is clamped in the range [0,1]. */
void kzcInterpolateLinearVector3(const struct KzcVector3* const point1, const struct KzcVector3* const point2,
                                 kzFloat t, struct KzcVector3* out_vector);

/** Returns evaluated value from the given polynomial. t is clamped in the range [0,1]. */
kzFloat kzcInterpolatePolynomial(kzUint degree, const kzFloat* coefficients, kzFloat t);

/**
 * Returns evaluated point from the given n-dimensional polynomial. t is clamped in the range [0,1].
 * \param coefficients 2-dimensional array flattened to 1-dimensional array. coefficients[degree][dimension] -> coefficients[degree * dimension]
 */
void kzcInterpolatePolynomialVector(kzUint dimension, kzUint degree, const kzFloat* coefficients, kzFloat t, kzFloat* out_point);

/**
 * Returns smoothly interpolated value in the range [0,1] between given edges.
 * The smoothing is calculated as specified in the OpenGL Shading Language specification.
 * edge1 must be less than edge2.
 * Value of the function is 0 if t <= edge1 and 1 if t >= edge2.
 * If edge1 < t < edge2, the value is interpolated smoothly between edge1 and edge2 in a way
 * that the derivative of the function is f'(edge1) == f'(edge2) == 0.
 */
kzFloat kzcInterpolateSmoothStep(kzFloat edge1, kzFloat edge2, kzFloat t);


#endif
