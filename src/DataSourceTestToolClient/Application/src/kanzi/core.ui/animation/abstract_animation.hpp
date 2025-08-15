// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_ANIMATION_HPP
#define KZ_ABSTRACT_ANIMATION_HPP


#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/cpp/optional.hpp>
#include <kanzi/core.ui/object/object.hpp>


namespace kanzi
{


/// Interface for abstract animations.
///
/// Classes derived from AbstractAnimation define animation data and algorithms.
/// AbstractAnimation interface exposes common methods to manipulate such classes.
class KANZI_API AbstractAnimation : public Object
{
public:

    /// Destructor.
    virtual ~AbstractAnimation()
    {
    }

    /// Returns the duration of the animation.
    /// \return Returns the duration of animation in milliseconds. If the animation is infinite returns nullopt.
    optional<chrono::milliseconds> getDuration()
    {
        return getDurationOverride();
    }

protected:

    /// Constructor.
    explicit AbstractAnimation(Domain* domain) : Object(domain)
    {
    }

    /// Virtual function the derived classes should overload to return duration.
    ///
    /// Default implementation returns nullopt to indicate infinite animation.
    virtual optional<chrono::milliseconds> getDurationOverride()
    {
        return nullopt;
    }
};


typedef shared_ptr<AbstractAnimation> AbstractAnimationSharedPtr;

}


#endif
