// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_STYLE_HPP
#define KZ_STYLE_HPP


#include <kanzi/core.ui/binding/binding.hpp>
#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/template/node_component_template.hpp>

#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core/cpp/vector.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


struct KzuBinaryFileInfo;
struct KzcInputStream;

namespace kanzi
{

class Domain;
class Style;
struct AppliedStyleEntry;

typedef shared_ptr<Style> StyleSharedPtr;

/**
 * Style applying properties, node components and bindings to nodes.
 */
class KANZI_API Style : public Resource
{
public:
    KZ_ABSTRACT_METACLASS_BEGIN(Style, Resource, "Kanzi.Style")
    KZ_METACLASS_END()

    typedef vector<NodeComponentTemplateSharedPtr> NodeComponentTemplateContainer;
    typedef NodeComponentTemplateContainer::const_iterator NodeComponentTemplateIterator;

    typedef vector<BindingSharedPtr> BindingContainer;
    typedef BindingContainer::const_iterator BindingIterator;

    typedef vector<Node*> NodeContainer;
    typedef NodeContainer::const_iterator NodeIterator;
    typedef NodeContainer::reverse_iterator NodeReverseIterator;

    typedef vector<Object*> ObjectContainer;
    typedef ObjectContainer::const_iterator ObjectIterator;
    typedef ObjectContainer::reverse_iterator ObjectReverseIterator;

    typedef unordered_map<AbstractPropertyType, AbstractPropertyTypeDescriptor::ValueSource*> ValueSourceContainer;
    typedef ValueSourceContainer::const_iterator ValueSourceIterator;
    typedef pair<AbstractPropertyType, AbstractPropertyTypeDescriptor::ValueSource*> ValueSourcePair;

    typedef pair<AbstractPropertyType, Variant> PropertyPair;
    typedef vector<PropertyPair> PropertyContainer;
    typedef PropertyContainer::const_iterator PropertyConstIterator;

    virtual ~Style() KZ_OVERRIDE;

    static StyleSharedPtr create(Domain* domain, string_view name, StyleSharedPtr parentStyle, const Metaclass* objectType, const PropertyContainer& properties, const BindingContainer& bindings,
                                 const NodeComponentTemplateContainer& nodeComponentTemplates);

    static StyleSharedPtr createWithValueModifiers(Domain* domain, string_view name, StyleSharedPtr parentStyle, const Metaclass* objectType, const PropertyContainer& properties, const BindingContainer& bindings,
                                                   const NodeComponentTemplateContainer& nodeComponentTemplates);

    /** Create an empty style. */
    static Style* createEmpty(Domain* domain, string_view name);

    /** Copy a style. */
    static Style* copy(const Style* sourceStyle);

    /** Load a style from kzb. */
    virtual void loadFromKZB(const ResourceLoaderThreadContext* threadContext, KzcInputStream* inputStream, const KzuBinaryFileInfo* file) KZ_OVERRIDE;

    /// Loads a style dictionary from a file. Used internally by Kanzi Engine.
    ///
    /// \param domain Domain
    /// \param name Name
    /// \param kzbFile KZB file where to load from.
    /// \param file Style file inside the KZB file where to load from.
    /// \param parser Parser pointing to the beginning of the file.
    static StyleSharedPtr loadFromKZB(Domain* domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

    /// Gets an iterator to the beginning of container of properties of a style.
    /// \return Iterator to the beginning of container of properties of a style.
    ValueSourceIterator beginProperties();

    /// Gets an iterator to the end of container of properties of a style.
    /// \return Iterator to the end of container of properties of a style.
    ValueSourceIterator endProperties();

    PropertyValuePrecedence getPrecedence() const
    {
        return m_precedence;
    }

    /** Get value source for a property type. */
    AbstractPropertyTypeDescriptor::ValueSource* getValueSource(AbstractPropertyType propertyType);

    /// Gets an iterator to the beginning of container of bindings of a style.
    /// \return Const iterator to the beginning of container of bindings of a style.
    BindingIterator beginBindings() const;

    /// Gets an iterator to the end of the container of bindings of a style.
    /// \return Const iterator to the end of the container of bindings of a style.
    BindingIterator endBindings() const;

    /// Gets an iterator to the beginning of container of node component templates of a style.
    /// \return Const iterator to the beginning of container of node component templates of a style.
    NodeComponentTemplateIterator beginNodeComponentTemplates() const;

    /// Gets an iterator to the end of the container of node component templates of a style.
    /// \return Const iterator to the end of the container of node component templates of a style.
    NodeComponentTemplateIterator endNodeComponentTemplates() const;

    /** Apply a style. */
    static void apply(AppliedStyleEntrySharedPtr appliedStyleEntry, Node* objectNode);
    /** Unapply a style. */
    static void unapply(AppliedStyleEntrySharedPtr appliedStyleEntry, Node* objectNode);
    /** Apply all styles to an object node. */
    static void applyAll(Node* applyObjectNode);

    /// Apply a style (generic).
    static void apply(AppliedStyleEntrySharedPtr appliedStyleEntry, Object* object);
    /// Unapply a style (generic).
    static void unapply(AppliedStyleEntrySharedPtr appliedStyleEntry, Object* object);

    /** Set style properties precedence. */
    void setPrecedence(PropertyValuePrecedence precedence);

protected:
    static bool applyTypedStyle(Node& target, const ResourceDictionary& dictionary);
    static bool applyTypedStyle(Node& target, const Node& scope);

    StyleSharedPtr m_parent;                 /**< Parent style. */
    optional<const Metaclass*> m_objectType; ///< Object type this style applies to, nullptr if the style applies to any type, or nullopt if there is no target type.
    bool m_useValueModifiers;                ///< Does this style apply value modifiers or value sources.
    PropertyValuePrecedence m_precedence;    /**< Property precedence of this style. */
    ValueSourceContainer m_valueSources;     /**< Property values of this style. <KzuPropertyType, void* (value source)>. */
    BindingContainer m_bindings;             /**< Bindings of this style .*/
    /// Node component templates of this style.
    NodeComponentTemplateContainer m_nodeComponentTemplates;

    Style(Domain* domain, string_view name);

    /** Copies bindings from one array to another. */
    static void copyBindings(const BindingContainer& source, BindingContainer& target);

    /** Copies parent style properties. */
    void copyParentProperties();

    /** Extracts property metadata for a style. */
    void createValueSources(const PropertyContainer& properties);

    /** Internal create function. */
    static Style* createInternal(Domain* domain, string_view name, StyleSharedPtr parentStyle, optional<const Metaclass*> objectType, const PropertyContainer& properties, const ValueSourceContainer* hashProperties,
                                 const BindingContainer& bindings, const NodeComponentTemplateContainer& nodeComponents, bool useValueModifiers);

    /** Empties contents of a style. */
    void cleanup();
};
}

#endif
