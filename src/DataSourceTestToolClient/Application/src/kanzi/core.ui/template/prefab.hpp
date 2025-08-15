// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_PREFAB_H
#define KZU_PREFAB_H

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core/cpp/algorithm.hpp>
#include <kanzi/core/cpp/unordered_set.hpp>
#include <kanzi/core/cpp/utility.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/property/property_type.hpp>
#include <kanzi/core.ui/property/variant.hpp>
#include <kanzi/core.ui/resource/resource.hpp>

#include <kanzi/core/legacy/kzs_types.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/util/collection/kzc_dynamic_array.hpp>

/* Forward declarations. */
struct KzcMemoryManager;
struct KzcInputStream;
struct KzuBinaryFileInfo;


namespace kanzi
{

// Forward declarations.
class Domain;
class Node;
class Binding;
class NodeComponentTemplate;
class Metaclass;
class ResourceDictionary;
class PrefabTemplateNode;
class PrefabTemplate;
class KzbFile;
class ReadOnlyMemoryFile;
class KzbMemoryParser;
typedef shared_ptr<Binding> BindingSharedPtr;
typedef shared_ptr<NodeComponentTemplate> NodeComponentTemplateSharedPtr;
typedef shared_ptr<ResourceDictionary> ResourceDictionarySharedPtr;
typedef shared_ptr<Node> NodeSharedPtr;
typedef weak_ptr<Node> NodeWeakPtr;
typedef shared_ptr<PrefabTemplate> PrefabTemplateSharedPtr;
typedef shared_ptr<PrefabTemplateNode> PrefabTemplateNodeSharedPtr;
typedef weak_ptr<PrefabTemplateNode> PrefabTemplateNodeWeakPtr;

class KANZI_API PrefabTemplateNode: public Resource
{
public:

    typedef set<NodeWeakPtr, owner_less<NodeWeakPtr> > InstanceReferenceContainer;
    typedef unordered_set<PrefabTemplateNode*> PlaceholderReferenceContainer;
    
    typedef vector<PrefabTemplateNodeSharedPtr> ChildContainer;
    typedef ChildContainer::const_iterator ConstChildIterator;
    typedef vector<BindingSharedPtr> BindingContainer;
    typedef vector<NodeComponentTemplateSharedPtr> NodeComponentTemplateContainer;
    typedef pair<AbstractPropertyType, Variant> PropertyEntry;
    typedef vector<PropertyEntry> PropertyContainer;

    /// Constructor.
    explicit PrefabTemplateNode(Domain* domain, string_view name);

    /// Destructor.
    virtual ~PrefabTemplateNode() KZ_OVERRIDE;

    /// Clean up expired elements from instances.
    void cleanupInstances();

    /// Create prefab-style binding.
    BindingSharedPtr createResourceBinding(const Variant& variant, AbstractPropertyType propertyType) const;

    /// Add child.
    /// \param child Child prefab template node.
    void addChild(PrefabTemplateNodeSharedPtr child)
    {
        children.push_back(child);
    }

    /// Add binding.
    /// \param binding Binding to be added.
    void addBinding(BindingSharedPtr binding)
    {
        m_bindings.push_back(binding);
    }

    /// Add property.
    /// \param propertyType Property type to add.
    /// \param value Value to add.
    void addProperty(AbstractPropertyType propertyType, const Variant& variant)
    {
        m_properties.emplace_back(propertyType, variant);
    }

    /// Tell if this prefab template node is the root of a prefab template node tree.
    bool isRoot() const
    {
        return m_isRoot;
    }
    /// Set the node as being a root of prefab template node tree.
    void setRoot(bool enabled)
    {
        m_isRoot = enabled;
    }

    /// Child nodes.
    ChildContainer children;
    /// Name.
    string name;
    /// Type identifier of the node.
    const Metaclass* typeIdentifier;
    
    /// Instances created from this prefab template node.
    InstanceReferenceContainer instances;
    /// Reference to another prefab template if the template node represents a prefab placeholder.
    PrefabTemplateSharedPtr referencedPrefab;
    /// List of placeholders created to point to the prefab template that owns this prefab template node.
    // TODO: this should be moved to prefab
    PlaceholderReferenceContainer referencingPlaceholders;

    /// Properties to write on the instantiated node.
    PropertyContainer m_properties;
    /// Bindings to create on the instantiated node.
    BindingContainer m_bindings;
    /// Node component templates from which node components are created for instantiated node.
    NodeComponentTemplateContainer m_nodeComponentTemplates;
    /// Resource dictionary for the instantiated node.
    ResourceDictionarySharedPtr m_resourceDictionary;
    /// Host name property, if the instantiated node is a screen.
    string m_host;

    /// Is this node the root of a prefab template node tree?
    bool m_isRoot;
};

}

/** Instantiates a prefab template. */
KANZI_API kanzi::NodeSharedPtr kzuPrefabTemplateInstantiate(kanzi::PrefabTemplate* prefabTemplate, kanzi::string_view rootName);

/** Instantiate the prefab where some node other than the root of the prefab is the template root.
 *  Custom controls use this function to act as template roots for their prefab contents.
 */
