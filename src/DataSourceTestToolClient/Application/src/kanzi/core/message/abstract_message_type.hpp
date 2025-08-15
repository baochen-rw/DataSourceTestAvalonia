// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_MESSAGE_TYPE_HPP
#define KZ_ABSTRACT_MESSAGE_TYPE_HPP


#include "abstract_message_type_descriptor.hpp"


namespace kanzi
{

class MessageArguments;
template <typename T> class MessageType;
template <typename T> class DynamicMessageType;

class KANZI_API AbstractMessageType
{
    template <typename T> friend class MessageType;
    template <typename T> friend class DynamicMessageType;

    typedef void (AbstractMessageType::*bool_type)() const;
    void this_type_does_not_support_comparisons() const
    {
    }

public:

    typedef MessageArguments ArgumentsType;
    typedef function<void(MessageArguments&)> FunctionType;

#ifdef KZ_SUPPORTS_EXPLICIT_OPERATOR

    explicit operator bool() const
    {
        return m_descriptor ? true : false;
    }

#else

    operator bool_type() const
    {
        return m_descriptor ? &AbstractMessageType::this_type_does_not_support_comparisons : 0;
    }

#endif

    friend bool operator==(const AbstractMessageType& left, const AbstractMessageType& right)
    {
        return left.m_descriptor == right.m_descriptor;
    }

    friend bool operator!=(const AbstractMessageType& left, const AbstractMessageType& right)
    {
        return !(left.m_descriptor == right.m_descriptor);
    }

    friend bool operator<(const AbstractMessageType& left, const AbstractMessageType& right)
    {
        return left.m_descriptor < right.m_descriptor;
    }

    explicit AbstractMessageType() : m_descriptor(0)
    {
    }

    explicit AbstractMessageType(string_view name) : m_descriptor(AbstractMessageTypeDescriptor::find(name))
    {
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

    string getName() const
    {
        return m_descriptor->getName();
    }

    MessageRouting getRouting() const
    {
        return m_descriptor->getRouting();
    }

    const Metaclass* getArgumentsMetaclass() const
    {
        return m_descriptor->getArgumentsMetaclass();
    }

private:

    explicit AbstractMessageType(const AbstractMessageTypeDescriptor* descriptor) : m_descriptor(descriptor)
    {
    }

    const AbstractMessageTypeDescriptor* m_descriptor;
};

}

#endif
