// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_HPP
#define KZ_NODE_HPP

#include "abstract_node_reference.hpp"
#include "abstract_resource_reference.hpp"

#include <kanzi/core.ui/resource/resource_manager.hpp>
#include <kanzi/core.ui/state_manager/state_manager.hpp>
#include <kanzi/core/cpp/limits.hpp>
#include <kanzi/core/cpp/set.hpp>
#include <kanzi/core/cpp/tuple.hpp>

#include <kanzi/core.ui/message/kzu_message_dispatcher.h>

// Forward declarations.
struct KzuBoundingVolume;
struct KzuMessageDispatcher;
struct KzuFont;

namespace kanzi
{

// Forward declarations.
class Binding;
class Box;
class ClickManipulator;
class InputManipulator;
class Material;
class Node;
class NodeComponent;
class Resource;
class ResourceDictionary;
class Style;
typedef shared_ptr<Binding> BindingSharedPtr;
typedef shared_ptr<ClickManipulator> ClickManipulatorSharedPtr;
typedef shared_ptr<InputManipulator> InputManipulatorSharedPtr;
typedef shared_ptr<Material> MaterialSharedPtr;
typedef shared_ptr<NodeComponent> NodeComponentSharedPtr;
typedef shared_ptr<ResourceDictionary> ResourceDictionarySharedPtr;
typedef shared_ptr<void> ScriptingContextSharedPtr;
typedef shared_ptr<KzuFont> FontSharedPtr;

/// Alias for shared pointer of Node.
typedef shared_ptr<Node> NodeSharedPtr;
/// Alias for shared pointer of const Node.
typedef shared_ptr<Node const> NodeConstSharedPtr;
/// Alias for weak pointer of Node.
typedef weak_ptr<Node> NodeWeakPtr;
/// Alias for weak pointer of const Node.
typedef weak_ptr<Node const> NodeConstWeakPtr;

/// Base class for scene graph nodes in Kanzi.
///
/// Examples
/// ----
///
/// To set node properties:
/// \snippet kz_test_objectnode.cpp Set Node properties
///
/// To introduce new message types and use them:
/// \snippet kz_test_objectnode.cpp Custom messages
class KANZI_API Node : public Object, public enable_shared_from_this<Node>
{
private:
    friend class InputManager;

    typedef tuple<AbstractPropertyType, AbstractResourceReference*> ResourceReferenceEntry;

    typedef function<void(MessageArguments*)> MessageSubscriptionFunction;
    typedef shared_ptr<MessageSubscriptionFunction> MessageSubscriptionFunctionSharedPtr;
    typedef weak_ptr<MessageSubscriptionFunction> MessageSubscriptionFunctionWeakPtr;

    /// Message subscription structure.
    struct MessageSubscription
    {
        explicit MessageSubscription(const KzuMessageType* messageType, MessageSubscriptionFunctionSharedPtr sharedFunction) :
            messageType(messageType),
            sharedFunction(sharedFunction)
        {
        }

        struct LessFunctor
        {
            bool operator()(const MessageSubscription& left, const MessageSubscription& right) const
            {
                //return left.functionWeakPtr.owner_before(right.functionWeakPtr);
                return left.sharedFunction < right.sharedFunction;
            }
        };

        const KzuMessageType* messageType;
        MessageSubscriptionFunctionSharedPtr sharedFunction;
    };

    typedef set<MessageSubscription, MessageSubscription::LessFunctor> MessageSubscriptionContainer;

public:
    /// Horizontal alignment options.
    enum HorizontalAlignment
    {
        HorizontalAlignmentLeft = 0,
        HorizontalAlignmentRight = 1,
        HorizontalAlignmentCenter = 2,
        HorizontalAlignmentStretch = 3
    };

    /// Vertical alignment options.
    enum VerticalAlignment
    {
        VerticalAlignmentBottom = 0,
        VerticalAlignmentTop = 1,
        VerticalAlignmentCenter = 2,
        VerticalAlignmentStretch = 3
    };

    /// Depth alignment options.
    enum DepthAlignment
    {
        DepthAlignmentBack = 0,
        DepthAlignmentFront = 1,
        DepthAlignmentCenter = 2,
        DepthAlignmentStretch = 3
    };

    /// Content stretch option.
    enum ContentStretch
    {
        ContentStretchNone,          /// Content is displayed unstretched in the middle of area.
        ContentStretchFill,          /// Content encompasses full area.
        ContentStretchUniform,       /// Content stretched to fill as much of area as possible. If aspect ratios do not match, leave area undrawn.
        ContentStretchUniformToFill, /// Content stretched to fill full area. If aspect ratios do not match, clip excess area.
        ContentStretchRepeat
    };

    /// \name Properties
    /// \{

    /// Name property.
    /// The default value is "".
    /// \see setName(), getName()
    static PropertyType<string> NameProperty;
    /// Gets the value of #NameProperty.
    /// \see setName()
    string getName() const
    {
        return getProperty(NameProperty);
    }
    /// Sets the value of #NameProperty.
    /// \see getName()
    void setName(string_view value)
    {
        setProperty(NameProperty, string(value));
    }

    /// Path property.
    /// The default value is "".
    /// \see setPath(), getPath()
    static PropertyType<string> PathProperty;
    /// Gets the value of #PathProperty.
    /// \see setPath()
    string getPath() const
    {
        return getProperty(PathProperty);
    }
    /// Sets the value of #PathProperty.
    /// \see getPath()
    void setPath(string value)
    {
        setProperty(PathProperty, value);
    }

    /// Locale property.
    /// The default value is "".
    /// \see setLocale(), getLocale()
    static PropertyType<string> LocaleProperty;
    /// Gets the value of #LocaleProperty.
    /// \see setLocale()
    string getLocale() const
    {
        return getProperty(LocaleProperty);
    }
    /// Sets the value of #LocaleProperty.
    /// \see getLocale()
    void setLocale(string value)
    {
        setProperty(LocaleProperty, value);
    }

    /// CreatedFromKZB property.
    /// The default value is false.
    /// \see setCreatedFromKZB(), isCreatedFromKZB()
    static PropertyType<bool> CreatedFromKZBProperty;

    /// HitTestable property.
    /// The default value is false.
    /// \see setHitTestable(), isHitTestable()
    static PropertyType<bool> HitTestableProperty;
    /// Gets the value of #HitTestableProperty.
    /// \see setHitTestable()
    bool isHitTestable() const
    {
        return getProperty(HitTestableProperty);
    }
    /// Sets the value of #HitTestableProperty.
    /// \see isHitTestable()
    void setHitTestable(bool value)
    {
        setProperty(HitTestableProperty, value);
    }

    /// HitTestableContainer property.
    /// The default value is false.
    /// \see setHitTestableContainer(), isHitTestableContainer()
    static PropertyType<bool> HitTestableContainerProperty;
    /// Gets the value of #HitTestableContainerProperty.
    /// \see setHitTestableContainer()
    bool isHitTestableContainer() const
    {
        return getProperty(HitTestableContainerProperty);
    }
    /// Sets the value of #HitTestableContainerProperty.
    /// \see isHitTestableContainer()
    void setHitTestableContainer(bool value)
    {
        setProperty(HitTestableContainerProperty, value);
    }

    /// Visible property.
    /// The default value is true.
    /// \see setVisible(), isVisible()
    static PropertyType<bool> VisibleProperty;
    /// Gets the value of #VisibleProperty.
    /// \see setVisible()
    bool isVisible() const
    {
        return getProperty(VisibleProperty);
    }
    /// Sets the value of #VisibleProperty.
    /// \see isVisible()
    void setVisible(bool value)
    {
        setProperty(VisibleProperty, value);
    }

