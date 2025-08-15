// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_VALUE_ANIMATION_HPP
#define KZ_VALUE_ANIMATION_HPP


#include "abstract_animation.hpp"
#include <kanzi/core/math/vector2.hpp>
#include <kanzi/core/math/vector3.hpp>
#include <kanzi/core/math/vector4.hpp>
#include <kanzi/core/math/color_rgba.hpp>
#include <kanzi/core/math/srt_value_2d.hpp>
#include <kanzi/core/math/srt_value_3d.hpp>


namespace kanzi
{

/// Interface template for value animations.
///
/// Classes derived from ValueAnimation define animation data and algorithms that animate values.
/// For example FromToAnimation defines animations between two values and KeyframeAnimation animates values along a sequence of keyframes.
/// ValueAnimation provides a common interface to retrieve a new animated value given current value and time.
///
/// ValueAnimation and derived classes operate only on values.
/// You can animate values of properties by combining classes like PropertyAnimationTimeline and PropertyFieldAnimationTimeline
/// with classes like FromToAnimation and KeyframeAnimation.
///
/// ValueAnimation is an interface template. TValueType template parameter defines the type of the animated value.
/// For example, FloatValueAnimation defines interface to animate float values and is defined as ValueAnimation<float>.
template <typename TValueType>
class ValueAnimation : public AbstractAnimation
{
public:

    /// Returns new animated value given current value and time.
    ///
    /// Classes derived from ValueAnimation define data and algorithms to calculate the value returned by this function.
    /// \param currentValue Current value that is used as basis for animation calculations.
    virtual TValueType getValue(const TValueType& currentValue, chrono::milliseconds time) = 0;

protected:

    /// Constructor.
    explicit ValueAnimation(Domain* domain) : AbstractAnimation(domain)
    {
    }
};


typedef ValueAnimation<bool> BoolAnimation;
typedef shared_ptr<BoolAnimation> BoolAnimationSharedPtr;
typedef ValueAnimation<int> IntAnimation;
typedef shared_ptr<IntAnimation> IntAnimationSharedPtr;
typedef ValueAnimation<float> FloatAnimation;
typedef shared_ptr<FloatAnimation> FloatAnimationSharedPtr;
typedef ValueAnimation<ColorRGBA> ColorRGBAAnimation;
typedef shared_ptr<ColorRGBAAnimation> ColorRGBAAnimationSharedPtr;
typedef ValueAnimation<Vector2> Vector2Animation;
typedef shared_ptr<Vector2Animation> Vector2AnimationSharedPtr;
typedef ValueAnimation<Vector3> Vector3Animation;
typedef shared_ptr<Vector3Animation> Vector3AnimationSharedPtr;
typedef ValueAnimation<Vector4> Vector4Animation;
typedef shared_ptr<Vector4Animation> Vector4AnimationSharedPtr;
typedef ValueAnimation<string> StringAnimation;
typedef shared_ptr<StringAnimation> StringAnimationSharedPtr;
typedef ValueAnimation<ResourceID> ResourceIDAnimation;
typedef shared_ptr<ResourceIDAnimation> ResourceIDAnimationSharedPtr;
typedef ValueAnimation<SRTValue2D> SRTValue2DAnimation;
typedef shared_ptr<SRTValue2DAnimation> SRTValue2DAnimationSharedPtr;
typedef ValueAnimation<SRTValue3D> SRTValue3DAnimation;
typedef shared_ptr<SRTValue3DAnimation> SRTValue3DAnimationSharedPtr;


}


#endif
