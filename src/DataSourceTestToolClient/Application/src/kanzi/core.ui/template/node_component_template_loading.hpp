// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_NODE_COMPONENT_TEMPLATE_LOADING_HPP
#define KZ_NODE_COMPONENT_TEMPLATE_LOADING_HPP

#include <kanzi/core/cpp/memory.hpp>
#include <kanzi/core/cpp/string.hpp>
#include <kanzi/core/cpp/string_view.hpp>

#include <kanzi/core/legacy/util/io/kzc_input_stream.hpp>
#include <kanzi/core.ui/kzb/kzu_binary_directory.h>
#include <kanzi/core.ui/kzb/object_loader.hpp>
#include <kanzi/core.ui/template/node_component_template.hpp>


namespace kanzi
{

/// Forward declarations.
class Domain;
class ObjectLoader;
class Object;
class KzbFile;
class KzbMemoryParser;

typedef shared_ptr<Object> ObjectSharedPtr;


/// Registers node component template loader for specified node component type.
///
/// \param objectLoader Object loader where to register loading of specified node component type.
/// \param metaclass Metaclass of node component to load.
KANZI_API void registerNodeComponentLoader(ObjectLoader& objectLoader, const Metaclass* metaclass);

/// Registers node component template loaders for build-in node component types.
///
/// \param objectLoader Object loader where to register loading of node components.
void registerNodeComponentLoaders(ObjectLoader& objectLoader);

}

#endif
