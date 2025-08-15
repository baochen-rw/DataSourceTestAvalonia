// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_NODE_REFERENCE_H
#define KZU_NODE_REFERENCE_H

#include <kanzi/core.ui/node/abstract_node_reference.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/node/relative_node_resolver.hpp>

namespace kanzi
{

template<typename NodeType>
class NodeReference: public AbstractNodeReference
{
public:
    typedef shared_ptr<NodeType> NodeTypeSharedPtr;
    typedef weak_ptr<NodeType> NodeTypeWeakPtr;

    explicit NodeReference(Node& baseNode, const PropertyType<string>& propertyType):
        m_baseNode(baseNode),
        m_propertyType(propertyType)
    {
        baseNode.addNodeReference(propertyType, this);
    }

    virtual ~NodeReference()
    {
        // Note that this call is made during derived class destructor, so the base class can still be safely used.
        m_baseNode.removeNodeReference(*this);
    }

    virtual void attach() KZ_OVERRIDE
    {
        m_resolver.attach(&m_baseNode, m_baseNode.getProperty(m_propertyType));
    }

    virtual void detach() KZ_OVERRIDE
    {
        m_resolver.detach();
    }

    virtual void update() KZ_OVERRIDE
    {
        detach();
        attach();
    }

    void setUserReference(const NodeTypeSharedPtr& node)
    {
        m_userNode = node;
    }

    NodeTypeSharedPtr get() const
    {
        NodeTypeSharedPtr userNode = m_userNode.lock();
        if(userNode)
        {
            return userNode;
        }

        NodeSharedPtr node = m_resolver.get();
        return dynamic_pointer_cast<NodeType>(node);
    }

private:

    NodeReference(const NodeReference&) KZ_DELETED_FUNCTION;
    NodeReference& operator=(const NodeReference&) KZ_DELETED_FUNCTION;

    Node& m_baseNode;
    const PropertyType<string>& m_propertyType;

    RelativeNodeResolver m_resolver;

    NodeTypeWeakPtr m_userNode;
    NodeTypeWeakPtr m_node;
};

}


#endif
