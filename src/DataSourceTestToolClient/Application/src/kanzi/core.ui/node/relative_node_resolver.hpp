// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KANZI_RELATIVE_NODE_RESOLVER_HPP
#define KANZI_RELATIVE_NODE_RESOLVER_HPP

#include <kanzi/core.ui/node/node.hpp>

namespace kanzi
{

class KANZI_API RelativeNodeResolver
{
public:

    explicit RelativeNodeResolver():
        m_sourceNode()
    {
    }

    void attach(Node* sourceNode, string_view relativePath);

    void detach();

    NodeSharedPtr get() const
    {
        return m_target.lock();
    }

    void resolve();

private:

    RelativeNodeResolver(const RelativeNodeResolver&) KZ_DELETED_FUNCTION;
    RelativeNodeResolver& operator=(const RelativeNodeResolver&) KZ_DELETED_FUNCTION;

    NodeWeakPtr m_target;
    Node* m_sourceNode;
    string m_relativePath;
};

}


#endif
