// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ANIMATION_RESOURCE_HPP
#define KZ_ANIMATION_RESOURCE_HPP


#include "timeline.hpp"

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core/cpp/string_view.hpp>


namespace kanzi
{

class AnimationResource;
class AbstractAnimation;
class ReadOnlyMemoryFile;

typedef shared_ptr<AnimationResource> AnimationResourceSharedPtr;
typedef shared_ptr<AbstractAnimation> AbstractAnimationSharedPtr;


/// A Resource wrapper class for animations.
/// Currently only supports loading of float keyframe animations.
class KANZI_API AnimationResource : public Resource
{
public:

    KZ_METACLASS_BEGIN(AnimationResource, Resource, "Kanzi.Animation.AnimationResource")
    KZ_METACLASS_END()

    /// Creates a new empty animation resource instance. The animation can be initialized using loadFromKZB function.
    /// \param domain Domain.
    /// \param name Animation name.
    /// \return Empty timeline resource.
    static AnimationResourceSharedPtr create(Domain* domain, string_view name);

    /// Gets the animation of the animation resource.
    /// \return Animation.
    AbstractAnimationSharedPtr getAnimation() const;

    /// Loads animation from KZB file.
    /// \param domain Domain.
    /// \param name Timeline name.
    /// \param kzbFile KZB file to load animation data from.
    /// \param parser Parser to parse animation data.
    /// \return Loaded animation.
    static AnimationResourceSharedPtr loadFromKZB(Domain*domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

private:

    /// Constructor.
    /// \param domain Domain.
    /// \param name Animation name.
    AnimationResource(Domain* domain, string_view name);

    // Actual animation.
    AbstractAnimationSharedPtr m_animation;
};

}

#endif
