// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_RESOURCE_PROFILING_ATTRIBUTES_HPP
#define KZ_RESOURCE_PROFILING_ATTRIBUTES_HPP

#include <kanzi/core.ui/resource/resource_profiling_categories.hpp>

#if defined(KANZI_DOXYGEN) || kzProfilingIsCategoryEnabledAtCompileTime(KZ_PROFILING_RESOURCE_LOADING_CATEGORY)

#include <kanzi/core/cpp/map.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>
#include <kanzi/core/cpp/variant.hpp>

namespace kanzi
{

/// \ingroup ResourceProfiling
/// Container for resource profiling attributes.
///
/// Each resource profiling attribute has a unique name.
class KANZI_API ResourceProfilingAttributes
{
public:
    /// Attribute value type.
    typedef variant<monostate, bool, uint64_t, string> Value;

    /// Attribute name type.
    typedef string AttributeName;

    /// Attributes container indexed with attribute name.
    typedef map<AttributeName, Value> AttributesContainer;

    /// Gets the attributes container.
    ///
    /// \return The attribute values container.
    const AttributesContainer& getAttributesContainer() const
    {
        return m_attributes;
    }

    /// Appends a new attribute.
    ///
    /// \note This function throws an exception if an attribute with \p name already exists.
    ///
    /// \param name The name of the new attribute.
    /// \param value The value of the new attribute.
    void appendAttribute(string_view name, const Value& value);

private:
    /// The attributes.
    AttributesContainer m_attributes;
};
}

#endif
#endif
