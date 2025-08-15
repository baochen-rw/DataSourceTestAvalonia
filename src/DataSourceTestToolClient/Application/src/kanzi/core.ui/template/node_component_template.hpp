// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_COMPONENT_TEMPLATE_HPP
#define KZ_NODE_COMPONENT_TEMPLATE_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core.ui/kzb/kzu_binary_directory.h>
#include <kanzi/core.ui/object/object.hpp>
#include <kanzi/core.ui/property/variant.hpp>

#include <kanzi/core/legacy/util/io/kzc_input_stream.hpp>

namespace kanzi
{

// Forward declarations.
class KzbFile;
class KzbMemoryParser;
class NodeComponentTemplate;
class NodeComponent;

// Node component template shared pointer types.
typedef shared_ptr<NodeComponentTemplate> NodeComponentTemplateSharedPtr;
typedef shared_ptr<NodeComponentTemplate const> NodeComponentTemplateConstSharedPtr;

// Node component shared pointer types.
typedef shared_ptr<NodeComponent> NodeComponentSharedPtr;


/// NodeComponentTemplate is the base class for all node component templates.
/// Node component template contains data and logic for instantiating node components of specific type.
class KANZI_API NodeComponentTemplate : public Object
{
public:

    /// Type for property value.
    typedef pair<AbstractPropertyType, Variant> PropertyEntry;
    /// Container type for property values.
    typedef vector<PropertyEntry> PropertyContainer;
    /// Iterator type for container of property values.
    typedef PropertyContainer::const_iterator ConstPropertyIterator;

    /// Creates instance of node component template.
    /// \param domain Domain.
    /// \param name Name to assign to every instanced node component.
    /// \param metaclass Metaclass to create node components from.
    /// \return Node component template.
    static NodeComponentTemplateSharedPtr create(Domain* domain, string_view name, const Metaclass* metaclass);

    /// Destructor.
    virtual ~NodeComponentTemplate();

    /// Instantiates node component from the node component template.
    /// \return Instanced node component.
    NodeComponentSharedPtr instantiate();

    /// Loads node component template data from KZB.
    /// Subclasses of NodeComponentTemplate can override this function to load type-specific data.
    /// In this case overriden function should call load() of base class before loading type-specific data.
    /// \param domain Domain.
    /// \param inputStream Input stream to load node component template from.
    /// \param file File in KZB to load node component template from.
    /// \return Loaded node component template.
    virtual void load(KzcInputStream* inputStream, const KzuBinaryFileInfo* file);

    /// Loads node component template data from KZB.
    /// Subclasses of NodeComponentTemplate can override this function to load type-specific data.
    /// In this case overriden function should call load() of base class before loading type-specific data.
    /// \param domain Domain.
    /// \param kzbFile KZB to load node component template from.
    /// \param parser Parser to parse node component template data.
    /// \return Loaded node component template.
    virtual void load(KzbFile& kzbFile, KzbMemoryParser& parser);

    /// Adds a property to set when instantiating the template.
    /// \param propertyType Property type.
    /// \param value Property value.
    void addPropertyValue(AbstractPropertyType propertyType, Variant value)
    {
        m_properties.push_back(PropertyEntry(propertyType, value));
    }

    /// Gets iterator to the beginning of properties container of the template.
    /// \return Const iterator to the beginning of properties container.
    ConstPropertyIterator beginProperties() const
    {
        return m_properties.cbegin();
    }
    /// Gets iterator to the end of properties container of the template.
    /// \return Const iterator to the end of properties container.
    ConstPropertyIterator endProperties() const
    {
        return m_properties.cend();
    }

protected:

    /// Constructor.
    /// \param domain Domain.
    /// \param name Name to use for instantiated node components.
    /// \param nodeComponentMetaclass Metaclass from which node component is created.
    explicit NodeComponentTemplate(Domain* domain, string_view name, const Metaclass* nodeComponentMetaclass);

    /// Initializes instantiated node component.
    /// Subclasses of NodeComponentTemplate can override this function to implemented additional
    /// initialization logic for node components of specific type. Overriden function should call
    /// onInstantiate() of base class before performing custom initialization logic.
    /// \param nodeComponent Node component to copy data to.
    virtual void onInstantiate(NodeComponent& nodeComponent);

    /// Copies properties from the node component template to specified node component.
    /// \param component Node component to copy properties to.
    void copyProperties(NodeComponent& component) const;

private:

    /// Metaclass from which node component is created.
    const Metaclass* m_metaclass;

    /// Name of node component instances.
    string m_name;

    /// Properties to write on the instantiated node component.
    PropertyContainer m_properties;
};

}

#endif
