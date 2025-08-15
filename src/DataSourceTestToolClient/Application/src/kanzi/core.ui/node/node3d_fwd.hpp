// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE3D_FWD_HPP
#define KZ_NODE3D_FWD_HPP

#include <kanzi/core/cpp/memory.hpp>


namespace kanzi
{

class Node3D;

typedef shared_ptr<Node3D> Node3DSharedPtr;
typedef weak_ptr<Node3D> Node3DWeakPtr;
typedef shared_ptr<Node3D const> Node3DConstSharedPtr;

}

#endif
