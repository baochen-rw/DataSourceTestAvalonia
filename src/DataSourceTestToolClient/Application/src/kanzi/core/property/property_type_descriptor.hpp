// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_PROPERTY_TYPE_DESCRIPTOR_HPP
#define KZ_PROPERTY_TYPE_DESCRIPTOR_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/property/abstract_property_type_descriptor.hpp>
#include <kanzi/core/property/property_data_type_traits.hpp>
#include <kanzi/core/util/reference_count_scope_guard.hpp>

namespace kanzi
{

class PropertyObject;

/// PropertyTypeDescriptor is used internally by the property system to implement all operations required for property types that have the same data type.
template <typename T>
class PropertyTypeDescriptor : public AbstractPropertyTypeDescriptor
{
public:

    typedef PropertyDataTypeTraits<T> Traits;

    struct TypedValueSource : public ValueSource
    {
        typename Traits::StorageType value;
    };

    typedef void (*ModifierCallback)(PropertyObject&, typename Traits::StorageType&, PropertyNotificationReason, void*);
    typedef void (*NotificationCallback)(PropertyObject&, const typename Traits::StorageType&, PropertyNotificationReason, void*);

    struct TypedModifierEntry : public ModifierEntry
    {
        explicit TypedModifierEntry(ModifierCallback modifierCallback, void* newOwner) : modifierCallback(modifierCallback)
        {
            owner = newOwner;
        }

        bool operator==(const TypedModifierEntry& other) const
        {
            return modifierCallback == other.modifierCallback && owner == other.owner;
        }

        ModifierCallback modifierCallback;
    };

    struct TypedModifierStorage : public ModifierStorage
    {
        explicit TypedModifierStorage():
            modifiedValue()
        {
        }

        typedef vector<TypedModifierEntry> ModifierEntryContainer;
        ModifierEntryContainer modifierEntries;

        TypedValueSource modifiedValue;
    };

    struct TypedNotificationEntry
    {
        explicit TypedNotificationEntry(NotificationCallback notificationCallback, void* owner) : notificationCallback(notificationCallback), owner(owner)
        {
        }

        bool operator==(const TypedNotificationEntry& other) const
        {
            return notificationCallback == other.notificationCallback && owner == other.owner;
        }

        NotificationCallback notificationCallback;
        void* owner;
    };

    struct TypedNotificationStorage : public NotificationStorage
    {
        /// Functor for cleaning up stale notification entries.
        struct CleanupFunctor
        {
            /// Constructor.
            explicit CleanupFunctor(TypedNotificationStorage& storage) :
                m_storage(storage)
            {
            }

            /// Call operator.
            void operator()()
            {
                m_storage.cleanupNotificationEntries();
            }

            /// Storage to clean.
            TypedNotificationStorage& m_storage;
        };

        /// Notification entry container type.
        typedef vector<TypedNotificationEntry> NotificationEntryContainer;

        /// Guard type for cleanup.
        typedef ReferenceCountScopeGuard<unsigned int, CleanupFunctor> GuardType;

        /// Constructor.
        explicit TypedNotificationStorage() :
            notificationDepth(0)
        {
        }

        /// Clean up invalidated notification entries.
        void cleanupNotificationEntries()
        {
            for (typename NotificationEntryContainer::iterator it = notificationEntries.begin(); (it != notificationEntries.end());)
            {
                if (!(*it).notificationCallback)
                {
                    it = notificationEntries.erase(it);
                }
                else
                {
                    ++it;
                }
            }
        }

        /// Notification entries.
        NotificationEntryContainer notificationEntries;
        /// Counter for notification depth.
        unsigned int notificationDepth;
    };

    explicit PropertyTypeDescriptor(FixedString name, typename Traits::ParameterType defaultValue, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo) :
        AbstractPropertyTypeDescriptor(name, changeFlags, inherited, editorInfo)
    {
        Traits::write(m_defaultValue, defaultValue);
    }