KANZI_API kanzi::NodeSharedPtr kzuPrefabTemplateInstantiateAsPart(kanzi::PrefabTemplate* prefabTemplate, kanzi::string_view rootName, kanzi::NodeSharedPtr templateRoot);

namespace kanzi
{

class KANZI_API PrefabTemplate : public Resource
{
public:

    /// Constructor.
    /// \param domain Domain to use.
    /// \param name Name of the prefab.
    explicit PrefabTemplate(Domain* domain, string_view name);

    KZ_METACLASS_BEGIN(PrefabTemplate, Resource, "Kanzi.PrefabTemplate")
    KZ_METACLASS_END()

    /// Creates a new prefab template.
    /// \param domain Domain to use.
    /// \param name Name of the prefab.
    static PrefabTemplateSharedPtr create(Domain* domain, string_view name);

    template <typename TNodeType>
    shared_ptr<TNodeType> instantiate(string_view rootName)
    {
        return dynamic_pointer_cast<TNodeType>(kzuPrefabTemplateInstantiate(this, rootName));
    }

    /// Instantiate the prefab where some node other than the root of the prefab is the template root.
    /// Custom controls use this function to act as template roots for their prefab contents.
    template <typename TNodeType>
    shared_ptr<TNodeType> instantiateAsPart(string_view rootName, NodeSharedPtr templateRoot)
    {
        return dynamic_pointer_cast<TNodeType>(kzuPrefabTemplateInstantiateAsPart(this, rootName, templateRoot));
    }

    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Loads prefab template from KZB and returns it.
    ///
    /// \param domain Domain.
    /// \param name Name of prefab template.
    /// \param kzbFile KZB to read prefab template from.
    /// \param file File entry in KZB which contains prefab template data.
    /// \param parser Parser to parse prefab template data.
    /// \return Loaded prefab template.
    static PrefabTemplateSharedPtr loadFromKZB(Domain* domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

    /// Prefab template root node.
    PrefabTemplateNodeSharedPtr root;
};

}

/** Creates a prefab template with type identifier. This is used for UI components and Layers. */
KANZI_API kanzi::PrefabTemplateNodeSharedPtr kzuPrefabTemplateNodeCreateTyped(kanzi::Domain* domain, const kanzi::Metaclass* typeIdentifier, kzString resourceName, kzString nodeName);
/** Creates a prefab template node representing a prefab placeholder. */
KANZI_API kanzi::PrefabTemplateNodeSharedPtr kzuPrefabTemplateNodeCreatePlaceholder(kanzi::Domain* domain, kanzi::PrefabTemplateSharedPtr instantiatedPrefab, kzString resourceName, kzString nodeName);

/** Loads the children of a prefab template node. */
KANZI_API kzsException kzuPrefabTemplateNodeLoadChildrenFromKZB(kanzi::PrefabTemplateNode* prefabTemplateNode,
                                                                struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);

KANZI_API void kzuPrefabTemplateNodeLoad(kanzi::PrefabTemplateNode* prefabTemplateNode, KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

/** Add a resource. */
KANZI_API kzsError kzuPrefabTemplateNodeAddResource(kanzi::PrefabTemplateNode* prefabTemplateNode, const kanzi::ResourceID& resourceID, const kanzi::string& resourceURL);

/** Add a child to template node. */
KANZI_API void kzuPrefabTemplateNodeAddChild(kanzi::PrefabTemplateNode* prefabTemplateNode, kanzi::PrefabTemplateNodeSharedPtr child);
/** Get the type of the node a node template creates. */
KANZI_API const kanzi::Metaclass* kzuPrefabTemplateNodeGetObjectType(const kanzi::PrefabTemplateNode* prefabTemplateNode);

/** Instantiates a template node. This function is for internal use. */
KANZI_API kanzi::NodeSharedPtr kzuPrefabTemplateNodeInstantiate(kanzi::PrefabTemplateNode* prefabTemplateNode, kanzi::NodeSharedPtr templateRoot);

/** Deletes all instances created from the given prefab template node. */
KANZI_API kzsError kzuPrefabTemplateNodeDeleteInstances(const kanzi::PrefabTemplateNode* prefabTemplateNode);


/** Creates a prefab template. */
KANZI_API kzsError kzuPrefabTemplateCreate(kanzi::Domain* domain, kanzi::string_view name, kanzi::PrefabTemplate** out_prefabTemplate);

/** Gets the root template node of a prefab. */
KANZI_API kanzi::PrefabTemplateNodeSharedPtr kzuPrefabTemplateGetRoot(const kanzi::PrefabTemplate* prefabTemplate);
/** Sets the root template node of a prefab. */
KANZI_API void kzuPrefabTemplateSetRoot(kanzi::PrefabTemplate* prefabTemplate, kanzi::PrefabTemplateNodeSharedPtr rootNode);

/** Update all existing instances of the prefab template node with updated data. */
KANZI_API kzsError kzuPrefabTemplateNodeUpdateInstances(const kanzi::PrefabTemplateNode* prefabTemplateNode);

/** Loads prefab from KZB. */
KANZI_API kzsError kzuPrefabTemplateLoadFromKZB(kanzi::PrefabTemplate* prefabTemplate, struct KzcInputStream* inputStream, const struct KzuBinaryFileInfo* file);


#endif
