// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE2D_HPP
#define KZ_NODE2D_HPP


#include "node.hpp"
#include "node_compositor2d.hpp"
#include "node_visual2d.hpp"

#include <kanzi/core.ui/graphics2d/composition_brush.hpp>
#include <kanzi/core.ui/graphics2d/composition_brush_renderer.hpp>
#include <kanzi/core.ui/graphics2d/composition_requirements.hpp>
#include <kanzi/core.ui/graphics2d/geometry_quad.hpp>
#include <kanzi/core/math/rectangle.hpp>
#include <kanzi/core.ui/graphics2d/composition_stack.hpp>
#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/array.hpp>
#include <kanzi/core/cpp/iterator.hpp>
#include <kanzi/core.ui/domain/domain.hpp>
#include <kanzi/core.ui/graphics2d/composition_manager.hpp>
#include <kanzi/core.ui/resource/resource_manager.hpp>

#include <kanzi/core/legacy/util/math/kzc_ray.hpp>

// Forward declaration.
struct KzuBoundingVolume;

namespace kanzi
{

typedef shared_ptr<Node2D> Node2DSharedPtr;
typedef shared_ptr<Node2D const> Node2DConstSharedPtr;
typedef weak_ptr<Node2D> Node2DWeakPtr;

/// Node2D is the base class of all 2D nodes.
///
/// Node2D implements functionality common to all 2D nodes, such as rendering, layout and hit testing.
/// You should use classes derived from Node2D like #Image2D, #EmptyNode2D and #StackLayout2D to construct UI graphs.
/// You can derive from Node2D to implement your own custom rendering and layout.
///
/// You can configure common parameters for rendering and layout with methods of Node2D.
/// Use methods of derived classes to control behavior specific to them.
///
/// Creating nodes
/// ==============
///
/// To construct 2D nodes, call a create functions that return a shared pointer to the node.
/// You can create an empty node:
/// \snippet test_node2d_snippets.cpp Create empty node
/// You can create an image node:
/// \snippet test_node2d_snippets.cpp Create image2d node
/// Each node has its own type of create function.
///
/// Constructors of nodes are protected, and cannot be accessed except for inheriting classes.
/// Node initialization happens within the create function, after constructing the node.
///
/// Node2D tree
/// ===========
///
/// Nodes are arranged to a scene graph.
/// You may think of scene graphs as directed acyclic graphs with no loops. In other words, each scene graph is a tree.
/// Each node may have multiple children but only one parent.
///
/// Scene graph root is always a 2D node.
/// The root node does not have a parent, and is is usually of type #Screen.
///
/// #Viewport2D nodes serve as windows to 3D scene graphs that are displayed in the viewport area.
/// Viewport nodes have #Scene nodes as children. Scenes have #Node3D children.
/// 
/// Constructing the scene graph
/// ----------------------------
///
/// You can manipulate the scene graph by adding children to nodes:
/// \snippet test_node2d_snippets.cpp Add child
/// You can remove children from a parent node:
/// \snippet test_node2d_snippets.cpp Remove child
/// Parents take ownership, and hold a reference to the children.
///
/// Iterating the scene graph
/// -------------------------
///
/// You can explore the scene graph from a node by iterating its children:
/// \snippet test_node2d_snippets.cpp Iterating children
/// You can also go upwards to the parent:
/// \snippet test_node2d_snippets.cpp Access parent
/// The parent returned is valid except for the root node that has no parent (it will return 0).
///
/// Finding nodes
/// -------------
///
/// Finding nodes in the scene graph is inherited from #Node base class.
/// You can look for nodes with a path:
/// \snippet test_node2d_snippets.cpp Lookup node child
/// The paths work relative from the node doing the lookup. You can also traverse upwards:
/// \snippet test_node2d_snippets.cpp Lookup node parent
/// If lookup fails, no node is returned.
/// For details, refer to scene graph lookup in #Node documentation.
///
/// Rendering
/// =========
///
/// Rendering nodes happens from root node downwards, iterating the tree in depth-first algorithm.
///
/// Each node has a foreground and a background. Foreground and background are rendered separately.
/// Node classes can override foreground or background rendering separately.
///
/// Foreground is the node content, for example an image.
/// Background is the full node area. It may be the same size as the node content or larger.
/// Fitting the content to the node area is controlled by #ContentStretchProperty, for details, see section about content stretch.
///
/// Rendering order
/// ---------------
///
/// Nodes are rendered in the order they were added to the parent node. Node added first will be rendered first 
/// You can modify the rendering order by reordering the children within the parent.
/// You can move nodes to the front to render them last:
/// \snippet test_node2d_snippets.cpp Move to front
/// You can move nodes to the back, to render them first:
/// \snippet test_node2d_snippets.cpp Move to back
/// Parent content is always rendered before rendering the children.
///
/// Brushes
/// -------
///
/// Rendering of node foreground, background and optional composition happens using brushes.
/// Brushes determine how the rendering is done. They can simply display a color or an image, tint content provided by node, or render using an arbitrary shader.
///
/// Nodes have foreground, background and composition brushes. These are accessed via
/// #ForegroundBrushProperty, #BackgroundBrushProperty and #CompositionBrushProperty
///
/// You can set the foreground brush:
/// \snippet test_node2d_snippets.cpp Setting foreground brush
/// Foreground brush is used to render the content the node provides, for example an Image2D node provides an image.
/// If node does not provide any foreground content, setting foreground brush has no effect.
///
/// You can set the background brush:
/// \snippet test_node2d_snippets.cpp Setting background brush
/// Background brush is used to render the content outside the node foreground area.
/// If the node has no foreground or the foreground is translucent, background will fill the entire node area.
/// If the node foreground fills the entire node area, no background will be rendered.
///
/// You can disable rendering by setting null brush:
/// \snippet test_node2d_snippets.cpp Disabling brushes
/// Note that some nodes have default brushes, so removing the property would not be enough to disable rendering -
/// the nodes would revert to default behavior.
///
/// Opacity
/// -------
///
/// Node translucency is controlled by #OpacityProperty.
/// You can set the opacity of a node:
/// \snippet test_node2d_snippets.cpp Setting opacity
/// Opacity affects node background, foreground, and all node children.
///
/// Node foreground and background may be translucent even if opacity property is not set if the brushes or content are translucent.
///
/// If node has children, setting Node2D as translucent affects all children.
/// To render the children correctly in regard to overlapping translucency, parent node may need to be composited.
/// See section about composition for details.
///
/// Render transformation
/// ---------------------
///
/// You can modify #RenderTransformationProperty to change where nodes are rendered in regard to their parent:
/// \snippet test_node2d_snippets.cpp Setting render transformation
/// Render transformation is specified as SRT - Scale, Rotation and Translation.
///
/// Render transform is relative to top left of 2D nodes by default.
/// You can change the origin point within the node by setting #RenderTransformationOriginProperty:
/// \snippet test_node2d_snippets.cpp Setting render transformation origin
/// Render transformation origin can also be set outside the node.
/// \snippet test_node2d_snippets.cpp Setting render transformation origin outside
/// The values set to render transform origin are relative to the size of the node.
/// Value of 0.5 ; 0.5 will be the center of the node regardless of actual node size.
///
/// Render transformation happens after layout transformation has been already applied.
/// Render transformation is not affected by layout constraints such as alignment and margins, and does not modify the size layout nodes take into account.
/// For details about layout transformation, see the appropriate section.
///
/// Perspective transformation
/// --------------------------
///
/// You may apply perspective transformation in 3D space to bring limited 3D effects to 2D scene graph.
/// Perspective transformation is an optional transformation applied as the last Node2D transformation.
/// Perspective transformation applies after layout and render transformations have already been applied.
///
/// You can set the perspective transformation:
/// \snippet test_node2d_snippets.cpp Setting perspective transformation
/// The projection for perspective transformation is applied in the space of current composition space.
/// Perspective transformation is specified as 3D SRT - 3-component Scale, Rotation and Translation vectors.
///
/// Currently the perspective transform has the following rules:
/// - Projection center is always at the center of the current composition target or screen.
/// - Field of view is locket at 45 degrees.
/// These restrictions are subject to change.
///
/// NodeVisual2D
/// ------------
///
/// All information related to foreground and background rendering in Node2D is stored in a separate object of type #NodeVisual2D.
/// This object holds brush and geometry information required to render the node.
/// To save memory, if node has nothing to render, no visual component is allocated.
///
/// Node2D will never release the visual component once it has been allocated once.
///
/// Composition
/// ===========
///
/// By default, nodes will be rendered into the rendering context of their parent.
/// Usually, the top-level rendering context is the back buffer, provided by #Screen node.
///
/// You can manually override this and render a node into a render target:
/// \snippet test_node2d_snippets.cpp Setting render target
/// If a render target is specified, the node will take its size from the render target size.
/// You can define fixed width and fixed height for a node that also has a render target set.
/// The fixed size can be smaller then render target size. In this case, rendering will only happen on a part of the render target area.
/// Specifying fixed size greater than render target size is undefined behavior.
/// Nodes rendered into a render target will still draw the resulting composition to the rendering context of their parent.
///
/// Even if render target has not been set, nodes may be rendered using render targets to achieve correct result.
///
/// #Viewport2D will always render to a render target if its opacity is not 1.0 or if its transformation has non-translation components:
/// \snippet test_node2d_snippets.cpp Automatic render target - viewport
/// Viewport2D is a 'window' to a 3D scene. It must be aligned to the units in the parent render context. If this is not the case, it needs to be composited.
///
/// All nodes will render to render targets if they have children and their opacity is not one:
/// \snippet test_node2d_snippets.cpp Automatic render target - children
/// The parent has opacity set, so it will first need to do composition of all its children, and then render this composition using that opacity.
/// 
/// When you manually assign a render target you can set it to take its size from the size of the node.
/// In this case, Kanzi resizes the composition target to the size that the node gets during layout:
/// \snippet test_texture.cpp node2d render target automatic size render target example
///
/// Offscreen rendering
/// -------------------
///
/// Nodes do not necessariyly have to draw their composition onto the render context of their parent.
/// You can enable or disable offscreen rendering:
/// \snippet test_node2d_snippets.cpp Setting offscreen rendering flag
/// If offscreen rendering is enabled, the node will not be drawn anywhere after rendering to its render target.
///
/// You can render the render target of the node using some other node:
/// \snippet test_node2d_snippets.cpp Using node render target
/// The render target behaves like a normal texture when used.
/// Setting the render target to an Image2D will determine its size unless fixed size has been used.
///
/// Render target clearing rules
/// ----------------------------
///
/// When a Node2D is rendered into a render target, it will clear the color and depth buffers of that render target.
/// If the render target has a depth buffer, and the node is not a #Viewport2D that will clear it in a #Renderpass, the depth buffer will be cleared.
/// If the node foreground does not fill complete composition area, or the combination of background and foreground is translucent, the color buffer will be cleared.
///
/// You can disable render target clearing:
/// \snippet test_node2d_snippets.cpp Disable render target clearing
/// Disabling clearing of render target will force the node to not clear even if it would otherwise decide to.
///
/// Cache render targets will be cleared if necessary even if clearing would be disabled.
///
/// Caching
/// -------
///
/// You can cache Node2D rendering results to avoid rendering them every frame.
/// There are three levels of caching. Caching the node content, caching node's children and caching the result combining both.
///
/// #CacheSelfProperty controls caching the node content.
/// You can enable or disable cache self:
/// \snippet test_node2d_snippets.cpp Set cache self property
/// If #CacheSelfProperty is enabled, node content will not change unless the property is disabled or the cache is invalidated.
/// You can invalidate the cache:
/// \snippet test_node2d_snippets.cpp Reset cache self
/// After invalidating, the node content will be rendered once. After this, it is considered cached again.
///
/// #CacheChildrenProperty controls caching of the children within the node area.
/// You can enable or disable cache children:
/// \snippet test_node2d_snippets.cpp Set cache children property
/// If #CacheChildrenProperty is enabled, the children or their locations will not change unless the property is disabled or the cache is invalidated.
/// You can invalidate the cache:
/// \snippet test_node2d_snippets.cpp Reset cache children
/// After invalidating, the children will be rendered once. After this, they are considered cached again.
///
/// #CacheResultProperty controls caching of the complete node result. This means both the children and their locations and node content.
/// You can enable or disable cache result: 
/// \snippet test_node2d_snippets.cpp Set cache result property
/// If #CacheResultProperty is enabled, nothing in the node area will not change unless the property is disabled or the cache is invalidated.
/// You can invalidate the cache:
/// \snippet test_node2d_snippets.cpp Reset cache result
/// After invalidating, the node area will be rendered once. After this, it is considered cached again.
///
/// You can enable or disable any combination of caches. Each level of cache is handled separately.
/// The user is responsible for using this feature in a responsible manner.
/// For example enabling self and children caches achieves the same visual effect as enabling result cache, but usually consumes more rendering time.
///
/// NodeCompositor2D
/// ----------------
///
/// All information related to compositing is stored in a separate class of type #NodeCompositor2D.
/// This object holds composition targets, caching information and a composition brush.
/// Since compositing implies rendering, it is not possible to allocate a compositor without also allocating a #NodeVisual2D.
/// To save memory, if composition is not needed, no compositor component is allocated.
///
/// Node2D will never release the compositor component once it has been allocated once.
/// Composition targets within compositor may be released if not needed.
///
/// Basic Layout
/// ============
///
/// 2D nodes will try to determine their size automatically.
/// 2D nodes with content will take the size of their content by default, e.g. Image2D will take the size of the image it displays.
/// #EmptyNode2D and #Viewport2D have unbounded layout by default - they will take all available size.
/// Available size for is calculated from the size of node's parent, or available screen area.
/// You can use layouts such as #StackLayout2D and #GridLayout2D to arrange their children in a more complex manner.
///
/// You can set a fixed size to a 2D node, this will override the size it would otherwise assume:
/// \snippet test_node2d_snippets.cpp Setting width and height
///
/// You configure the node to determine its size automatically by removing fixed sizes:
/// \snippet test_node2d_snippets.cpp Removing width and height
/// or:
/// \snippet test_node2d_snippets.cpp Setting automatic size
///
/// You can configure a node to take its width or height based on a specified fixed size and an aspect ratio:
/// \snippet test_node2d_snippets.cpp Setting aspect ratio
/// If fixed width and aspect ratio are defined, height is width divided by aspect ratio.
/// If fixed height and aspect ratio are defined, width is height multiplied by aspect ratio.
/// If both fixed width and fixed height are defined, aspect ratio has no effect.
///
/// If neither width or height are defined, but aspect ratio is defined, the result depends on the node.
/// Nodes that have unbounded layout, take the largest size they can with the given aspect ratio while still fitting within their allocated size.
/// Aspect ratio has no effect with nodes with content that defines its size. This is analogous to having both fixed width and fixed height.
///
/// Nodes have an allocated area specified by the parent's area or a layout node.
/// You can configure 2D node to align in its allocated area by setting horizontal and vertical alignment:
/// \snippet test_node2d_snippets.cpp Setting horizontal and vertical alignment
/// Horizontal alignment can be #HorizontalAlignmentLeft, #HorizontalAlignmentRight, #HorizontalAlignmentCenter or #HorizontalAlignmentStretch.
/// Vertical alignment can be #VerticalAlignmentTop, #VerticalAlignmentBottom, #VerticalAlignmentCenter or #VerticalAlignmentStretch.
///
/// You can configure 2D node to fill its allocated area by setting alignment to stretch:
/// \snippet test_node2d_snippets.cpp Setting stretch alignment
///
/// You can offset 2D nodes from the edges of its parent:
/// \snippet test_node2d_snippets.cpp Setting horizontal and vertical margins
/// For horizontal margins, the order of values is left, then right.
/// For vertical margins, the order of values is top, then bottom.
/// If margins are not specified, the node will be aligned exactly at the edge of allocated area.
/// If margins are specified, the node will be offset from the edge of allocated area by an amount equal to the margin.
///
/// Layout transformation
/// ---------------------
///
/// You can modify #LayoutTransformationProperty to change the transformation of a node in regard to its parent:
/// \snippet test_node2d_snippets.cpp Setting layout transformation
/// Layout transform  is specified as SRT - Scale, Rotation and Translation.
///
/// A node transformed with layout transformation gets its alignment and margin applied after the transformation.
/// Render transformation is applied after layout transformation, alignment and margins.
///
/// For information about render transformation or perspective transformation, see the corresponding sections.
///
/// Content stretch
/// ---------------
///
/// Node foreground content (e.g. image) has rules on how to stretch in relation to node area.
/// The different content stretch modes are #ContentStretchNone, #ContentStretchFill, #ContentStretchUniform and #ContentStretchUniformToFill.
/// You can set content stretch mode:
/// \snippet test_node2d_snippets.cpp Setting content stretch
///
/// Having no value for content stretch is the same as having #ContentStretchUniform.
/// This means foreground content is stretched to fill node area while keeping its aspect ratio.
/// If node aspect ratio is different from content aspect ratio, the remaining area is left for background rendering.
///
/// #ContentStretchNone means the foreground area will be centered in node area and keep the exact size it would have, for example image size.
/// If node is smaller than the foreground area, it will only display a part of the content.
/// If node is larger than foreground area, the remaining area is left for background rendering.
///
/// #ContentStretchFill means the foreground area will take the exact node area.
/// This may alter the aspect ratio of content.
///
/// #ContentStretchUniformToFill means the foreground area will be centered to node area and then uniformly scaled to fill it.
/// If node aspect ratio is different from content aspect ratio, node will only display part of the content.
///
/// Layout in main loop
/// -------------------
///
/// During the program main loop, layout is called for the root node.
/// Before calling layout, the screen node allocated size will be set to current graphics output size.
/// Layout pass only evaluates nodes marked as requiring layout.
/// Render is called immediately after layout.
///
/// As render is called immediately after layout, user may do modification to the scene graph and see the changes before next call to user's update function.
/// It may be useful to determine node calculated sizes or locations before waiting for the next frame.
/// You may call layout manually:
/// \snippet test_node2d_snippets.cpp Manual layout
///
/// After calling #layout(), you can call #getActualSize() to get the size determined by the node.
/// Default allocated size is unbounded layout or infinity.
/// When calling layout() manually, you must set allocated size for the node receiving the #layout() call.
///
/// For details, see layout section under "Implementing custom node derived from Node2D".
///
/// Hit testing
/// ===========
///
/// You can hit test nodes in regard to their location on screen:
/// \snippet test_node2d_snippets.cpp Hit testing
/// Hit testing uses the 'world' or 'render' coordinates of the node.
/// These coordinates are relative to the screen, not to the parent node or to the node that does the hit testing.
/// Node visibility and all transformations are taken into account.
///
/// Hit testing transforms global coordinates into Node2D local coordinates to determine if the node is hit.
/// You can determine world (screen) space coordinates in Node2D local coordinate space:
/// \snippet test_node2d_snippets.cpp Local coordinates
/// The return enclosed in optional value, but is always valid if the node has a real is non-degenerate transformation.
///
/// You can test whether or not given coordinates would hit a node:
/// \snippet test_node2d_snippets.cpp Checking contains global
/// Checking whether a global coordinate is within a node is equal to calling #globalToLocal() and then testing the result with #containsLocal().
///
/// Implementing custom node derived from Node2D
/// ============================================
///
/// To do custom rendering and layout, a custom Node2D implementation must be implemented.
///
/// Defining the class
/// ------------------
///
/// Custom Node2D implementations are defined by inheriting from Node2D base class.
///
/// To define a simple Node2D implementation see the following example:
/// \snippet test_node2d_snippets.cpp Custom Node2D example
/// This example describes a very simple class inherited from Node2D.
///
/// The following sections go through parts of the node declaration one at a time and explain the segments.
///
/// Metaclass
/// ---------
///
/// Each class derived from Node2D must have a metaclass definition
/// To declare the metaclass, inherit from Node2D base class and list the properties specific to the inherited node:
/// \snippet test_node2d_snippets.cpp Metaclass definition
/// 
/// For details about metaclass, see the description in #Node documentation.
///
/// Property types
/// --------------
///
/// Local property types are declared in metaclass to belong to the node.
/// Additionally, property types must be declared within the node:
/// \snippet test_node2d_snippets.cpp Property definition
/// It is also often useful to declare setters and getters to wrap #getProperty() and #setProperty() for the custom property.
/// \snippet test_node2d_snippets.cpp Property access
///
/// After being declared in the class, the property must have a specific definition.
/// The definition lists property metadata. The example property is defined as follows:
/// \snippet test_node2d_snippets.cpp Property definition
///
/// Note that the property has #PropertyTypeChangeFlagFinalTransformation -flag set.
/// This means that #updateRender must be called for the node if it has been changed.
///
/// There are various property change flags that determine what has to be recalculated when the property is changed.
/// #PropertyTypeChangeFlagMeasure means the node has to be measured. This will cause measure and arrange to propagate from the node.
/// #measure() will be ran to the node and potentially all of its parents if measured size changed.
/// Then, #arrange() and #updateRender() will be ran to node, all of the changed nodes and their descendants
/// #PropertyTypeChangeFlagArrange means the node has to be arranged. This will cause arrange to propagate from the node.
/// #arrange() and #updateRender() will be ran to the node and all of its children.
/// #PropertyTypeChangeFlagFinalTransformation means that node transformation and transformations of its children have to be updated.
/// #updateRender() will be ran to the node and all its children.
///
/// Nodes may have class values for properties:
/// \snippet test_node2d_snippets.cpp Property class value
/// Class values override the default value the node would have for a property otherwise, but the value applies only to objects of a certain class.
///
/// For more information about properties in nodes, refer to #Node documentation.
///
/// Message types
/// -------------
///
/// To communicate with each other, nodes in Kanzi can send messages.
/// Message types must be declared in nodes:
/// \snippet test_node2d_snippets.cpp Message declaration
/// Like the node itself, the message class must define a metaclass and properties.
///
/// Message type, metadata and related property metadata must be defined in addition to being declared in the node:
/// \snippet test_node2d_snippets.cpp Message definition
/// The argument definition is similar to property type definition. Also the message type and studio metadata need to be defined.
///
/// Node can subscribe to listen any messages. Typically on initialization.
///
/// For more information about messages, refer to #Node documentation.
///
/// Initialize pattern
/// ------------------
///
/// Constructing a node initializes node-specific values and passes to base class constructor.
/// \snippet test_node2d_snippets.cpp Constructor
/// Class values are initialized in the constructor.
///
/// Further initialization is done in Node::initialize(), that is called from the create function:
/// \snippet test_node2d_snippets.cpp Create function
///
/// In this example, the node subscribes to listen a message defined earlier upon initialize:
/// \snippet test_node2d_snippets.cpp Message subscription
///
/// For details of initialization, refer to #Node documentation.
///
/// Attach and detach
/// -----------------
///
/// When a node becomes a part of the scene graph, it is attached.
/// When node no longer is a part of a scene graph, it is detached.
/// Nodes may also be attached or detached if their parent is attached or detached - typically if their parent is added or removed from the scene graph.
///
/// Attaching connects and activates node features related to its location in the scene graph.
/// This includes resource references, bindings, triggers, input manipulators, etc.
///
/// For details on attach and detach, refer to #Node documentation.
///
/// Rendering
/// ---------
///
/// Custom node rendering is controlled by overriding rendering functions and setting the render type.
/// During render process, nodes will first call their rendering functions, and then rendering will descend to the children.
///
/// Rendering functions
/// -------------------
///
/// To override foreground rendering, implement #renderForegroundOverride().
/// Default implementation of #renderForegroundOverride() is empty, since all nodes decide on their own rendering.
/// 
/// You can override all rendering of node itself, meaning both foreground and background, by implementing #renderSelfOverride().
/// Default implementation of #renderSelfOverride() applies the composition stack, and then defers to background and foreground rendering.
/// When implementing this function, remember to ensure that the viewport settings are correct before issuing draw calls.
/// Applying the composition stack
///
/// To use normal background rendering within overridden rendering, call #renderBackground().
/// #renderBackground() checks if background brush exists, and then renders the background quad.
/// In the case of opaque foreground, background rendering will render a 'frame' around the node content area if possible.
///
/// For most nodes, implementing #renderSelfOverride() is enough.
///
/// Render type
/// -----------
///
/// Node2D rendering is controlled by #RenderType. It should be set upon constructor or node initialization to reflect on node rendering behavior.
/// #RenderType acts as a hint to the rendering system, regarding how to set viewport settings and how to handle background rendering.
///
/// #RenderTypeNone is used for nodes that do not have a foreground and will not render it.
///
/// #RenderTypeTexture is used for nodes that render their foreground as a rectangular quad - for example #Image2D.
///
/// #RenderTypeManual is used for nodes that handle their own foreground rendering.
/// It implies the system having to set up viewport coordinates for the area of the node, this will push a local viewport area onto the composition stack.
/// Nodes using #RenderTypeManual should implement #renderSelfOverride.
///
/// #RenderTypeManualClipped is using nodes that handle their own foreground rendering, but do not need a local viewport area.
/// This implies nodes using #RenderTypeManualClipped either clip their own content, or that the user does not care about clipping.
/// Nodes using #RenderTypeManualClipped should implement at least #renderForegroundOverride, possibly #renderSelfOverride.
///
/// Layout
/// ------
///
/// Custom nodes also follow the layout directives described in the earlier section.
/// Layout can be partially overridden by implementing layout functions.
///
/// Node desired size is determined in #measure().
/// Measurement pass descends recursively downwards until nodes that are flagged as needing measure are found.
/// For every node the size of which was changed, measure ascends upwards to the root and flags node as requiring arrange.
/// To override the size that would otherwise be determined for the node, implement #measureOverride():
/// \snippet test_node2d_snippets.cpp Measure
/// Content desired size for node is determined by the size returned from #measureOverride().
/// Desired size for node is affected by the content desired size returned and node properties.
/// 
/// Node actual size and transformation is determined in #arrange().
/// Arrange pass descends recursively downwards to nodes that are flagged as needing arrange, and then arranges them and all their children.
/// Arrange process reads available size for node, then determines transformation and actual size based on node properties.
///
/// Nodes performing layout on theit children, for example #StackLayout2D, must implement #arrangeOverride().
/// During parent arrange pass, children have already been measured.
/// Arranging children works by iterating over child nodes and setting their allocated sizes and arrange transformations.
/// For non-layout nodes, (default) #arrangeOverride() sets child node allocated size as the node actual size, and resets child arrange transformation.
/// 
/// Node final transformation, brushes and composition settings are determined in #updateRender().
/// #updateRender() is called after arrange for all nodes that were marked as requiring transformation updated.
/// Nodes may implement #updateRenderOverride() to do custom clipping or modify brush or composition settings:
/// \snippet test_node2d_snippets.cpp Update render
class KANZI_API Node2D : public Node
{
    // Enabled until tool module can use multi domain for thumbnails.
    friend class Screen;

