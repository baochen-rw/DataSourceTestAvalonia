// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_ABSTRACT_PROPERTY_TYPE_DESCRIPTOR_HPP
#define KZ_ABSTRACT_PROPERTY_TYPE_DESCRIPTOR_HPP

#include <kanzi/core/cpp/intrusive_ptr.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/type_traits.hpp>
#include <kanzi/core/cpp/unordered_map.hpp>
#include <kanzi/core/cpp/vector.hpp>
#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/metadata/editor_metadata.hpp>
#include <kanzi/core/metadata/metadata.hpp>
#include <kanzi/core/property/property_data_type.hpp>
#include <kanzi/core/property/property_field.hpp>
#include <kanzi/core/string/fixed_string.hpp>


/// Flag to indicate that the property was loaded from .KZB data.
#define KZU_PROPERTY_MANAGER_FLAG_KEEP_DURING_PATCHING 1
/// Flag to indicate that the property will not be copied when copying properties.
#define KZU_PROPERTY_MANAGER_FLAG_NON_COPYABLE 2


namespace kanzi
{

/// Each property type has a set of property change flags that indicate what kind of effects changing the property has.
/// For example, when the text property of a text block is changed, then the text block layout has to be recalculated, so the
/// text property type has #PropertyTypeChangeFlagMeasure.
enum PropertyTypeChangeFlag
{
    /// Property type with this flag affects final transformation of an object and all its children.
    /// Causes updateRender() to be ran.
    PropertyTypeChangeFlagFinalTransformation = 1u << 1,

    /// Property type with this flag causes layout measure() to be ran.
    /// Set by property changes that affect layout.
    PropertyTypeChangeFlagMeasure = 1u << 2,

    /// Property type with this flag affects measure requirement of node's parent.
    PropertyTypeChangeFlagParentMeasure = 1u << 7,

    /// Property type with this flag causes layout arrange() to be ran.
    /// Flag is also set by measure pass on nodes where measurements were changed.
    PropertyTypeChangeFlagArrange = 1u << 3,

    /// Property type with this flag affects rendering and causes updateRender() to be ran.
    PropertyTypeChangeFlagRender = 1u << 4,

    /// Change flag set when updateRender() is ran, causes node to be drawn.
    PropertyTypeChangeFlagDraw = 1u << 5,

    /// Property type with this flag informs that constraints are in use.
    PropertyTypeChangeFlagConstraint = 1u << 18
};

/// Property notification reason.
enum PropertyNotificationReason
{
    /// The property value was modified.
    PropertyNotificationReasonChanged,

    /// The property value was removed.
    PropertyNotificationReasonRemoved
};

/// Property value precedence.
enum PropertyValuePrecedence
{
    /// Property value precedence used by the class default values.
    PropertyValuePrecedenceClass,

    /// Property value precedence used by styles.
    PropertyValuePrecedenceStyle,

    /// Property value precedence used by state managers.
    PropertyValuePrecedenceStateManager,

    /// Property value precedence used by local values.
    PropertyValuePrecedenceLocal
};


// Forward declarations.
class PropertyObject;

/// AbstractPropertyTypeDescriptor is used internally by the property type system to manage property types.
///
/// You should use PropertyType, DynamicPropertyType and AbstractPropertyType classes if you want to get or set properties.
class KANZI_API AbstractPropertyTypeDescriptor
{
public:

    explicit AbstractPropertyTypeDescriptor(FixedString name, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo);
    explicit AbstractPropertyTypeDescriptor(MetadataGeneratedName name, uint32_t changeFlags, bool inherited, PropertyTypeEditorInfoSharedPtr editorInfo);
    virtual ~AbstractPropertyTypeDescriptor();

    /// Name of the property type.
    const char* m_name;
    /// Unqualified name of the property type.
    const char* m_unqualifiedName;
    /// Flags of property type.
    uint32_t m_flags;
    /// Change flags set on an object where a property of this type is set.
    uint32_t m_changeFlags;

    /// Bit flag to encode that the property type is inherited.
    static const uint32_t s_inheritedFlag = 1u;
    /// Bit flag to encode that the name of the property type is a local copy.
    static const uint32_t s_managedStringFlag = 1u << 31u;
    /// Bit mask to extract inherited flag from m_flags.
    static const uint32_t s_inheritedMask = ~s_managedStringFlag;

#if defined KZ_EDITOR_INFO_METADATA
    /// Editor information about the property type.
    kanzi::PropertyTypeEditorInfoSharedPtr m_editorInfo;
#endif

