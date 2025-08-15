// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_EDITOR_METADATA_HPP
#define KZ_EDITOR_METADATA_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/unordered_map.hpp>

#include <kanzi/core/legacy/debug/kzs_error.hpp>

// Editor metadata is included only in MSVC builds.
// Comment out the define below to disable editor info in metadata.
#ifdef _MSC_VER
#define KZ_EDITOR_INFO_METADATA
#endif

namespace kanzi
{

/// Editor information for metadata.
///
/// Metadata in metaclasses, property types and message types may contain information for Kanzi Studio.
/// This information may include tooltips, default values and so on.
struct PropertyTypeEditorInfo
{
    struct AttributeDictionary
    {
    private:
        
        typedef unordered_map<string, string> Dictionary;

    public:

        typedef Dictionary::const_iterator AttributeIterator;

        /// Friendly display name used in Kanzi Studio.
        string displayName;
        /// Tooltip used in Kanzi Studio.
        string tooltip;
        /// Category name used in Kanzi Studio.
        string category;
        /// Help heading used in Kanzi Studio.
        string helpHeading;
        /// Value provider used in Kanzi Studio.
        string valueProvider;
        /// Host definition that defines object types for which Kanzi Studio suggests the property.
        string host;
        /// Editor type used in Kanzi Studio.
        string editor;

        AttributeIterator begin() const
        {
            return m_dictionary.begin();
        }

        AttributeIterator end() const
        {
            return m_dictionary.end();
        }

        string& operator[] (const string& key)
        {
            kzAssert(key != "AffectConstraint");
            kzAssert(key != "AffectFinalTransformation");
            kzAssert(key != "AffectLayout");
            kzAssert(key != "AffectParentLayout");
            kzAssert(key != "AffectPartialRenderingObject");
            kzAssert(key != "AffectPartialRenderingTree");
            kzAssert(key != "AffectRender");
            kzAssert(key != "AffectRenderTree");
            kzAssert(key != "EngineDoc");
            kzAssert(key != "EngineFile");
            kzAssert(key != "EngineName");
            kzAssert(key != "EngineObjectType");
            kzAssert(key != "ExportToEngine");
            kzAssert(key != "Inheritable");
            kzAssert(key != "Name");
            kzAssert(key != "Namespace");
            kzAssert(key != "ProjectObjectExportType");
            kzAssert(key != "DisplayName");
            kzAssert(key != "Tooltip");
            kzAssert(key != "Category");
            kzAssert(key != "HelpHeading");
            kzAssert(key != "ValueProvider");
            // Following asserts disabled due to properties in ProgressiveView2D
            // kzAssert(key != "Type");
            // kzAssert(key != "TargetType");
            kzAssert(key != "Options");
            kzAssert(key != "Host");
            kzAssert(key != "Editor");

            return m_dictionary[key];
        }

        AttributeIterator find(const string& key) const
        {
            return m_dictionary.find(key);
        }

    private:

        Dictionary m_dictionary;
    };

    typedef AttributeDictionary::AttributeIterator AttributeIterator;
    AttributeDictionary attributes;

    explicit PropertyTypeEditorInfo()
    {
    }

    explicit PropertyTypeEditorInfo(AttributeDictionary dictionary) : attributes(dictionary)
    {
    }
};

#if defined KZ_EDITOR_INFO_METADATA
typedef shared_ptr<PropertyTypeEditorInfo> PropertyTypeEditorInfoSharedPtr;
#else
typedef PropertyTypeEditorInfo* PropertyTypeEditorInfoSharedPtr;
#endif

}

#if defined KZ_EDITOR_INFO_METADATA
#define KZ_PROPERTY_TYPE_EDITOR_INFO(x)     new kanzi::PropertyTypeEditorInfo(x)
#define KZ_DECLARE_EDITOR_METADATA(x)       new kanzi::PropertyTypeEditorInfo([]() -> kanzi::PropertyTypeEditorInfo::AttributeDictionary { kanzi::PropertyTypeEditorInfo::AttributeDictionary metadata; x  return metadata; }())
#else
#define KZ_PROPERTY_TYPE_EDITOR_INFO(x)     (kanzi::PropertyTypeEditorInfo*)0
#define KZ_DECLARE_EDITOR_METADATA(x)       (kanzi::PropertyTypeEditorInfo*)0
#endif

#endif