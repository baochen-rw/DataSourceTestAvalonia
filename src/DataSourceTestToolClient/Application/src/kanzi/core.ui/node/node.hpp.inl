// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_HPP_INL
#define KZ_NODE_HPP_INL

namespace kanzi
{

template <typename DataType>
DataType Node::getAbstractProperty(AbstractPropertyType abstractPropertyType) const
{
    DynamicPropertyType<DataType> dynamicPropertyType(abstractPropertyType);
    return getProperty(dynamicPropertyType);
}

template <typename DataType>
optional<typename PropertyType<DataType>::DataType> Node::getOptionalAbstractProperty(AbstractPropertyType abstractPropertyType) const
{
    DynamicPropertyType<DataType> dynamicPropertyType(abstractPropertyType);
    return getOptionalProperty(dynamicPropertyType);
}

template <typename TMessageType, typename TClass, typename TClassMethod>
Node::MessageSubscriptionToken Node::addMessageHandler(TMessageType& messageType, TClass* messageHandlerObject, TClassMethod method)
{
    return addMessageHandler(messageType, messageHandlerObject, method, this);
}

template <typename TMessageType, typename TClass, typename TClassMethod>
Node::MessageSubscriptionToken Node::addMessageFilter(TMessageType& messageType, TClass* messageHandlerObject, TClassMethod method)
{
    return addMessageHandler(messageType, messageHandlerObject, method, KZ_NULL);
}

template <typename TMessageType>
Node::MessageSubscriptionToken Node::addMessageHandler(const TMessageType& messageType, typename TMessageType::FunctionType function)
{
    return addMessageHandler(messageType, function, this);
}

template <typename TMessageType>
Node::MessageSubscriptionToken Node::addMessageFilter(const TMessageType& messageType, typename TMessageType::FunctionType function)
{
    return addMessageHandler(messageType, function, KZ_NULL);
}

template <typename TArgumentsType>
void Node::dispatchMessage(const MessageType<TArgumentsType>& messageType, typename MessageType<TArgumentsType>::ArgumentsType& messageArguments)
{
    if (messageArguments.isHandled())
    {
        kzThrowException(runtime_error("Trying to dispatch a message with arguments marked as handled."));
    }
    kzsError result;
    messageArguments.setType_internal(messageType);
    result = kzuMessageDispatcherDispatchMessage(getMessageDispatcher(), &messageArguments, this);
    kzThrowIfError(result);
}

template <typename TMessageType, typename TClass, typename TClassMethod>
Node::MessageSubscriptionToken Node::addMessageHandler(TMessageType& messageType, TClass* messageHandlerObject, TClassMethod method, Node* messageSourceFilter)
{
#if defined KZ_SUPPORTS_LAMBDA
    auto lockable = weak_ptr<void>(messageHandlerObject->shared_from_this());
    return addMessageHandlerInternal(messageType.get(), [messageHandlerObject, method, lockable](MessageArguments* message)
    {
        auto lock = lockable.lock();
        if (lock)
        {
            (messageHandlerObject->*method)(*static_cast<typename TMessageType::ArgumentsType*>(message));
        }
    },
        messageSourceFilter);
#else
    typename TMessageType::FunctionType methodInvoker = bind(method, messageHandlerObject, placeholders::_1);
    shared_ptr<void> lockObject = messageHandlerObject->shared_from_this();
    MessageSubscriptionFunction trackedPtrInvoker = bind(&trackedMessageAdapter<TMessageType>, methodInvoker, weak_ptr<void>(lockObject), placeholders::_1);

    return addMessageHandlerInternal(messageType.get(), trackedPtrInvoker, messageSourceFilter);
#endif
}

template <typename TMessageType>
Node::MessageSubscriptionToken Node::addMessageHandler(const TMessageType& messageType, typename TMessageType::FunctionType function, Node* messageSourceFilter)
{
#if defined KZ_SUPPORTS_LAMBDA
    return addMessageHandlerInternal(messageType.get(), [function](MessageArguments* message)
    {
        function(*static_cast<typename TMessageType::ArgumentsType*>(message));
    },
        messageSourceFilter);
#else
    MessageSubscriptionFunction functorInvoker = bind(&functorMessageAdapter<TMessageType>, function, placeholders::_1);

    return addMessageHandlerInternal(messageType.get(), functorInvoker, messageSourceFilter);
#endif
}

template<typename T>
shared_ptr<T> Node::acquireResource(const ResourceID& id) const
{
    ResourceSharedPtr resource = acquireResource(id);
    if (resource)
    {
        shared_ptr<T> convertedResource = dynamic_pointer_cast<T>(resource);
        if (!convertedResource)
        {
            kzThrowException(runtime_error("Bad dynamic cast when acquiring resource id '" + id.toString() + "'"));
        }
        return convertedResource;
    }
    return shared_ptr<T>();
}

template<typename T>
shared_ptr<T> Node::tryAcquireResource(const ResourceID& id) const
{
    return dynamic_pointer_cast<T>(tryAcquireResource(id));
}

template <typename Type>
shared_ptr<Type> Node::lookupNode(string_view pathOrKey)
{
    Node* node = lookupNodeRaw(pathOrKey);
    if (!node)
    {
        return shared_ptr<Type>();
    }

    return dynamic_pointer_cast<Type>(node->shared_from_this());
}

template <typename TNodeType>
shared_ptr<TNodeType> Node::findAbstractChild(string_view name)
{
    return dynamic_pointer_cast<TNodeType>(findAbstractChildOverride(name));
}

template <class TMessageType>
void Node::trackedMessageAdapter(typename TMessageType::FunctionType& function, const weak_ptr<void>& weakPtr, MessageArguments* message)
{
    // Acquire ownership
    shared_ptr<void> lock = weakPtr.lock();
    if (lock)
    {
        function(*static_cast<typename TMessageType::ArgumentsType*>(message));
    }
}

template <class TMessageType>
void Node::functorMessageAdapter(typename TMessageType::FunctionType& function, MessageArguments* message)
{
    function(*static_cast<typename TMessageType::ArgumentsType*>(message));
}

template <typename Type>
shared_ptr<Type> findParent(const Node& node)
{
    Node* currentNode = node.getParent();

    while (currentNode)
    {
        if (dynamic_cast<Type*>(currentNode))
        {
            // It is safe to use static_cast now
            return static_pointer_cast<Type>(currentNode->shared_from_this());
        }

        currentNode = currentNode->getParent();
    }

    return shared_ptr<Type>();
}

template <typename Type>
shared_ptr<Type> Node::lookupNodeComponent(string_view name)
{
    if (!name.empty())
    {
        // Retrieve node component by name if it is specified.
        NodeComponentSharedPtr nodeComponent = findNodeComponent(name);

        return dynamic_pointer_cast<Type>(nodeComponent);
    }
    else
    {
        // If name is not specified, retrieve the fist anonymous node component which implements specified type.
        const Metaclass* metaclass = Type::getStaticMetaclass();
        NodeComponentSharedPtr nodeComponent = findAnonymousNodeComponent(metaclass);

        return dynamic_pointer_cast<Type>(nodeComponent);
    }
}

}

#endif // KZ_NODE_HPP_INL