    /// Enabled property.
    /// The default value is true.
    /// \see setEnabled(), isEnabled()
    static PropertyType<bool> EnabledProperty;
    /// Gets the value of #EnabledProperty.
    /// \see setEnabled()
    bool isEnabled() const
    {
        return getProperty(EnabledProperty);
    }
    /// Sets the value of #EnabledProperty.
    /// \see isEnabled()
    void setEnabled(bool value)
    {
        setProperty(EnabledProperty, value);
    }

    /// The property specifies whether a node can get active focus and can participate
    /// in the focus chain navigation. When the node is also a focus scope, it specifies
    /// whether the scope is a focus fence.
    /// The default value is true.
    /// \see setFocusable(), isFocusable()
    static PropertyType<bool> FocusableProperty;
    /// Gets the value of #FocusableProperty.
    /// \see setFocusable()
    bool isFocusable() const
    {
        return getProperty(FocusableProperty);
    }
    /// Sets the value of #FocusableProperty.
    /// \param value true to set the node focusable, false if not.
    /// \see isFocusable()
    void setFocusable(bool value)
    {
        setProperty(FocusableProperty, value);
    }

    /// Specifies that the node is the active focus node, which receives
    /// keyboard messages. There is only one node in an application that can have
    /// active focus.
    /// The default value is false.
    /// \see setFocused(), isFocused()
    static PropertyType<bool> FocusedProperty;
    /// Gets the value of #FocusedProperty.
    /// \see setFocused()
    bool isFocused() const
    {
        return getProperty(FocusedProperty);
    }
    /// Sets the value of #FocusedProperty.
    /// \param value true to set the active focus, false to clear it.
    /// \see isFocused(), FocusManager::trySetActiveFocus()
    void setFocused(bool value)
    {
        setProperty(FocusedProperty, value);
    }

    /// Specifies that the node has logical focus state. An application can have
    /// multiple logical focus nodes set, however only one node in a focus scope
    /// can have logical focus set.
    /// The default value is false.
    /// \see FocusManager::trySetActiveFocus(), FocusManager::FocusScopeProperty, setScopeFocusedNode()
    static PropertyType<bool> LogicalFocusProperty;
    /// Returns the #LogicalFocusedProperty value.
    bool hasLogicalFocus() const
    {
        return getProperty(LogicalFocusProperty);
    }
    /// Sets the value of #LogicalFocusProperty.
    /// \param value true to set the logical focus, false to clear it.
    void setLogicalFocus(bool value)
    {
        setProperty(LogicalFocusProperty, value);
    }

    /// Font property.
    /// Defines the resource ID of the font resource.
    /// The default value is ResourceSharedPtr().
    /// \see setFont(), getFont()
    static PropertyType<ResourceSharedPtr> FontProperty;
    /// Gets the value of #FontProperty.
    /// \see setFont()
    FontSharedPtr getFont() const;
    /// Sets the value of #FontProperty.
    /// \see getFont()
    void setFont(FontSharedPtr value);

    /// VisibleAmountInParent property.
    /// The default value is 1.0f.
    /// \see setVisibleAmountInParent(), getVisibleAmountInParent()
    static PropertyType<float> VisibleAmountInParentProperty;
    /// Gets the value of #VisibleAmountInParentProperty.
    /// \see setVisibleAmountInParent()
    float getVisibleAmountInParent() const
    {
        return getProperty(VisibleAmountInParentProperty);
    }
    /// Sets the value of #VisibleAmountInParentProperty.
    /// \see getVisibleAmountInParent()
    void setVisibleAmountInParent(float value)
    {
        setProperty(VisibleAmountInParentProperty, value);
    }

    /// Projection2DTo3DScale property.
    /// The default value is 0.02f.
    /// \see setProjection2DTo3DScale(), getProjection2DTo3DScale()
    static PropertyType<float> Projection2DTo3DScaleProperty;
    /// Gets the value of #Projection2DTo3DScaleProperty.
    /// \see setProjection2DTo3DScale()
    float getProjection2DTo3DScale() const
    {
        return getProperty(Projection2DTo3DScaleProperty);
    }
    /// Sets the value of #Projection2DTo3DScaleProperty.
    /// \see getProjection2DTo3DScale()
    void setProjection2DTo3DScale(float value)
    {
        setProperty(Projection2DTo3DScaleProperty, value);
    }

    /// EnableClick property.
    /// The default value is false.
    /// \see setEnableClick(), isEnableClick()
    static PropertyType<bool> EnableClickProperty;
    /// Gets the value of #EnableClickProperty.
    /// \see setEnableClick()
    bool isEnableClick() const
    {
        return getProperty(EnableClickProperty);
    }
    /// Sets the value of #EnableClickProperty.
    /// \see isEnableClick()
    void setEnableClick(bool value)
    {
        setProperty(EnableClickProperty, value);
    }

    /// EnableMultiClick property.
    /// The default value is false.
    /// \see setEnableMultiClick(), isEnableMultiClick()
    static PropertyType<bool> EnableMultiClickProperty;
    /// Gets the value of #EnableMultiClickProperty.
    /// \see setEnableMultiClick()
    bool isEnableMultiClick() const
    {
        return getProperty(EnableMultiClickProperty);
    }
    /// Sets the value of #EnableMultiClickProperty.
    /// \see isEnableMultiClick()
    void setEnableMultiClick(bool value)
    {
        setProperty(EnableMultiClickProperty, value);
    }

    /// Style property.
    /// The default value is ResourceSharedPtr().
    /// \see setStyle(), getStyle()
    static PropertyType<ResourceSharedPtr> StyleProperty;
    /// Gets the value of #StyleProperty.
    /// \see setStyle()
    ResourceSharedPtr getStyle() const
    {
        return getProperty(StyleProperty);
    }
    /// Sets the value of #StyleProperty.
    /// \see getStyle()
    void setStyle(ResourceSharedPtr value)
    {
        setProperty(StyleProperty, value);
    }

    /// StateManager property.
    /// The default value is ResourceSharedPtr().
    /// \see setStateManager(), getStateManager()
    static PropertyType<ResourceSharedPtr> StateManagerProperty;
    /// Gets the value of #StateManagerProperty.
    /// \see setStateManager()
    ResourceSharedPtr getStateManager() const
    {
        return getProperty(StateManagerProperty);
    }
    /// Sets the value of #StateManagerProperty.
    /// \see getStateManager()
    void setStateManager(ResourceSharedPtr value)
    {
        setProperty(StateManagerProperty, value);
    }

    /// PrefabTemplateSource property.
    /// The default value is 0.
    /// \see setPrefabTemplateSource(), getPrefabTemplateSource()
    static PropertyType<void*> PrefabTemplateSourceProperty;

    /// Width property.
    /// The default value is 0.0f.
    /// \see setWidth(), getWidth()
    static PropertyType<float> WidthProperty;
    /// Gets the value of #WidthProperty.
    /// \see setWidth()
    float getWidth() const
    {
        return getProperty(WidthProperty);
    }
    /// Sets the value of #WidthProperty.
    /// \see getWidth()
    void setWidth(float value)
    {
        setProperty(WidthProperty, value);
    }

    /// Height property.
    /// The default value is 0.0f.
    /// \see setHeight(), getHeight()
    static PropertyType<float> HeightProperty;
    /// Gets the value of #HeightProperty.
    /// \see setHeight()
    float getHeight() const
    {
        return getProperty(HeightProperty);
    }
    /// Sets the value of #HeightProperty.
    /// \see getHeight()
    void setHeight(float value)
    {
        setProperty(HeightProperty, value);
    }

