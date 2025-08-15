// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_INPUT_MANAGER_HPP
#define KZ_INPUT_MANAGER_HPP

#include <kanzi/core.ui/input/input_manipulator.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core/cpp/vector.hpp>

struct KzsEvent;
struct KzsInputEventKey;
struct KzsInputEventTouch;
struct KzsInputEventPointer;
struct KzsEventQueue;

namespace kanzi
{

// Forward declarations.
class Domain;
class Node2D;
class FocusManager;

/// InputManager converts the events from the given event queue into input specific
/// messages. The events supported are key, touch, and mouse pointer events. The key
/// events are dispatched through Keyboard::KeyDownMessage and Keyboard::KeyUpMessage.
/// The touch and pointer events are unified into press, change and release messages,
/// and forwarded to InputManipulators, which in turn handles the input and dispatch
/// those through proprietary messages. The input manipulators are gathered automatically
/// from the node or its children passed as argument to the processEvents() method.
/// \see Keyboard, InputManipulator
class KANZI_API InputManager
{
public:
    /// Create an input manager.
    /// \param domain The domain that owns the input manager.
    explicit InputManager(Domain* domain);
    virtual ~InputManager();

    /// Returns the instance of the focus manager.
    /// \return Instance of the focus manager.
    FocusManager* getFocusManager() const;

    /// Processes a queue of input events.
    /// \param queue Event queue that holds events that are processed.
    /// \param node A node whose subtree can receive events that are processed. 
    void processEvents(const struct KzsEventQueue* queue, Node2D* node);

    /// Attempts to set focus to a node.
    /// \deprecated in version 3.6.3. Use FocusManager's trySetActiveFocus() instead.
    NodeSharedPtr setFocus(NodeSharedPtr newFocusNode);
    
    /// Gets currently focused node.
    /// \deprecated in version 3.6.3. Use FocusManager's getActiveFocus() instead.
    NodeSharedPtr getFocus() const;

    /// Node notifies the input manager that Kanzi is detaching it from the scene graph.
    /// \param node The node which is detached.
    void notifyNodeDetached(Node& node);

private:
    friend class InputManipulator;

    /// Removes the input manipulator dependencies from input manager.
    /// \param inputManipulator The input manipulator that is removed from the input manager.
    void notifyManipulatorDetached(InputManipulator* inputManipulator);

    /// Notifies the input manager of input manipulator state change.
    /// \param inputManipulator The input manipulator whose state changed.
    void notifyManipulatorStateChange(InputManipulator* inputManipulator);

    /// Processes key event.
    /// \param keyEvent The key event that is processed.
    void processKeyEvent(const struct KzsInputEventKey* keyEvent);

    /// Processes touch event.
    void processTouchEvent(const struct KzsInputEventTouch* touchEvent, Node2D* node);

    /// Processes pointer event.
    void processPointerEvent(const struct KzsInputEventPointer* pointerEvent, Node2D* node);

    /// Processes touch points.
    void processTouchPoints();

    /// Removes all touch points that are in the "up" state from the touch point cache.
    void purgeTouchPoints();

    /// Processes pointer events to update hover states of the nodes in a subtree of
    /// the passed \a node.
    /// \param pointerEvent Pointer event to process.
    /// \param node The node where the hit testing starts. 
    void updateHoverStates(const struct KzsInputEventPointer* pointerEvent, Node2D* node);

    /// Clears the hover from the passed \a node if it currently has the hover.
    /// \param node A node to clear hover from.
    void clearHoverFromNode(Node& node);

    /// Processes a single input event.
    void processSingleInputEvent(const struct KzsEvent* inputEvent, Node2D* node);

    /// Touch location enumeration.
    enum TouchLocation
    {
        InsideNode,
        OutsideNode
    };

    /// Updates the internal storage with new touch point data.
    void updateTouchPoint(const KzuInputTouchPoint& touchPoint);

    /// Container for touch points.
    typedef vector<KzuInputTouchPoint> TouchPointVector;
    typedef TouchPointVector::const_iterator TouchPointVectorConstIterator;
    typedef TouchPointVector::iterator TouchPointVectorIterator;

    /// Collection of attached InputManipulators.
    struct InputManipulatorCollection
    {
    public:
        /// Collection constructor
        InputManipulatorCollection(InputManager* owner);
        /// Returns true if the collection is empty.
        bool isEmpty();
        /// Adds a manipulator to the collection.
        /// \param inputManipulator A manipulator that is added.
        void add(InputManipulator* inputManipulator);
        /// Removes the manipulator from the collection.

        void remove(InputManipulator* inputManipulator);
        /// Erases all null-manipulator elements from the collection.
        void compact();
        /// Clears handled status of all attached input manipulators.
        void clearStatus();
        /// Checks whether there are invalid attached manipulators.
        bool hasInvalid();
        /// Checks whether the given manipulator is allowed.
        bool isAllowed(InputManipulator* inputManipulator);
        /// Removes all manipulators except the given one.
        void removeIncompatibleManipulators(InputManipulator* inputManipulator);
        /// Updates every manipulator which is marked as not handled.
        void updateUnhandledManipulators(const InputManipulator::TouchInfo& info, TouchLocation touchLocation);
        /// Update input manipulator with touch info.
        void updateManipulator(InputManipulator* inputManipulator, const InputManipulator::TouchInfo& info, TouchLocation touchLocation);

        /// Clears the handled state of a manipulator.
        static void clearManipulatorStatus(InputManipulator* manipulator);
        /// This callback detaches a given manipulator. The manipulator is reset, and
        /// its position in the collection is set to null.
        static bool detachManipulator(InputManipulator* currentManipulator, InputManipulator*& manipulator);
        /// This callback removes all the manipulators except the given one from the collection.
        static void removeIncompatibleManipulator(InputManipulator* currentManipulator, InputManipulator*& manipulator);
    
    private:
        /// The address of the owning input manager instance.
        const InputManager* m_manager;
        /// The storage with the attached manipulators.
        vector<InputManipulator*> m_storage;
    };

    /// Attached input manipulators.
    InputManipulatorCollection m_attachedManipulators;
    /// All active touch points.
    TouchPointVector m_touchPoints;

    /// The node that had hover over when the previous pointer event was processed.
    NodeWeakPtr m_previouslyHovered;

    /// Domain owning the input manager.
    const Domain* m_domain;
    /// Whether the input manager currently handles events.
    bool m_isInEventHandling;
};
}

#endif
