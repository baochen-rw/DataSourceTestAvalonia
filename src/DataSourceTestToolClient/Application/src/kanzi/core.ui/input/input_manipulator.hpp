// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INPUT_MANIPULATOR_HPP
#define KZ_INPUT_MANIPULATOR_HPP

#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/node/node_fwd.hpp>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/message/message_type.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

#include <kanzi/core/legacy/util/math/kzc_ray.hpp>

/// Invalid touch point identifier.
#define KZU_INPUT_TOUCH_INVALID_ID              ((unsigned int)-1)

namespace kanzi
{

// Forward declarations.
class Node;
class Node2D;
class InputManipulator;
class MessageArguments;
class PanManipulator;
struct KzuInputTouchPoint;
class InputManager;

typedef shared_ptr<InputManipulator> InputManipulatorSharedPtr;
typedef weak_ptr<InputManipulator> InputManipulatorWeakPtr;

/// Touch point state.
enum KzuInputTouchPointState
{
    /// The point has been created by touching the screen.
    KZU_INPUT_TOUCH_POINT_STATE_DOWN = 0,

    /// The point has not moved since last report.
    KZU_INPUT_TOUCH_POINT_STATE_STATIONARY = 1,

    /// The point has moved since last report.
    KZU_INPUT_TOUCH_POINT_STATE_MOVE = 2,

    // The point has been released.
    KZU_INPUT_TOUCH_POINT_STATE_UP = 3
};

/// The structure describes the attributes for a touch point or mouse hit. The description 
/// includes the information about the identifier, state, coordinates, ray, and distance. 
/// Ray and distance fields are only applicable for 3D spaces.
/// \see InputManipulator
struct KzuInputTouchPoint
{
    /// Constructor.
    explicit KzuInputTouchPoint() :
        id(KZU_INPUT_TOUCH_INVALID_ID),
        state(KZU_INPUT_TOUCH_POINT_STATE_UP),
        x(0.0f),
        y(0.0f),
        distance(0.0f)
    {
    }

    /// Touch identifier.
    unsigned int id;

    /// Touch state.
    KzuInputTouchPointState state;

    /// Touch x coordinate.
    float x;

    /// Touch y coordinate.
    float y;

    /// Hit test object node.
    NodeWeakPtr objectNode;

    /// Hit test ray in 3D space.
    KzcRay ray;

    /// Hit test distance. This is the distance between the camera and the bounding 
    /// box of the hit test node.
    float distance;
};

/// Helper predicate functor which you can use to search for a touch point within 
/// a touch point container using the identifier of a touch point.
struct TouchPointIdEquals
{
    /// Constructor.
    /// \param id Touch point id to search for.
    explicit TouchPointIdEquals(unsigned int id)
        : touchPointId(id)
    {
    }

    /// Compares the ID of given touch point against constructor argument.
    /// \param touchPoint Touch point to compare.
    /// \return True, if IDs of touch point match, otherwise false.
    bool operator()(const KzuInputTouchPoint& touchPoint) const
    {
        return touchPoint.id == touchPointId;
    }

    /// Compares the ID of given touch point against constructor argument.
    /// \param touchPoint Pointer to touch point to compare.
    /// \return True, if IDs of touch point match, otherwise false.
    bool operator()(const KzuInputTouchPoint* touchPoint) const
    {
        return touchPoint->id == touchPointId;
    }

private:
    /// Touch point ID argument.
    const unsigned int touchPointId;
};

/// Helper predicate functor which you can use to search within a touch point 
/// container using the state of a touch point.
struct TouchPointStateEquals
{
    /// Constructor.
    /// \param state Touch point state to search for.
    explicit TouchPointStateEquals(KzuInputTouchPointState state)
        : touchPointState(state)
    {
    }

    /// Compares state of given touch point against constructor argument.
    /// \param touchPoint Touch point to compare.
    /// \return True, if touch point states match.
    bool operator()(const KzuInputTouchPoint& touchPoint) const
    {
        return touchPoint.state == touchPointState;
    }