    /// Depth property.
    /// The default value is 0.0f.
    /// \see setDepth(), getDepth()
    static PropertyType<float> DepthProperty;
    /// Gets the value of #DepthProperty.
    /// \see setDepth()
    float getDepth() const
    {
        return getProperty(DepthProperty);
    }
    /// Sets the value of #DepthProperty.
    /// \see getDepth()
    void setDepth(float value)
    {
        setProperty(DepthProperty, value);
    }

    /// ActualWidth property.
    /// The default value is 0.0f.
    /// \see setActualWidth(), getActualWidth()
    static PropertyType<float> ActualWidthProperty;
    /// Gets the value of #ActualWidthProperty.
    /// \see setActualWidth()
    float getActualWidth() const
    {
        return getProperty(ActualWidthProperty);
    }
    /// Sets the value of #ActualWidthProperty.
    /// \see getActualWidth()
    void setActualWidth(float value)
    {
        setProperty(ActualWidthProperty, value);
    }

    /// ActualHeight property.
    /// The default value is 0.0f.
    /// \see setActualHeight(), getActualHeight()
    static PropertyType<float> ActualHeightProperty;
    /// Gets the value of #ActualHeightProperty.
    /// \see setActualHeight()
    float getActualHeight() const
    {
        return getProperty(ActualHeightProperty);
    }
    /// Sets the value of #ActualHeightProperty.
    /// \see getActualHeight()
    void setActualHeight(float value)
    {
        setProperty(ActualHeightProperty, value);
    }

    /// ActualDepth property.
    /// The default value is 0.0f.
    /// \see setActualDepth(), getActualDepth()
    static PropertyType<float> ActualDepthProperty;
    /// Gets the value of #ActualDepthProperty.
    /// \see setActualDepth()
    float getActualDepth() const
    {
        return getProperty(ActualDepthProperty);
    }
    /// Sets the value of #ActualDepthProperty.
    /// \see getActualDepth()
    void setActualDepth(float value)
    {
        setProperty(ActualDepthProperty, value);
    }

    /// HorizontalAlignment property.
    /// The default value is Node::HorizontalAlignmentCenter.
    /// \see setHorizontalAlignment(), getHorizontalAlignment()
    static PropertyType<Node::HorizontalAlignment> HorizontalAlignmentProperty;
    /// Gets the value of #HorizontalAlignmentProperty.
    /// \see setHorizontalAlignment()
    Node::HorizontalAlignment getHorizontalAlignment() const
    {
        return getProperty(HorizontalAlignmentProperty);
    }
    /// Sets the value of #HorizontalAlignmentProperty.
    /// \see getHorizontalAlignment()
    void setHorizontalAlignment(Node::HorizontalAlignment value)
    {
        setProperty(HorizontalAlignmentProperty, value);
    }

    /// VerticalAlignment property.
    /// The default value is Node::VerticalAlignmentCenter.
    /// \see setVerticalAlignment(), getVerticalAlignment()
    static PropertyType<Node::VerticalAlignment> VerticalAlignmentProperty;
    /// Gets the value of #VerticalAlignmentProperty.
    /// \see setVerticalAlignment()
    Node::VerticalAlignment getVerticalAlignment() const
    {
        return getProperty(VerticalAlignmentProperty);
    }
    /// Sets the value of #VerticalAlignmentProperty.
    /// \see getVerticalAlignment()
    void setVerticalAlignment(Node::VerticalAlignment value)
    {
        setProperty(VerticalAlignmentProperty, value);
    }

    /// DepthAlignment property.
    /// The default value is Node::DepthAlignmentCenter.
    /// \see setDepthAlignment(), getDepthAlignment()
    static PropertyType<Node::DepthAlignment> DepthAlignmentProperty;
    /// Gets the value of #DepthAlignmentProperty.
    /// \see setDepthAlignment()
    Node::DepthAlignment getDepthAlignment() const
    {
        return getProperty(DepthAlignmentProperty);
    }
    /// Sets the value of #DepthAlignmentProperty.
    /// \see getDepthAlignment()
    void setDepthAlignment(Node::DepthAlignment value)
    {
        setProperty(DepthAlignmentProperty, value);
    }

    /// Sets the horizontal space between this node and other nodes that are adjacent to this node in a layout.
    /// The X component sets the left margin and the Y component sets the right margin. The default value is Vector2(0.0f, 0.0f).
    /// \see setHorizontalMargin(), getHorizontalMargin()
    static PropertyType<Vector2> HorizontalMarginProperty;
    /// Gets the value of #HorizontalMarginProperty.
    /// \see setHorizontalMargin()
    Vector2 getHorizontalMargin() const
    {
        return getProperty(HorizontalMarginProperty);
    }
    /// Sets the value of #HorizontalMarginProperty.
    /// \see getHorizontalMargin()
    void setHorizontalMargin(Vector2 value)
    {
        setProperty(HorizontalMarginProperty, value);
    }

    /// Sets the vertical space between this node and other nodes that are adjacent to this node in a layout.
    /// The X component sets the bottom margin and the Y component sets the top margin. The default value is Vector2(0.0f, 0.0f).
    /// \see setVerticalMargin(), getVerticalMargin()
    static PropertyType<Vector2> VerticalMarginProperty;
    /// Gets the value of #VerticalMarginProperty.
    /// \see setVerticalMargin()
    Vector2 getVerticalMargin() const
    {
        return getProperty(VerticalMarginProperty);
    }
    /// Sets the value of #VerticalMarginProperty.
    /// \see getVerticalMargin()
    void setVerticalMargin(Vector2 value)
    {
        setProperty(VerticalMarginProperty, value);
    }

    /// Sets the space in the depth direction between this node and other nodes that are adjacent to this node in a layout.
    /// The X component sets the back margin and the Y component sets the front margin. The default value is Vector2(0.0f, 0.0f).
    /// \see setDepthMargin(), getDepthMargin()
    static PropertyType<Vector2> DepthMarginProperty;
    /// Gets the value of #DepthMarginProperty.
    /// \see setDepthMargin()
    Vector2 getDepthMargin() const
    {
        return getProperty(DepthMarginProperty);
    }
    /// Sets the value of #DepthMarginProperty.
    /// \see getDepthMargin()
    void setDepthMargin(Vector2 value)
    {
        setProperty(DepthMarginProperty, value);
    }

    /// ContentStretch property.
    /// The default value is Node::ContentStretchUniform.
    /// \see setContentStretch(), getContentStretch()
    static PropertyType<Node::ContentStretch> ContentStretchProperty;
    /// Gets the value of #ContentStretchProperty.
    /// \see setContentStretch()
    Node::ContentStretch getContentStretch() const
    {
        return getProperty(ContentStretchProperty);
    }
    /// Sets the value of #ContentStretchProperty.
    /// \see getContentStretch()
    void setContentStretch(Node::ContentStretch value)
    {
        setProperty(ContentStretchProperty, value);
    }

    /// Opacity property.
    /// The default value is 1.0f.
    /// \see setOpacity(), getOpacity()
    static PropertyType<float> OpacityProperty;
    /// Gets the value of #OpacityProperty.
    /// \see setOpacity()
    float getOpacity() const
    {
        return getProperty(OpacityProperty);
    }
    /// Sets the value of #OpacityProperty.
    /// \see getOpacity()
    void setOpacity(float value)
    {
        setProperty(OpacityProperty, value);
    }

