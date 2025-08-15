// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_TAG_HPP
#define KZ_TAG_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/string.hpp>

namespace kanzi
{

class Node;

/// Tag represents a mark that can be added to a node to mark that
/// the node is of certain kind. For example transparent nodes can be
/// marked with a "Transparent" tag. The transparent nodes can then be
/// rendered in a different way than other objects by using a tag filter
/// that selects only nodes with the "Transparent" tag.
class KANZI_API Tag
{
public:

    /// Creates a transparent tag that is used in the default composer.
    /// \return A tag for transparent objects.
    static Tag createTransparentTag();

    /// Adds a tag to the node.
    /// If the node already has the tag, does nothing.
    /// \param node The node that is tagged.
    /// \param tag The added tag.
    static void addTag(Node& node, const Tag& tag);

    /// Removes a tag from the node.
    /// If the node doesn't have the tag, does nothing.
    /// \param node The node where the tag is removed.
    /// \param tag The removed tag.
    static void removeTag(Node& node, const Tag& tag);

    /// Checks if a node has a tag.
    /// \param node The node that is checked.
    /// \param tag The tag that is checked.
    /// \return True if the node has the tag; false otherwise.
    static bool hasTag(Node& node, const Tag& tag);

    /// Creates a tag.
    /// \param name The name of the tag.
    explicit Tag(const string& name);

private:

    string m_name;
};

}

#endif