    explicit PropertyTypeDescriptor(MetadataGeneratedName name, typename Traits::ParameterType defaultValue, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo) :
        AbstractPropertyTypeDescriptor(name, changeFlags, inherited, editorInfo)
    {
        Traits::write(m_defaultValue, defaultValue);
    }

    virtual ~PropertyTypeDescriptor() KZ_OVERRIDE
    {
        kzAssert(!m_typeNotificationEntries || m_typeNotificationEntries->notificationEntries.empty());
    }

    typename Traits::ReturnType getDefaultValue() const
    {
        return Traits::read(m_defaultValue);
    }

    virtual kanzi::PropertyDataType getDataType() const KZ_OVERRIDE
    {
        return Traits::dataType;
    }

    virtual TypedValueSource* constructValueSource() KZ_OVERRIDE
    {
        return new TypedValueSource;
    }

    virtual void destructValueSource(ValueSource* valueSource) KZ_OVERRIDE
    {
        delete static_cast<TypedValueSource*>(valueSource);
    }

    virtual TypedModifierStorage* constructModifierStorage() KZ_OVERRIDE
    {
        return new TypedModifierStorage;
    }

    virtual void destructModifierStorage(ModifierStorage* modifierStorage) KZ_OVERRIDE
    {
        delete static_cast<TypedModifierStorage*>(modifierStorage);
    }

    virtual TypedValueSource* getModifierValueSource(ModifierStorage* modifierStorage) KZ_OVERRIDE
    {
        kzAssert(modifierStorage);

        TypedModifierStorage* typedModifierStorage = static_cast<TypedModifierStorage*>(modifierStorage);
        if (typedModifierStorage->modifierEntries.empty())
        {
            return 0;
        }

        return &typedModifierStorage->modifiedValue;
    }

    virtual void validateModifiers(PropertyObject& object, PropertyStorage& propertyStorage, PropertyNotificationReason reason) KZ_OVERRIDE
    {
        kzAssert(propertyStorage.modifierStorage);

        TypedModifierStorage* typedModifierStorage = static_cast<TypedModifierStorage*>(propertyStorage.modifierStorage);

        if (typedModifierStorage->modifierEntries.empty())
        {
            return;
        }

        if (reason != PropertyNotificationReasonRemoved)
        {
            if (propertyStorage.valueSourceEntries.empty())
            {
                typedModifierStorage->modifiedValue.value = getDefaultValue();
            }
            else
            {
                ValueSourceEntry* valueSourceEntry = &propertyStorage.valueSourceEntries.front();
                TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(valueSourceEntry->valueSource);
                typedModifierStorage->modifiedValue.value = typedValueSource->value;
            }
        }

        // TODO: reentrancy

        for (size_t i = 0, end = typedModifierStorage->modifierEntries.size(); i != end; ++i)
        {
            TypedModifierEntry& typedModifierEntry = typedModifierStorage->modifierEntries[i];
            if (typedModifierEntry.modifierCallback)
            {
                typedModifierEntry.modifierCallback(object, typedModifierStorage->modifiedValue.value, reason, typedModifierEntry.owner);
            }
        }
    }

    virtual TypedNotificationStorage* constructNotificationStorage() KZ_OVERRIDE
    {
        return new TypedNotificationStorage;
    }

    virtual void destructNotificationStorage(NotificationStorage* notificationStorage) KZ_OVERRIDE
    {
        delete static_cast<TypedNotificationStorage*>(notificationStorage);
    }

