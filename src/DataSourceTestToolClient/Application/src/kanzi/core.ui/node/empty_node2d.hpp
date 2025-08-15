// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_EMPTY_LAYER_H
#define KZU_EMPTY_LAYER_H


#include <kanzi/core.ui/node/node2d.hpp>

namespace kanzi
{

class EmptyNode2D;

typedef shared_ptr<EmptyNode2D> EmptyNode2DSharedPtr;

/// Empty Node 2D can be used to group other 2D nodes.
class KANZI_API EmptyNode2D : public Node2D
{
public:

    /// Creates an empty node.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    static EmptyNode2DSharedPtr create(Domain* domain, string_view name);

    /// Creates an empty node.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    /// \param width Node width.
    /// \param height Node height.
    static EmptyNode2DSharedPtr create(Domain* domain, string_view name, float width, float height);

    /// Creates an empty node.
    ///
    /// \param domain UI domain to use.
    /// \param name Node name.
    /// \param width Node width.
    /// \param height Node height.
    /// \param color Use background color.
    static EmptyNode2DSharedPtr create(Domain* domain, string_view name, float width, float height, ColorRGBA color);

    KZ_METACLASS_BEGIN(EmptyNode2D, Node2D, "Kanzi.EmptyNode2D")
    KZ_METACLASS_END()

protected:

    explicit EmptyNode2D(Domain* domain, string_view name);
};

}


#endif