    // Viewport3D requires access to measure/arrangeIterate().
    friend class Viewport3D;

    // TODO: Remove this friend.
    friend void doListBoxArrange(Node2D& node);

public:

    // Pixel formats.
    enum PixelFormat
    {
        /// Managed render targets use RGB format.
        PixelFormatRgb,

        /// Managed render targets use RGBA format.
        PixelFormatRgba
    };

    /// Hint for foreground handling of nodes.
    enum ForegroundHint
    {
        /// No hint given, assumed the background of a node can be rendered after content.
        ForegroundHintNone,

        /// Some elements rendered within the node are translucent over the background.
        ForegroundHintTranslucent,

        /// Node content is assumed to be fully opaque thus, that background does not need to be rendered.
        ForegroundHintOpaque
    };

    /// Node2D render type - affects elementary decisions about node rendering.
    enum RenderType
    {
        /// Will not render itself except for its children.
        RenderTypeNone,

        /// Node will render itself as textured quad.
        RenderTypeTexture,

        /// Node handles its own rendering.
        RenderTypeManual,

        /// Node handles its own rendering, but also clips its own content.
        /// This means the node using this will not need additional composition area definitions, and can rendered directly. 
        RenderTypeManualClipped,
    };

    typedef Vector2 LayoutVectorType;
    typedef Matrix3x3 LayoutMatrixType;