    virtual void invokeGlobalNotificationHandlers(PropertyObject& object, ValueSource* finalValueSource, PropertyNotificationReason reason) KZ_OVERRIDE
    {
        if (!m_typeNotificationEntries)
        {
            return;
        }

        // Pass the changed value from value source or use default value of the type as a surrogate when the changed value is not available,
        // e.g. in "removed" notifications and when no value sources or modifiers are available.
        TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(finalValueSource);
        const T& changedValue = typedValueSource ? typedValueSource->value : m_defaultValue;

        // Prevent removal while notifications are in progress.
        typename TypedNotificationStorage::GuardType guard(m_typeNotificationEntries->notificationDepth, typename TypedNotificationStorage::CleanupFunctor(*m_typeNotificationEntries));

        for (size_t i = 0, end = m_typeNotificationEntries->notificationEntries.size(); i != end; ++i)
        {
            TypedNotificationEntry& entry = m_typeNotificationEntries->notificationEntries[i];
            if (entry.notificationCallback)
            {
                entry.notificationCallback(object, changedValue, reason, entry.owner);
            }
        }
    }

    virtual void invokeNotificationHandlers(PropertyObject& object, ValueSource* finalValueSource, NotificationStorage* notificationStorage, PropertyNotificationReason reason) KZ_OVERRIDE
    {
        if (!notificationStorage)
        {
            return;
        }

        // Pass the changed value from value source or use default value of the type as a surrogate when the changed value is not available,
        // e.g. in "removed" notifications and when no value sources or modifiers are available.
        TypedValueSource* typedValueSource = static_cast<TypedValueSource*>(finalValueSource);
        const T& changedValue = typedValueSource ? typedValueSource->value : m_defaultValue;

        TypedNotificationStorage* typedNotificationStorage = static_cast<TypedNotificationStorage*>(notificationStorage);

        // Prevent removal while notifications are in progress.
        typename TypedNotificationStorage::GuardType guard(typedNotificationStorage->notificationDepth, typename TypedNotificationStorage::CleanupFunctor(*typedNotificationStorage));

        for (size_t i = 0, end = typedNotificationStorage->notificationEntries.size(); i != end; ++i)
        {
            // Assert that notification entries have not been removed while processing is in progress. Adding entries is legal.
            kzAssert(end <= typedNotificationStorage->notificationEntries.size());

            TypedNotificationEntry& entry = typedNotificationStorage->notificationEntries[i];
            if (entry.notificationCallback)
            {
                entry.notificationCallback(object, changedValue, reason, entry.owner);
            }
        }
    }

    /// AbstractPropertyTypeDescriptor::copyValueSource() implementation.
    virtual void copyValueSource(AbstractPropertyTypeDescriptor::ValueSource* dst, const AbstractPropertyTypeDescriptor::ValueSource* src) KZ_OVERRIDE
    {
        const TypedValueSource* typedSrc = static_cast<const TypedValueSource*>(src);
        T value = Traits::read(typedSrc->value);

        TypedValueSource* typedDst = static_cast<TypedValueSource*>(dst);
        Traits::write(typedDst->value, value);
    }

    void addNotificationHandler(NotificationCallback callback, void* owner)
    {
        if (!m_typeNotificationEntries)
        {
            m_typeNotificationEntries.reset(new TypedNotificationStorage);
        }

        TypedNotificationEntry notificationEntry(callback, owner);
        m_typeNotificationEntries->notificationEntries.push_back(notificationEntry);
    }

    void removeNotificationHandler(NotificationCallback callback, void* owner)
    {
        typedef typename TypedNotificationStorage::NotificationEntryContainer::iterator NotificationEntryIterator;

        if (!m_typeNotificationEntries)
        {
            return;
        }

        TypedNotificationEntry notificationEntry(callback, owner);
        if (m_typeNotificationEntries->notificationDepth == 0)
        {
            erase(m_typeNotificationEntries->notificationEntries, notificationEntry);
        }
        else
        {
            for (NotificationEntryIterator it = m_typeNotificationEntries->notificationEntries.begin(), endIt = m_typeNotificationEntries->notificationEntries.end(); (it != endIt); ++it)
            {
                if ((*it) == notificationEntry)
                {
                    (*it).notificationCallback = 0;
                    break;
                }
            }

        }
    }

    // TODO: add default-constructible default value optimization to save storage
    typename Traits::StorageType m_defaultValue;
    unique_ptr<TypedNotificationStorage> m_typeNotificationEntries;
};

}

#endif
