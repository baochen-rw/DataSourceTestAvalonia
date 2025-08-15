// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE2D_FWD_HPP
#define KZ_NODE2D_FWD_HPP

#include <kanzi/core/cpp/memory.hpp>


namespace kanzi
{

class Node2D;

typedef shared_ptr<Node2D> Node2DSharedPtr;
typedef weak_ptr<Node2D> Node2DWeakPtr;
typedef shared_ptr<Node2D const> Node2DConstSharedPtr;

}

#endif
