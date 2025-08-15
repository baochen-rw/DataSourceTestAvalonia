// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TIMELINE_PLAYBACK_CONTEXT_HPP
#define KZ_TIMELINE_PLAYBACK_CONTEXT_HPP


#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string_view.hpp>

namespace kanzi
{

class Object;


/// Helper interface which defines the context of animation playback,
/// i.e. how to resolve objects for timelines, should playback be relative or absolute, etc.
class KANZI_API TimelinePlaybackContext
{
public:

    explicit TimelinePlaybackContext() :
        m_relativePlayback(false)
    {
    }

    virtual ~TimelinePlaybackContext()
    {
    }

    virtual shared_ptr<Object> lookupObject(string_view path)
    {
        return lookupObjectOverride(path);
    }

    void setRelativePlayback(bool isRelative)
    {
        m_relativePlayback = isRelative;
    }

    bool isRelativePlayback()
    {
        return m_relativePlayback;
    }

protected:

    virtual shared_ptr<Object> lookupObjectOverride(string_view path) = 0;

private:

    bool m_relativePlayback;
};

}

#endif