// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PREFAB_VIEW_HPP
#define KZ_PREFAB_VIEW_HPP

#include <kanzi/ui/ui_api.hpp>

#include <kanzi/core.ui/node/node.hpp>
#include <kanzi/core.ui/template/prefab.hpp>

namespace kanzi
{

// Forward declarations.
class Domain;

/// Prefab view concept class.
class KANZI_UI_API PrefabViewConcept
{
public:
    /// \name Properties
    /// \{

    /// Prefab property.
    /// The default value is ResourceSharedPtr().
    /// \see setPrefab(), getPrefab()
    static PropertyType<ResourceSharedPtr> PrefabProperty;

    /// \}

    /// Message arguments 
    class KANZI_UI_API AsynchronousLoadCompletedMessageArguments : public MessageArguments
    {
    public:
        /// \name Properties
        /// \{
#include "prefab_view_asynchronous_load_completed_properties.h"
        /// \}

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(AsynchronousLoadCompletedMessageArguments, MessageArguments, "Kanzi.PrefabViewConcept.AsynchronousLoadCompletedMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(PrefabTemplateProperty)
        KZ_METACLASS_END()

        /// Sets prefab template argument.
        void setPrefabTemplate(ResourceID resourceId)
        {
            setArgument(PrefabTemplateProperty, resourceId.toString());
        }
        /// Gets prefab template url argument.
        ResourceID getPrefabTemplate() const
        {
            return ResourceID(getArgument(PrefabTemplateProperty));
        }

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Message arguments 
    class KANZI_UI_API LoadAsynchronouslyMessageArguments : public MessageArguments
    {
    public:
        /// \name Properties
        /// \{
#include "prefab_view_load_asynchronously_properties.h"
        /// \}

        KZ_MESSAGE_ARGUMENTS_METACLASS_BEGIN(LoadAsynchronouslyMessageArguments, MessageArguments, "Kanzi.PrefabViewConcept.LoadAsynchronouslyMessageArguments")
            KZ_METACLASS_PROPERTY_TYPE(PrefabTemplateProperty)
        KZ_METACLASS_END()

        /// Sets prefab template argument.
        void setPrefabTemplate(ResourceID resourceId)
        {
            setArgument(PrefabTemplateProperty, resourceId.toString());
        }
        /// Gets prefab template url argument.
        ResourceID getPrefabTemplate() const
        {
            return ResourceID(getArgument(PrefabTemplateProperty));
        }

        static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
    };

    /// Asynchronous load complete message.
    static MessageType<AsynchronousLoadCompletedMessageArguments> AsynchronousLoadCompletedMessage;
    /// Start asynchronous load message.
    static MessageType<LoadAsynchronouslyMessageArguments> LoadAsynchronouslyMessage;

    KZ_MIXIN_METACLASS_BEGIN(PrefabViewConcept, "Kanzi.PrefabViewConcept")
        KZ_METACLASS_MESSAGE_TYPE(AsynchronousLoadCompletedMessage)
        KZ_METACLASS_MESSAGE_TYPE(LoadAsynchronouslyMessage)
        KZ_METACLASS_PROPERTY_TYPE(PrefabProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();
};

/// Base class for prefab views.
template <typename TBaseClass, typename TDerivedClass>
class KANZI_UI_TEMPLATE_API PrefabViewConceptImpl : public TBaseClass, public PrefabViewConcept
{
    /// Internal accessor for the Curiously Recurring Template Pattern.
    TDerivedClass* getThisObject()
    {
        return static_cast<TDerivedClass*>(this);
    }

    /// Internal accessor for the Curiously Recurring Template Pattern.
    const TDerivedClass* getThisObject() const
    {
        return static_cast<const TDerivedClass*>(this);
    }

public:

    typedef shared_ptr<TBaseClass> NodeTypeSharedPtr;

    KZ_TEMPLATE_METACLASS_BEGIN(PrefabViewConceptImpl, TBaseClass)
        KZ_METACLASS_MIXIN(PrefabViewConcept)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Gets the value of #PrefabProperty.
    /// \see setPrefab()
    PrefabTemplateSharedPtr getPrefab() const;
    /// Sets the value of #PrefabProperty.
    /// \see getPrefab()
    void setPrefab(PrefabTemplateSharedPtr value);

    /// Gets the node instantiated from prefab.
    /// \return Instantiated node.
    NodeTypeSharedPtr getInstantiatedNode() const;

    /// Post #LoadAsynchronouslyMessage to load a prefab.
    /// \param key ResourceID referring to the prefab to load.
    void loadPrefabAsynchronously(ResourceID key);

protected:

    /// Initialize the prefab view.
    void initialize();

    /// Constructor.
    /// \param domain The domain the new node belongs to.
    /// \param name The name of the node.
    explicit PrefabViewConceptImpl(Domain* domain, string_view name);

    /// Node::onNodePropertyChanged() implementation.
    virtual void onNodePropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// Message handler for load asynchronously message.
    void onLoadAsynchronously(LoadAsynchronouslyMessageArguments& arguments);

    /// Callback for async load completion.
    /// Takes weak_ptr of prefab view to allow the prefab view to be destroyed before completion.
    static void onAsyncLoadCompletedCallback(weak_ptr<TDerivedClass> prefabView, ResourceID key);
    
    /// Function to be ran from #onAsyncLoadCompletedCallback.
    void onAsyncLoadCompleted(ResourceID key);

    /// Updates the displayed node by creating a new node from the specified prefab template
    /// and removing the old node.
    /// \param prefabTemplate The prefab template that will be instantiated.
    void updateNode(PrefabTemplateSharedPtr prefabTemplate);

private:

    /// Resource ID for acquire task, to ensure the callback is only ran for the latest acquire.
    ResourceID m_acquireTaskResourceId;

    /// Node that prefab view instantiates from #PrefabProperty.
    NodeTypeSharedPtr m_instantiatedNode;
};

}


#endif


