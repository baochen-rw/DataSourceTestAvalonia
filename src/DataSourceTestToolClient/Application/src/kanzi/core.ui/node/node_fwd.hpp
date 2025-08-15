// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_FWD_HPP
#define KZ_NODE_FWD_HPP

#include <kanzi/core/cpp/memory.hpp>


namespace kanzi
{

    class Node;

    typedef shared_ptr<Node> NodeSharedPtr;
    typedef weak_ptr<Node> NodeWeakPtr;
    typedef shared_ptr<Node const> NodeConstSharedPtr;

}

#endif