    /// Kanzi updates the #HoverProperty for a hit testable node to indicate whether
    /// the node is the foremost node under the cursor. Kanzi also sets #HoverProperty
    /// to true for the all of the ancestors of the foremost hit testable node under the cursor.
    /// \see isHover()
    static PropertyType<bool> HoverProperty;
    /// Returns whether the node has #HoverProperty set to true.
    /// \return If the #HoverProperty is set to true, \e true,
    /// otherwise \e false.
    bool isHover() const
    {
        return getProperty(HoverProperty);
    };

    /// ClipChildren property.
    /// The default value is true.
    /// \see setClipChildren(), isClipChildren()
    static PropertyType<bool> ClipChildrenProperty;
    /// Gets the value of #ClipChildrenProperty.
    /// \see setClipChildren()
    bool isClipChildren() const
    {
        return getProperty(ClipChildrenProperty);
    }
    /// Sets the value of #ClipChildrenProperty.
    /// \see isClipChildren()
    void setClipChildren(bool value)
    {
        setProperty(ClipChildrenProperty, value);
    }

    /// SceneGraphAddNodeChangeChildFlags property.
    /// The default value is PropertyTypeChangeFlagFinalTransformation | PropertyTypeChangeFlagMeasure.
    /// \see setSceneGraphAddNodeChangeChildFlags(), getSceneGraphAddNodeChangeChildFlags()
    static PropertyType<int> SceneGraphAddNodeChangeChildFlagsProperty;

    /// SceneGraphAddNodeChangeParentFlags property.
    /// The default value is PropertyTypeChangeFlagMeasure.
    /// \see setSceneGraphAddNodeChangeParentFlags(), getSceneGraphAddNodeChangeParentFlags()
    static PropertyType<int> SceneGraphAddNodeChangeParentFlagsProperty;

    /// SceneGraphRemoveNodeChangeChildFlags property.
    /// The default value is 0.
    /// \see setSceneGraphRemoveNodeChangeChildFlags(), getSceneGraphRemoveNodeChangeChildFlags()
    static PropertyType<int> SceneGraphRemoveNodeChangeChildFlagsProperty;

    /// SceneGraphRemoveNodeChangeParentFlags property.
    /// The default value is PropertyTypeChangeFlagMeasure.
    /// \see setSceneGraphRemoveNodeChangeParentFlags(), getSceneGraphRemoveNodeChangeParentFlags()
    static PropertyType<int> SceneGraphRemoveNodeChangeParentFlagsProperty;

    /// \}