    /// Compares state of given touch point against constructor argument.
    /// \param touchPoint Pointer to touch point to compare.
    /// \return True, if touch point states match.
    bool operator()(const KzuInputTouchPoint* touchPoint) const
    {
        return touchPoint->state == touchPointState;
    }

private:
    /// Touch point state argument.
    const KzuInputTouchPointState touchPointState;
};

/// The base class for the input manipulator. Use the input manipulators to recognize gestures, 
/// such as click or pinch, from incoming touch events. Kanzi does not differentiate touch events 
/// from mouse events. 
/// 
/// To use an input manipulator on a node, add it to that node with the Node::addInputManipulator() 
/// method. You can add more than one input manipulator to a node, but you can use only one to 
/// recognize a gesture. When you want to handle more than one gesture on a node, link the input 
/// manipulators to each other in order of importance of the gestures that they recognize.
///
/// You can link input manipulators sequentially. For example, if you want a node to recognize 
/// the pan, double-click, and click gestures in this order, link the ClickManipulator to the 
/// MultiClickManipulator, and the MultiClickManipulator to the PanManipulator.
/// 
/// The linking of the manipulators is directional. The linked manipulator is called the \b depend 
/// manipulator and the manipulator the dependant is linked to is called the \b fail manipulator.
/// You can link the two manipulators by calling #requireToFail() on the fail manipulator, passing 
/// the dependant manipulator as argument.
///
/// To receive both click and multi-click messages on a node, you need to configure the click 
/// manipulator to wait for the failure of the multi-click manipulator:
/// \snippet test_input_manipulators.cpp requireToFail
///
/// Gesture recognition
/// ----
/// Kanzi dispatches the touch points from the events to manipulators attached to nodes in phases:
/// -# Kanzi tunnels the touch points to nodes starting from the root node and ending at the 
/// hit test node. In this phase only the input manipulators that have the #RoutingTunneling 
/// routing mode set receive the touch points for recognition.
/// -# Kanzi continues to bubble the touch points from the hit test node to the root node, 
/// updating the nodes with input manipulators that have the #RoutingBubbling routing mode set.
/// -# Kanzi updates the input manipulators that are outside of the hierarchy of 
/// the hit test node.
///
/// The touch gesture recognition happens in the #notifyTouchInside() or #notifyTouchOutside()
/// methods of an input manipulator. Every input manipulator attached to a hit test 
/// node receives all the touch points occurred in the application. In each input manipulator
/// you must set the correct state to inform Kanzi that the input manipulator recognized a 
/// gesture. You do this by calling the #setState() method with the apropriate #State value.
/// 
/// When an input manipulator recognizes a touch event as a starting action of a gesture:
/// -# The manipulator enters the #StatePossible state. Usually every input manipulator 
/// takes the first touch point as a possible starting point of the gesture it recognizes.
/// In this phase, every input manipulator in the #StatePossible state receives the touch event.
/// -# When a manipulator recognizes the incoming touch event as a comprehensive gesture, 
/// depending on the type of the gesture, this manipulator sets its state to either #StateBegin,
/// #StateEnd, or #StateFail state.
/// -# Manipulators which recognize gestures where the touch point location is not changing, 
/// such as click or multi-click, and gestures where the touch location is updated, set the 
/// state to #StateEnd.
/// -# If the gesture recognition fails, manipulators set the #StateFail state value. 
/// It is important that you mark the gesture recognition failure in the failing manipulator.
/// This enables Kanzi to continue dispatching the touch event to the dependant manipulators.
/// Kanzi calls #onFail() method on the dependant manipulator linked, continuing the gesture 
/// recognition in that manipulator.
/// 
/// During and on gesture recognition, input manipulators can dispatch messages to the 
/// attached node, to inform the subscribed message handlers about the progress of the gesture. 
///
/// \see ClickManipulator, DragAndDropManipulator, LongPressManipulator, MultiClickManipulator,
/// PanManipulator, PinchManipulator
class KANZI_API InputManipulator : public Object
{
public:

    /// Enumeration for possible input manipulator states during touch or mouse input sequence.
    enum State
    {
        /// The manipulator is in initial state.
        StateReady,
        /// The manipulator started processing, but has not yet recognized a gesture. The system
        /// can fail the manipulator automatically.
        StatePossible,
        /// The manipulator recognized a continuous gesture.
        StateBegin,
        /// The manipulator recognized changes in a continuous gesture.
        StateChange,
        /// The manipulator finished recognizing a gesture.
        StateEnd,
        /// The manipulator failed recognizing a gesture.
        StateFail,
        /// Not in use.
        StateDelayed,
        /// Not in use.
        StateCanceled
    };

    /// Enumeration for the available touch event routing modes.
    enum TouchEventRoutingMode
    {
        /// Touch points are dispatched to the manipulators from the hit test node
        /// to the root node.
        RoutingBubbling,
        /// Touch points are dispatched to the manipulators from the root node to
        /// the hit test node.
        RoutingTunneling
    };

    typedef vector<KzuInputTouchPoint*> TouchPointsContainer;
    typedef TouchPointsContainer::const_iterator TouchPointsConstIterator;

