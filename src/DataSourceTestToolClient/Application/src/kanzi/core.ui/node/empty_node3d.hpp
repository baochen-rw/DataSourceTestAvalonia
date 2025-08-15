// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_EMPTY_NODE3D_H
#define KZU_EMPTY_NODE3D_H

#include <kanzi/core.ui/node/node3d.hpp>

namespace kanzi
{

class EmptyNode3D;

typedef shared_ptr<EmptyNode3D> EmptyNode3DSharedPtr;


class KANZI_API EmptyNode3D : public Node3D
{
public:

    static EmptyNode3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(EmptyNode3D, Node3D, "Kanzi.EmptyNode3D")
    KZ_METACLASS_END()

protected:

    explicit EmptyNode3D(Domain* domain, string_view name);
};

}

#endif

#endif
