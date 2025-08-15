// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PAN_MANIPULATOR_HPP
#define KZ_PAN_MANIPULATOR_HPP

#include "input_manipulator.hpp"

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core.ui/input/input_manipulator.hpp>

namespace kanzi
{

class PanManipulator;

typedef shared_ptr<PanManipulator> PanManipulatorSharedPtr;

/// Pan input manipulator recognizes pan gesture from incoming touch events. It generates messages necessary to 
/// implement logic for objects users can move or pan. For example, use the pan input manipulator to create a map view.
///
/// Examples
/// ----
///
/// To receive the pan move events, add message handler for the MovedMessage.
///
/// First create a handler method:
/// \snippet test_input_manipulators.cpp Pan moved message handler
///
/// Then add a message handler for your node:
/// \snippet test_input_manipulators.cpp Subscribe pan moved

class KANZI_API PanManipulator : public InputManipulator
{
public:
    /// Message arguments for pan gesture started message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API StartedMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StartedMessageArguments, InputMessageArguments, "Kanzi.PanManipulator.StartedMessageArguments")
        KZ_METACLASS_END()
    };

    /// Message arguments for moved message sent during pan gesture. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API MovedMessageArguments: public InputMessageArguments
    {
    public:

#include "pan_manipulator_properties.h"

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(MovedMessageArguments, InputMessageArguments, "Kanzi.PanManipulator.MovedMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(PanDeltaProperty)
        KZ_METACLASS_END()

        /// The distance in pixels pan has progressed since the last message in the pan gesture sequence.
        Vector2 getDelta() const { return getArgument(PanDeltaProperty); };
        void setDelta(Vector2 value) { setArgument(PanDeltaProperty, value); };

		static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Message arguments for pan gesture finished message. Inherits argument properties from InputManipulator::InputMessageArguments.
    class KANZI_API FinishedMessageArguments: public InputMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(FinishedMessageArguments, InputMessageArguments, "Kanzi.PanManipulator.FinishedMessageArguments")
        KZ_METACLASS_END()
    };
    
    /// Message type for notifying start of the pan gesture.
    /// StartedMessage is generated when touch is pressed or arrives to the attached node area.
    static MessageType<StartedMessageArguments> StartedMessage;
    /// Message type for notifying position updates during pan gesture.
    /// MovedMessage is sent first when the pan threshold is exceeded either on horizontal or vertical axis and after that when the tracked touch has moved between updates.
    static MessageType<MovedMessageArguments> MovedMessage;
    /// Message type for notifying completion of the pan gesture.
    /// FinishedMessage is sent when the tracked touch is released or the gesture is canceled.
    static MessageType<FinishedMessageArguments> FinishedMessage;

    KZ_METACLASS_BEGIN(PanManipulator, InputManipulator, "Kanzi.PanManipulator")
        KZ_METACLASS_MESSAGE_TYPE(StartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(MovedMessage)
        KZ_METACLASS_MESSAGE_TYPE(FinishedMessage)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    static PanManipulatorSharedPtr create(Domain* domain, string_view /*name*/ = "")
    {
        return make_polymorphic_shared_ptr<InputManipulator>(new PanManipulator(domain));
    }

    /// Set the threshold the finger has to move before pan is recognized.
    /// Components of the threshold may be Node2D::unboundedLayoutValue() to disable recognition along an axis.
    /// \param threshold Threshold in pixels required for the pan to be recognized.
    /// \param panAxis Axis for pan threshold.
    void setRecognitionThreshold(Vector2 threshold)
    {
        m_panThreshold = threshold;
    }
    /// Returns the gesture recognition threshold values.
    Vector2 getRecognitionThreshold() const
    {
        return m_panThreshold;
    }

    /// Returns the minimum number of touches on the node area for this gesture to be recognized. The default is 1.
    /// \see setMaximumNumberOfTouches()
    size_t getMinimumNumberOfTouches();
    
    /// Sets the minimum number of touches on the node area for this gesture to be recognized.
    /// \see getMaximumNumberOfTouches()
    void setMinimumNumberOfTouches(size_t minimumTouches);

    /// Returns the maximum number of touches on the node area for this gesture to be recognized. The default is unlimited.
    /// \see setMaximumNumberOfTouches()
    size_t getMaximumNumberOfTouches();

    /// Sets the maximum number of touches on the node area for this gesture to be recognized.
    /// \see getMaximumNumberOfTouches()
    void setMaximumNumberOfTouches(size_t maximumTouches);

protected:
    /// Constructor.
    explicit PanManipulator(Domain* domain);

    /// InputManipulator::notifyTouchInside implementation
    virtual void notifyTouchInside(const TouchInfo& touchInfo) KZ_OVERRIDE;
    
    /// InputManipulator::notifyTouchOutside implementation
    virtual void notifyTouchOutside(const TouchInfo& touchInfo) KZ_OVERRIDE;
    
    /// InputManipulator::onReset implementation
    virtual void onReset() KZ_OVERRIDE;

    /// Update the pan gesture state based on the touch event.
    void trackPan(const InputManipulator::TouchInfo& touchInfo);

private:

    /// Recognition threshold in pixels along cardinal directions.
    /// Components may be Node2D::unboundedLayoutValue() to disable recognition in that direction.
    Vector2 m_panThreshold;

    /// Touch ID.
    unsigned int m_touchId;
    /// Position the panning started from in global space.
    Vector2 m_position;
    /// Position the panning started from in local space of nearest 2D parent.
    optional<Vector2> m_localPosition;
    /// Is tracking panning.
    bool m_panning;
    /// Minimum number of touches
    size_t m_minimumTouches;
    /// Maximum number of touches
    size_t m_maximumTouches;
};

}


#endif
