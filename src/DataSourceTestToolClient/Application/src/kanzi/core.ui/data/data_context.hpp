// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_DATA_CONTEXT_HPP
#define KZ_DATA_CONTEXT_HPP

#include <kanzi/core.ui/resource/resource.hpp>
#include <kanzi/core/cpp/functional.hpp>

namespace kanzi
{

// Forward declarations.
class DataContext;
class DataObject;
typedef shared_ptr<DataObject> DataObjectSharedPtr;
typedef shared_ptr<DataContext> DataContextSharedPtr;

/// DataContext acts as a container for data.
///
/// All data within the data context is described as a tree of data objects. 
/// The class provides access and look-up functionality of the contained data objects.
class KANZI_API DataContext : public Resource
{
public:

    /// Callback function type for change subscriptions.
    typedef function<void()> ModifiedFunction;
    /// Token type that can be used to identify the change subscription.
    typedef shared_ptr<void> ModifiedSubscriptionToken;

    /// Functor for cleaning up stale notification entries.
    class DataContextNotificationCleanupFunctor;

protected:

    /// Subscription entry.
    struct ModifiedSubscription
    {
        ModifiedFunction function;
    };

    /// Subscription shared pointer type.
    typedef shared_ptr<ModifiedSubscription> ModifiedSubscriptionSharedPtr;
    /// Container for subscriptions.
    typedef vector<ModifiedSubscriptionSharedPtr> ModifiedSubscriptionContainer;

public:

    /// \name Properties
    /// \{
#include "data_context_properties.h"
    /// \}

    KZ_STATIC_METACLASS_BEGIN(DataContext, "Kanzi.DataContext")
        KZ_METACLASS_PROPERTY_TYPE(DataContextProperty)
        KZ_METACLASS_PROPERTY_TYPE(ItemsSourceProperty)
    KZ_METACLASS_END()

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Allows to subscribe to modifications in this data context.
    /// \param callback Callback that is invoked when a change occurs in this data context.
    /// \return Token that can be used to identify and remove given subscripion.
    ModifiedSubscriptionToken addModifiedNotificationHandler(ModifiedFunction callback);
    /// Allows to unsubscribe from modifications in this data context.
    /// \param token Token to identify the subscription that should be removed.
    void removeModifiedNotificationHandler(ModifiedSubscriptionToken token);

    /// Triggers modification procedure in this data context, which invokes the subscriptions.
    /// Should be called by derived classes whenever the value of the object is changed.
    void notifyModified();

    /// Retrieves the root object of the underlying data tree. Needs to be implemented by the derived class.
    /// \return Returns data object that is the root of the data tree.
    virtual DataObjectSharedPtr getData() = 0;

    template <typename Type>
    shared_ptr<Type> lookupDataContextOfType(string_view relativePath)
    {
        DataContextSharedPtr result = lookupDataContext(relativePath);
        if (result)
        {
            return dynamic_pointer_cast<Type>(result);
        }

        return shared_ptr<Type>();
    }

    /// Performs object look-up by path.
    /// \param relativePath Path of the object where to look at, separated by '.'.
    /// \return Data object that was found, or empty pointer if there was no such object.
    virtual DataContextSharedPtr lookupDataContext(string_view relativePath) = 0;

protected:

    /// Protected standard constructor.
    /// \param name Name of the data context.
    explicit DataContext(Domain* domain, string_view name);

private:

    /// Clean up notification entries marked for removal.
    /// Called at the end of notification execution.
    void cleanupNotificationEntries();

protected:

    /// Subscriptions to data context being modified.
    ModifiedSubscriptionContainer m_subscriptions;
    /// Notification pass guard integer for triggering removal at end.
    unsigned int m_notificationPassGuard;
};
}
#endif
