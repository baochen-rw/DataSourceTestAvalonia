// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CONTENT_ITEM_HPP
#define KZ_CONTENT_ITEM_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/memory.hpp>


namespace kanzi
{

class Node;
class ResourceID;
typedef shared_ptr<Node> NodeSharedPtr;


/// Base class for exposing abstract access to content of UI controls with single content item model.
class KANZI_API ContentItemModel
{
public:

    virtual ~ContentItemModel() {}

    virtual void setContentItem(const ResourceID& resourceId) = 0;
};

}

#endif
