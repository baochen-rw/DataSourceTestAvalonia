// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STATE_MANAGER_HPP
#define KZ_STATE_MANAGER_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/message/message_type.hpp>
#include <kanzi/core/metadata/metaclass.hpp>

#include <kanzi/core.ui/animation/from_to_animation.hpp>
#include <kanzi/core.ui/animation/keyframe_animation.hpp>
#include <kanzi/core.ui/message/message_arguments.hpp>
#include <kanzi/core.ui/property/variant.hpp>
#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core.ui/resource/resource_manager.hpp>

// Forward declarations.
struct KzuBinaryFileInfo;
struct KzcInputStream;
struct KzcMemoryManager;

namespace kanzi
{

// Forward declarations.
struct AppliedStyleEntry;
class Domain;
class KzbFile;
class KzbMemoryParser;
class ParallelTimeline;
class ReadOnlyMemoryFile;
class StateManager;
class Style;
class Timeline;
class TimelinePlayback;
typedef shared_ptr<StateManager> StateManagerSharedPtr;
typedef weak_ptr<StateManager> StateManagerWeakPtr;
typedef shared_ptr<Style> StyleSharedPtr;
typedef shared_ptr<Timeline> TimelineSharedPtr;
typedef shared_ptr<TimelinePlayback> TimelinePlaybackSharedPtr;

/// \class StateManager
/// State manager for managing states of nodes or application.
class KANZI_API StateManager : public Resource
{
public:
    /// State manager animation mode.
    enum AnimationMode
    {
        AnimationModeCustom       = 0,
        AnimationModeLinear       = 1,
        AnimationModeSmoothStep   = 2,
        AnimationModeStep         = 3,
        AnimationModeSmootherStep = 4,
        AnimationModeBack         = 5,
        AnimationModeBounce       = 6,
        AnimationModeCircle       = 7,
        AnimationModeCubic        = 8,
        AnimationModeElastic      = 9,
        AnimationModeExponential  = 10,
        AnimationModePower        = 11,
        AnimationModeQuadratic    = 12,
        AnimationModeQuartic      = 13,
        AnimationModeQuintic      = 14,
        AnimationModeSine         = 15
    };

    /// State manager transition return time calculation type.
    enum TransitionReturnTimeType
    {
        /// Play only elapsed time.
        TransitionReturnTimeElapsed = 1,
        /// Always play full time.
        TransitionReturnTimeFull = 2
    };

    class StateGroup;
    class State;
    class StateTransition;
    class StateTransitionAnimation;
    class StateObject;
    class StateManagerRuntime;
    typedef shared_ptr<StateManagerRuntime> StateManagerRuntimeSharedPtr;
    typedef weak_ptr<StateManagerRuntime> StateManagerRuntimeWeakPtr;
    typedef unique_ptr<StateGroup> StateGroupPtr;
    typedef vector<StateGroupPtr> StateGroupContainer;
    typedef StateGroupContainer::const_iterator StateGroupIterator;
    typedef unique_ptr<State> StatePtr;
    typedef vector<StatePtr> StateContainer;
    typedef StateContainer::const_iterator StateIterator;
    typedef unique_ptr<StateTransition> StateTransitionPtr;
    typedef vector<StateTransitionPtr> StateTransitionContainer;
    typedef StateTransitionContainer::const_iterator StateTransitionIterator;
    typedef unique_ptr<StateTransitionAnimation> StateTransitionAnimationPtr;
    typedef vector<StateTransitionAnimationPtr> StateTransitionAnimationContainer;
    typedef StateTransitionAnimationContainer::const_iterator StateTransitionAnimationIterator;
    typedef unique_ptr<StateObject> StateObjectPtr;
    typedef vector<StateObjectPtr> StateObjectContainer;
    typedef StateObjectContainer::const_iterator StateObjectIterator;

protected:
    class StateGroupRuntime;
    class StateRuntime;
    class StateObjectRuntime;
    class TargetObject;

    typedef shared_ptr<StateGroupRuntime> StateGroupRuntimeSharedPtr;
    typedef shared_ptr<StateRuntime> StateRuntimeSharedPtr;
    typedef shared_ptr<StateObjectRuntime> StateObjectRuntimeSharedPtr;
    typedef shared_ptr<TargetObject> TargetObjectSharedPtr;
    typedef weak_ptr<StateObjectRuntime> StateObjectRuntimeWeakPtr;
    typedef weak_ptr<TargetObject> TargetObjectWeakPtr;

