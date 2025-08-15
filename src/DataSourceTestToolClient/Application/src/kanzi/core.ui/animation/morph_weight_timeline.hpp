// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_MORPH_WEIGHT_TIMELINE_HPP
#define KZ_MORPH_WEIGHT_TIMELINE_HPP

#include "keyframe_animation.hpp"
#include "timeline.hpp"

namespace kanzi
{

class MorphWeightTimeline;
typedef shared_ptr<MorphWeightTimeline> MorphWeightTimelineSharedPtr;

/// Timeline for animating morph weights.
///
/// Multiple morph timelines control all morph weights related to one Morph.
///
/// Morph weigth timelines are implicitly created when morph animations are loaded from kzbs.
///
/// Examples
/// ----
///
/// To manually create a morph timeline and create a playback for timeline clock:
/// \snippet test_morph_weight_timeline.cpp Morph weight animation example
class KANZI_API MorphWeightTimeline : public Timeline
{
public:

    KZ_METACLASS_BEGIN(MorphWeightTimeline, Timeline, "Kanzi.Animation.MorphWeightTimeline")
    KZ_METACLASS_END()

    /// Creates a new morph timeline.
    ///
    /// \param domain Domain.
    /// \param path Path to object containing the morph to be animated.
    /// \param morphIndex Index of morph weight being animated.
    /// \param animation Animation to use.
    static MorphWeightTimelineSharedPtr create(Domain* domain, string_view path, size_t morphIndex, FloatAnimationSharedPtr animation);

    /// Creates a new morph timeline.
    ///
    /// \param domain Domain.
    /// \param name Timeline name.
    static MorphWeightTimelineSharedPtr create(Domain* domain, string_view /*name*/)
    {
        return make_polymorphic_shared_ptr<Timeline>(new MorphWeightTimeline(domain));
    }

    /// Gets animation.
    FloatAnimationSharedPtr getAnimation() const
    {
        return m_animation;
    }
    /// Gets path of object the morph of which is being animated.
    string getObjectPath() const
    {
        return m_objectPath;
    }
    /// Gets index of morph weight being animated.
    size_t getMorphWeightIndex() const
    {
        return m_morphIndex;
    }

    /// Loads timeline from KZB file.
    /// \param domain Domain.
    /// \param name Timeline name.
    /// \param kzbFile KZB file to load timeline data from.
    /// \param parser Parser to parse timeline data.
    /// \return Loaded timeline.
    static ObjectSharedPtr load(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser);

protected:
    /// Constructor.
    ///
    /// \param domain Domain.
    /// \param path Path to object containing the morph to be animated.
    /// \param morphIndex Index of morph weight being animated.
    /// \param animation Animation to use.
    explicit MorphWeightTimeline(Domain* domain, string_view path, size_t morphIndex, FloatAnimationSharedPtr animation);

    /// Constructor.
    ///
    /// \param domain Domain.
    explicit MorphWeightTimeline(Domain* domain);

    /// TimelinePlayback::createPlaybackOverride() implementation.
    virtual TimelinePlaybackSharedPtr createPlaybackOverride(TimelinePlaybackContext& context) KZ_OVERRIDE;

    /// TimelinePlayback::calculateContentDuration() implementation.
    virtual optional<chrono::milliseconds> calculateContentDuration() KZ_OVERRIDE;

    /// Timeline::loadOverride() implementation.
    virtual void loadOverride(Domain* domain, string_view name, KzbFile& kzbFile, KzbMemoryParser& parser) KZ_OVERRIDE;

private:
    /// Float animation for weights.
    FloatAnimationSharedPtr m_animation;
    /// Path to object with morph runtime.
    string m_objectPath;
    /// Index within morph runtime for this morph timeline.
    size_t m_morphIndex;
};

}

#endif // KZ_MORPH_TIMELINE_HPP

#endif
