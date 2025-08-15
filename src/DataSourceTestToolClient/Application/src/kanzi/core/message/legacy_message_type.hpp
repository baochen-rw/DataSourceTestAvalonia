// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_LEGACY_MESSAGE_TYPE_HPP
#define KZ_LEGACY_MESSAGE_TYPE_HPP


#include "message_routing.hpp"

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/metadata/metadata.hpp>
#include <kanzi/core/error/exception.hpp>
#include <kanzi/core/string/fixed_string.hpp>


namespace kanzi
{

class Metaclass;

}

struct KANZI_API KzuMessageType
{
    explicit KzuMessageType(kanzi::MetadataGeneratedName name, kanzi::MessageRouting routing);
    explicit KzuMessageType(kanzi::FixedString name, kanzi::MessageRouting routing);

    const char* getName() const
    {
        return m_name;
    }

    kanzi::MessageRouting getRouting() const
    {
        return static_cast<kanzi::MessageRouting>(m_flags & s_routingMask);
    }

    const kanzi::Metaclass* getArgumentsMetaclass() const
    {
        return m_argumentsMetaclass;
    }

    void attachArgumentsMetaclass(const kanzi::Metaclass* metaclass) const;

protected:

    ~KzuMessageType();

private:

    /// Bit flag to encode that the name of the message type is a local copy.
    static const uint32_t s_managedStringFlag = 1u << 31u;
    /// Bit mask to extract routing from m_flags.
    static const uint32_t s_routingMask = ~s_managedStringFlag;

    uint32_t m_flags;
    const char* m_name;
    mutable const kanzi::Metaclass* m_argumentsMetaclass;    
};


#endif
