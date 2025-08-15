// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_MESSAGE_TYPE_HPP
#define KZ_MESSAGE_TYPE_HPP


#include "message_routing.hpp"
#include "abstract_message_type_descriptor.hpp"
#include "abstract_message_type.hpp"

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/type_traits.hpp>
#include <kanzi/core/cpp/stdexcept.hpp>
#include <kanzi/core/cpp/functional.hpp>
#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/string/fixed_string.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>


struct KzcInputStream;

namespace kanzi
{

class Metaclass;
class AbstractMessageType;
class MessageArguments;
template <typename T> class DynamicMessageType;

template<typename T>
struct MessageArgumentsBaseMetaclassWrapper
{
    static const Metaclass* getStaticMetaclass()
    {
        return T::getStaticMetaclass();
    }
};

template<>
struct MessageArgumentsBaseMetaclassWrapper<MessageArguments>
{
    static const Metaclass* getStaticMetaclass()
    {
        return 0;
    }
};

template <class TArguments>
class MessageType
{
    friend class AbstractMessageType;
    template <typename T> friend class DynamicMessageType;

public:

    typedef TArguments ArgumentsType;
    typedef function<void (ArgumentsType&)> FunctionType;

    explicit MessageType(FixedString name, PropertyTypeEditorInfo* editorInfo) :
        m_descriptor(new AbstractMessageTypeDescriptor(name, MessageRoutingTunnelingBubbling, editorInfo))
    {
        // Instantiate getArgumentsMetaclass to make sure TArguments has a metaclass.
        (void)&getArgumentsMetaclass;
    }

    explicit MessageType(FixedString name, MessageRouting routing, PropertyTypeEditorInfo* editorInfo) :
        m_descriptor(new AbstractMessageTypeDescriptor(name, routing, editorInfo))
    {
        // Instantiate getArgumentsMetaclass to make sure TArguments has a metaclass.
        (void)&getArgumentsMetaclass;
    }

    explicit MessageType(MetadataGeneratedName name, MessageRouting routing, PropertyTypeEditorInfo* editorInfo) :
        m_descriptor(new AbstractMessageTypeDescriptor(name, routing, editorInfo))
    {
        // Instantiate getArgumentsMetaclass to make sure TArguments has a metaclass.
        (void)&getArgumentsMetaclass;
    }

    ~MessageType()
    {
        delete m_descriptor;
    }

    operator AbstractMessageType() const
    {
        return AbstractMessageType(m_descriptor);
    }

    string getName() const
    {
        return m_descriptor->getName();
    }

    MessageRouting getRouting() const
    {
        return m_descriptor->getRouting();
    }

    static const Metaclass* getArgumentsMetaclass()
    {
        return MessageArgumentsBaseMetaclassWrapper<ArgumentsType>::getStaticMetaclass();
    }

    const KzuMessageType* get() const
    {
        return m_descriptor;
    }

    /// Gets editor info for the message type.
    /// \return Shared pointer to editor info.
    PropertyTypeEditorInfoSharedPtr getEditorInfo() const
    {
        return m_descriptor->getEditorInfo();
    }

    void attachArgumentsMetaclass() const
    {
        kzAssert(m_descriptor);
        m_descriptor->attachArgumentsMetaclass(getArgumentsMetaclass());
    }

protected:

    explicit MessageType() : m_descriptor(0)
    {
    }

    MessageType(const MessageType&) KZ_DELETED_FUNCTION;
    MessageType& operator=(const MessageType&) KZ_DELETED_FUNCTION;

    const AbstractMessageTypeDescriptor* m_descriptor;
};

}


#endif