    typedef vector<StateGroupRuntimeSharedPtr> StateGroupRuntimeContainer;
    typedef StateGroupRuntimeContainer::const_iterator StateGroupRuntimeIterator;
    typedef vector<StateRuntimeSharedPtr> StateRuntimeContainer;
    typedef StateRuntimeContainer::const_iterator StateRuntimeIterator;
    typedef vector<StateObjectRuntimeSharedPtr> StateObjectRuntimeContainer;
    typedef StateObjectRuntimeContainer::iterator StateObjectRuntimeIterator;

public:
#include "state_manager_properties.h"

    /// Represents base message arguments of state manager messages.
    class KANZI_API StateManagerMessageArguments : public MessageArguments
    {
    public:
#include "state_manager_message_properties.h"

        explicit StateManagerMessageArguments(StateManager* stateManager) :
            m_stateManager(stateManager)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StateManagerMessageArguments, MessageArguments, "Message.StateManager.MessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerStateGroupProperty)
        KZ_METACLASS_END()

        string getStateGroup() const
        {
            return getArgument(MessageArgumentStateManagerStateGroupProperty);
        }

        void setStateGroup(const string& stateGroupName)
        {
            setArgument(MessageArgumentStateManagerStateGroupProperty, stateGroupName);
        }

        StateManager* getStateManager() const
        {
            return m_stateManager;
        }

    private:
        StateManager* m_stateManager;
    };

    class KANZI_API StateChangeMessageArguments : public StateManagerMessageArguments
    {
    public:
#include "state_manager_state_change_message_properties.h"

        explicit StateChangeMessageArguments(StateManager* stateManager) :
            StateManagerMessageArguments(stateManager)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(StateChangeMessageArguments, StateManagerMessageArguments, "Message.StateManagerStateChange.MessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerImmediateProperty)
        KZ_METACLASS_END()

        bool isImmediate() const
        {
            return getArgument(MessageArgumentStateManagerImmediateProperty);
        }

        void setImmediate(bool immediate)
        {
            setArgument(MessageArgumentStateManagerImmediateProperty, immediate);
        }
    };

    /// Represents message arguments of GoToState message of state manager.
    class KANZI_API GoToStateMessageArguments : public StateChangeMessageArguments
    {
    public:
#include "state_manager_go_to_state_message_properties.h"

        /// Constructor, do not use state manager message argument used in base message argument class.
        explicit GoToStateMessageArguments() :
            StateChangeMessageArguments(0)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(GoToStateMessageArguments, StateChangeMessageArguments, "Message.StateManagerGoToState.MessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerStateProperty)
        KZ_METACLASS_END()

        string getState() const
        {
            return getArgument(MessageArgumentStateManagerStateProperty);
        }

        void setState(const string& stateName)
        {
            setArgument(MessageArgumentStateManagerStateProperty, stateName);
        }
    };

    /// Represents message arguments of GoToNextDefinedState message of state manager.
    class KANZI_API GoToDefinedStateMessageArguments : public StateChangeMessageArguments
    {
    public:
#include "state_manager_go_to_defined_state_message_properties.h"

        /// Constructor, do not use state manager message argument used in base message argument class.
        explicit GoToDefinedStateMessageArguments() :
            StateChangeMessageArguments(0)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(GoToDefinedStateMessageArguments, StateChangeMessageArguments, "Message.StateManagerGoToDefinedState.MessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerLoopStatesProperty)
        KZ_METACLASS_END()

        bool isLoopStates() const
        {
            return getArgument(MessageArgumentStateManagerLoopStatesProperty);
        }

        void setLoopStates(bool loopStates)
        {
            setArgument(MessageArgumentStateManagerLoopStatesProperty, loopStates);
        }
    };