    const char* getName() const
    {
        return m_name;
    }

    const char* getUnqualifiedName() const
    {
        return m_unqualifiedName;
    }

    virtual kanzi::PropertyDataType getDataType() const = 0;

    bool isInherited() const
    {
        return (m_flags & s_inheritedMask) != 0;
    }

    uint32_t getChangeFlags() const
    {
        return m_changeFlags;
    }

    kanzi::PropertyTypeEditorInfoSharedPtr getEditorInfo() const
    {
#if defined KZ_EDITOR_INFO_METADATA
        return m_editorInfo;
#else
        return 0;
#endif
    }

    struct ValueSource
    {
    };

    struct ValueModifier
    {
    };

    struct ValueSourceEntry
    {
        explicit ValueSourceEntry(ValueSource* valueSource, void* owner, PropertyValuePrecedence precedence) : valueSource(valueSource), owner(owner), precedence(precedence)
        {
        }

        ValueSource* valueSource;
        void* owner;    // TODO: this could be moved to the value source itself. these will make lifetime of entries important
        PropertyValuePrecedence precedence; // TODO: same as above
    };

    KZ_STATIC_ASSERT(is_nothrow_move_constructible<ValueSourceEntry>::value, "Error");
    KZ_STATIC_ASSERT(KZ_IS_TRIVIALLY_COPYABLE<ValueSourceEntry>::value, "Error");

    struct ModifierEntry
    {
        void* owner;    // TODO: can be moved to modifier itself. same comment as for value sources + valueModifiers are callbacks and therefore not unique
    };

    struct ModifierStorage
    {
    };

    struct NotificationStorage
    {
    };

    struct PropertyStorage : public UsingIntrusivePtr
    {
        typedef vector<ValueSourceEntry> ValueSourceEntryContainer;
        typedef ValueSourceEntryContainer::iterator ValueSourceEntryIterator;
        typedef ValueSourceEntryContainer::const_iterator ValueSourceEntryConstIterator;
        typedef ValueSourceEntryContainer::reverse_iterator ValueSourceEntryReverseIterator;
        typedef ValueSourceEntryContainer::const_reverse_iterator ValueSourceEntryConstReverseIterator;

        explicit PropertyStorage(AbstractPropertyTypeDescriptor* descriptor) :
            descriptor(descriptor),
            flags(0),
            modifierStorage(0),
            notificationStorage(0)
        {
        }

        ~PropertyStorage()
        {
            if (notificationStorage)
            {
                descriptor->destructNotificationStorage(notificationStorage);
            }

            if (modifierStorage)
            {
                descriptor->destructModifierStorage(modifierStorage);
            }

            if (!valueSourceEntries.empty())
            {
                ValueSourceEntry* entry = &valueSourceEntries.front();
                if (entry->precedence == PropertyValuePrecedenceLocal)
                {
                    descriptor->destructValueSource(entry->valueSource);
                }
            }
        }

        /// Get value source with highest priority, modifier stack included.
        ValueSource* getFinalValueSource() const
        {
            if (modifierStorage)
            {
                AbstractPropertyTypeDescriptor::ValueSource* modifierValueSource = descriptor->getModifierValueSource(modifierStorage);
                if (modifierValueSource)
                {
                    return modifierValueSource;
                }
            }

            if (valueSourceEntries.empty())
            {
                return 0;
            }

            return valueSourceEntries.front().valueSource;
        }

        /// Get value source entry with highest priority, disregard modifiers.
        const ValueSourceEntry* getTopValueSourceEntry() const
        {
            if (valueSourceEntries.empty())
            {
                return 0;
            }

            return &(valueSourceEntries.front());
        }

        /// Get value source entry with highest priority, disregard modifiers.
        ValueSourceEntry* getTopValueSourceEntry()
        {
            if (valueSourceEntries.empty())
            {
                return 0;
            }

            return &(valueSourceEntries.front());
        }

        /// Get value source with highest priority, disregard modifiers.
        ValueSource* getTopValueSource() const
        {
            if (valueSourceEntries.empty())
            {
                return 0;
            }

            return valueSourceEntries.front().valueSource;
        }

