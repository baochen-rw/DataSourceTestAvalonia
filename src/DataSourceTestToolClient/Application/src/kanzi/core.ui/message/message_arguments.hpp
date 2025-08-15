// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MESSAGE_ARGUMENTS_HPP
#define KZ_MESSAGE_ARGUMENTS_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/chrono.hpp>
#include <kanzi/core/property/property_type.hpp>
#include <kanzi/core.ui/property/variant.hpp>
#include <kanzi/core/message/message_type.hpp>


// Forward declarations.
struct KzuMessageDispatcher;


namespace kanzi
{

// Forward declarations.
class Node;
class Metaclass;


/// Message arguments is the base class for arguments passed in messages.
class KANZI_API MessageArguments
{
public:

    /// Linked list entry containing arguments type and value.
    /// Used internally.
    struct ArgumentEntry
    {
        /// Constructor.
        explicit ArgumentEntry() : next(KZ_NULL)
        {
        }

        /// Next argument in linked list of arguments.
        ArgumentEntry* next;
        /// Message argument type.
        AbstractPropertyType type;
        /// Message argument value.
        Variant variant;
    };

    explicit MessageArguments();
    // Internal constructor. TODO: remove when messages are no longer dispatched in C.
    explicit MessageArguments(AbstractMessageType messageType);

    ~MessageArguments();

    template <typename TDataType>
    TDataType getArgument(const PropertyType<TDataType>& argumentType) const
    {
        const ArgumentEntry* argument = findArgument(argumentType);
        if (argument)
        {
            return get<TDataType>(argument->variant);
        }

        return argumentType.getDefaultValue();
    }

    bool getAbstractArgument(AbstractPropertyType argumentType, Variant& variant) const;

    template <typename TDataType>
    void setArgument(const PropertyType<TDataType>& argumentType, typename PropertyType<TDataType>::DataType value)
    {
        ArgumentEntry* argument = acquireArgument(argumentType);
        argument->variant = kanzi::move(value);
    }

    void setAbstractArgument(AbstractPropertyType argumentType, const Variant& variant);

    bool isFrom(const Node& source) const
    {
        return m_source == &source;
    }

    shared_ptr<Node> getSource() const;

    void setHandled(bool handled)
    {
        m_handled = handled;
    }

    bool isHandled() const
    {
        return m_handled;
    }

    chrono::milliseconds getTimestamp() const
    {
        return m_timestamp;
    }

    KzuMessageDispatcher* getDispatcher() const
    {
        return m_dispatcher;
    }

    AbstractMessageType getType() const
    {
        return m_messageType;
    }

    void setSource(Node* source)
    {
        m_source = source;
    }

    void setTimestamp(chrono::milliseconds timestamp)
    {
        m_timestamp = timestamp;
    }

    void setValid(bool valid)
    {
        m_valid = valid;
    }

    bool isValid() const
    {
        return m_valid;
    }

    /// Internal function.
    void setDispatcher_internal(KzuMessageDispatcher* dispatcher)
    {
        m_dispatcher = dispatcher;
    }
    
    /// Internal function.
    void setType_internal(AbstractMessageType type)
    {
        m_messageType = type;
    }

    /// Gets the current size of memory pool of argument entries.
    static size_t getArgumentAllocatorPoolSize();

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        // TODO provide info
        return PropertyTypeEditorInfoSharedPtr();
    }

private:

    MessageArguments(const MessageArguments&) KZ_DELETED_FUNCTION;
    MessageArguments& operator=(const MessageArguments&) KZ_DELETED_FUNCTION;

    /// Finds the message argument that matches the given property type or creates it if it doesn't exist.
    ArgumentEntry* acquireArgument(AbstractPropertyType argumentType);
    /// Finds the message argument that matches the given property type.
    ArgumentEntry* findArgument(AbstractPropertyType argumentType);
    /// Finds the message argument that matches the given property type.
    const ArgumentEntry* findArgument(AbstractPropertyType argumentType) const;
    /// Release all message arguments.
    void releaseArguments();

    /// Indicates whether arguments object is valid.
    bool m_valid;
    /// Indicates whether arguments object has been handled.
    bool m_handled;
    /// Timestamp of the message.
    chrono::milliseconds m_timestamp;
    /// Dispatcher handling the message.
    KzuMessageDispatcher* m_dispatcher;
    /// Message type of the arguments.
    AbstractMessageType m_messageType;
    /// Source of the message.
    Node* m_source;
    /// First entry in the linked list of arguments.
    ArgumentEntry* m_firstArgument;
};

}


#endif
