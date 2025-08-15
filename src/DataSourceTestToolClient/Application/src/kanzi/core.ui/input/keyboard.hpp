// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/platform/input/common/kzs_input.h>
#include <kanzi/core/metadata/metaclass.hpp>

namespace kanzi
{

/// Represents keyboard.
class KANZI_API Keyboard
{
public:

    /// Represents base message arguments for key state change messages.
    class KANZI_API KeyStateChangedMessageArguments: public MessageArguments
    {
    public:

        /// \name Properties
        /// \{
#include "keyboard_properties.h"
        /// \}

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(KeyStateChangedMessageArguments, MessageArguments, "Kanzi.Keyboard.KeyStateChangedMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(KeyProperty)
        KZ_METACLASS_END()

        KzsInputKey getKey() const { return static_cast<KzsInputKey>(getArgument(KeyProperty)); };
        void setKey(KzsInputKey value) { setArgument(KeyProperty, static_cast<int>(value)); };
    };

    /// Represents message arguments of key down message.
    class KANZI_API KeyDownMessageArguments: public KeyStateChangedMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(KeyDownMessageArguments, KeyStateChangedMessageArguments, "Kanzi.Keyboard.KeyDownMessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of key up message.
    class KANZI_API KeyUpMessageArguments: public KeyStateChangedMessageArguments
    {
    public:

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(KeyUpMessageArguments, KeyStateChangedMessageArguments, "Kanzi.Keyboard.KeyUpMessageArguments")
        KZ_METACLASS_END()
    };

    static MessageType<KeyDownMessageArguments> KeyDownMessage;
    static MessageType<KeyUpMessageArguments> KeyUpMessage;

    KZ_STATIC_METACLASS_BEGIN(Keyboard, "Kanzi.Keyboard")
        KZ_METACLASS_MESSAGE_TYPE(KeyDownMessage)
        KZ_METACLASS_MESSAGE_TYPE(KeyUpMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

}

#endif