    // TODO: split layout functionality to LayoutItemConcept
    KZ_ABSTRACT_METACLASS_BEGIN(Node, Object, "Kanzi.Node")
        KZ_METACLASS_PROPERTY_TYPE(NameProperty)
        KZ_METACLASS_PROPERTY_TYPE(PathProperty)
        KZ_METACLASS_PROPERTY_TYPE(LocaleProperty)
        KZ_METACLASS_PROPERTY_TYPE(WidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(HeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthProperty)
        KZ_METACLASS_PROPERTY_TYPE(ActualWidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(ActualHeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(ActualDepthProperty)
        KZ_METACLASS_PROPERTY_TYPE(HorizontalAlignmentProperty)
        KZ_METACLASS_PROPERTY_TYPE(VerticalAlignmentProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthAlignmentProperty)
        KZ_METACLASS_PROPERTY_TYPE(HorizontalMarginProperty)
        KZ_METACLASS_PROPERTY_TYPE(VerticalMarginProperty)
        KZ_METACLASS_PROPERTY_TYPE(DepthMarginProperty)
        KZ_METACLASS_PROPERTY_TYPE(HitTestableProperty)
        KZ_METACLASS_PROPERTY_TYPE(HitTestableContainerProperty)
        KZ_METACLASS_PROPERTY_TYPE(VisibleProperty)
        KZ_METACLASS_PROPERTY_TYPE(EnabledProperty)
        KZ_METACLASS_PROPERTY_TYPE(FocusableProperty)
        KZ_METACLASS_PROPERTY_TYPE(FocusedProperty)
        KZ_METACLASS_PROPERTY_TYPE(LogicalFocusProperty)
        KZ_METACLASS_PROPERTY_TYPE(FontProperty)
        KZ_METACLASS_PROPERTY_TYPE(VisibleAmountInParentProperty)
        KZ_METACLASS_PROPERTY_TYPE(ClipChildrenProperty)
        KZ_METACLASS_PROPERTY_TYPE(EnableClickProperty)
        KZ_METACLASS_PROPERTY_TYPE(EnableMultiClickProperty)
        KZ_METACLASS_PROPERTY_TYPE(ContentStretchProperty)
        KZ_METACLASS_PROPERTY_TYPE(OpacityProperty)
        KZ_METACLASS_PROPERTY_TYPE(HoverProperty)
        KZ_METACLASS_PROPERTY_TYPE(StyleProperty)
        KZ_METACLASS_PROPERTY_TYPE(StateManagerProperty)
        KZ_METACLASS_PROPERTY_TYPE(Projection2DTo3DScaleProperty)
        KZ_METACLASS_PROPERTY_TYPE(PrefabTemplateSourceProperty)
        KZ_METACLASS_PROPERTY_TYPE(CreatedFromKZBProperty)
    KZ_METACLASS_END()

    /// Destructor.
    virtual ~Node();

    /// Returns the current value of a property.
    ///
    /// The value returned by this function is the result of the property system evaluating the inputs that can affect the values of properties.
    /// The final value is calculated by determining the base value of the property and applying existing modifiers to it.
    ///
    /// Base value is affected by the following inputs where the highest entry in the list determines the base value:
    /// 1. Local value set with setProperty or loaded from kzb
    /// 2. Value set by a style affecting the property.
    /// 3. Value defined by class metadata.
    ///
    /// When the base value is determined the system applies modifiers to the value that can change the value or replace it completely.
    /// The following is the list of possible modifiers, where the order of evaluation is determined by the order the modifiers were added or applied.
    /// 1. Values defined is states of state manager.
    /// 2. Animations.
    ///
    /// If the property metadata specifies that the property is inheritable and no inputs for the property value can be determined at the current node
    /// the system iterates the scene graph to the root until inputs are found or the root is reached.
    ///
    /// If no inputs to the property value can be established the system returns the value registered in the property type metadata.
    /// \param propertyType The property type identifying the property to retrieve.
    /// \return Returns the evaluated property value.
    template <typename DataType>
    typename PropertyType<DataType>::Traits::ReturnType getProperty(const PropertyType<DataType>& propertyType) const
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename PropertyType<DataType>::Traits Traits;
        typedef typename Descriptor::TypedValueSource TypedValueSource;

        Descriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::ValueSource* finalValueSource = getNodeFinalValueSource(*descriptor);
        if (!finalValueSource)
        {
            return propertyType.getDefaultValue();
        }

        TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(finalValueSource);
        return Traits::read(typedValueSource->value);
    }

    AbstractPropertyTypeDescriptor::ValueSource* getNodeFinalValueSource(AbstractPropertyTypeDescriptor& descriptor) const
    {
        AbstractPropertyTypeDescriptor::ValueSource* valueSource = getNonClassValueSource(descriptor);
        if (valueSource)
        {
            return valueSource;
        }

        // For inherited properties, traverse non-class values upwards.
        if (descriptor.isInherited())
        {
            for (const Node* currentNode = getParent(); currentNode; currentNode = currentNode->getParent())
            {
                valueSource = currentNode->getNonClassValueSource(descriptor);
                if (valueSource)
                {
                    return valueSource;
                }
            }
        }

        // If nothing else found, return class value source.
        return getClassValueSource(descriptor);
    }

    /// Evaluates the property value in the same way as the overload above but does not default to the value in property metadata if there are no inputs to the property value.
    /// \param propertyType The property type identifying the property to retrieve.
    /// \param value The reference that receives the value the function evaluates. The reference is not modified if there are no inputs to the property value.
    /// \return Returns true if there are inputs into the property value, false otherwise.
    template <typename DataType>
    optional<typename PropertyType<DataType>::Traits::ReturnType> getOptionalProperty(const PropertyType<DataType>& propertyType) const
    {
        typedef typename PropertyType<DataType>::Descriptor Descriptor;
        typedef typename PropertyType<DataType>::Traits Traits;
        typedef typename Descriptor::TypedValueSource TypedValueSource;

        Descriptor* descriptor = propertyType.get();
        kzAssert(descriptor);
        AbstractPropertyTypeDescriptor::ValueSource* finalValueSource = getNodeFinalValueSource(*descriptor);
        if (!finalValueSource)
        {
            return nullopt;
        }

        TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(finalValueSource);
        return Traits::read(typedValueSource->value);
    }

    template <typename DataType>
    DataType getAbstractProperty(AbstractPropertyType abstractPropertyType) const;

    template <typename DataType>
    optional<typename PropertyType<DataType>::DataType> getOptionalAbstractProperty(AbstractPropertyType abstractPropertyType) const;

    /// Message subscription token for nodes.
    class MessageSubscriptionToken
    {
        friend class Node;
        const KzuMessageType* m_messageType;
        MessageSubscriptionFunctionWeakPtr m_functionWeakPtr;

    public:
        explicit MessageSubscriptionToken(const KzuMessageType* messageType, MessageSubscriptionFunctionSharedPtr messageSubscriptionFunction) :
            m_messageType(messageType),
            m_functionWeakPtr(messageSubscriptionFunction)
        {
        }

        explicit MessageSubscriptionToken() :
            m_messageType()
        {
        }

        bool isValid() const
        {
            return !m_functionWeakPtr.expired();
        }
    };

    typedef kanzi::vector<Node::MessageSubscriptionToken> MessageSubscriptionTokenVector;

    /// Adds a message handler where handler is a method to invoke on an object.
    /// The handler is invoked when a message of messageType is signaled in the node the handler is added to.
    template <typename TMessageType, typename TClass, typename TClassMethod>
    MessageSubscriptionToken addMessageHandler(TMessageType& messageType, TClass* messageHandlerObject, TClassMethod method);

    /// Adds a message filter where filter is a method to invoke on an object.
    /// The filter is invoked when a message of messageType bubbles through the node the handler is added to.
    template <typename TMessageType, typename TClass, typename TClassMethod>
    MessageSubscriptionToken addMessageFilter(TMessageType& messageType, TClass* messageHandlerObject, TClassMethod method);

    /// Adds a message handler where handler is function.
    /// The handler is invoked when a message of messageType is signaled in the node the handler is added to.
    template <typename TMessageType>
    MessageSubscriptionToken addMessageHandler(const TMessageType& messageType, typename TMessageType::FunctionType function);

    /// Adds a message filter where filter is function.
    /// The filter is invoked when a message of messageType bubbles through the node the handler is added to.
    template <typename TMessageType>
    MessageSubscriptionToken addMessageFilter(const TMessageType& messageType, typename TMessageType::FunctionType function);

    /// Adds a message handler where handler is function and accepted source is explicitly defined.
    /// The handler is invoked when a message of messageType bubbles through the node the handler is added to, but only if it was dispatched from the given source node.
    /// \param messageType Message type to listen to.
    /// \param function Function to invoke when message is received.
    /// \param messageSourceFilter Only accept messages
    template <typename TMessageType>
    MessageSubscriptionToken addMessageHandler(const TMessageType& messageType, typename TMessageType::FunctionType function, Node* messageSourceFilter);

    /// Removes a message subscription.
    void removeMessageHandler(MessageSubscriptionToken token);

    /// Dispatches a message with specified arguments.
    template <typename TArgumentsType>
    void dispatchMessage(const MessageType<TArgumentsType>& messageType, typename MessageType<TArgumentsType>::ArgumentsType& messageArguments);

    // TODO: use ResourceID in the name
    /// Adds a resource manager resource to an object node. If resourceID already exists in object, removes the existing entry. If resourceURL is NULL, error is thrown. */
    void addResource(const ResourceID& resourceId, string_view resourceUrl);
    /// Removes a resource with given ID from object node resource dictionary. Does not do anything if resourceID was not found. */
    void removeResource(const ResourceID& resourceId);
    /// Returns if object node resource dictionary contains the resource with given ID. Resource can be any type: style, alias or resource manager resource. */
    bool containsResource(const ResourceID& resourceID) const;

    /// Tries to find Resource URL for Resource ID from this node.
    optional<string> findResourceURL(const ResourceID& resourceId) const;

    /// Acquires a resource from the node or the node's closest ancestor having the resource id in the resource dictionary.
    /// If the resource id maps to a resource url, but the url doesn't map to any resource, throws an exception.
    /// \param id Name of the resource.
    /// \return Shared pointer to the resource, or nullptr if the resource id doesn't map to any resource url.
    ResourceSharedPtr acquireResource(const ResourceID& id) const;

    /// Acquires a resource from the node or the node's closest ancestor having the resource id in the resource dictionary, and casts the resource to given type.
    /// If the cast fails, or the found resource url doesn't map to a resource, throws an exception.
    /// \param id Name of the resource.
    /// \return Shared pointer to the resource, or nullptr if the resource id doesn't map to any resource url.
    template <typename T>
    shared_ptr<T> acquireResource(const ResourceID& id) const;

    /// Acquires a resource from the node or the node's closest ancestor having the resource id in the resource dictionary.
    /// \param id Name of the resource.
    /// \return Shared pointer to the resource, or nullptr if the resource id or resource url doesn't map to any resource.
    ResourceSharedPtr tryAcquireResource(const ResourceID& id) const;

    /// Posts an asynchronous task to acquire a resource.
    /// \param key Name of the resource.
    /// \param func Callback to execute upon completion of the task.
    /// \return Task created or an empty shared pointer on failure.
    ResourceManager::AcquireTaskSharedPtr acquireResourceAsync(const ResourceID& key, ResourceManager::AsyncAcquireFinishedCallback func) const;

    /// Acquires a resource from the node or the node's closest ancestor having the resource and casts the resource to given type.
    /// \param id Name of the resource.
    /// \return Shared pointer to the resource, or nullptr if the resource is not found.
    template <typename T>
    shared_ptr<T> tryAcquireResource(const ResourceID& id) const;


    /// Gets the resource dictionary of the node, if the node has one.
    /// \return The resource dictionary of the node, or nullptr if the node doesn't have a resource dictionary.
    ResourceDictionarySharedPtr getResourceDictionary() const;

    /// Gets the resource dictionary of the node. Creates the dictionary if it doesn't exist.
    /// \return The resource dictionary of the node.
    ResourceDictionarySharedPtr acquireResourceDictionary();

    /// Forces the re-evaluation of resource IDs in a node tree.
    /// If you modify a resource dictionary of a node that is already attached, you can use this to update the resource properties.
    /// Note that you need to use this function only if you modify the dictionary directly through #getResourceDictionary or #acquireResourceDictionary.
    /// If you use other Node class functions like #addResource or #setResourceDictionary, you don't need to call this.
    void notifyResourceDictionaryModified();

    /// Replaces the resource dictionary of the node.
    /// Updates all the resource references of the child nodes.
    /// \param resourceDictionary The resource dictionary.
    void setResourceDictionary(ResourceDictionarySharedPtr resourceDictionary);

    /// Add a nested resource dictionary to the resource dictionary of the node.
    /// Updates all the resource references of the child nodes.
    /// \param resourceDictionary The nested resource dictionary.
    void addResourceDictionary(ResourceDictionarySharedPtr resourceDictionary);


    /** Adds alias resource to an object node. */
    //kzsError addAliasResource(kzString resourceId, kzString targetPath);
    /** Removes alias resource from an object node. */
    //kzsError removeAliasResource(kzString resourceId);

    /// Adds anonymous resource (such as style) for object node resources.
    void addAnonymousResource(ResourceSharedPtr resource);
    /// Removes anonymous resource from object node resources.
    void removeAnonymousResource(const Resource& resource);

    bool isNamed(string_view name) const;

    /// Returns the parent of the node.
    Node* getParent() const;

    void setParent(Node* parent);

    enum VisitorOrder
    {
        VisitorPreOrder,
        VisitorPostOrder
    };

    enum VisitorResult
    {
        VisitorAbort,
        VisitorContinue,
        VisitorContinueSibling
    };

    typedef function<VisitorResult(Node&)> Visitor;

    VisitorResult visit(const Visitor& visitor, VisitorOrder order);
    VisitorResult visitDescendants(const Visitor& visitor, VisitorOrder order);

    /// Returns a node of specified type by looking it up with specified path or alias.
    template <typename Type>
    shared_ptr<Type> lookupNode(string_view pathOrKey);

    /// Get an object node by another node and a relative path. User should use lookupNode.
    ///
    /// \param relativePath Path to use for relative lookup.
    /// \return Pointer to node.
    Node* lookupNodeRaw(string_view relativePath);

    /// Lookup for an object from a node.
    ///
    /// Object found may be another node or a resource within a node.
    ///
    /// \param relativePath Relative path to use for lookup.
    /// \return Shared pointer referencing object. May be empty if no object found.
    ObjectSharedPtr lookupObject(string_view relativePath);

    /// Lookup for an node and possible object from within the node for state manager.
    ///
    /// If the path points to a resource within the node, the node, and the associated abstract property type will be returned.
    ///
    /// \param relativePath Relative path to use for lookup.
    /// \return Tuple of node and possibly abstract property type.
    tuple<NodeSharedPtr, AbstractPropertyType> lookupObjectForStateManager(string_view relativePath);

    /// Lookup for an object from a node.
    ///
    /// Object found may be another node or a resource within a node.
    ///
    /// \param relativePath Relative path to use for lookup.
    /// \return Shared pointer referencing object. May be empty if no object found.
    template <typename Type>
    shared_ptr<Type> lookupObject(string_view path)
    {
        return dynamic_pointer_cast<Type>(lookupObject(path));
    }

    /// Find a child by name. Finds direct children as well as children connected indirectly for example Viewport->Scene.
    template <typename TNodeType>
    shared_ptr<TNodeType> findAbstractChild(string_view name);

    virtual bool addAbstractChildOverride(NodeSharedPtr child) = 0;
    virtual size_t getAbstractChildCountOverride() = 0;
    virtual NodeSharedPtr getAbstractChildOverride(size_t index) = 0;
    virtual bool removeAbstractChildOverride(Node& child) = 0;

    /** Transfers the ownership and attaches an input manipulator to an object node. */
    void addInputManipulator(InputManipulatorSharedPtr inputManipulator);
    /** Removes the ownership and detaches an input manipulator from an object node. */
    void removeInputManipulator(InputManipulator& inputManipulator);

    /** Gets the input manipulator iterator. */
    typedef vector<InputManipulatorSharedPtr> InputManipulatorContainer;
    typedef InputManipulatorContainer::iterator InputManipulatorIterator;
    typedef InputManipulatorContainer::const_iterator InputManipulatorConstIterator;
    InputManipulatorConstIterator beginInputManipulators() const;
    InputManipulatorConstIterator endInputManipulators() const;

    /** Transfers the ownership of a binding rule to an object node. */
    void addBinding(BindingSharedPtr binding);
    /** Transfers the ownership of a binding rule to an object node and sets the owner of binding rule. */
    void addBindingWithOwner(BindingSharedPtr binding, shared_ptr<void> owner);
    /** Removes the ownership and detaches a binding rule from an object node. */
    void removeBinding(Binding& binding);
    /** Removes all bindings with the specified owner. */
    void removeBindingsWithOwner(shared_ptr<void> owner);

    /** binding entry. */
    struct BindingEntry
    {
        BindingEntry(BindingSharedPtr binding, shared_ptr<void> owner) :
            binding(binding),
            owner(owner)
        {
        }

        BindingSharedPtr binding; /**< Binding. */
        shared_ptr<void> owner;   /**< Owner of the binding. */
    };

    /** Gets the bindings iterator. */
    typedef vector<BindingEntry> BindingContainer;
    typedef BindingContainer::iterator BindingIterator;
    typedef BindingContainer::const_iterator BindingConstIterator;
    BindingConstIterator beginBindings() const;
    BindingConstIterator endBindings() const;

    /** Transfers the ownership of a node component to an object node. */
    void addNodeComponent(NodeComponentSharedPtr nodeComponent);
    /** Transfers the ownership of a node component to an object node and sets the owner of the node component. */
    void addNodeComponentWithOwner(NodeComponentSharedPtr nodeComponent, const void* owner);
    /** Removes the ownership of a node component from an object node. */
    void removeNodeComponent(NodeComponent& nodeComponent);
    /** Removes all bindings with the specified owner. */
    void removeNodeComponentWithOwner(const void* owner);

    /** Object node component entry. */
    struct NodeComponentEntry
    {
        NodeComponentEntry(NodeComponentSharedPtr nodeComponent, const void* owner) :
            nodeComponent(nodeComponent),
            owner(owner)
        {
        }

        NodeComponentSharedPtr nodeComponent; /**< Node component. */
        const void* owner;                    /**< Owner of the node component. */
    };

    /** Gets the node component iterator. */
    typedef vector<NodeComponentEntry> NodeComponentContainer;
    typedef NodeComponentContainer::iterator NodeComponentIterator;
    typedef NodeComponentContainer::const_iterator NodeComponentConstIterator;
    NodeComponentConstIterator beginNodeComponents() const;
    NodeComponentConstIterator endNodeComponents() const;

    /// Returns a node component of specified type by looking it up with specified name.
    /// If name is not specified, then the first anonymous node component of specified type
    /// is returned.
    template <typename Type>
    shared_ptr<Type> lookupNodeComponent(string_view name);

    /// Sets whether the object node is renderable.
    void setRenderable(bool state);

    /// Returns whether node is renderable.
    bool isRenderable() const;

    /// Checks if the node and all of its ancestors are visible.
    bool isEffectivelyVisible() const;
    /// Checks if the node and all of its ancestors are enabled.
    bool isEffectivelyEnabled() const;

    /// Get current change flags.
    ///
    /// \return Change flags directly.
    uint32_t getChangeFlags() const
    {
        return m_changeFlags;
    }
    /// Get current child change flags.
    ///
    /// \return Child change flags directly.
    uint32_t getChildChangeFlags() const
    {
        return m_childChangeFlags;
    }

    /// Sets a change flag.
    void setChangeFlag(uint32_t flag);
    /// Clears a change flag.
    void clearChangeFlag(uint32_t flag);
    /// Checks if a change flag is set.
    bool isChangeFlagSet(uint32_t flag) const;
    /// Checks if any of given flags is set.
    bool isAnyChangeFlagSet(uint32_t flag) const;

    /// Sets a child change flag.
    void setChildChangeFlag(uint32_t flag);
    /// Clears a child change flag.
    void clearChildChangeFlag(uint32_t flag);
    /// Checks if child change flags match.
    bool isChildChangeFlagSet(uint32_t flag) const;
    /// Checks if any child change flags (corresponding to given mask) are set.
    bool isAnyChildChangeFlagSet(uint32_t flag) const;

    /// Check if the node needs measure.
    bool isInvalidMeasure() const;
    /// Invalidates measure for the node.
    void invalidateMeasure();
    /// Validates measure for the node.
    void validateMeasure();

    /// Checks if the node needs arrange.
    bool isInvalidArrange() const;
    /// Invalidates arrange.
    void invalidateArrange();
    /// Validates arrange.
    void validateArrange();

    /// Returns if node render flag is invalid.
    bool isInvalidRender() const;
    /// Validates render for node.
    void validateRender();
    /// Invalidates render for node.
    void invalidateRender();

    /// Tells if final transform flag is invalid for node.
    bool isInvalidFinalTransform() const;
    /// Invalidates final transform for node.
    void invalidateFinalTransform();

    /// Tells if node draw flag is invalid.
    bool isInvalidDraw();
    /// Invalidates draw flag for the node.
    void invalidateDraw();
    /// Validates draw flags for the node.
    void validateDraw();
    /// Recursively validates draw for the children from this 2D node onwards.
    /// Called internally by the system in situations where draw does not otherwise descend to the node.
    void validateDrawForChildrenRecursive();

    /// Returns true if initialize() has been called, false otherwise.
    bool isInitialized() const;
    /// Returns true if the node is attached to a screen or one of its descendants.
    bool isAttached() const;
    /// Returns true if node is in the process of attaching, false otherwise.
    bool isAttaching() const;
    /// Returns true if the node currently detaching.
    bool isDetaching() const;

    /// Attaches an object node and its children recursively.
    void attachRecursive();
    /// Detaches an object node and its children recursively.
    void detachRecursive();

    /** Gets bounding volume from object node. Returns KZ_NULL if the object is not renderable. */
    virtual const KzuBoundingVolume* getBoundingVolume() const;

    /** Applies a style to an object node. Returns a style entry that is used to unapply the style. */
    AppliedStyleEntrySharedPtr applyStyle(StyleSharedPtr style);
    /** Applies a style to an object node. Returns a style entry that is used to unapply the style. The style must be unapplied manually. */
    AppliedStyleEntrySharedPtr applyManualStyle(StyleSharedPtr style);
    /** Unapplies a style from an object node. */
    void unapplyStyle(AppliedStyleEntrySharedPtr appliedStyleEntry);
    /** Apply all styles for an object node. */
    void applyStyles();
    /** Unapplies and removes all applied styles. */
    void unapplyStyles();
    /** Applies styles recursively. */
    void applyStylesRecursive();
    /** Unapplies styles recursively. */
    void unapplyStylesRecursive();

    /** Destroys all object node data loaded from KZB, including properties, bindings, node comopnents, resources etc. */
    void removeKZBData();

    // Adds an abstract resource reference to the node.
    ///
    /// This is a helper for automatic resource tracking in ResourceReference.
    ///
    /// \param propertyType Property type to listen changes on.
    /// \param reference Reference to react on.
    void addResourceReference(AbstractPropertyType propertyType, AbstractResourceReference* reference);
    // Removes an abstract resource reference from the node.
    ///
    /// This is a helper for automatic resource tracking in ResourceReference.
    ///
    /// \param reference Reference to remove.
    void removeResourceReference(const AbstractResourceReference& reference);

    // Adds an abstract node reference to the node. This is a helper for automatic resource tracking in NodeReference.
    void addNodeReference(AbstractPropertyType propertyType, AbstractNodeReference* reference);
    // Removes an abstract node reference from the node. This is a helper for automatic resource tracking in NodeReference.
    void removeNodeReference(const AbstractNodeReference& reference);

    /// Reattaches an object node after potential resource change.
    virtual void restoreResources()
    {
    }

    ScriptingContextSharedPtr getScriptingContext() const
    {
        return m_scriptingContext;
    }
    void setScriptingContext(ScriptingContextSharedPtr context)
    {
        m_scriptingContext = context;
    }

    /// Indicates whether a value is valid layout value. Valid layout value is a non-negative floating point number.
    /// Valid layout value can be positive infinity (unbounded layout value).
    /// \param value Value to test if it is unbound layout value.
    /// \return true if the value if valid layout value, false otherwise.
    static bool isValidLayoutValue(float value)
    {
        return (!isnan(value) && (value >= 0.0f));
    }

    /// Returns an unbounded layout value.
    /// \return Unbounded layout value.
    static float unboundedLayoutValue()
    {
        return numeric_limits<float>::infinity();
    }

    /// Indicates whether a value is an unbound layout value.
    /// \param layoutValue Value to test if it is unbound layout value.
    /// \return true if the layoutValue is unbound layout value, false otherwise.
    static bool isUnboundedLayoutValue(float layoutValue)
    {
        return (layoutValue == numeric_limits<float>::infinity());
    }

    /// Replaces layout value with the specified value if it is unbounded and returns it.
    /// \param layoutValue Layout value to test if it is unbounded layout value.
    /// \param resetValue The value which is returned if layoutValue is unbounded layout value.
    /// \return resetValue if layoutValue is an unbounded layout value, layoutValue otherwise.
    static float replaceUnboundedLayoutValue(float layoutValue, float resetValue)
    {
        return isUnboundedLayoutValue(layoutValue) ? resetValue : layoutValue;
    }

    /// Replaces layout value with zero if it is unbounded layout value and returns it.
    /// \param layoutValue Layout value to test if it is unbounded layout value.
    /// \return Zero if layoutValue is an unbounded layout value, layoutValue otherwise.
    static float replaceUnboundedLayoutValueWithZero(float layoutValue)
    {
        return replaceUnboundedLayoutValue(layoutValue, 0.0f);
    }

    /// Sets the template root of this node.
    /// Template root is used in template root bindings.
    /// This is an internal function.
    void setTemplateRoot(NodeSharedPtr templateRoot)
    {
        m_templateRoot = templateRoot;
    }

    /// Gets the template root of this node.
    /// Template root is used in template root bindings.
    /// This is an internal function.
    NodeSharedPtr getTemplateRoot() const
    {
        return m_templateRoot.lock();
    }

    /// The method tries to move the active focus on this node.
    /// \return \e true if the focus was moved on this node, \e false if not.
    bool trySetActiveFocus();

protected:
    /// Constructor.
    explicit Node(Domain* domain, string_view name);

    void initialize();

    /// Called when an object node becomes attached.
    virtual void onAttached();

    /// Called when an object node becomes detached.
    virtual void onDetached();

    /// Method executed on node property change.
    ///
    /// \param propertyType Property that was changed in node.
    /// \param reason Change reason.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason);

    // Implements child look up by name
    virtual NodeSharedPtr findAbstractChildOverride(string_view name) = 0;

    virtual VisitorResult visitAbstractChildOverride(const Visitor& visitor, VisitorOrder order) = 0;

    static VisitorResult updateResourceVisitor(Node& node, const ResourceID& id);

    static VisitorResult updateAllResourcesVisitor(Node& node);

    static VisitorResult applyStylesVisitor(Node& node, bool apply);

    static VisitorResult attachVisitor(Node& node);

    static VisitorResult detachVisitor(Node& node);

    /// Visitor for validating draw.
    static VisitorResult validateDrawVisitor(Node& node);

    /// Processes notification handlers for node and property storage.
    /// \param node Node to invoke change notification on.
    /// \param propertyType Changed property type.
    /// \param nodePropertyStorage Property storage for the node being modified.
    /// \param changedPropertyStorage Property storage actually being changed (not necessarily from node).
    /// \param reason Change reason.
    /// \return True of node still exists after notification handlers have been changed.
    static bool processPropertyChanged(Node& node, AbstractPropertyType propertyType, const PropertyStoragePtr& nodePropertyStorage,
                                       AbstractPropertyTypeDescriptor::PropertyStorage* changedPropertyStorage, PropertyNotificationReason reason);

    static VisitorResult propertyChangedVisitor(Node& node, AbstractPropertyType propertyType, AbstractPropertyTypeDescriptor::PropertyStorage* propertyStorage, PropertyNotificationReason reason);

    /// Invokes property notifications for inherited properties during scene graph tree connections.
    void updatePropertiesForConnectedNode();
    /// Invokes property notifications for inherited properties during scene graph tree disconnections.
    void updatePropertiesForDisconnectedNode(Node* oldParent);

    void updateResourceReferences();
    void updateResourceReferences(AbstractPropertyType propertyType);
    void updateResourceReferencesRecursive();
    void updateResourceReferencesRecursive(const ResourceID& resourceID);

    /// Attaches the object node.
    void attach();
    /// Detaches the object node.
    void detach();

    virtual void notifyPropertyHandlers(PropertyStoragePtr& propertyStorage, PropertyNotificationReason reason) KZ_OVERRIDE;

private:
    // TODO use shared_ptr<void> for locks
    template <typename TMessageType, typename TClass, typename TClassMethod>
    MessageSubscriptionToken addMessageHandler(TMessageType& messageType, TClass* messageHandlerObject, TClassMethod method, Node* messageSourceFilter);

    MessageSubscriptionToken addMessageHandlerInternal(const KzuMessageType* messageType, MessageSubscriptionFunction function, Node* messageSourceFilter);

    void removeMessageHandler(MessageSubscription subscription);

    static kzsError subscriptionAdapter(MessageArguments* message, void* userData);

    template <class TMessageType>
    static void trackedMessageAdapter(typename TMessageType::FunctionType& function, const weak_ptr<void>& weakPtr, MessageArguments* message);

    template <class TMessageType>
    static void functorMessageAdapter(typename TMessageType::FunctionType& function, MessageArguments* message);

    static bool isInvalidResourceReference(const ResourceReferenceEntry& entry);

    void startResourceReferenceModification();
    void finishResourceReferenceModification();

    /// Object::onPropertyChanged override. Classes derived from Node should override onNodePropertyChanged instead.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_FINAL KZ_OVERRIDE;

    /// Called on attach or when state manager is changed.
    void attachStateManager();
    /// Called on detach or when state manager is changed.
    void detachStateManager();

    /// Finds a node component with the given name.
    NodeComponentSharedPtr findNodeComponent(string_view name) const;

    /// Finds a node component with no name and a type that is derived from the given metaclass.
    NodeComponentSharedPtr findAnonymousNodeComponent(const Metaclass* metaclass) const;

    Node(const Node&) KZ_DELETED_FUNCTION;
    Node& operator=(const Node&) KZ_DELETED_FUNCTION;

    Node* m_parent; /**< Parent of the object. */

    enum StateFlags
    {
        StateInitialized = 1 << 0,
        StateRenderable = 1 << 1,
        StateAttached = 1 << 2,
        StateAttaching = 1 << 3,
        StateDetaching = 1 << 4
    };

    /// Node state flags.
    uint32_t m_flags;
    uint32_t m_changeFlags;      /**< A collection of system defined (layout, render) and user defined change flags. */
    uint32_t m_childChangeFlags; /**< A collection of system defined (layout, render) and user defined change flags for any children. */

    ResourceDictionarySharedPtr m_resourceDictionary;

    BindingContainer m_bindings;                   /**< Object node bindings. */
    NodeComponentContainer m_nodeComponents;       /**< Object node components. */
    InputManipulatorContainer m_inputManipulators; /**< Object node input manipulators */

    MessageSubscriptionContainer m_messageSubscriptions;

    typedef vector<ResourceReferenceEntry> ResourceReferenceContainer;
    ResourceReferenceContainer m_resourceReferences;
    size_t m_resourceReferencesModificationCallDepth;

    typedef tuple<AbstractPropertyType, AbstractNodeReference*> NodeReferenceEntry;
    typedef vector<NodeReferenceEntry> NodeReferenceContainer;
    NodeReferenceContainer m_nodeReferences;

    ClickManipulatorSharedPtr m_clickManipulator; /**< Click manipulator that is added in onAttached if enable click property is set. */
    /// State manager runtime state.
    StateManager::StateManagerRuntimeSharedPtr m_stateManagerRuntime;
    ScriptingContextSharedPtr m_scriptingContext;
    string m_cachedName;
    /// Pointer to template root of this node.
    /// Template root is used in template root bindings.
    NodeWeakPtr m_templateRoot;
};

/// Gets tree height from the object node to the parent. If no parents, height = 1,
/// if single parent, and parent's parent is null, height = 2 and so on.
///
/// \param node Node the tree height of which to get.
/// \return Tree height of node.
KANZI_API unsigned int getTreeHeight(const Node& node);

/// Gets the relative path from base object node to target object node,
/// or nullopt if path could not be found.
///
/// \param targetNode Node the path to which to get.
/// \param baseNode Node the patch from which to get.
/// \return Path from base node to target node or nullopt.
KANZI_API optional<string> getRelativePath(const Node& targetNode, const Node& baseNode);

/// Gets first common parent from nodeA and nodeB, or null if not found.
///
/// \param nodeA Node the common parent of which with nodeB to find.
/// \param nodeB Node the common parent of which with nodeA to find.
/// \return First common parent of nodeA and nodeB or null.
KANZI_API Node* findCommonParent(const Node& nodeA, const Node& nodeB);

/// Gets the root node of the scene graph where the node belongs to
/// or null if node does not belong to any scene graph.
///
/// \param node Node the root node of which to find.
/// \return Root node of scene graph or null.
KANZI_API Node* getRoot(Node& node);

/// Gets the root node of the scene graph where the node belongs to
/// or null if node does not belong to any scene graph.
///
/// \param node Node the root node of which to find.
/// \return Root node of scene graph or null.
KANZI_API const Node* getRoot(const Node& node);

/// Indicates whether one node is the parent of another node.
///
/// \param child Node to indicate whether it belongs to the parent node.
/// \param parent Node to indicate whether it has the child node as its child.
/// \return True if the child node is child of the parent node, false otherwise.
KANZI_API bool isParentOf(const Node& child, const Node& parent);

/// Indicates whether one node is the ancestor of another node at any level in the scene graph hierarchy.
///
/// \param node Node to indicate whether it is the descendant of the ancestor node.
/// \return True if the ancestor node is the parent of the node at any level, false otherwise.
KANZI_API bool isAncestorOf(const Node& node, const Node& ancestor);

/// Gets nearest parent of specified type.
///
/// \param node Node the parent of specified type of which to get.
/// \return Parent node of specified type of the node.
template <typename Type>
shared_ptr<Type> findParent(const Node& node);
}

// Include the headers required for implementations of node functions.
#include <kanzi/core.ui/node/node.hpp.inl>

#endif