        /// Gets any value source that does not have class default value priority.
        /// \return Value source found or 0.
        ValueSource* getNonClassValueSource() const
        {
            if (modifierStorage)
            {
                AbstractPropertyTypeDescriptor::ValueSource* modifierValueSource = descriptor->getModifierValueSource(modifierStorage);
                if (modifierValueSource)
                {
                    return modifierValueSource;
                }
            }

            if (!valueSourceEntries.empty())
            {
                const ValueSourceEntry& frontEntry = valueSourceEntries.front();
                if (frontEntry.precedence > PropertyValuePrecedenceClass)
                {
                    return frontEntry.valueSource;
                }
            }

            return 0;
        }

        /// Gets value source if it has class default value priority (or lower).
        /// \return Value source found or 0.
        ValueSource* getClassValueSource() const
        {
            if (!valueSourceEntries.empty())
            {
                ValueSourceEntryContainer::const_reverse_iterator itBegin = crbegin(valueSourceEntries);
                for (ValueSourceEntryContainer::const_reverse_iterator it = itBegin, itEnd = crend(valueSourceEntries); (it != itEnd); ++it)
                {
                    // Iterate from the back until a higher-than class precedence is found.
                    if ((*it).precedence > PropertyValuePrecedenceClass)
                    {
                        // If not at beginning, check if previous value exists, it will have class precedence or lower.
                        if (it != itBegin)
                        {
                            --it;
                            kzAssert((*it).precedence <= PropertyValuePrecedenceClass);
                            return (*it).valueSource;
                        }

                        // No class precedence found.
                        return 0;
                    }
                }

                // Iteration complete but no higher-than class precedence found, return front.
                const ValueSourceEntry& frontEntry = valueSourceEntries.front();
                kzAssert(frontEntry.precedence <= PropertyValuePrecedenceClass);
                return frontEntry.valueSource;
            }

            return 0;
        }

    private:

        KZ_USING_INTRUSIVE_PTR(PropertyStorage)

    public:

        AbstractPropertyTypeDescriptor* descriptor;
        uint32_t flags;
        ValueSourceEntryContainer valueSourceEntries;
        ModifierStorage* modifierStorage;
        NotificationStorage* notificationStorage;
    };

    virtual ValueSource* constructValueSource() = 0;
    virtual void destructValueSource(ValueSource* valueSource) = 0;

    virtual ModifierStorage* constructModifierStorage() = 0;
    virtual void destructModifierStorage(ModifierStorage* modifierStorage) = 0;

    virtual ValueSource* getModifierValueSource(ModifierStorage* modifierStorage) = 0;

    virtual void validateModifiers(PropertyObject& object, PropertyStorage& propertyStorage, PropertyNotificationReason reason) = 0;

    virtual NotificationStorage* constructNotificationStorage() = 0;
    virtual void destructNotificationStorage(NotificationStorage* notificationStorage) = 0;

    virtual void invokeGlobalNotificationHandlers(PropertyObject& object, ValueSource* finalValueSource, PropertyNotificationReason reason) = 0;
    virtual void invokeNotificationHandlers(PropertyObject& object, ValueSource* finalValueSource, NotificationStorage* notificationStorage, PropertyNotificationReason reason) = 0;

    /// Copy value source with type corresponding to this descriptor.
    /// \param dst Destination value source.
    /// \param src Source value source.
    virtual void copyValueSource(AbstractPropertyTypeDescriptor::ValueSource* dst, const AbstractPropertyTypeDescriptor::ValueSource* src) = 0;

    /// Finds a fixed property type by name.
    static AbstractPropertyTypeDescriptor* findDescriptor(string_view name);

    typedef unique_ptr<AbstractPropertyTypeDescriptor> ManagedDescriptor;

    static void registerDescriptor(ManagedDescriptor descriptor);

private:

    void parseUnqualifiedName();

    /// Register a property type in fixed properties. After a property type is registered to fixed properties,
    /// it is possible to find it by its name.
    static void registerDescriptor(AbstractPropertyTypeDescriptor* descriptor);

    static void unregisterDescriptor(AbstractPropertyTypeDescriptor* descriptor);
};

/// Alias for map of all property types.
typedef unordered_map<string_view, AbstractPropertyTypeDescriptor*> PropertyTypeRegistry;

/// Get iterator to the beginning of registry of all property types.
/// \return A const iterator to the beginning of property type registry.
KANZI_API PropertyTypeRegistry::const_iterator beginPropertyTypes();

/// Get iterator to the end of registry of all property types.
/// \return A const iterator to the end of property type registry.
KANZI_API PropertyTypeRegistry::const_iterator endPropertyTypes();

}


#endif
