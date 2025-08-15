// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DYNAMIC_MESSAGE_TYPE_HPP
#define KZ_DYNAMIC_MESSAGE_TYPE_HPP

#include "message_type.hpp"

#include <kanzi/core/core_api.hpp>
#include <kanzi/core/metadata/metaclass.hpp>


namespace kanzi
{

template <typename TArgumentsClass>
class KANZI_CORE_TEMPLATE_API DynamicMessageType : public MessageType<TArgumentsClass>
{
public:

    explicit DynamicMessageType(string_view name)
    {
        const AbstractMessageTypeDescriptor* descriptor = AbstractMessageTypeDescriptor::find(name);

        if (!descriptor)
        {
            kzThrowException(logic_error("Failed to find message type '" + string(name) + "'"));
        }

        const Metaclass* staticMetaclass = this->getArgumentsMetaclass();
        const Metaclass* dynamicMetaclass = descriptor->getArgumentsMetaclass();
        // Note that null arguments class means that the MessageArguments base class is used.
        if (staticMetaclass && (!dynamicMetaclass || !dynamicMetaclass->isDerivedFrom(staticMetaclass)))
        {
            kzThrowException(logic_error("Trying to construct DynamicMessageType with mismatched arguments."));
        }

        this->m_descriptor = descriptor;
    }

    explicit DynamicMessageType(AbstractMessageType abstractMessageType)
    {
        if (!abstractMessageType)
        {
            kzThrowException(logic_error("Trying to construct DynamicMessageType from null AbstractMessageType"));
        }

        const Metaclass* staticMetaclass = this->getArgumentsMetaclass();
        const Metaclass* dynamicMetaclass = abstractMessageType.getArgumentsMetaclass();
        // Note that null arguments class means that the MessageArguments base class is used.
        if (staticMetaclass && (!dynamicMetaclass || !dynamicMetaclass->isDerivedFrom(staticMetaclass)))
        {
            kzThrowException(logic_error("Trying to construct DynamicMessageType with mismatched arguments."));
        }

        this->m_descriptor = abstractMessageType.m_descriptor;
    }

    ~DynamicMessageType()
    {
        this->m_descriptor = 0;
    }
};


}


#endif
