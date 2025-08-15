// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_ABSTRACT_NODE_REFERENCE_H
#define KZU_ABSTRACT_NODE_REFERENCE_H


#include <kanzi/core/legacy/kzs_types.hpp>


namespace kanzi
{

class KANZI_API AbstractNodeReference
{
public:

    virtual void attach() = 0;
    virtual void detach() = 0;

    virtual void update() = 0;

protected:

    ~AbstractNodeReference() {}
};

}


#endif
