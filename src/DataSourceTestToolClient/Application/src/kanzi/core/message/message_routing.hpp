// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MESSAGE_ROUTING_HPP
#define KZ_MESSAGE_ROUTING_HPP


namespace kanzi
{

/// Message routing modes.
enum MessageRouting
{
    /// Identifies both, the tunneling and the bubbling phase.
    MessageRoutingTunnelingBubbling = 0,
    /// Identifies the tunneling phase, during which a message travels down the node tree from the first child node of
    /// the Screen node (the root node) to the node where the message originated.
    MessageRoutingTunneling = 1,
    /// Identifies the bubbling phase, during which a message travels up the node tree from the node where the message
    /// originated to the first child node of the Screen node (the root node).
    MessageRoutingBubbling = 2,
    /// Not implemented.
    MessageRoutingDirect = 3
};

}

#endif
