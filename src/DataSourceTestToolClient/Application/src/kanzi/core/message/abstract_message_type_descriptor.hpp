// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_MESSAGE_TYPE_DESCRIPTOR_HPP
#define KZ_ABSTRACT_MESSAGE_TYPE_DESCRIPTOR_HPP

#include "legacy_message_type.hpp"
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/metadata/editor_metadata.hpp>

struct KzcInputStream;

namespace kanzi
{

class KANZI_API AbstractMessageTypeDescriptor : public KzuMessageType
{
public:
    
    explicit AbstractMessageTypeDescriptor(MetadataGeneratedName name, MessageRouting routing, PropertyTypeEditorInfo* editorInfo);
    explicit AbstractMessageTypeDescriptor(FixedString name, MessageRouting routing, PropertyTypeEditorInfo* editorInfo);
    ~AbstractMessageTypeDescriptor();
    
    typedef unique_ptr<AbstractMessageTypeDescriptor> ManagedDescriptor;
    
    static const AbstractMessageTypeDescriptor* find(string_view name);

    static void registerDescriptor(ManagedDescriptor descriptor);

    /// Gets editor info for the message type.
    /// \return Shared pointer to editor info.
    PropertyTypeEditorInfoSharedPtr getEditorInfo() const
    {
#if defined(KZ_EDITOR_INFO_METADATA)
        return m_editorInfo;
#else
        return 0;
#endif
}

private:
    
    static void registerDescriptor(AbstractMessageTypeDescriptor* descriptor);
    static void unregisterDescriptor(AbstractMessageTypeDescriptor* descriptor);

#if defined(KZ_EDITOR_INFO_METADATA)
    PropertyTypeEditorInfoSharedPtr m_editorInfo;
#endif
};

}

#endif
