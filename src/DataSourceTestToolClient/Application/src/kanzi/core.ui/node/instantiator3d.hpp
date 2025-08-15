// Copyright 2008-2021 by Rightware. All rights reserved.

#ifdef KANZI_FEATURE_3D

#ifndef KZU_INSTANCIATOR_H
#define KZU_INSTANCIATOR_H

#include <kanzi/core.ui/node/node_reference.hpp>
#include <kanzi/core.ui/node/node3d.hpp>


namespace kanzi
{

class Instantiator3D;

/// Instantiator3DNode shared pointer.
typedef shared_ptr<Instantiator3D> Instantiator3DSharedPtr;


/// Instantiator3D node is a 3D node that replicates the appearance of 3D object, or a tree of 3D objects
/// the instantiator node targets.
///
/// Instantiator3D node contains a reference to a target object or a tree of objects. When Kanzi renders the
/// instantiator node, the instantiator node copies the appearance of the object the instantiator node targets.
/// This means that all changes to the target object are always reflected in the instantiator node. For example, you
/// can use the instantiator node to create a reflection.
///
/// Each instantiator node has a unique transformation, so you can use more than one instantiator node to
/// target the same object. You cannot override other properties in the instantiator node, so all instances
/// are identical. However, each instantiator node is rendered separately. For example, this enables lights to
/// differently affect instantiator nodes in different positions.
/// 
/// To create truly unique instances of an object, convert that object to a prefab, and create instances of
/// that prefab.
///
/// Note that instantiator nodes affect only rendering. Because the layout size of an instantiator node is 0
/// you cannot use them in layouts.
///
/// Examples
/// ---
///
/// To create a reflection using an instantiator node.
/// \snippet kz_test_instantiator.cpp Reflection example


class KANZI_API Instantiator3D : public Node3D
{
public:

    /// \name Properties
    /// \{

    /// Node property.
    /// The default value is "".
    /// \see setNode(), getNode()
    static PropertyType<string> NodeProperty;

    /// \}

    /// Creates an instantiator node.
    /// \param domain The UI domain the new instantiator node belongs to.
    /// \param name The name of the instantiator node.
    /// \return The created node.
    static Instantiator3DSharedPtr create(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(Instantiator3D, Node3D, "Kanzi.Instantiator3D")
        KZ_METACLASS_PROPERTY_TYPE(NodeProperty)
    KZ_METACLASS_END()

    /// Sets the target node of the instantiator node. The instantiator node replicates the appearance of the target node.
    /// \param targetNode A node that this instantiator node replicates.
    void setTarget(const Node3DSharedPtr& targetNode);

    /// Gets the target node of the instantiator node.
    /// \return The target node of the instantiator node.
    Node3DSharedPtr getTarget() const;

protected:

    /// Constructor.
    /// \param domain The UI domain the new instantiator node belongs to.
    /// \param name The name of the instantiator node.
    explicit Instantiator3D(Domain* domain, string_view name);

private:

    /// Target node reference.
    NodeReference<Node3D> m_targetNode;
};

}

#endif

#endif  // KANZI_FEATURE_3D