    static float layoutUp() { return -1.0f; }

    /// Indicates whether a size is valid layout size. Size is valid if all its
    /// elements are valid layout values (see Node::isValidLayoutValue()).
    /// \param size Size to test if it is unbound layout size.
    /// \return true if the size if valid layout size, false otherwise.
    static bool isValidLayoutSize(Vector2 size)
    {
        return (Node::isValidLayoutValue(size.getX()) && Node::isValidLayoutValue(size.getY()));
    }

    /// Returns an unbounded layout size.
    /// \return Unbounded layout size.
    static Vector2 unboundedLayoutSize()
    {
        return Vector2(unboundedLayoutValue(), unboundedLayoutValue());
    }

    /// Indicates whether a layout size is an unbound layout size. Size is layout unbound size
    /// if any of its elements is unbounded layout value.
    /// \param layoutSize Layout size to test if it is unbound layout size.
    /// \return true if the layoutSize is unbound layout size, false otherwise.
    static bool isUnboundedLayoutSize(Vector2 layoutSize)
    {
        return (isUnboundedLayoutValue(layoutSize.getX()) || isUnboundedLayoutValue(layoutSize.getY()));
    }

    /// Replaces any element of a layout size with appropriate element of the reset size if it is unbounded and returns the size.
    /// \param layoutSize Layout size to test if any of its elements is unbounded layout value.
    /// \param resetSize The size whose values are used as a replacement for specified layout size's unbounded value elements.
    /// \return layoutSize with its unbounded value elements replaced with the elements of resetSize.
    static Vector2 replaceUnboundedLayoutSize(Vector2 layoutSize, Vector2 resetSize)
    {
        return Vector2(Node::replaceUnboundedLayoutValue(layoutSize.getX(), resetSize.getX()),
                       Node::replaceUnboundedLayoutValue(layoutSize.getY(), resetSize.getY()));
    }