    /// Structure to hold the state of the current touch points.
    struct TouchInfo
    {
        /// Touch points detected over the recipient node.
        TouchPointsContainer touchPoints;
        /// All touch points, including the touch points detected over the recipient.
        TouchPointsContainer allTouchPoints;
    };

     
    /// Message arguments for input manipulator messages.
    class KANZI_API InputMessageArguments : public MessageArguments
    {
    public:
#include "input_manipulator_properties.h"

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(InputMessageArguments, MessageArguments, "Kanzi.InputManipulator.InputMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(ManipulatorPointProperty)
            KZ_METACLASS_PROPERTY_TYPE(ManipulatorRayOriginProperty)
            KZ_METACLASS_PROPERTY_TYPE(ManipulatorRayDirectionProperty)
            KZ_METACLASS_PROPERTY_TYPE(HitTestPointProperty)
            KZ_METACLASS_PROPERTY_TYPE(HitTestRayOriginProperty)
            KZ_METACLASS_PROPERTY_TYPE(HitTestRayDirectionProperty)
            KZ_METACLASS_PROPERTY_TYPE(HitTestObjectProperty)
        KZ_METACLASS_END()

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

        /// The position of the primary touch point. 
        /// When hitting a 2D node, the value is in local space of the attached node or the provided reference
        /// node (see InputManipulator::setReferenceNode)
        /// When hitting a 3D node, the value is in local space of the enclosing viewport node.
        Vector2 getPoint() const { return getArgument(ManipulatorPointProperty); };
        void setPoint(Vector2 value) { setArgument(ManipulatorPointProperty, value); };

        /// The origin of the pick ray in the local space of the enclosing viewport node.
        /// ManipulatorRayOriginProperty is Provided when hitting a 3D node.
        Vector3 getRayOrigin() const { return getArgument(ManipulatorRayOriginProperty); };
        void setRayOrigin(Vector3 value) { setArgument(ManipulatorRayOriginProperty, value); };

        /// Pick ray direction vector (normalized) in the local space of the enclosing viewport node.
        /// ManipulatorRayDirectionProperty is provided when hitting a 3D node.
        Vector3 getRayDirection() const { return getArgument(ManipulatorRayDirectionProperty); };
        void setRayDirection(Vector3 value) { setArgument(ManipulatorRayDirectionProperty, value); };

        /// The position of the primary touch point in the object space of the node that generated the hit test.
        /// When hitting a 2D node, the value is in screen space.
        /// When hitting a 3D node, the value is in local space of the hit test camera.
        Vector2 getHitTestPoint() const { return getArgument(HitTestPointProperty); };
        void setHitTestPoint(Vector2 value) { setArgument(HitTestPointProperty, value); };

        /// Origin of the hit test ray in the local space of the hit test camera. Provided when hitting a 3D node.
        Vector3 getHitTestRayOrigin() const { return getArgument(HitTestRayOriginProperty); };
        void setHitTestRayOrigin(Vector3 value) { setArgument(HitTestRayOriginProperty, value); };

        /// Hit test ray direction vector (normalized) in the local space of the hit test camera. Provided when hitting a 3D node.
        Vector3 getHitTestRayDirection() const { return getArgument(HitTestRayDirectionProperty); };
        void setHitTestRayDirection(Vector3 value) { setArgument(HitTestRayDirectionProperty, value); };
    };

    KZ_ABSTRACT_METACLASS_BEGIN(InputManipulator, Object, "Kanzi.InputManipulator")
        KZ_METACLASS_NESTED_METACLASS(InputMessageArguments)
    KZ_METACLASS_END()

    /// Destructor.
    virtual ~InputManipulator();

    /// Reset the manipulator. When you reset a manipulator, you set its state to the 
    /// initial state (#StateReady).
    void reset();
    /// Notify manipulator of touch canceling.
    void cancel();

    /// Get the state of the input manipulator.
    /// \return The current state of the input manipulator.
    State getState() const;
    /// Set the state of the input manipulator.
    /// \param state The new state of the input manipulator.
    void setState(State state);

    /// Gets the node to which the input manipulator is attached.
    /// \return The pointer to the node to which the input manipulator is attached. If the 
    /// input manipulator is not attached to any node, \e nullptr.
    Node* getAttachedNode() const;
    /// Sets the input manipulator that must fail before Kanzi can recognize this 
    /// input manipulator.
    /// \param manipulatorToFail The manipulator whose failure is required in order for this manipulator to succeed.
    void requireToFail(InputManipulatorWeakPtr manipulatorToFail);
    /// Gets the fail manipulator.
    /// \return The input manipulator on which this input manipulator depends.
    InputManipulatorWeakPtr getFailManipulator() const;
    /// Gets the dependant input manipulator. When this input manipulator fails, 
    /// Kanzi notifies the dependant input manipulator.
    /// \return The manipulator object this manipulator depends on.
    InputManipulator* getDependManipulator() const;