    /// Represents message arguments of GoToNextDefinedState message of state manager.
    class KANZI_API GoToNextDefinedStateMessageArguments : public GoToDefinedStateMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(GoToNextDefinedStateMessageArguments, GoToDefinedStateMessageArguments, "Message.StateManagerGoToNextDefinedState.MessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of GoToPreviousDefinedState message of state manager.
    class KANZI_API GoToPreviousDefinedStateMessageArguments : public GoToDefinedStateMessageArguments
    {
    public:
        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(GoToPreviousDefinedStateMessageArguments, GoToDefinedStateMessageArguments, "Message.StateManagerGoToPreviousDefinedState.MessageArguments")
        KZ_METACLASS_END()
    };

    /// Represents message arguments of EnteredState message of state manager.
    class KANZI_API EnteredStateMessageArguments : public StateManagerMessageArguments
    {
    public:
#include "state_manager_entered_state_message_properties.h"

        explicit EnteredStateMessageArguments(StateManager* stateManager) :
            StateManagerMessageArguments(stateManager)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(EnteredStateMessageArguments, StateManagerMessageArguments, "Message.StateManagerEnteredState.MessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerEnteredStateProperty)
        KZ_METACLASS_END()

        string getState() const
        {
            return getArgument(MessageArgumentStateManagerEnteredStateProperty);
        }

        void setState(const string& stateName)
        {
            setArgument(MessageArgumentStateManagerEnteredStateProperty, stateName);
        }
    };

    /// Represents message arguments of LeftState message of state manager.
    class KANZI_API LeftStateMessageArguments : public StateManagerMessageArguments
    {
    public:
#include "state_manager_left_state_message_properties.h"

        explicit LeftStateMessageArguments(StateManager* stateManager) :
            StateManagerMessageArguments(stateManager)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(LeftStateMessageArguments, StateManagerMessageArguments, "Message.StateManagerLeftState.MessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerLeftStateProperty)
        KZ_METACLASS_END()

        string getState() const
        {
            return getArgument(MessageArgumentStateManagerLeftStateProperty);
        }

        void setState(const string& stateName)
        {
            setArgument(MessageArgumentStateManagerLeftStateProperty, stateName);
        }
    };

    class KANZI_API TransitionMessageArguments : public StateManagerMessageArguments
    {
    public:
#include "state_manager_transition_message_properties.h"

        explicit TransitionMessageArguments(StateManager* stateManager) :
            StateManagerMessageArguments(stateManager)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(TransitionMessageArguments, StateManagerMessageArguments, "Message.StateManagerTransition.MessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerSourceStateProperty)
            KZ_METACLASS_PROPERTY_TYPE(MessageArgumentStateManagerTargetStateProperty)
        KZ_METACLASS_END()

        /// Gets from state property.
        string getSourceState() const
        {
            return getArgument(MessageArgumentStateManagerSourceStateProperty);
        }

        /// Sets from state property.
        void setSourceState(string_view stateName)
        {
            setArgument(MessageArgumentStateManagerSourceStateProperty, string(stateName));
        }

        /// Gets from state property.
        string getTargetState() const
        {
            return getArgument(MessageArgumentStateManagerTargetStateProperty);
        }

        /// Sets from state property.
        void setTargetState(string_view stateName)
        {
            setArgument(MessageArgumentStateManagerTargetStateProperty, string(stateName));
        }
    };

    /// Represents message arguments of TransitionStarted message of state manager.
    class KANZI_API TransitionStartedMessageArguments : public TransitionMessageArguments
    {
    public:

        explicit TransitionStartedMessageArguments(StateManager* stateManager) :
            TransitionMessageArguments(stateManager)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(TransitionStartedMessageArguments, TransitionMessageArguments, "Message.StateManagerTransitionStarted.MessageArguments")
        KZ_METACLASS_END()
    };


    /// Represents message arguments of TransitionFinished message of state manager.
    class KANZI_API TransitionFinishedMessageArguments : public TransitionMessageArguments
    {
    public:

        explicit TransitionFinishedMessageArguments(StateManager* stateManager) :
            TransitionMessageArguments(stateManager)
        {
        }

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(TransitionFinishedMessageArguments, TransitionMessageArguments, "Message.StateManagerTransitionFinished.MessageArguments")
        KZ_METACLASS_END()
    };

    static MessageType<GoToStateMessageArguments> GoToStateMessage;
    static MessageType<GoToNextDefinedStateMessageArguments> GoToNextDefinedStateMessage;
    static MessageType<GoToPreviousDefinedStateMessageArguments> GoToPreviousDefinedStateMessage;
    static MessageType<EnteredStateMessageArguments> EnteredStateMessage;
    static MessageType<LeftStateMessageArguments> LeftStateMessage;
    static MessageType<TransitionStartedMessageArguments> TransitionStartedMessage;
    static MessageType<TransitionFinishedMessageArguments> TransitionFinishedMessage;

    KZ_STATIC_METACLASS_BEGIN(StateManager, "Kanzi.StateManager")
        KZ_METACLASS_MESSAGE_TYPE(GoToStateMessage)
        KZ_METACLASS_MESSAGE_TYPE(GoToNextDefinedStateMessage)
        KZ_METACLASS_MESSAGE_TYPE(GoToPreviousDefinedStateMessage)
        KZ_METACLASS_MESSAGE_TYPE(EnteredStateMessage)
        KZ_METACLASS_MESSAGE_TYPE(LeftStateMessage)
        KZ_METACLASS_MESSAGE_TYPE(TransitionStartedMessage)
        KZ_METACLASS_MESSAGE_TYPE(TransitionFinishedMessage)
        KZ_METACLASS_PROPERTY_TYPE(LongestPathProperty)
    KZ_METACLASS_END()

    class KANZI_API StateGroup
    {
    public:
        static StateGroupPtr create();
        
        /// Move constructor.
        /// \param other Source state group.
        StateGroup(KZ_RV_REF(StateGroup) other) :
            m_controlType(other.m_controlType),
            m_name(other.m_name),
            m_initialStateName(other.m_initialStateName),
            m_states(kanzi::move(other.m_states)),
            m_transitions(kanzi::move(other.m_transitions))
        {
        }

        /// Move operator.
        /// \param other Source state group.
        /// \return This state group after move.
        StateGroup& operator=(KZ_RV_REF(StateGroup) other)
        {
            m_controlType = other.m_controlType;
            m_name = other.m_name;
            m_initialStateName = other.m_initialStateName;
            m_states = kanzi::move(other.m_states);
            m_transitions = kanzi::move(other.m_transitions);
            return *this;
        }

        /// Post go to state message with this state group.
        void goToState(Node* objectNode, string_view stateName, bool immediate);

        void setControlType(AbstractPropertyType type);
        AbstractPropertyType getControlType() const;
        string getName() const;
        void setName(string_view name);
        bool equalName(string_view name) const;
        void setInitialStateName(string_view name);
        bool hasInitialState() const;
        bool equalInitialState(const State& state) const;
        void addState(StatePtr state);
        StateIterator beginStates() const;
        StateIterator endStates() const;
        void addTransition(StateTransitionPtr transition);
        StateTransitionIterator beginTransitions() const;
        StateTransitionIterator endTransitions() const;

        /// Destructor.
        ~StateGroup();

    private:

        KZ_MOVABLE_BUT_NOT_COPYABLE(StateGroup)

        /// Constructor.
        explicit StateGroup();

        /// Control property type.
        AbstractPropertyType m_controlType;
        /// State group name.
        string m_name;
        /// Name of the initial state if no control property set.
        string m_initialStateName;
        /// States.
        StateContainer m_states;
        /// Transitions.
        StateTransitionContainer m_transitions;
    };

    class KANZI_API State
    {
    public:
        static StatePtr create();
        State(KZ_RV_REF(State) other) :
            m_name(other.m_name),
            m_controlValue(other.m_controlValue),
            m_objects(kanzi::move(other.m_objects))
        {
        }
        State& operator=(KZ_RV_REF(State) other)
        {
            m_name = other.m_name;
            m_controlValue = other.m_controlValue;
            m_objects = kanzi::move(other.m_objects);
            return *this;
        }
        /// Sets name of the state.
        void setName(string_view name);
        /// Returns true if name of the state is equal to attribute.
        bool equalName(string_view name) const;
        /// Returns name of the state.
        const string& getName() const;
        /// Sets control property value of the state.
        void setControlValue(const Variant& value);
        /// Returns true if control property value of the state is equal to attribute.
        bool equalControlValue(const Variant& value) const;
        /// Adds new state object to state.
        void addStateObject(StateObjectPtr stateObject);
        /// Returns iterator to first state object.
        StateObjectIterator beginStateObjects() const;
        /// Returns iterator to last state object.
        StateObjectIterator endStateObjects() const;

    private:

        KZ_MOVABLE_BUT_NOT_COPYABLE(State)

        explicit State();

        /// State name.
        string m_name;
        /// Control property value.
        Variant m_controlValue;
        /// State objects.
        StateObjectContainer m_objects;
    };

    /// Easing function arguments.
    struct EasingArguments
    {
        /// Constructor.
        explicit EasingArguments()
        {
            argument1.amplitude = 1.0f;
            argument2.springiness = 3.0f;
        }

        /// First argument.
        union
        {
            /// Amplitude of the back easing function.
            float amplitude;
            /// Power of the power easing function.
            float power;
            /// Exponent of the exponential easing function.
            float exponent;
            /// Oscillations of the elastic easing function.
            float oscillations;
        } argument1;

        /// Second argument.
        union
        {
            /// Springiness of the elastic easing function.
            float springiness;
        } argument2;
    };

    class KANZI_API StateTransition
    {
    public:
        /// Create a state transition.
        static StateTransitionPtr create();

        StateTransition(KZ_RV_REF(StateTransition) other) :
            m_fromState(other.m_fromState),
            m_toState(other.m_toState),
            m_startTime(other.m_startTime),
            m_duration(other.m_duration),
            m_returnTimeType(other.m_returnTimeType),
            m_defaultAnimationMode(other.m_defaultAnimationMode),
            m_defaultEasingArguments(other.m_defaultEasingArguments),
            m_defaultAnimationEasingMode(other.m_defaultAnimationEasingMode),
            m_animations(kanzi::move(other.m_animations))
        {
        }
        StateTransition& operator=(KZ_RV_REF(StateTransition) other)
        {
            m_fromState = other.m_fromState;
            m_toState = other.m_toState;
            m_startTime = other.m_startTime;
            m_duration = other.m_duration;
            m_returnTimeType = other.m_returnTimeType;
            m_defaultAnimationMode = other.m_defaultAnimationMode;
            m_defaultEasingArguments = other.m_defaultEasingArguments;
            m_defaultAnimationEasingMode = other.m_defaultAnimationEasingMode;
            m_animations = kanzi::move(other.m_animations);
            return *this;
        }
        /// Sets transition start time, in ms.
        void setStartTime(chrono::milliseconds startTime);
        /// Returns transition start time, in ms.
        chrono::milliseconds getStartTime() const;
        /// Sets transition duration, in ms.
        void setDuration(chrono::milliseconds durationMs);
        /// Returns transition duration, in ms.
        chrono::milliseconds getDuration() const;
        /// Sets return time type of state transition.
        void setReturnTimeType(TransitionReturnTimeType type);
        /// Returns return time type of state transition.
        TransitionReturnTimeType getReturnTimeType() const;
        /// Sets state that acts as origin for this transition.
        void setFromState(string_view name);
        /// Returns true if this transition has origin state.
        bool hasFromState() const;
        /// Returns true if state is same as origin of this transition.
        bool equalFromState(const StateRuntime& state) const;
        /// Sets state that acts as target for this transition.
        void setToState(string_view name);
        /// Returns true if this transition has target state.
        bool hasToState() const;
        /// Returns true if state is same as target of this transition.
        bool equalToState(const StateRuntime& state) const;
        /// Sets default animation mode for this transition.
        void setDefaultAnimationMode(AnimationMode mode);
        /// Returns default animation mode for this transition.
        AnimationMode getDefaultAnimationMode() const;
        /// Sets the default easing function arguments.
        void setDefaultEasingArguments(const EasingArguments& easingArguments);
        /// Gets the default easing function arguments.
        EasingArguments getDefaultEasingArguments() const;
        /// Sets default animation easing mode for this transition.
        void setDefaultAnimationEasingMode(AnimationEasingMode mode);
        /// Returns default animation easing mode for this transition.
        AnimationEasingMode getDefaultAnimationEasingMode() const;
        /// Adds transition animation to transition.
        void addTransitionAnimation(StateTransitionAnimationPtr animation);
        /// Returns iterator to first transition animation.
        StateTransitionAnimationIterator beginAnimations() const;
        /// Returns iterator to last transition animation.
        StateTransitionAnimationIterator endAnimations() const;

    private:

        KZ_MOVABLE_BUT_NOT_COPYABLE(StateTransition)

        /// Constructor.
        explicit StateTransition() :
            m_startTime(chrono::milliseconds::zero()),
            m_duration(chrono::milliseconds::zero()),
            m_returnTimeType(TransitionReturnTimeElapsed),
            m_defaultAnimationMode(AnimationModeLinear),
            m_defaultAnimationEasingMode(AnimationEaseIn)
        {
        }

        /// From state name.
        string m_fromState;
        /// To state name.
        string m_toState;
        /// Transition start time.
        chrono::milliseconds m_startTime;
        /// Duration in ms.
        chrono::milliseconds m_duration;
        /// The way time is calculated when returning in the middle of transition.
        TransitionReturnTimeType m_returnTimeType;
        /// Default animation mode.
        AnimationMode m_defaultAnimationMode;
        /// Default easing function arguments.
        EasingArguments m_defaultEasingArguments;
        /// Default easing mode.
        AnimationEasingMode m_defaultAnimationEasingMode;
        /// Animation list.
        StateTransitionAnimationContainer m_animations;
    };

    class KANZI_API StateTransitionAnimation
    {
    public:
        explicit StateTransitionAnimation() :
            m_propertyType(),
            m_startTime(chrono::milliseconds::zero()),
            m_mode(AnimationModeLinear),
            m_easingMode(AnimationEaseIn),
            m_longerPath(false)
        {
        }

        static StateTransitionAnimationPtr create();

        /// Sets animation start time, in ms.
        void setStartTime(chrono::milliseconds startTime);
        /// Returns animation start time, in ms.
        chrono::milliseconds getStartTime() const;
        /// Sets property being animated by this transition animation.
        void setPropertyType(AbstractPropertyType propertyType);
        /// Returns property being animated by this transition animation.
        AbstractPropertyType getPropertyType() const;
        /// Gets object path that contains the animated property.
        string getObjectPath() const;
        /// Sets object path that contains the animated property.
        void setObjectPath(string_view path);
        /// Returns true if parameter is same as the animated property.
        bool equalObjectPath(string_view path) const;
        /// Sets animation mode of this transition animation.
        void setAnimationMode(AnimationMode mode);
        /// Returns animation mode of this transition animation.
        AnimationMode getAnimationMode() const;
        /// Sets the easing function arguments.
        void setEasingArguments(const EasingArguments& easingArguments);
        /// Gets the easing function arguments.
        EasingArguments getEasingArguments() const;
        /// Sets easing mode for this animation.
        void setEasingMode(AnimationEasingMode mode);
        /// Returns easing mode for this animation.
        AnimationEasingMode getEasingMode() const;
        /// Sets custom animation for this transition animation.
        void setCustomAnimation(TimelineSharedPtr animation);
        /// Returns custom animation of this transition animation.
        TimelineSharedPtr getCustomAnimation() const;
        /// Sets this transition animation to use longer path.
        void setLongerPath(bool value);
        /// Does this transition animation use longer path.
        bool isLongerPath() const;

    private:
        /// Object path.
        string m_objectPath;
        /// Property type. Owned by property registry.
        AbstractPropertyType m_propertyType;
        /// Animation start time.
        chrono::milliseconds m_startTime;
        /// Animation mode.
        AnimationMode m_mode;
        /// Easing function arguments.
        EasingArguments m_easingArguments;
        /// Easing mode.
        AnimationEasingMode m_easingMode;
        /// Custom animation.
        TimelineSharedPtr m_customAnimation;
        /// Uses longer path for quaternion interpolation.
        bool m_longerPath;
    };

    class KANZI_API StateObject
    {
    public:
        static StateObjectPtr create();
        /// Sets target object path for this state object.
        void setPath(string_view path);
        /// Returns target object path for this state object.
        const string& getPath() const;
        /// Sets style for this state object. The given style is supposed to define the property values for target object when this state object is active.
        void setStyle(const StyleSharedPtr& style);
        /// Return style of this state object.
        StyleSharedPtr getStyle() const;

    private:
        /// Object path.
        string m_path;
        /// Style.
        StyleSharedPtr m_style;
    };

    /// Destructor.
    ~StateManager();

    /// Create a state manager.
    static StateManagerSharedPtr create(Domain* domain, string_view name);

    /// Create an empty state manager.
    static StateManager* createEmpty(Domain* domain, string_view name);

    /// Add new state group to state manager.
    void addStateGroup(StateGroupPtr stateGroup);

    /// Returns an iterator to start of the state group container.
    /// \return Iterator at the beginning of the container.
    StateGroupIterator beginStateGroups() const
    {
        return m_groups.begin();
    }

    /// Returns an iterator to end of the state group container.
    /// \return Iterator at the end of the container.
    StateGroupIterator endStateGroups() const
    {
        return m_groups.end();
    }

    /// Attach a state manager runtime.
    /// \param stateManager Shared pointer to this state manager.
    /// \param objectNode Object node to attach to.
    StateManagerRuntimeSharedPtr attach(StateManagerSharedPtr stateManager, Node& objectNode);

    /// Attempt to go to a state.
    /// \param objectNode Node to post the message on.
    /// \param stateGroupName Name of the state group to do the transition in.
    /// \param stateName Name of the state to transition to.
    /// \param immediate True to omit transition animations.
    static void goToState(Node* objectNode, string_view stateGroupName, string_view stateName, bool immediate);
    /// Attempt to go to a state.
    /// If state manager attached to node has multiple state groups with the same name, it is not clearly defined which state is selected.
    /// \param objectNode Node to post the message on.
    /// \param stateName Name of the state to transition to.
    /// \param immediate True to omit transition animations.
    static void goToState(Node* objectNode, string_view stateName, bool immediate);

    /// Load a state manager from kzb.
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    static StatePtr loadStateFromKZB(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file, bool hasControlType);

    static StateObjectPtr loadStateObjectFromKZB(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file);

    static StateTransitionPtr loadTransitionFromKZB(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file);

    static StateTransitionAnimationPtr loadTransitionAnimationFromKZB(KzcInputStream* inputStream, Domain* domain, const KzuBinaryFileInfo* file);

    /// Factory function for StateManager Load Task, which loads a StateManager from a kzb file.
    /// \param name Name of the StateManager being loaded.
    /// \param kzbFile Pointer to instance of KzbFile, which holds information about the kzb file.
    /// \param file Pointer to instance of ReadOnlyMemoryFile, which wraps the actual kzb file.
    /// \return Shared pointer to created load task.
    static ResourceManager::LoadTaskSharedPtr createLoadTask(string_view name, KzbFile* kzbFile, unique_ptr<ReadOnlyMemoryFile> file);

protected:

    /// TargetObject.
    ///
    /// TargetObject is responsible for keeping track of a target object (node or resource) to which state object runtimes apply their styles.
    /// TargetObject also notifies referencing state object runtimes when target becomes acquired or lost.
    class TargetObject
    {
    public:

        /// Constructor.
        ///
        /// \param rootNode Root node for resolving target.
        /// \param objectPath Path to target relative to root node.
        explicit TargetObject(Node* rootNode, string_view objectPath);

        /// Destructor.
        ~TargetObject();

        /// Register state object runtime which should be notified when target is acquired or lost.
        ///
        /// \param stateObjectRuntime State object runtime which should be notified.
        void registerStateObjectRuntime(StateObjectRuntimeSharedPtr stateObjectRuntime);

        /// Gets acquired target. If target is not found, null pointer is returned.
        /// This always returns the cloned object if a clone has been made.
        /// \return Acquired target or null pointer.
        Object* get();

        /// Gets acquired target. If target is not found, null pointer is returned.
        /// Gets the base object even if clone has been made.
        /// \return Acquired target or null pointer.
        Object* getBaseObject();

        /// Refreshes target.
        /// Currently TargetObject is not able to automatically detect when target is acquired, so this function
        /// should be manually called. Calling this function might trigger notification about acquiring the target.
        void sync();

        /// Destroys TargetObject.
        /// After TargetObject is destroyed, it does not track its target and get() function always returns null pointer.
        void destroy();

        /// Tells if there is a cloned target resource.
        /// \return True if clone exists, false if not.
        bool hasClonedTargetResource() const
        {
            return static_cast<bool>(m_clonedTargetResource);
        }

    private:

        typedef vector<StateObjectRuntimeWeakPtr> StateObjectRuntimeVector;

        /// Unacquires current target.
        void unacquireTarget();

        /// Notifies registered state object runtimes when target is acquired.
        void notifyTargetAcquired();

        /// Notifies registered state object runtimes when target is lost.
        void notifyTargetLost();

        /// Modifier callback which substitutes value of target resource property with cloned resource.
        static void targetPropertyModifierCallback(PropertyObject& object, ResourceSharedPtr& value, PropertyNotificationReason reason, void* owner);

        /// Listener for path property of target node.
        static void onTargetNodePathPropertyChanged(PropertyObject& object, const string& value, PropertyNotificationReason reason, void* userData);

        /// Root node for resolving target.
        Node* m_rootNode;
        /// Path to target relative to root node.
        string m_objectPath;

        /// Resolved target node.
        weak_ptr<Node> m_targetNode;
        /// Resolved target property.
        AbstractPropertyType m_targetNodeProperty;
        /// Cloned resource which substitutes value of resolved target property.
        ResourceSharedPtr m_clonedTargetResource;

        /// State object runtimes which should be notified about acquiring or losing target.
        StateObjectRuntimeVector m_referencingStateObjectRuntimes;
    };

    /// State object runtime.
    class StateObjectRuntime
    {
    public:
        enum ApplyTargetType
        {
            /// Not applied.
            NotApplied = 0,

            /// Applied to target node.
            AppliedToNode = 1,

            /// Applied to clone.
            AppliedToClone = 2,
        };

        /// Create new state object runtime.
        static StateObjectRuntimeSharedPtr create(const StateObjectPtr& stateObject);

        /// Destructor.
        ~StateObjectRuntime();

        /// Gets state object.
        StateObject* getStateObject() const;

        /// Gets target, or null pointer if target is not acquired.
        Object* getTarget() const;

        /// Gets the object that has the style entry applied.
        /// \return Pointer to cloned or base object, depending on which has the style entry applied.
        Object* getAppliedTarget();

        /// Assigns target object.
        /// \param runtime Shared pointer to this state objct runtime.
        void assignTargetObject(StateObjectRuntimeSharedPtr runtime, TargetObjectSharedPtr targetObject);

        /// Applies state style to its target.
        void apply();

        /// Unapplies state style from its target.
        void unapply();

        /// Notification callback which is called by TargetObject when target is acquired.
        void onTargetAcquired();

        /// Notification callback which is called by TargetObject just before target is lost.
        void onBeforeTargetLost();
        
    private:

        /// Constructor.
        explicit StateObjectRuntime(const StateObjectPtr& stateObject);

        /// State object.
        StateObject* m_stateObject;

        /// Target object to track the target.
        TargetObjectWeakPtr m_targetObject;

        /// Applied state style entry.
        weak_ptr<AppliedStyleEntry> m_appliedStateStyle;

        /// Enumeration indicating the status of the apply.
        ApplyTargetType m_applyStatus;
    };

    /// State runtime.
    class StateRuntime
    {
    public:
        static StateRuntimeSharedPtr create(State& state);

        State* m_state;
        StateObjectRuntimeContainer m_stateObjectRuntimes;

    protected:
        explicit StateRuntime(State& state);
    };

    /// State group runtime.
    class StateGroupRuntime
    {
    public:
        static StateGroupRuntimeSharedPtr create(const StateManagerRuntimeSharedPtr& stateManagerRuntime, StateGroup& stateGroup);

        void stopTransition();

        /// Set initial state.
        /// Should be called after creating the state group runtime, after it has been added to group runtimes.
        void goToInitialState();

        /// Go to a state in a state group.
        void goToState(const StateRuntimeSharedPtr& newStateRuntime, bool immediate);

        /// Sync the state in the state group.
        void syncState(bool immediate);

        /// State manager runtime.
        StateManagerRuntimeWeakPtr m_stateManagerRuntime;
        /// State group.
        StateGroup* m_group;
        /// State runtimes.
        StateRuntimeContainer m_stateRuntimes;
        /// Current state runtime.
        StateRuntimeSharedPtr m_currentStateRuntime;
        /// Previous state.
        State* m_previousState;
        /// Transition timeline playback.
        TimelinePlaybackSharedPtr m_transitionPlayback;
        /// Is in transition.
        bool m_inTransition;
        /// Base transition time in ms.
        chrono::milliseconds m_transitionBaseTime;
        /// Property type the property notification handler has been installed for.
        /// If no notification handler has been installed, the property type is empty.
        AbstractPropertyType m_notificationHandlerPropertyType;

        template <typename T>
        static void controlPropertyNotificationHandler(PropertyObject& object, const typename PropertyType<T>::Traits::StorageType&, PropertyNotificationReason reason, void* userData);

        template <typename T>
        void toggleControlPropertyNotificationHandler(Node* node, AbstractPropertyType propertyType, bool add);

        void toggleControlPropertyNotificationHandler(Node* node, AbstractPropertyType propertyType, bool add);

        /// Destructor.
        ~StateGroupRuntime();

    protected:
        explicit StateGroupRuntime(const StateManagerRuntimeSharedPtr& stateManagerRuntime, StateGroup& stateGroup);

        /// Transition finished message handler.
        void onTransitionFinished(TimelinePlayback&);

        /// Create an animation for a state group.
        void createAnimation(Object* stateObject, string_view stateObjectPath, AbstractPropertyType propertyType, AbstractPropertyTypeDescriptor::ValueSource* valueSource,
                             chrono::milliseconds start, chrono::milliseconds duration, AnimationMode animationMode, const EasingArguments& easingArguments,
                             AnimationEasingMode easingMode, ParallelTimeline& timeline, bool longerPath);

        /// Dispatches TransitionStarted message on the attached node.
        void sendTransitionStarted();

        /// Dispatches TransitionFinished message on the attached node.
        void sendTransitionFinished();
    };

    explicit StateManager(Domain* domain, string_view name)
        : Resource(domain, name)
    {
    }

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Cleanup state manager internals.
    void cleanup();

    /// Go to state message handler.
    static void goToStateHandler(StateManagerRuntime& stateManagerRuntime, GoToStateMessageArguments& goToStateMessage);

    /// Go to next defined state message handler.
    static void goToNextDefinedState(StateManagerRuntime& stateManagerRuntime, GoToNextDefinedStateMessageArguments& goToNextDefinedStateMessage);

    /// Go to previous defined state message handler.
    static void goToPreviousDefinedState(StateManagerRuntime& stateManagerRuntime, GoToPreviousDefinedStateMessageArguments& goToPreviousDefinedStateMessage);

    StateGroupContainer m_groups;
};

}


#endif
