// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZ_NODE3D_HPP
#define KZ_NODE3D_HPP

#include "node_reference.hpp"
#include "node.hpp"

struct KzuTransformedObjectNode;

namespace kanzi
{

// Forward declarations.
class MaterialRenderer;
class Node3D;
class Renderer3D;
class RenderPass;
class TransformedScene3D;

/// Node3D shared pointer type.
typedef shared_ptr<Node3D> Node3DSharedPtr;
/// Node3D const shared pointer type.
typedef shared_ptr<const Node3D> Node3DConstSharedPtr;
/// Node3D weak pointer type.
typedef weak_ptr<Node3D> Node3DWeakPtr;

/// Base class for all 3D nodes
class KANZI_API Node3D : public Node
{
public:

    typedef Vector3 LayoutVectorType;
    typedef Matrix4x4 LayoutMatrixType;

    static float layoutUp() { return 1.0f; }

    /// Indicates whether a size is valid layout size. Size is valid if all its
    /// elements are valid layout values (see Node::isValidLayoutValue()).
    /// \param size Size to test if it is unbound layout size.
    /// \return true if the size if valid layout size, false otherwise.
    static bool isValidLayoutSize(Vector3 size)
    {
        return (Node::isValidLayoutValue(size.getX()) && Node::isValidLayoutValue(size.getY()) && Node::isValidLayoutValue(size.getZ()));
    }

    /// Returns an unbounded layout size.
    /// \return Unbounded layout size.
    static Vector3 unboundedLayoutSize()
    {
        return Vector3(unboundedLayoutValue(), unboundedLayoutValue(), unboundedLayoutValue());
    }

    /// Indicates whether a layout size is an unbound layout size. Size is layout unbound size
    /// if any of its elements is unbounded layout value.
    /// \param layoutSize Layout size to test if it is unbound layout size.
    /// \return true if the layoutSize is unbound layout size, false otherwise.
    static bool isUnboundedLayoutSize(Vector3 layoutSize)
    {
        return (isUnboundedLayoutValue(layoutSize.getX()) || isUnboundedLayoutValue(layoutSize.getY()) || isUnboundedLayoutValue(layoutSize.getZ()));
    }

    /// Replaces any element of a layout size with appropriate element of the reset size if it is unbounded and returns the size.
    /// \param layoutSize Layout size to test if any of its elements is unbounded layout value.
    /// \param resetSize The size whose values are used as a replacement for specified layout size's unbounded value elements.
    /// \return layoutSize with its unbounded value elements replaced with the elements of resetSize.
    static Vector3 replaceUnboundedLayoutSize(Vector3 layoutSize, Vector3 resetSize)
    {
        return Vector3(Node::replaceUnboundedLayoutValue(layoutSize.getX(), resetSize.getX()),
                       Node::replaceUnboundedLayoutValue(layoutSize.getY(), resetSize.getY()),
                       Node::replaceUnboundedLayoutValue(layoutSize.getZ(), resetSize.getZ()));
    }

    /// Replaces any element of a layout size with zero if it is unbounded and returns the size.
    /// \param layoutSize Layout size to test if any of its elements is unbounded layout value.
    /// \return layoutSize with its unbounded value elements replaced with zero.
    static Vector3 replaceUnboundedLayoutSizeWithZero(Vector3 layoutSize)
    {
        return replaceUnboundedLayoutSize(layoutSize, Vector3(0.0f, 0.0f, 0.0f));
    }

#include "node3d_properties.h"

    /// RenderTransformation property.
    /// 
    /// The default value is SRTValue3D(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f)).
    /// \see setRenderTransformation(), getRenderTransformation()
    static PropertyType<SRTValue3D> RenderTransformationProperty;

    /// Gets the value of #RenderTransformationProperty.
    /// \see setRenderTransformation()
    SRTValue3D getRenderTransformation() const
    {
        return getProperty(RenderTransformationProperty);
    }

    /// Sets the value of #RenderTransformationProperty.
    /// \see getRenderTransformation()
    void setRenderTransformation(SRTValue3D value)
    {
        setProperty(RenderTransformationProperty, value);
    }


    /// LayoutTransformation property.
    /// 
    /// The default value is SRTValue3D(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f)).
    /// \see setLayoutTransformation(), getLayoutTransformation()
    static PropertyType<SRTValue3D> LayoutTransformationProperty;

    /// Gets the value of #LayoutTransformationProperty.
    /// \see setLayoutTransformation()
    SRTValue3D getLayoutTransformation() const
    {
        return getProperty(LayoutTransformationProperty);
    }

    /// Sets the value of #LayoutTransformationProperty.
    /// \see getLayoutTransformation()
    void setLayoutTransformation(SRTValue3D value)
    {
        setProperty(LayoutTransformationProperty, value);
    }

    virtual ~Node3D();

