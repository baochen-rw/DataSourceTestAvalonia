// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_COMMAND_HPP
#define KZ_COMMAND_HPP

#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

namespace kanzi
{

/// Command class defines property and message types used in implementation of commands.
class KANZI_API Command
{
public:

    static PropertyType<string> CommandProperty;

    /// Represents the message arguments for command messages.
    class KANZI_API CommandMessageArguments: public MessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(CommandMessageArguments, MessageArguments, "Kanzi.Command.CommandMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(CommandProperty)
        KZ_METACLASS_END()

        string getCommand() const { return getArgument(CommandProperty); };
        void setCommand(string value) { setArgument(CommandProperty, value); };
    };

    static MessageType<CommandMessageArguments> CommandMessage;

    KZ_STATIC_METACLASS_BEGIN(Command, "Kanzi.Command")
        KZ_METACLASS_PROPERTY_TYPE(CommandProperty)
        KZ_METACLASS_MESSAGE_TYPE(CommandMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

}

#endif