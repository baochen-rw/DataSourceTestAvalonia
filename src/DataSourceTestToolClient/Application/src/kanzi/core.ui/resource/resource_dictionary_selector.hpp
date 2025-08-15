// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_DICTIONARY_SELECTOR_HPP
#define KZ_RESOURCE_DICTIONARY_SELECTOR_HPP


#include <kanzi/core.ui/resource/resource_dictionary.hpp>


namespace kanzi
{

class ResourceDictionarySelector;

/// Resource dictionary selector shared pointer.
typedef shared_ptr<ResourceDictionarySelector> ResourceDictionarySelectorSharedPtr;


/// A resource dictionary selector is a type of a resource dictionary that redirects resource queries to its only nested dictionary.
/// This type of dictionary is used internally by Screen to implement switching of locales and themes in theme groups.
/// You can use Screen::setLocale to set the current locale and Screen::activateTheme to activate a theme in a theme group.
class KANZI_API ResourceDictionarySelector : public ResourceDictionary
{
public:

#include "resource_dictionary_selector_properties.h"

    KZ_METACLASS_BEGIN(ResourceDictionarySelector, ResourceDictionary, "Kanzi.ResourceDictionarySelector")
        KZ_METACLASS_PROPERTY_TYPE(SelectedDictionaryProperty)
    KZ_METACLASS_END()


    /// Creates a resource dictionary selector.
    /// \param domain The domain to which the resource dictionary selector belongs.
    /// \param name The name of the resource dictionary selector.
    /// \return The pointer to the resource dictionary selector.
    static ResourceDictionarySelectorSharedPtr create(Domain* domain, string_view name);

    /// Selects a dictionary given an URL.
    /// Resource dictionary selector loads the dictionary and will redirect all resource queries to it.
    /// The selected dictionary doesn't change if the resource dictionary selector cannot load the new dictionary.
    /// \param dictionaryUrl The URL to load the dictionary from.
    /// \return True if the dictionary was successfully loaded, false otherwise. 
    bool selectDictionary(string_view dictionaryUrl);

    /// Returns the currently selected dictionary.
    /// \return The currently selected dictionary or null if no dictionary is selected.
    ResourceDictionarySharedPtr getSelectedDictionary() const
    {
        return dynamic_pointer_cast<ResourceDictionary>(getProperty(SelectedDictionaryProperty));
    }

    /// Sets the currently selected dictionary.
    void setSelectedDictionary(ResourceDictionarySharedPtr dictionary)
    {
        setProperty(SelectedDictionaryProperty, dictionary);
    }

    static PropertyTypeEditorInfoSharedPtr makeEditorInfo();

    /// Loads a resource dictionary selector from a file. Used internally by Kanzi Engine.
    ///
    /// \param domain Domain
    /// \param name Name
    /// \param kzbFile KZB file where to load from.
    /// \param file Resource Dictionary selector file inside the KZB file where to load from.
    /// \param parser Parser pointing to the beginning of the file.
    static ResourceDictionarySelectorSharedPtr loadFromKZB(Domain* domain, string_view name, KzbFile& kzbFile, ReadOnlyMemoryFile& file, KzbMemoryParser& parser);

protected:

    /// Constructor.
    /// \param domain The domain to which the resource dictionary selector belongs.
    /// \param name The name of the resource dictionary selector.
    explicit ResourceDictionarySelector(Domain* domain, string_view name);

    /// Implements Object::onPropertyChanged.
    virtual void onPropertyChanged(AbstractPropertyType propertyType, PropertyNotificationReason reason) KZ_OVERRIDE;

    /// ResourceDictionary::findOverride() implementation.
    virtual optional<string> findOverride(const ResourceID& key) const KZ_OVERRIDE;
    /// Implements ResourceDictionary::acquireOverride.
    virtual ResourceSharedPtr acquireOverride(const ResourceID& key) const KZ_OVERRIDE;
    /// Implements ResourceDictionary::tryAcquireOverride.
    virtual ResourceSharedPtr tryAcquireOverride(const ResourceID& key) const KZ_OVERRIDE;
    /// ResourceDictionary::acquireAsyncOverride() implementation.
    virtual ResourceManager::AcquireTaskSharedPtr acquireAsyncOverride(const ResourceID& key, ResourceManager::AsyncAcquireFinishedCallback func) const KZ_OVERRIDE;
    /// Implements ResourceDictionary::cloneOverride.
    virtual ResourceDictionarySharedPtr cloneOverride() const KZ_OVERRIDE;

    /*static PropertyTypeEditorInfoSharedPtr makeEditorInfo()
    {
        return PropertyTypeEditorInfoSharedPtr();
    }*/

private:

    /// The currently selected dictionary that receives all resource queries.
    ResourceDictionarySharedPtr m_selectedDictionary;
};

}


#endif