    /// Replaces any element of a layout size with zero if it is unbounded and returns the size.
    /// \param layoutSize Layout size to test if any of its elements is unbounded layout value.
    /// \return layoutSize with its unbounded value elements replaced with zero.
    static Vector2 replaceUnboundedLayoutSizeWithZero(Vector2 layoutSize)
    {
        return replaceUnboundedLayoutSize(layoutSize, Vector2(0.0f, 0.0f));
    }

    /// Clipping information carried from parents.
    struct ClippingArea
    {
        /// Type of rectangle used for clipping.
        typedef Rectangle<float> RectangleType;

        /// Empty constructor.
        explicit ClippingArea() :
          m_clippingRectangle(0.0f, 0.0f, 0.0f, 0.0f),
          m_childClippingRectangle(0.0f, 0.0f, 0.0f, 0.0f),
          m_clippingRectangleChanged(true),
          m_clipSelfEnabled(false),
          m_clipChildrenEnabled(false)
        {
        }

        /// Constructor.
        /// \param rectangle Clipping rectangle.
        /// \param childRectangle Clipping rectangle for children.
        /// \param previousRectangle Previous clipping rectangle.
        /// \param clipSelfEnabled True if the node should clip self into the clipping rectangle.
        /// \param clipChildrenEnabled True if the children of the node should clip themselves into the child clipping rectangle.
        explicit ClippingArea(RectangleType rectangle, RectangleType childRectangle, RectangleType previousRectangle, bool clipSelfEnabled, bool clipChildrenEnabled) :
          m_clippingRectangle(rectangle),
          m_childClippingRectangle(childRectangle),
          m_clippingRectangleChanged(rectangle != previousRectangle),
          m_clipSelfEnabled(clipSelfEnabled),
          m_clipChildrenEnabled(clipChildrenEnabled)
        {
        }

        /// Constructor where node and child clipping rectangles are equal.
        /// \param rectangle Clipping rectangle.
        /// \param previousRectangle Previous clipping rectangle.
        /// \param clipSelfEnabled True if the node should clip self into the clipping rectangle.
        /// \param clipChildrenEnabled True if the children of the node should clip themselves into the child clipping rectangle.
        explicit ClippingArea(RectangleType rectangle, RectangleType previousRectangle, bool clipSelfEnabled, bool clipChildrenEnabled) :
            m_clippingRectangle(rectangle),
            m_childClippingRectangle(rectangle),
            m_clippingRectangleChanged(rectangle != previousRectangle),
            m_clipSelfEnabled(clipSelfEnabled),
            m_clipChildrenEnabled(clipChildrenEnabled)
        {
        }

        /// Gets the clipping rectangle for the node content.
        RectangleType getClippingRectangle() const
        {
            return m_clippingRectangle;
        }
        
        /// Gets the clipping rectangle passed down to the children of the node.
        RectangleType getChildClippingRectangle() const
        {
            return m_childClippingRectangle;
        }

        /// Sets the clipping rectangle passed down to the children of the node.
        void setChildClippingRectangle(RectangleType rect)
        {
            m_childClippingRectangle = rect;
        }

        /// Get height.
        ///
        /// \return Height.
        float getHeight() const
        {
            return m_clippingRectangle.getHeight();
        }

        /// Set height.
        ///
        /// \param height New height.
        void setHeight(float height)
        {
            m_clippingRectangle.setHeight(height);
        }

        /// Get left edge.
        ///
        /// \return Left edge.
        float getOffsetX() const
        {
            return m_clippingRectangle.getX();
        }

        /// Set left edge.
        ///
        /// \param offset New X offset.
        void setOffsetX(float offset)
        {
            m_clippingRectangle.setX(offset);
        }

        /// Get top edge.
        ///
        /// \return Top edge.
        float getOffsetY() const
        {
            return m_clippingRectangle.getY();
        }

        /// Set top edge.
        ///
        /// \param offset New Y offset.
        void setOffsetY(float offset)
        {
            m_clippingRectangle.setY(offset);
        }

        /// Get right edge.
        ///
        /// \return Right edge.
        float getX2() const
        {
            return m_clippingRectangle.getX() + m_clippingRectangle.getWidth();
        }

        /// Get bottom edge.
        ///
        /// \return Bottom edge.
        float getY2() const
        {
            return m_clippingRectangle.getY() + m_clippingRectangle.getHeight();
        }

        /// Get width.
        ///
        /// \return Width.
        float getWidth() const
        {
            return m_clippingRectangle.getWidth();
        }

        /// Set width edge.
        ///
        /// \param width New width.
        void setWidth(float width)
        {
            m_clippingRectangle.setWidth(width);
        }

        /// Intersect area with a rectangle.
        ///
        /// \param rectangle Rectangle to intersect with.
        void intersect(RectangleType intersectionArea)
        {
            m_clippingRectangle = intersection(m_clippingRectangle, intersectionArea);
        }

        /// Tell if clipping rectangle is changed.
        ///
        /// \return True if yes, false if no.
        bool isClippingRectangleChanged() const
        {
            return m_clippingRectangleChanged;
        }

        /// Tell if node should clip itself tot he clipping area defined.
        /// \return True if yes, false if no.
        bool isClipSelfEnabled() const
        {
            return m_clipSelfEnabled;
        }

        /// Set enabled flag.
        /// \param enabled New enabled flag.
        void setClipSelfEnabled(bool enabled)
        {
            m_clipSelfEnabled = enabled;
        }

        /// Tell if the node is passing a clipping rectangle down to its children.
        /// \return True if yes, false if no.
        bool isClipChildrenEnabled() const
        {
            return m_clipChildrenEnabled;
        }

        /// Set propagate flag.
        /// \param enabled New enabled flag.
        void setClipChildrenEnabled(bool enabled)
        {
            m_clipChildrenEnabled = enabled;
        }

    private:
        /// Rectangle this node will be clipped to.
        /// Corresponds to the area of the parent.
        RectangleType m_clippingRectangle;
        /// Rectangle that the children of this node will be clipped to.
        /// Corresponds to the area of this node.
        RectangleType m_childClippingRectangle;

        /// Is area changed from previous frame.
        bool m_clippingRectangleChanged;
        /// Should the node clip itself to the rectangle specified?
        bool m_clipSelfEnabled;
        /// Should the children of the node clip themselves to the child clipping rectangle specified?
        bool m_clipChildrenEnabled;
    };

    /// \name Properties
    /// \{

#include "node2d_properties.h"

    /// LayoutTransformation property.
    /// 
    /// The default value is SRT(Vector2(1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f)).
    /// \see setLayoutTransformation(), getLayoutTransformation()
    static PropertyType<SRTValue2D> LayoutTransformationProperty;

    /// RenderTransformation property.
    /// 
    /// The default value is SRT(Vector2(1.0f, 1.0f), 0.0f, Vector2(0.0f, 0.0f)).
    /// \see setRenderTransformation(), getRenderTransformation()
    static PropertyType<SRTValue2D> RenderTransformationProperty;

    /// PerspectiveTransformation property.
    ///
    /// The default value is identity.
    /// \see setPerspectiveTransformation, getPerspectiveTransformaton
    static PropertyType<SRTValue3D> PerspectiveTransformationProperty;

    /// RenderTransformationOrigin property.
    /// The default value is Vector2(0.0f,  0.0f).
    /// \see setRenderTransformationOrigin(), getRenderTransformationOrigin()
    static PropertyType<Vector2> RenderTransformationOriginProperty;
    /// Gets the value of #RenderTransformationOriginProperty.
    /// \see setRenderTransformationOrigin()
    Vector2 getRenderTransformationOrigin() const { return getProperty(RenderTransformationOriginProperty); }
    /// Sets the value of #RenderTransformationOriginProperty.
    /// \see getRenderTransformationOrigin()
    void setRenderTransformationOrigin(Vector2 value) { setProperty(RenderTransformationOriginProperty, value); }

    /// SnapToPixel property.
    /// The default value is false.
    /// \see setSnapToPixel(), isSnapToPixel()
    static PropertyType<bool> SnapToPixelProperty;
    /// Gets the value of #SnapToPixelProperty.
    /// \see setSnapToPixel()
    bool isSnapToPixel() const { return getProperty(SnapToPixelProperty); }
    /// Sets the value of #SnapToPixelProperty.
    /// \see isSnapToPixel()
    void setSnapToPixel(bool value) { setProperty(SnapToPixelProperty, value); }

    /// BackgroundBrush property.
    /// The default value is ResourceSharedPtr().
    /// \see setBackgroundBrush(), getBackgroundBrush()
    static PropertyType<ResourceSharedPtr> BackgroundBrushProperty;

    /// CompositionBrush property.
    /// The default value is ResourceSharedPtr().
    /// \see setCompositionBrush(), getCompositionBrush()
    static PropertyType<ResourceSharedPtr> CompositionBrushProperty;

    /// ForegroundBrush property.
    /// The default value is ResourceSharedPtr().
    /// \see setForegroundBrush(), getForegroundBrush()
    static PropertyType<ResourceSharedPtr> ForegroundBrushProperty;

    /// \}