    KZ_ABSTRACT_METACLASS_BEGIN(Node3D, Node, "Kanzi.Node3D")
        KZ_METACLASS_PROPERTY_TYPE(LayoutTransformationProperty)
        KZ_METACLASS_PROPERTY_TYPE(RenderTransformationProperty)
        KZ_METACLASS_PROPERTY_TYPE(FinalTransformationProperty)
        KZ_METACLASS_PROPERTY_TYPE(FrustumCullMarginProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /** Gets child count from object. */
    size_t getChildCount() const;

    /** Returns a child from given index from object node. */
    Node3DSharedPtr getChild(size_t index) const;
    /** Returns the index of a child in an object node. */
    size_t getChildIndex(const Node& child) const;
    /// Returns whether or not the child exists.
    bool hasChild(const Node& child) const;

    /** Adds a child node for object node.
    * Adding a 3D object node as a child of a 2D object node is only allowed when adding a scene to a viewport layer.
    * Screens can have only one child which is a layer.
    * \return KZS_SUCCESS on success. KZU_EXCEPTION_INVALID_ADD_CHILD_OPERATION if the above rules are violated.
    */
    void addChild(const Node3DSharedPtr& child);

    /** Adds a child node for object node to given index.
    * Adding a 3D object node as a child of a 2D object node is only allowed when adding a scene to a viewport layer.
    * Screens can have only one child which is a layer.
    * \return KZS_SUCCESS on success. KZU_EXCEPTION_INVALID_ADD_CHILD_OPERATION if the above rules are violated.
    */
    void insertChild(size_t index, const Node3DSharedPtr& child);

    /** Removes child node from parent object. */
    void removeChild(const Node& child);
    /** Removes child node from parent object node at specified index. */
    void removeChild(size_t index);
    /** Removes all child nodes from parent object. */
    void removeAllChildren();


    /** Iterators for children */
    typedef vector<Node3DSharedPtr> ChildContainer;
    // TODO: wrong word order
    typedef ChildContainer::const_iterator ChildConstIterator;
    typedef ChildContainer::const_reverse_iterator ChildConstReverseIterator;
    ChildConstIterator beginChildren() const;
    ChildConstIterator endChildren() const;
    ChildConstReverseIterator rbeginChildren() const;
    ChildConstReverseIterator rendChildren() const;

    virtual bool addAbstractChildOverride(NodeSharedPtr child) KZ_OVERRIDE;
    virtual size_t getAbstractChildCountOverride() KZ_OVERRIDE;
    virtual NodeSharedPtr getAbstractChildOverride(size_t index) KZ_OVERRIDE;
    virtual bool removeAbstractChildOverride(Node& child) KZ_OVERRIDE;

    /// Repositions the node to the beginning of its parent's children, so that it is drawn first.
    void moveToBack();
    /// Repositions the node to the end of its parent's children, so that it is drawn last.
    void moveToFront();

    /// Sets node to automatically determine width.
    void setAutoWidth();
    /// Sets node to automatically determine height.
    void setAutoHeight();
    /// Sets node to automatically determine depth.
    void setAutoDepth();
    /// Sets node to automatically determine width, height and depth.
    void setAutoSize();
    /// Sets size properties of the node.
    /// \param width The value of the WidthProperty.
    /// \param height The value of the HeightProperty.
    /// \param depth The value of the DepthProperty.
    void setSize(float width, float height, float depth);

    /** Set core desired size for an object. */
    void setCoreDesiredSize(const Vector3& coreDesiredSize);
    /** Get core desired size of an object. */
    Vector3 getCoreDesiredSize() const;
    /** Set desired size for an object. */
    void setDesiredSize(const Vector3& desiredSize);
    /** Get desired size for of object. */
    Vector3 getDesiredSize() const;
    /** Set allocated size for an object. */
    void setAllocatedSize(const Vector3& layoutSize);
    /** Get allocated size of an object. */
    Vector3 getAllocatedSize() const;
    /** Set actual size for an object. */
    void setActualSize(const Vector3& actualSize);
    /** Get actual size of an object. */
    Vector3 getActualSize() const;
    /** Set bounding box size for an object. */
    void setLayoutBoundingBoxSize(const Vector3& bboxMin, const Vector3& bboxMax);
    /** Get bounding box size for an object. */
    void getLayoutBoundingBoxSize(Vector3& bboxMin, Vector3& bboxMax) const;
    /** Set allocated offset for an object. */
    void setAllocatedOffset(const Vector3& allocatedOffset);
    /** Get allocated offset of an object. */
    Vector3 getAllocatedOffset() const;
    /** Set stretch scale for an object. */
    void setStretchScale(const Vector3& stretchScale);
    /** Get stretch scale of an object. */
    Vector3 getStretchScale() const;
    /** Set pivot offset for an object. */
    void setPivotOffset(const Vector3& pivotOffset);
    /** Get pivot offset of an object. */
    Vector3 getPivotOffset() const;

    /** Returns the size of object node. */
    kzsError getSize(Vector3& out_size) const;
    /** Returns the minimum coordinates for object nodes bounding volume. */
    kzsError getMaximumBoundingBoxCoordinates(Vector3& out_size) const;
    /** Returns the maximum coordinates for object nodes bounding volume. */
    kzsError getMinimumBoundingBoxCoordinates(Vector3& out_size) const;

    /** Sets the layout transformation of the object. */
    void setArrangeTransformation(const Matrix4x4& value);
    /** Gets the layout transformation of the object. */
    Matrix4x4 getArrangeTransformation() const;

    /** Recursively calculate the layouts in the scene. I.e. calls the measure and arrange functions of every KzuUiComponentNode in the scene. */
    void layout();
    /** Initial scene measure. */
    void measureIterate();
    /** Perform layout measurement on a node. */
    virtual bool measureRecursive();
    /** Initial scene arrange. */
    void arrangeIterate();
    void arrangeIterateLayout(bool propagateArrange);
    void arrangeIterateLayoutChild(bool propagateArrange);

    /** Perform the default measure step. */
    void measure(const Vector3& availableSize);
    /** Perform layout arrangement on a node. */
    void arrange();

    /// Default implementation of measure for a layout that accommodates all children at its center.
    Vector3 centeredMeasure(Vector3 availableSize) const;

    /// Default implementation of arrange for a layout that accommodates all children at its center.
    void centeredArrange(Vector3 actualSize) const;

    bool isPrimitiveLayout() const { return m_primitiveLayout; }

    /// Node-specific render function where the node renders itself.
    /// \param renderer Renderer to use.
    /// \param transformedObjectNode Transformed object corresponding with this object.
    /// \param worldTransformation Transformation of the node.
    virtual void render(Renderer3D& renderer, const KzuTransformedObjectNode& transformedNode, const Matrix4x4& worldTransformation);

    /// Render function which passes the control to the render pass which executes the rendering.
    /// \param renderPass The render pass which executes the rendering.
    /// \param transformedObjectNode The transformed node corresponding to this node.
    void render(RenderPass& renderPass, const KzuTransformedObjectNode& transformedNode);

    Node3DSharedPtr getLookAtTarget() const;
    Node3DSharedPtr getPositionConstraintTarget() const;
    Node3DSharedPtr getOrientationConstraintTarget() const;
    Node3DSharedPtr getFaceToCameraTarget() const;

    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

protected:

    explicit Node3D(Domain* domain, string_view name);

    void initialize();

    virtual NodeSharedPtr findAbstractChildOverride(string_view name) KZ_OVERRIDE;

    virtual VisitorResult visitAbstractChildOverride(const Visitor& visitor, VisitorOrder order) KZ_OVERRIDE;

    virtual Vector3 measureOverride(Vector3 availableSize);

    virtual void arrangeOverride(Vector3 actualSize);

    /// Node-specific render function which passes the control to the render pass which executes the rendering.
    /// \param renderPass The render pass which executes the rendering.
    /// \param transformedObjectNode The transformed node corresponding to this node.
    virtual void renderOverride(RenderPass& renderPass, const KzuTransformedObjectNode& transformedNode);

    void setPrimitiveLayout(bool primitive) { m_primitiveLayout = primitive; }

private:

    NodeReference<Node3D> m_lookAtTarget;
    NodeReference<Node3D> m_positionConstrainTarget;
    NodeReference<Node3D> m_orientationConstraintTarget;
    NodeReference<Node3D> m_faceToCameraTarget;

    ChildContainer m_children; /**< Direct 3D children of the object. */
    /** Object node UI layout data. */
    bool m_primitiveLayout;
    Vector3 m_coreDesiredSize;          /**< Node desired size reported by the node and limited by user specified size. */
    Vector3 m_desiredSize;              /**< Node desired size including common properties like transform and margins. */
    Vector3 m_allocatedSize;            /**< Size allocated for the node by the parent. */
    Vector3 m_actualSize;               /**< Actual size of the node after the layout pass. */
    Vector3 m_pivotOffset;              /**< Pivot offset of the node. */
    Vector3 m_stretchScale;             /**< Stretch scale of the node. */
    Vector3 m_allocatedOffset;          /**< Offset generated by margins and alignment. */
    Vector3 m_boundingBoxMin;           /**< Bounding box minimum for compound mesh bounding box calculation. */
    Vector3 m_boundingBoxMax;           /**< Bounding box maximum for compound mesh bounding box calculation. */
    Matrix4x4 m_arrangeTransformation;   /**< The transformation of an object after layout calculations. */
};



/// Sets node transformation so that the node is in a given position looking at the given point.
/// \param position The new translation of the node.
/// \param lookAtPoint A point where the node is looking at.
/// \param upVector The new up vector of the node.
KANZI_API void nodeLookAt(Node3D& node, Vector3 position, Vector3 lookAtPoint, Vector3 upVector);

}


#endif

#endif
