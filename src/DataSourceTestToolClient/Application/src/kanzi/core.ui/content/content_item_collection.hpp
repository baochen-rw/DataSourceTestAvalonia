// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZ_CONTENT_ITEM_COLLECTION_HPP
#define KZ_CONTENT_ITEM_COLLECTION_HPP

#include <kanzi/core/cpp/platform.hpp>
#include <kanzi/core/cpp/memory.hpp>


namespace kanzi
{

class Node;
typedef shared_ptr<Node> NodeSharedPtr;


/// Base class for exposing abstract access to collections of items of UI controls with content.
class KANZI_API ContentItemCollectionModel
{
public:

    virtual ~ContentItemCollectionModel() {}

    virtual bool addContentItem(NodeSharedPtr abstractItem) = 0;
    virtual bool removeContentItem(NodeSharedPtr abstractItem) = 0;
    virtual void removeAllContentItems() = 0;
    virtual size_t getContentItemCount() = 0;
    virtual NodeSharedPtr getContentItem(size_t index) = 0;
};

}

#endif