    KZ_ABSTRACT_METACLASS_BEGIN(Node2D, Node, "Kanzi.Node2D")
        KZ_METACLASS_PROPERTY_TYPE(AspectRatioProperty)
        KZ_METACLASS_PROPERTY_TYPE(CacheChildrenProperty)
        KZ_METACLASS_PROPERTY_TYPE(CacheResultProperty)
        KZ_METACLASS_PROPERTY_TYPE(CacheSelfProperty)
        KZ_METACLASS_PROPERTY_TYPE(LayoutTransformationProperty)
        KZ_METACLASS_PROPERTY_TYPE(PerspectiveTransformationProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderTransformationOriginProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderTransformationProperty)
        KZ_METACLASS_PROPERTY_TYPE(SnapToPixelProperty)
        KZ_METACLASS_PROPERTY_TYPE(BackgroundBrushProperty)
        KZ_METACLASS_PROPERTY_TYPE(CompositionBrushProperty)
        KZ_METACLASS_PROPERTY_TYPE(ForegroundBrushProperty)
        KZ_METACLASS_PROPERTY_TYPE(ForceCompositionProperty)
        KZ_METACLASS_PROPERTY_TYPE(ForegroundHintProperty)
        KZ_METACLASS_PROPERTY_TYPE(OffscreenRenderingProperty)
        KZ_METACLASS_PROPERTY_TYPE(DisableRenderTargetClearProperty)
        KZ_METACLASS_PROPERTY_TYPE(PixelFormatProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderSelfProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderTargetProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderTargetMinimumWidthProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderTargetMinimumHeightProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderTargetReallocationLimitProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    virtual ~Node2D();

    /// Container type for children.
    typedef vector<Node2DSharedPtr> ChildContainer;
    /// Iterator type for children
    typedef ChildContainer::const_iterator ChildConstIterator;
    /// Reverse iterator type for children
    typedef ChildContainer::const_reverse_iterator ChildConstReverseIterator;
    ChildConstIterator beginChildren() const;
    ChildConstIterator endChildren() const;
    ChildConstReverseIterator rbeginChildren() const;
    ChildConstReverseIterator rendChildren() const;

    /// Adds a child node.
    ///
    /// Adding a 3D node node as a child of a 2D node is only allowed when adding a scene to a viewport.
    /// Screens can have only one child which is a 2D node.
    void addChild(Node2DSharedPtr child);
    /// Adds a child node for object node to given index.
    ///
    /// Adding a 3D node node as a child of a 2D node is only allowed when adding a scene to a viewport.
    /// Screens can have only one child which is a 2D node.
    void insertChild(size_t index, Node2DSharedPtr child);
    /// Removes child node.
    void removeChild(const Node& child);
    /// Removes child node at specified index.
    void removeChild(size_t index);
    /// Removes all child nodes.
    void removeAllChildren();

    /// Returns a child from given index from object node.
    Node2DSharedPtr getChild(size_t index) const;
    /// Returns the index of a child in an object node.
    size_t getChildIndex(const Node& child) const;
    /// Returns whether or not the child exists.
    bool hasChild(const Node& child) const;

    /// Gets the number of children of the node.
    size_t getChildCount() const;

    /// Repositions the node to the beginning of its parent's children, so that it is drawn first.
    void moveToBack();
    /// Repositions the node to the end of its parent's children, so that it is drawn last.
    void moveToFront();

    /// Get render type.
    ///
    /// \return Render type enumeration.
    RenderType getRenderType() const
    {
        return m_renderType;
    }

    /// Gets value of #BackgroundBrushProperty.
    BrushSharedPtr getBackgroundBrush() const
    {
        return dynamic_pointer_cast<Brush>(getProperty(BackgroundBrushProperty));
    }
    /// Sets value of #BackgroundBrushProperty.
    void setBackgroundBrush(BrushSharedPtr value)
    {
        setProperty(BackgroundBrushProperty, value);
    }
    /// Gets value of #CompositionBrushProperty.
    BrushSharedPtr getCompositionBrush() const
    {
        return dynamic_pointer_cast<Brush>(getProperty(CompositionBrushProperty));
    }
    /// Sets value of #CompositionBrushProperty.
    void setCompositionBrush(BrushSharedPtr value)
    {
        setProperty(CompositionBrushProperty, value);
    }
    /// Gets value of #ForegroundBrushProperty.
    BrushSharedPtr getForegroundBrush() const
    {
        return dynamic_pointer_cast<Brush>(getProperty(ForegroundBrushProperty));
    }
    /// Sets value of #ForegroundBrushProperty.
    void setForegroundBrush(BrushSharedPtr value)
    {
        setProperty(ForegroundBrushProperty, value);
    }

    /// Get background brush renderer.
    ///
    /// \return Pointer to background brush renderer.
    BrushRenderer* getBackgroundBrushRenderer() const
    {
        return m_visual ? m_visual->getBackgroundBrushRenderer() : 0;
    }    
    /// Get foreground brush renderer.
    ///
    /// \return Pointer to foreground brush renderer.
    BrushRenderer* getForegroundBrushRenderer() const
    {
        return m_visual ? m_visual->getForegroundBrushRenderer() : 0;
    }    
    /// Access cache children brush renderer.
    ///
    /// \return Pointer to brush renderer.
    BrushRenderer* getCacheChildrenBrushRenderer() const
    {
        return m_compositor ? m_compositor->getCacheChildrenBrushRenderer() : 0;
    }
    /// Access cache self brush renderer.
    ///
    /// \return Pointer to brush renderer.
    BrushRenderer* getCacheSelfBrushRenderer() const
    {
        return m_compositor ? m_compositor->getCacheSelfBrushRenderer() : 0;
    }
    /// Access cache result brush renderer.
    ///
    /// \return Pointer to brush renderer.
    BrushRenderer* getCompositionBrushRenderer() const
    {
        return m_compositor ? m_compositor->getCompositionBrushRenderer() : 0;
    }

    /// Gets the value of #RenderTransformationProperty.
    /// \see setRenderTransformation()
    SRTValue2D getRenderTransformation() const
    {
        return getProperty(RenderTransformationProperty);
    }
    /// Sets the value of #RenderTransformationProperty.
    /// \see getRenderTransformation()
    void setRenderTransformation(SRTValue2D value)
    {
        setProperty(RenderTransformationProperty, value);
    }

    /// Gets the value of #PerspectiveTransformationProperty.
    /// \see setPerspectiveTransformation()
    SRTValue3D getPerspectiveTransformation() const
    {
        return getProperty(PerspectiveTransformationProperty);
    }
    /// Sets the value of #PerspectiveTransformationProperty.
    /// \see getPerspectiveTransformation()
    void setPerspectiveTransformation(SRTValue3D value)
    {
        setProperty(PerspectiveTransformationProperty, value);
    }

    /// Render individual 2D node
    ///
    /// \param renderer Renderer to use.
    /// \param compositionStack Render context stack to use.
    void render(Renderer3D& renderer, CompositionStack& compositionStack);

    /// Access visual component.
    ///
    /// \return Pointer to visual component or NULL if it doesn't exist.
    NodeVisual2D* getVisual() const
    {
        return m_visual.get();
    }

    /// Gets value of #RenderTargetProperty.
    TextureSharedPtr getRenderTarget() const
    {
        return dynamic_pointer_cast<Texture>(getProperty(RenderTargetProperty));
    }
    /// Sets value of #RenderTargetProperty.
    void setRenderTarget(TextureSharedPtr texture)
    {
        setProperty(RenderTargetProperty, texture);
    }

    /// Returns composition target combining all Node2D content.
    ///
    /// This is either user-set composition target or automatically created one.
    ///
    /// May return empty shared pointer if no composition target has been created or set.
    TextureSharedPtr getFinalCompositionTarget() const
    {
        return m_compositor ? m_compositor->getFinalCompositionTarget() : TextureSharedPtr();
    }

    /// Tell if node should cache its children.
    ///
    /// Should only be used from outside the node.
    bool hasCacheChildren() const
    {
        return m_compositor ? m_compositor->isCacheChildren() : false;
    }
    /// Tell if node has cache children composition target.
    ///
    /// Should only be used from outside the node.
    bool hasCacheChildrenCompositionTarget() const
    {
        return m_compositor ? static_cast<bool>(m_compositor->getCacheChildrenCompositionTarget()) : false;
    }
    /// Tell if children cache is valid.
    bool isCacheChildrenValid() const
    {
        if (m_compositor)
        {
            return m_compositor->isCacheChildrenValid();
        }
        return false;
    }
    /// Reset cached content for children.
    ///
    /// Does not change the caching property - if caching is on, the cache will be recreated on next render.
    void resetCacheChildren()
    {
        if (m_compositor)
        {
            m_compositor->setCacheChildrenValid(false);
        }
    }

    /// Tell if node should cache its result.
    ///
    /// This means the combination of node itself and its children.
    ///
    /// Should only be used from outside the node.
    bool hasCacheResult() const
    {
        return m_compositor ? m_compositor->isCacheResult() : false;
    }
    /// Tell if node has final composition target.
    ///
    /// Should only be used from outside the node.
    bool hasFinalCompositionTarget() const
    {
        return static_cast<bool>(getFinalCompositionTarget());
    }
    /// Tell if children cache is valid.
    bool isCacheResultValid() const
    {
        if (m_compositor)
        {
            return m_compositor->isCacheFinalValid();
        }
        return false;
    }
    /// Reset cached content for complete node content including itself and its children.
    ///
    /// Does not change the caching property - if caching is on, the cache will be recreated on next render.
    void resetCacheResult()
    {
        if (m_compositor)
        {
            m_compositor->setCacheFinalValid(false);
        }
    }

    /// Tell if node should cache itself.
    ///
    /// Should only be used from outside the node.
    bool hasCacheSelf() const
    {
        return m_compositor ? m_compositor->isCacheSelf() : false;
    }
    /// Tell if node has cache children composition target.
    ///
    /// Should only be used from outside the node.
    bool hasCacheSelfCompositionTarget() const
    {
        return m_compositor ? static_cast<bool>(m_compositor->getCacheSelfCompositionTarget()) : false;
    }
    /// Tell if children cache is valid.
    bool isCacheSelfValid() const
    {
        if (m_compositor)
        {
            return m_compositor->isCacheSelfValid();
        }
        return false;
    }
    /// Reset cached content for node itself.
    ///
    /// Does not change the caching property - if caching is on, the cache will be recreated on next render.
    void resetCacheSelf()
    {
        if (m_compositor)
        {
            m_compositor->setCacheSelfValid(false);
        }
    }

    /// Access composition manager.
    CompositionManager* getCompositionManager() const
    {
        return getDomain()->getCompositionManager();
    }

    /// Access compositor component.
    ///
    /// \return Pointer to compositor component or NULL if it doesn't exist.
    NodeCompositor2D* getCompositor() const
    {
        return m_compositor.get();
    }

    /// Sets node to automatically determine width.
    void setAutoWidth();
    /// Sets node to automatically determine height.
    void setAutoHeight();
    /// Sets node to automatically determine both width and height.
    void setAutoSize();
    /// Sets size properties of the node.
    /// \param width The value of the WidthProperty.
    /// \param height The value of the HeightProperty.
    void setSize(float width, float height);
    /// Sets size properties of the node.
    /// \deprecated This function is deprecated! Use setSize instead.
    /// \sa setSize
    void setLayoutSize(float width, float height)
    {
        setSize(width, height);
    }

    /// Gets the value of #LayoutTransformationProperty.
    /// \see setLayoutTransformation()
    SRTValue2D getLayoutTransformation() const
    {
        return getProperty(LayoutTransformationProperty);
    }
    /// Sets the value of #LayoutTransformationProperty.
    /// \see getLayoutTransformation()
    void setLayoutTransformation(SRTValue2D value)
    {
        setProperty(LayoutTransformationProperty, value);
    }

    /// Get desired size.
    ///
    /// \return Size vector.
    Vector2 getDesiredSize() const
    {
        return m_desiredSize;
    }
    /// Set desired size.
    ///
    /// \param size New size vector.
    void setDesiredSize(Vector2 size)
    {
        m_desiredSize = size;
    }

    /// Get allocated size.
    ///
    /// \return Size vector.
    Vector2 getAllocatedSize() const
    {
        return m_allocatedSize;
    }
    /// Set allocated size.
    ///
    /// If allocated size differs from existing, will invalidate arrange as a side effect.
    ///
    /// \param size New size vector.
    void setAllocatedSize(Vector2 allocatedSize)
    {
        if (m_allocatedSize != allocatedSize)
        {
            kzAssert(isValidLayoutSize(allocatedSize));
            m_allocatedSize = allocatedSize;
            invalidateArrange();
        }
    }

    /// Get actual size.
    /// \return Size vector.
    Vector2 getActualSize() const
    {
        return m_actualSize;
    }
    /// Set actual size.
    ///
    /// \param size New size vector.
    void setActualSize(Vector2 actualSize)
    {
        kzAssert(isValidLayoutSize(actualSize));

        // Changing actual size invalidates transform.
        if (m_actualSize != actualSize)
        {
            m_actualSize = actualSize;
            setActualWidth(actualSize.getX());
            setActualHeight(actualSize.getY());
            invalidateFinalTransform();
        }
    }
    /// Set actual size.
    ///
    /// \param sizeX New size X component.
    /// \param sizeY New size Y component.
    void setActualSize(float sizeX, float sizeY)
    {
        setActualSize(Vector2(sizeX, sizeY));
    }

    /// Get arrange transform.
    /// \return Transformation matrix.
    Matrix3x3 getArrangeTransform() const
    {
        return m_arrangeTransform;
    }
    /// Set arrange transform.
    /// If Layout transform differs existing, will invalidate arrange as a side effect.
    /// \param transform New transformation matrix.
    void setArrangeTransform(Matrix3x3 transform)
    {
        if(m_arrangeTransform != transform)
        {
            m_arrangeTransform = transform;
            setChangeFlag(PropertyTypeChangeFlagArrange | PropertyTypeChangeFlagFinalTransformation);
        }
    }

    /// Does layout pass starting from this node and iterating recursively all of its children.
    ///
    /// Measure pass only descends up to nodes marked for requiring measure and then propagates upwards for all nodes that were changed.
    /// After measure, all nodes marked for requiring arrange and all their children are arranged.
    ///
    /// Node actual size is not known before layout. User may call layout manually to determine node actual sizes.
    /// Before calling layout, the node must have allocated size set to limit node area to anything less than infinity.
    /// Normal layout process sets allocated size to current composition size.
    ///
    /// \param rootTransform Transform applied to root node for arrange pass if set. Can be used to offset complete scene graph, but should usually be empty.
    void layout(optional<Matrix3x3> rootTransform);
    /// Does layout pass with no root transformation (identity).
    ///
    /// Otherwise same as #layout() with optional Matrix3x3.
    void layout()
    {
        layout(nullopt);
    }
    /// Measure one node.
    ///
    /// \param availableSize Available size passed from parent, may be NULL.
    /// \param handleStretch Should the node handle stretching of node to fill available space?
    /// \return True if measure should be propagated, false if not.
    bool measure(const Vector2* availableSize, bool handleStretch);
    /// Perform measure recursively.
    /// TODO explain why this is virtual
    virtual bool measureRecursive();
    /// Arrange one Node2D.
    void arrange();
    /// Extract one Node2D.
    void extract();

    /// Get world transform.
    ///
    /// \return Transformation matrix.
    Matrix3x3 getWorldTransform() const
    {
        return m_worldTransform;
    }

    /// Tell if a node area contains a point (defined in node's own space).
    ///
    /// \return True if yes, false if no.
    bool containsLocal(Vector2 point) const;
    /// Tell if a node area contains a point (defined in screen space).
    ///
    /// If true, the node-space coordinates have been written into outgoing point.
    optional<Vector2> containsGlobal(Vector2 point) const;

    optional<Vector2> globalToLocal(Vector2 point) const;

    /// Hit test visitor function.
    typedef NodeSharedPtr (*HitTestVisitor)(Node2D& node, Vector2 nodePoint, void* userData);

    /// Performs a hit test to a 2D node and all its child nodes.
    /// Returns the topmost 2D node under given point.
    /// \param point Point in world coordinates.
    /// \return Node hit or an empty shared pointer.
    NodeSharedPtr hitTest(Vector2 point);
    /// Performs a hit test to a 2D node and all its child nodes.
    /// This is a wrapper function that allows to filter only selected types of nodes for hit testing.
    /// \param point Point in world coordinates.
    /// \param type Metaclass type to limit hit testing to.
    /// \return Node hit or an empty shared pointer.
    NodeSharedPtr hitTest(Vector2 point, const Metaclass* type);
    /// Recursively hit test nodes from this node downwards and call visitor function on nodes hit.
    /// Used for specific implementations of hit testing.
    /// \param point Point in world coordinates.
    /// \param visitor Visitor function to call on nodes.
    /// \param userData User data passed to visitor function.
    /// \return Node hit or an empty shared pointer.
    NodeSharedPtr hitTestIterate(Vector2 point, HitTestVisitor visitor, void* userData);

    /// Default implementation of Node2D content hit test. Just returns the node itself.
    /// \param point Point in node space.
    /// \return Tuple of found node, ray hitting that node and distance along the ray.
    virtual tuple<NodeSharedPtr, KzcRay, float> hitTestContent(Vector2 point);

    /// Wrapper for hitTest(Vector2), casts the return value.
    /// \param point Point in world coordinates.
    /// \return Typed node hit or an empty shared pointer.
    template <typename T> shared_ptr<T> hitTest(Vector2 point)
    {
        return dynamic_pointer_cast<T>(hitTest(point));
    }

    /// Wrapper for hitTest(Vector2, const Metaclass), casts the return value.
    /// \param point Point in world coordinates.
    /// \param type Metaclass type to limit hit testing to.
    /// \return Typed node hit or an empty shared pointer.
    template <typename T> shared_ptr<T> hitTest(Vector2 point, const Metaclass* type)
    {
        return dynamic_pointer_cast<T>(hitTest(point, type));
    }

    /// Node::findAbstractChildOverride() implementation.
    /// TODO: to be moved to protected
    virtual NodeSharedPtr findAbstractChildOverride(string_view name) KZ_OVERRIDE;
    /// Node::visitAabstractChild implementation.
    /// TODO: to be moved to protected
    virtual VisitorResult visitAbstractChildOverride(const Visitor& visitor, VisitorOrder order) KZ_OVERRIDE;

    /// Node::addAbstractChildOverride() implementation.
    virtual bool addAbstractChildOverride(NodeSharedPtr child) KZ_OVERRIDE;
    /// Node::getAbstractChildCountOverride() implementation.
    virtual size_t getAbstractChildCountOverride() KZ_OVERRIDE;
    /// Node::getAbstractChildOverride() implementation.
    virtual NodeSharedPtr getAbstractChildOverride(size_t index) KZ_OVERRIDE;
    /// Node::removeAbstractChildOverride() implementation.
    virtual bool removeAbstractChildOverride(Node& child) KZ_OVERRIDE;

public: // TODO: internal public, could be protected, but tests need them

    /// Tell if composition requires alpha.
    ///
    /// \return True if yes, false if no.
    bool compositionRequiresAlpha() const
    {
        return m_compositionRequirements.isAlphaRequired();
    }
    /// Turn composition alpha requirement on or off.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setCompositionRequiresAlpha(bool enabled)
    {
        m_compositionRequirements.setAlphaRequired(enabled);
    }

    /// Tell if composition requires depth.
    ///
    /// \return True if yes, false if no.
    bool compositionRequiresDepth() const
    {
        return m_compositionRequirements.isDepthRequired();
    }
    /// Turn composition depth requirement on or off.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setCompositionRequiresDepth(bool enabled)
    {
        m_compositionRequirements.setDepthRequired(enabled);
    }

    /// Tell if composition requires stencil.
    ///
    /// \return True if yes.
    bool compositionRequiresStencil() const
    {
        return m_compositionRequirements.isStencilRequired();
    }
    /// Turn composition stencil requirement on or off.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setCompositionRequiresStencil(bool enabled)
    {
        m_compositionRequirements.setStencilRequired(enabled);
    }

    /// Gets the background quad description.
    ///
    /// This function returns a copy of the background quad struct. Should be only used for tests.
    QuadDescription getBackgroundQuad() const
    {
        return m_backgroundQuadDescription;
    }
    /// Get clipping area.
    ///
    /// This function returns a copy of the clipping struct. Should be only used for tests.
    ClippingArea getClippingArea() const
    {
        return m_clipping;
    }

    /// Get opacity after propagation from layouting hierarchy.
    ///
    /// \return Current layouted opacity.
    float getLayoutOpacity() const
    {
        return m_layoutOpacity;
    }

    /// Gets transformation used to render the 2D node.
    ///
    /// \return Transform reference.
    Matrix3x3 getRenderQuadTransform() const
    {
        return m_compositionSpaceTransform;
    }

    /// Tell if Node2D has the center clip area (the area of itself).
    ///
    /// \return True if yes, false if no.
    bool hasCenterClipArea() const
    {
        return ((m_clippingMask & QuadDescription::ClippingResultCenter) != 0);
    }

    /// Tell if Node2D has outside clipping area.
    ///
    /// This means any area outside clipping area.
    ///
    /// \return True if yes, false if no.
    bool hasOutsideClipArea() const
    {
        return ((m_clippingMask & QuadDescription::ClippingResultOutside) != 0);
    }

    /// Tell if Node2D foreground has translucency.
    ///
    /// \return True if yes, false if no.
    bool hasTranslucentForeground() const
    {
        return m_flags[ForegroundIsTranslucent];
    }
    /// Set foreground translucency status.
    ///
    /// This is calculated from layout time to combine factors deciding translucency.
    ///
    /// \param enabled True to enable, false to disable.
    void setForegroundIsTranslucent(bool enabled)
    {
        m_flags[ForegroundIsTranslucent] = enabled;
    }

    /// Turn composition request on or off.
    ///
    /// This is a composition request from code, not by setting a property.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setFinalCompositionRequested(bool enabled)
    {
        if(enabled)
        {
            acquireCompositor().setFinalCompositionRequested(true);
        }
        else if(m_compositor)
        {
            m_compositor->setFinalCompositionRequested(false);
        }
    }
    
    /// Indicates whether composition target requires color clear before rendering.
    ///
    /// Composition clear is requested if, for some reason, node does not fill complete foreground area. This
    /// may be due to the foreground being smaller than node area or due to the foreground not being present.
    ///
    /// Composition clear being requested does not tell whether or not it is allowed. There may be external
    /// reasons such as background brush covering the complete node area or clearing being disabled that
    /// prevent it.
    bool isCompositionClearColorRequired() const
    {
        // Foreground does not fill complete area or is not available.
        if ((m_renderType == RenderTypeManual) || (m_renderType == RenderTypeManualClipped) ||
            hasOutsideClipArea() || !getForegroundBrushRenderer())
        {
            return true;
        }
        return false;
    }

    /// Indicates whether this Node2D is allowed and should clear the color buffer of its own composition target.
    ///
    /// By default, clearing is allowed but can be explicitly denied by user using properties.
    ///
    /// This function does not access the property, but rather a flag determined during layout.
    bool isClearColorAllowed() const
    {
        return m_flags[AllowClear] && !m_compositionRequirements.hasColorClear();
    }
    /// Set clear color allowed.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setClearColorAllowed(bool enabled)
    {
        m_flags[AllowClear] = enabled;
    }

    /// Tell if rendering children is allowed.
    ///
    /// \return True if yes, false if no.
    bool isRenderChildrenAllowed() const
    {
        return m_flags[AllowRenderChildren];
    }
    /// Tell if render self is allowed.
    ///
    /// \return True if yes, false if no.
    bool isRenderSelfAllowed() const
    {
        return m_flags[AllowRenderSelf];
    }

    /// Tell if Node2D is visible for hit testing.
    ///
    /// This is different from node being merely visible, it must also be not rendered offscreen.
    ///
    /// \return True if yes, false if no.
    bool isVisibleForHitTesting() const
    {
        return isVisible() && (!m_compositor || !m_compositor->isOffscreenRendering());
    }

    /// Tell if background brush rendering is required.
    ///
    /// \return True if yes, false if no.
    bool requiresBackgroundBrushRendering() const
    {
        // No background brush to begin with.
        if (!getBackgroundBrushRenderer())
        {
            return false;
        }

        // If foreground is translucent or does not fill the complete foreground area, the background brush must be rendered.
        return hasTranslucentForeground() || hasOutsideClipArea();
    }
    /// Tell if foreground brush rendering is required.
    ///
    /// \return True if yes, false if no.
    bool requiresForegroundBrushRendering() const
    {
        return getForegroundBrushRenderer() && hasCenterClipArea();
    }

    /// Tell if children require extract flag is on.
    ///
    /// \return True if yes, false if no.
    bool hasChildrenRequireExtract() const
    {
        return m_flags[ChildrenRequireExtract];
    }
    /// Set children require extract flag.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setChildrenRequireExtract(bool enabled)
    {
        m_flags[ChildrenRequireExtract] = enabled;
    }
    /// Tell if node requires extraction.
    ///
    /// \return True if yes, false if no.
    bool requiresExtract() const
    {
        return m_flags[RequiresExtract];
    }
    /// Turn extract requirement on or off.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setRequiresExtract(bool enabled)
    {
        m_flags[RequiresExtract] = enabled;
    }

    /// Tell if node itself is going to get rendered into a composition target.
    ///
    /// This is analogous to the final node result or the node itself being rendered into a composition target.
    bool isSelfInCompositionTarget() const
    {
        return m_compositor ? (m_compositor->isFinalCompositionRequired() || m_compositor->isSelfCompositionRequired()) : false;
    }

    /// Get size desired by content.
    /// TODO: ugly
    /// \return Size vector.
    Vector2 getContentDesiredSize() const
    {
        return m_contentDesiredSize;
    }

    /// Get second pass desired size.
    /// TODO: ugly
    /// \return Size vector.
    Vector2 getSecondPassDesiredSize() const
    {
        return m_secondPassDesiredSize ? *m_secondPassDesiredSize : Vector2(unboundedLayoutSize());
    }

    /// Get size desired by user.
    /// TODO: ugly
    /// \return Size vector.
    Vector2 getUserDesiredSize() const
    {
        return m_userDesiredSize;
    }

    /// Get partial arrange transform.
    /// TODO: ugly
    /// \return Propagate transform.
    Matrix3x3 getPartialArrangeTransform() const
    {
        return m_partialArrangeTransform;
    }

    /// Tell if node is completely clipped (and needs not be rendered).
    ///
    /// \return True if yes, false if no.
    bool isCompletelyClipped() const
    {
        return (m_clippingMask == 0);
    }

    /// Tell if node is completely transparent.
    ///
    /// \return True if yes, false if no.
    bool isCompletelyTransparent() const
    {
        return (getLayoutOpacity() <= 0.0f);
    }

protected:

    /// Different Node2D flags for bit set.
    enum Node2DFlags
    {
        /// Is clearing allowed?
        /// This flag is turned on by default, but can be disabled by node properties.
        /// 2D nodes only clear color buffers, even if other buffers are created.
        AllowClear = 0,

        /// Are children rendered for this node or are they handled in a special manner?
        AllowRenderChildren = 1,
        /// Is the node allowed to render itself?
        AllowRenderSelf = 2,

        /// Does layout detected foreground translucency?
        ForegroundIsTranslucent = 3,
        /// Has an extra request been filed (by implementations) for foreground translucency?.
        ForegroundTranslucencyRequested = 4,

        /// Is background quad required.
        RequiresBackgroundQuad = 5,

        /// Does the node need extract called?
        RequiresExtract = 6,
        /// Does the node have children that need extract?
        ChildrenRequireExtract = 7,

        /// Number of options.
        Node2DFlagsBitCount = 8,
    };

    /// Constructor.
    ///
    /// \param domain Domain to use.
    /// \param name Node name.
    explicit Node2D(Domain* domain, string_view name);

    void initialize();

    /// Initializes and returns visual structure.
    /// TODO: rename to NodeVisual2D
    /// Allocates memory for rendering-related information. By default this information is unallocated.
    NodeVisual2D& acquireVisual();

    /// Node-specific top-level render call.
    /// Allows for overriding the complete Node2D rendering process.
    /// Should normally not be overridden. Even if overridden, inherited implementations should usually call base implementation.
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    virtual void renderOverride(Renderer3D& renderer, CompositionStack& compositionStack);

    /// Render a Node2D and then recursively all its children.
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param baseTransform Transform applied to node itself in parent space.
    void renderRecursive(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform);

    /// Node-specific rendering.
    ///
    /// Default implementation renders background normally and passes to foreground render. Inherit to render more complex forms.
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param baseTransform Transform applied to node itself in parent space.
    /// \param quad Quad to use for filling node area.
    virtual void renderSelfOverride(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform);

    /// Render all children of a Node2D.
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param baseTransform Transform applied to node itself in parent space.
    void renderChildren(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform);

    /// Render background quad of a Node2D.
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param baseTransform Transform applied to node itself in parent space.
    void renderBackground(Renderer3D& renderer, const CompositionStack& compositionStack, const Matrix3x3& baseTransform);

    /// Render foreground of a Node2D.
    ///
    /// Calls renderForegroundOverride().
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param baseTransform Transform applied to node itself in parent space.
    void renderForeground(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform);

    /// Node-specific foreground render.
    ///
    /// Default implementation does nothing.
    ///
    /// \param renderer Renderer.
    /// \param compositionStack Render context stack.
    /// \param baseTransform Transform applied to node itself in parent space.
    virtual void renderForegroundOverride(Renderer3D& renderer, CompositionStack& compositionStack, const Matrix3x3& baseTransform);

    /// Push local viewport and scissor area into composition stack if it's required.
    /// Nodes with render mode #RenderModeManual will rely on viewport and scissoring settings to clip their
    /// output. This needs an additional composition area pushed to the composition stack.
    /// \param compositionStack Composition stack.
    /// \return True if a new area was pushed into composition stack and needs to be popped after rendering.
    bool pushLocalViewportArea(CompositionStack& compositionStack);

    /// Initializes and returns composition structure.
    /// TODO: rename to NodeCompositor2D
    /// Allocates memory for all composition-related information. By default this information is unallocated.
    NodeCompositor2D& acquireCompositor();

    /// Clear node render target.
    ///
    /// \param renderer Renderer to use.
    /// \param renderTarget Render target to clear.
    /// \param limits Render target size.
    /// \param clearColor Clear color buffer.
    void clearCompositionTarget(Renderer3D& renderer, CompositionStack& compositionStack, bool clearColor);

    /// Default implementation of Node2D size calculation.
    virtual Vector2 measureOverride(Vector2 availableSize);
    /// Perform arrange recursively.
    virtual void arrangeRecursive(const Matrix3x3& worldTransform, const Matrix3x3& parentTransform, bool arrangeNeeded, bool transformChanged);
    /// Default implementation of Node2D arrange.
    virtual void arrangeOverride(Vector2 actualSize);

    /// Get aspect ratio property assigned to the node.
    ///
    /// Aspect ratio of 0 or smaller equals no aspect ratio set.
    ///
    /// \return optional aspect ratio.
    optional<float> getUserAspectRatio() const;

    /// Get layout height property assigned to the node.
    ///
    /// Having an offscreen render target overrides the node's default size.
    ///
    /// Sizes smaller than 0 are clamped to 0.
    ///
    /// \return Optional height.
    optional<float> getUserHeight() const;

    /// Get layout width property assigned to the node.
    ///
    /// Having an offscreen render target overrides the node's default size.
    ///
    /// Sizes smaller than 0 are clamped to 0.
    ///
    /// \return Optional width.
    optional<float> getUserWidth() const;

    /// Get desired size axis aligned bounding box minimum.
    /// \return Desired size minimum.
    Vector2 getDesiredSizeAxisAlignedBoundingBoxMinimum() const
    {
        return m_desiredSizeAxisAlignedBoundingBoxMin;
    }
    /// Set desired size axis aligned bounding box minimum.
    /// \param size New size vector.
    void setDesiredSizeAxisAlignedBoundingBoxMinimum(Vector2 size)
    {
        m_desiredSizeAxisAlignedBoundingBoxMin = size;
    }
    /// Set desired size axis aligned bounding box minimum.
    /// \param sizeX New desired minimum size X component.
    /// \param sizeY New desired minimum size Y component.
    void setDesiredSizeAxisAlignedBoundingBoxMinimum(float sizeX, float sizeY)
    {
        m_desiredSizeAxisAlignedBoundingBoxMin = Vector2(sizeX, sizeY);
    }

    /// Get desired size axis aligned bounding box maximum.
    /// \return Desired size maximum.
    Vector2 getDesiredSizeAxisAlignedBoundingBoxMaximum() const
    {
        return m_desiredSizeAxisAlignedBoundingBoxMax;
    }
    /// Set desired size axis aligned bounding box maximum.
    /// \param size New size vector.
    void setDesiredSizeAxisAlignedBoundingBoxMaximum(Vector2 size)
    {
        m_desiredSizeAxisAlignedBoundingBoxMax = size;
    }
    /// Set desired size maximum.
    /// \param sizeX New desired maximum size X component.
    /// \param sizeY New desired maximum size Y component.
    void setDesiredSizeAxisAlignedBoundingBoxMaximum(float sizeX, float sizeY)
    {
        m_desiredSizeAxisAlignedBoundingBoxMax = Vector2(sizeX, sizeY);
    }

    /// Calculate new transformed bounding area.
    ///
    /// \param transform Matrix to use for calculation.
    /// \param sizeIn Input size.
    void calculateTransformedBoundingArea(const Matrix3x3& transform, Vector2 sizeIn);

    /// Update final transformation.
    ///
    /// Updates the transformation status based on node properties and calculations in measure and arrange phases.
    ///
    /// Called from within #updateRender() if necessary (if transform has changed).
    ///
    /// \param worldTransform Transformation in world space.
    /// \param parentTransform Parent's transformation in its composition space.
    /// \return Transformation of this node in its composition space.
    Matrix3x3 updateFinalTransform(const Matrix3x3& worldTransform, const Matrix3x3& parentTransform);

    /// Validate node for rendering.
    ///
    /// This is the final part of layouting. (Re)Calculate transformation components, decide whether or not to render to
    /// an FBO, etc.
    ///
    /// Transformations are only recalculated if parent transform or node transform has been changed.
    ///
    /// \param worldTransform Transformation in world space.
    /// \param parentTransform Transformation in parent space.
    /// \param transformChanged Indicates whether transform (local or parent) has changed and needs updating.
    /// \return True if there are additional reasons (detected during transform) to propagate transformation process downward.
    bool updateRender(const Matrix3x3& worldTransform, const Matrix3x3& parentTransform, bool transformChanged);

    /// Node-specific updates done before render.
    virtual void updateRenderOverride();

    /// Calculate content stretch.
    ///
    /// \param renderSize Rendering area size.
    /// \param contentSize Size of content rendered to rendering area.
    /// \param foregroundTiling Foreground tiling.
    /// \param backgroundTiling Background tiling.
    /// \return optional foreground quad, if it's relevant.
    optional<QuadDescription> calculateContentStretch(Vector2 renderSize, Vector2 contentSize);

    /// Calculate clipping parameters.
    ///
    /// \return New clipping parameters.
    ClippingArea calculateClippingArea(const Matrix3x3& parentSpaceTransform) const;

    /// Perform rectangle clipping.
    ///
    /// \param backgroundQuad Background quad, modified in-place.
    /// \param foregroundQuad Optional foreground quad, modified in-place.
    /// \return New clipping mask.
    unsigned int performClipping(QuadDescription& backgroundQuad, optional<QuadDescription>& foregroundQuad, unsigned int clippingResult);

    /// Extract children of node, called from extraction implementations.
    void extractChildren() const;

    /// Node2D extract function.
    virtual void onExtract();

    /// Node::onDetached() implementation.
    virtual void onDetached() KZ_OVERRIDE;

    /// Node::onNodePropertyChanged implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Node::restoreResources() implementation.
    virtual void restoreResources() KZ_OVERRIDE;

    /// Tell if the size of the node is empty or invalid.
    ///
    /// Node must have positive size, greater than zero on both axes to be considered having a non-empty size.
    ///
    /// Having empty size prevents rendering of node itself but not of its children.
    bool isEmptyActualSize() const
    {
        kzAssert(isValidLayoutSize(m_actualSize));
        return (m_actualSize.getX() <= 0.0f) || (m_actualSize.getY() <= 0.0f);
    }

    /// Tell if foreground hint is opaque.
    ///
    /// \return True if yes, false if no.
    bool isForegroundHintOpaque() const
    {
        return (m_foregroundHint == Node2D::ForegroundHintOpaque);
    }
    /// Tell if foreground hint is translucent.
    ///
    /// \return True if yes, false if no.
    bool isForegroundHintTranslucent() const
    {
        return (m_foregroundHint == Node2D::ForegroundHintTranslucent);
    }

    /// Tell if foreground translucency has been requested.
    ///
    /// \return True if yes, false if no.
    bool isForegroundTranslucencyRequested() const
    {
        return m_flags[ForegroundTranslucencyRequested];
    }
    /// Turn foreground translucency request on or off.
    ///
    /// This is a way to request 'extra' translucency in updateRenderOverride() implementations inherited classes.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setForegroundTranslucencyRequested(bool enabled)
    {
        m_flags[ForegroundTranslucencyRequested] = enabled;
    }

    /// Sets partial arrange transform.
    /// If the transform has changed, invalidates final transformation.
    /// \param transform New partial arrange transform.
    void setPartialArrangeTransform(Matrix3x3 transform)
    {
        if (m_partialArrangeTransform != transform)
        {
            m_partialArrangeTransform = transform;
            invalidateFinalTransform();
        }
    }

    /// Turn render children on or off.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setRenderChildrenAllowed(bool enabled)
    {
        m_flags[AllowRenderChildren] = enabled;
    }
    /// Turn render self on or off.
    ///
    /// \param enabled True to turn on, false to turn off.
    void setRenderSelfAllowed(bool enabled)
    {
        m_flags[AllowRenderSelf] = enabled;
    }

    /// Set render type.
    ///
    /// \param renderType Render type.
    void setRenderType(RenderType renderType)
    {
        m_renderType = renderType;
    }

    /// Update content texture for the foreground brush.
    void updateContentTexture(TextureSharedPtr texture)
    {
        if(m_visual)
        {
            m_visual->updateContentTexture(texture);
        }
    }

    /// Set second pass desired size.
    /// TODO: ugly
    /// \param size New size vector.
    void setSecondPassDesiredSize(Vector2 size)
    {
        m_secondPassDesiredSize = size;
    }

protected:
    /// Visual information.
    unique_ptr<NodeVisual2D> m_visual;

    /// Composition and caching information.
    unique_ptr<NodeCompositor2D> m_compositor;

    /// Background clipping quad / composition quad description.
    QuadDescription m_backgroundQuadDescription;

    /// Clipping parameters.
    ClippingArea m_clipping;

    /// Composition requirements for this 2D node.
    CompositionRequirements m_compositionRequirements;

private:

    ClassPropertyDefaultValue<HorizontalAlignment> m_classValueHorizontalAlignmentProperty;
    ClassPropertyDefaultValue<VerticalAlignment> m_classValueVerticalAlignmentProperty;
    // TODO something
    ClassPropertyDefaultValue<ResourceSharedPtr> m_classValueBackgroundBrushProperty;

    /// Layout transform. Set by layouts controlling the node.
    Matrix3x3 m_arrangeTransform;
    /// A temporary transform used to pass a partially calculated layout transform from arrange pass to transform pass.
    Matrix3x3 m_partialArrangeTransform;
    /// Transform in current render composition target space.
    /// This transformation is used to actually render the node.
    Matrix3x3 m_compositionSpaceTransform;
    /// Composition space transform passed to children.
    /// This is the base transform children of the node will use for rendering, multiplied by their own transform.
    /// Unless the node itself is composited, child composition space transform is equal to composition space transform.
    Matrix3x3 m_childCompositionSpaceTransform;
    /// World transform.
    /// Represents node transformation in top-level composition space.
    /// Used for hit testing within the top-level composition space.
    Matrix3x3 m_worldTransform;

    /// Desired size from content.
    Vector2 m_contentDesiredSize;
    /// Desired size modified by user width / height properties.
    Vector2 m_userDesiredSize;
    /// Desired size after properties, transformations and margins.
    Vector2 m_desiredSize;
    /// Desired size used by layouts implementing 2 pass measure.
    optional<Vector2> m_secondPassDesiredSize;
    /// Minimum point of node desired size quad.
    Vector2 m_desiredSizeAxisAlignedBoundingBoxMin;
    /// Maximum point of node desired size quad.
    Vector2 m_desiredSizeAxisAlignedBoundingBoxMax;
    /// Size available for this node (from parent).
    Vector2 m_allocatedSize;
    /// Actual size (allocated size minus margins).
    Vector2 m_actualSize;

    /// Opacity, determined during the layout phase.
    float m_layoutOpacity;

    /// Clipping result mask.
    uint32_t m_clippingMask;

    /// Foreground hint, should the foreground of the node be interpreted as transparent or not?
    ForegroundHint m_foregroundHint;
    /// Which kind of rendering node will use.
    RenderType m_renderType;

    /// Node flags.
    bitset<Node2DFlagsBitCount> m_flags;

    /// Children of the 2D node.
    ChildContainer m_children;
};

}

#endif
