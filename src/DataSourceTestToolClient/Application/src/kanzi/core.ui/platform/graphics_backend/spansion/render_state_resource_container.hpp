// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RENDER_STATE_HPP
#define KZ_RENDER_STATE_HPP


#include <kanzi/property/property_type.hpp>


namespace kanzi
{
class Texture;
class Resource;

/// Render state resource container.
///
/// Required for render state to store resource IDs and resources themselves upon change.
class RenderStateResourceContainer
{
public:
    /// Empty constructor.
    explicit RenderStateResourceContainer();

    /// Constructor.
    explicit RenderStateResourceContainer(Resource* resource);

    /// Access object.
    Texture* getResource() const;

private:
    Resource* m_resource;
};

}


#endif