    /// Tells whether the input manipulator is attached to a node.
    /// \return True, if the input manipulator is attached, otherwise false.
    bool isAttached() const
    {
        return m_node ? true : false;
    }

    /// Override the attached node as the hit test reference node.
    /// \param referenceNode The pointer to the reference node.
    void setReferenceNode(NodeWeakPtr referenceNode)
    {
        m_referenceNode = referenceNode;
    }

    /// Sets the touch event routing mode that you want the input manager to use
    /// when distributing the touch points to manipulators. The default mode is 
    /// #RoutingBubbling.
    ///
    /// Set the mode to #RoutingTunneling when you want Kanzi to recognize an underlying 
    /// gesture before the gestures in the child nodes of the node with an input 
    /// manipulator. For example, use the #RoutingTunneling routing mode for a node with 
    /// a two-finger pan input manipulator which has a Scroll View child node. With 
    /// this setting the input manager recognizes the two-finger pan before the pan 
    /// in the Scroll View node.
    ///
    /// \param mode The touch event routing mode you want the input manager to use.
    /// \see TouchEventRoutingMode
    void setTouchEventRoutingMode(TouchEventRoutingMode mode)
    {
        m_touchEventRoutingMode = mode;
    }

    /// Returns the current touch event routing mode.
    /// \return The current touch event routing mode that the input manager uses.
    TouchEventRoutingMode getTouchEventRoutingMode()
    {
        return m_touchEventRoutingMode;
    }

protected:
    /// Constructor
    explicit InputManipulator(Domain* domain);
    /// Attach function for input manipulators. Called when the manipulator is attached
    /// to a node.
    virtual void onAttach();
    /// Detach function for input manipulators. Called when the manipulator is detached
    /// from a node.
    virtual void onDetach();
    /// Reset function for input manipulators. Called when the manipulator is reset.
    virtual void onReset();
    /// Cancel function for input manipulators. Called when the gesture recognition for
    /// the manipulator is cancelled.
    virtual void onCancel();
    /// Fail function for input manipulators. Called by the dependant manipulator on
    /// gesture recognition failure.
    virtual void onFail();
    /// Notify the input manipulator about touch events that occur inside the subtree 
    /// of the input manipulator
    /// \param touchInfo The available touch points, including those that occur over
    /// the attached node.
    virtual void notifyTouchInside(const TouchInfo& touchInfo);
    /// Notify the input manipulator about touch events that occur outside the subtree 
    /// of the input manipulator
    /// \param touchInfo The touch points ocurring outside of the subtree.
    virtual void notifyTouchOutside(const TouchInfo& touchInfo);

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        // TODO provide info
        return PropertyTypeEditorInfoSharedPtr();
    }

    /// Add hit test information arguments to the message from the touch point.
    /// Derive local point and manipulator node from touch point.
    /// \param message Target message.
    /// \param touchPoint Current touch point.
    void addHitTestArguments(MessageArguments& message, const KzuInputTouchPoint& touchPoint);

private:
    /// Attach the input manipulator to the node. Called automatically when manipulator is added to the node.
    void attach(Node& node);
    /// Detach the input manipulator. Called automatically when manipulator is removed from the node.
    void detach();
    /// Get the change flag of the manipulator. Used internally.
    /// \internal
    bool isHandled() const;
    /// Set the change flag of the manipulator. Used internally.
    /// \internal
    void setHandled(bool handled);
    /// Attach or detach the input manager to the manipulator during recognition. Used internally.
    /// \internal
    void setInputManager(InputManager* inputManager);
    /// Get the attached input manager of the manipulator. Used internally.
    /// \internal
    InputManager* getInputManager() const;

    // Find the 2D manipulator node for this input manipulator.
    // \return 2D manipulator node or 0.
    Node2D* findNearestParent2D();

    // The node where the input manipulator is attached to.
    Node* m_node;
    // Input manager reference.
    InputManager* m_inputManager;
    // The state of the manipulator.
    State m_state;
    // The handled flag to identify input phases.
    bool m_handled;
    // The input manipulator that has to fail for this manipulator to succeed.
    InputManipulatorWeakPtr m_failManipulator;
    // The input manipulator that will be notified in case this manipulator fails.
    InputManipulator* m_dependManipulator;
    // Optional override for the hit test node (default is the node where the input manipulator
    // is attached to).
    NodeWeakPtr m_referenceNode;
    // The routing mode for touch events.
    TouchEventRoutingMode m_touchEventRoutingMode;

    friend class InputManager;
    friend class InputManipulatorCollection;
    friend class Node;
    friend class PanManipulator;
};


}


#endif
