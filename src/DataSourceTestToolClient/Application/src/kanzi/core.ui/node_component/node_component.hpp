// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_COMPONENT_HPP
#define KZ_NODE_COMPONENT_HPP

#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/object/object.hpp>

namespace kanzi
{

// Forward declarations.
class NodeComponent;
typedef shared_ptr<Node> NodeSharedPtr;
typedef weak_ptr<Node> NodeWeakPtr;

// Node component shared pointer types.
typedef shared_ptr<NodeComponent> NodeComponentSharedPtr;
typedef shared_ptr<NodeComponent const> NodeComponentConstSharedPtr;

/// NodeComponent is the base class for all node components.
/// Node component is an isolated piece of logic which can be attached to any node
/// in order to add additional functionality to it. Examples of node component could be
/// Trigger which performs specific actions when certain conditions are met or AnimationPlayer
/// which animates specific properties of the node it is attached to and its child nodes.
///
/// Node component can only be attached to a single node at a time. After node component is
/// detached from one node, it can be attached to any other node.
///
/// Node component starts to perform its logic after it is attached to a certain node by calling
/// its attach() function. After node component is detached from its node by calling its detach()
/// function it becomes inactive and stops to perform its logic.
class KANZI_API NodeComponent : public Object, public enable_shared_from_this<NodeComponent>
{
public:

    /// State indicating if component is attached to a node, detached from any node
    /// or in process of attaching/detaching.
    enum State
    {
        /// Indicates node component detached from any node.
        StateDetached,
        /// Indicates node component in progress of detaching from the node.
        StateDetaching,
        /// Indicates node component in progress of attaching to a node.
        StateAttaching,
        /// Indicates node component attached to a node.
        StateAttached
    };

    /// Name property specifies the name of node component.
    static PropertyType<string> NameProperty;

    /// Base class for message arguments that are sent to a node component.
    /// It contains the name of a node component to which the message is sent.
    class KANZI_API NodeComponentTargetMessageArguments : public MessageArguments
    {
    public:

        /// Target name property specifies the name of node component to which the message is sent.
        /// The message is broadcast to all node components on a node if this property is not set
        /// or if it is set to empty string.
        static PropertyType<string> TargetNodeComponentNameProperty;

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NodeComponentTargetMessageArguments, MessageArguments, "Kanzi.NodeComponent.NodeComponentMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(TargetNodeComponentNameProperty)
        KZ_METACLASS_END()

        /// Sets value of TargetNodeComponentName property.
        /// \param targetNodeComponentName Name of target node component.
        void setTargetNodeComponentName(string_view targetNodeComponentName)
        {
            setArgument(TargetNodeComponentNameProperty, string(targetNodeComponentName));
        }

        /// Gets value of TargetNodeComponentName property.
        /// \return Name of target node component.
        string getTargetNodeComponentName() const
        {
            return getArgument(TargetNodeComponentNameProperty);
        }

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Legacy name for NodeComponentTargetMessageArguments.
    /// \deprecated In Kanzi 3.6.10. Use NodeComponentTargetMessageArguments instead.
    typedef NodeComponentTargetMessageArguments NodeComponentMessageArguments;

    /// Base class for message arguments that are sent by a node component.
    /// It contains the name of a node component that sent the message.
    class KANZI_COREUI_API NodeComponentSourceMessageArguments : public MessageArguments
    {
    public:

