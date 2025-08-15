// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_SCENEGRAPH_TIMELINE_PLAYBACK_CONTEXT_HPP
#define KZ_SCENEGRAPH_TIMELINE_PLAYBACK_CONTEXT_HPP


#include "timeline_playback_context.hpp"
#include <kanzi/core.ui/node/node.hpp>

namespace kanzi
{

/// Helper class to resolve objects for animation timelines.
class KANZI_API SceneGraphTimelinePlaybackContext : public TimelinePlaybackContext
{
public:

    explicit SceneGraphTimelinePlaybackContext(Node& node);

    /// Gets the node this Scene Graph Timeline Playback Context is referring to.
    /// \return Reference to the node.
    Node& getNode()
    {
        return m_node;
    }

protected:

    virtual shared_ptr<Object> lookupObjectOverride(string_view path) KZ_OVERRIDE;

private:

    SceneGraphTimelinePlaybackContext(const SceneGraphTimelinePlaybackContext&) KZ_DELETED_FUNCTION;
    SceneGraphTimelinePlaybackContext& operator=(const SceneGraphTimelinePlaybackContext&) KZ_DELETED_FUNCTION;

    Node& m_node;
};

}

#endif