        /// Specifies the name of a node component that is sending a message.
        /// The name can be empty in either of these cases:
        /// - If a node component name is not set in Kanzi Studio
        /// - If a node component code sends the message without setting the name
        static PropertyType<string> SourceNodeComponentNameProperty;

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(NodeComponentSourceMessageArguments, MessageArguments, "Kanzi.NodeComponent.NodeComponentSourceMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(SourceNodeComponentNameProperty)
        KZ_METACLASS_END()

        /// Sets the value of the SourceNodeComponentNameProperty.
        /// \param sourceNodeComponentName Name of source node component.
        void setSourceNodeComponentName(string_view sourceNodeComponentName)
        {
            setArgument(SourceNodeComponentNameProperty, string(sourceNodeComponentName));
        }

        /// Gets the value of the SourceNodeComponentNameProperty.
        /// \return Name of source node component.
        string getSourceNodeComponentName() const
        {
            return getArgument(SourceNodeComponentNameProperty);
        }

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    KZ_ABSTRACT_METACLASS_BEGIN(NodeComponent, Object, "Kanzi.NodeComponent")
        KZ_METACLASS_PROPERTY_TYPE(NameProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Destructor.
    virtual ~NodeComponent();

    /// Sets the name of node component.
    /// \param name Name of node component.
    void setName(string_view name);

    /// Gets the name of node component.
    /// \return Name of node component.
    string getName() const;

    /// Returns the node the node component is attached to
    /// or null pointer if node component is not attached to a node.
    /// \return Node the node component is attached to.
    NodeSharedPtr getNode() const;

    /// Attaches node component to node.
    void attach(NodeWeakPtr node);
    /// Detaches node component from the node it was attached to.
    void detach();

    /// Gets the state of node component indicating if component is attached to a node,
    /// detached from any node or in process of attaching/detaching.
    /// \return State of node component.
    State getState() const;

    /// Indicates whether node component is in the process of attaching to a node.
    /// \return true if node component is in the process of attaching, false otherwise.
    bool isAttaching() const;
    /// Indicates whether node component is attached to a node.
    /// \return true if node component is attached, false otherwise.
    bool isAttached() const;
    /// Indicates whether node component is in the process of attaching to a node or already attached.
    /// \return true if node component is in the process of attaching or already attached, false otherwise.
    bool isAttachingOrAttached() const;

    /// Indicates whether node component currently detaching from the node.
    /// \return true if node component currently detaching, false otherwise.
    bool isDetaching() const;
    /// Indicates whether node component is detached from any node.
    ///  \return true if node component is detached, false otherwise.
    bool isDetached() const;
    /// Indicates whether node component is in the process of detaching from the node or already detached.
    /// \return true if node component is in the process of detaching or already detached, false otherwise.
    bool isDetachingOrDetached() const;

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param name Name of node component.
    explicit NodeComponent(Domain* domain, string_view name);

    /// NodeComponent calls this function during attaching of node component to a node.
    /// Subclasses of NodeComponent can override this function to add custom logic which
    /// will be performed during node component attach. By default this function does nothing.
    virtual void attachOverride();

    /// NodeComponent calls this function during detaching of node component from a node.
    /// Subclasses of NodeComponent can override this function to add custom logic which
    /// will be performed during node component detach. By default this function does nothing.
    virtual void detachOverride();

    /// Handler function for node component messages.
    /// Does target name checking from the message.
    ///
    /// \param nodeComponent Node component the message handler function of which to call.
    /// \param method Message handler function of node component.
    /// \param messageArguments Message arguments.
    template<typename TMessageType, typename TClass, typename TMethod>
    static void nodeComponentMessageHandler(TClass* nodeComponent, TMethod method, typename TMessageType::ArgumentsType& messageArguments)
    {
        // Call message handler of node component if target name from the message matches the node component name
        // or if target name is not specified in the message (in this case broadcast message to every node component).
        const string targetName = messageArguments.getTargetNodeComponentName();
        const string nodeComponentName = nodeComponent->getName();
        if (targetName.empty())
        {
            // If target name of the message is empty, call handler of every node component.
            (nodeComponent->*method)(messageArguments);

            // Set message as not handled to broadcast it to all other components of the node.
            messageArguments.setHandled(false);
        }
        else if (!nodeComponentName.empty() && targetName == nodeComponentName)
        {
            // If target name of the message matches component name, call handler and leave message handled.
            (nodeComponent->*method)(messageArguments);
        }
        else
        {
            // The message is not addressed to this node component, so set message as not handled.
            messageArguments.setHandled(false);
        }
    }

    /// Kanzi calls the message handler that you add using this function when the target
    /// name of the incoming message matches the name of the node component, or if
    /// the message is broadcast to all node components with an empty target name.
    ///
    /// \param messageType Type of message to handle.
    /// \param nodeComponent Node component the message handler of which should be called.
    /// \param method Message handler function of node component.
    /// \return Message subscription token.
    template <typename TMessageType, typename TClass, typename TMethod>
    Node::MessageSubscriptionToken addNodeComponentMessageHandler(TMessageType& messageType, TClass* nodeComponent, TMethod method);

    /// Removes message handler added via #addNodeComponentMessageHandler function.
    /// \param subscriptionToken Subscription token of message handler to remove.
    void removeNodeComponentMessageFilter(Node::MessageSubscriptionToken subscriptionToken);

    /// Adds the name of the node component to the message arguments and dispatches the message to the node of the node component.
    /// You must derive the message arguments from NodeComponentSourceMessageArguments.
    /// \param messageType The type of the dispatched message.
    /// \param messageArguments The arguments of the dispatched message.
    template <typename TArgumentsType>
    void dispatchMessage(const MessageType<TArgumentsType>& messageType, typename MessageType<TArgumentsType>::ArgumentsType& messageArguments)
    {
        NodeSharedPtr node = getNode();
        kzAssert(node);
        messageArguments.setSourceNodeComponentName(getName());
        node->dispatchMessage(messageType, messageArguments);
    }

private:

    /// Node the node component is attached to.
    NodeWeakPtr m_node;

    /// State of node component, whether it is attached to a node
    /// or detached or in process of attaching/detaching.
    State m_state;
};


template <typename TMessageType, typename TClass, typename TMethod>
Node::MessageSubscriptionToken NodeComponent::addNodeComponentMessageHandler(TMessageType& messageType, TClass* nodeComponent, TMethod method)
{
    return getNode()->addMessageHandler(messageType, bind(&nodeComponentMessageHandler<TMessageType, TClass, TMethod>, nodeComponent, method, placeholders::_1));
}

}

#endif
