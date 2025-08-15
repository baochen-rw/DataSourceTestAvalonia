// Copyright 2008-2021 by Rightware. All rights reserved.

#ifndef KZU_VIRTUAL_ITEM_LIST_H
#define KZU_VIRTUAL_ITEM_LIST_H


#include <kanzi/core/legacy/debug/kzs_error.hpp>
#include <kanzi/core/legacy/kzs_types.hpp>


/* Forward declarations. */
struct KzuObjectGenerator;
struct KzuUiListBox;
struct KzcVector3;
struct KzcMemoryManager;


/**
* \struct KzuVirtualItemList
* A virtual collection of items that supports iteration.
*/
struct KzuVirtualItemList;


/** Preferred element when exact match cannot be found. */
enum KzuVirtualItemListDirectionPreference
{
    KZU_VIRTUAL_ITEM_LIST_PREFER_PREVIOUS, /**< Prefer previous element. */
    KZU_VIRTUAL_ITEM_LIST_PREFER_NEXT      /**< Prefer next element. */
};


/**
* Function that returns a one-dimensional width of a virtual item, based on it's dimensions.
*
* As an example, if used in a horizontal layout the function should return object's width.
* This value is used for determining how much space an item will need in the virtual item list.
*/
typedef float (*KzuVirtualItemWidthFunction)(const struct KzcVector3* size);

/** Function that returns size of an item in the list box. */
typedef kzsError (*KzuVirtualItemSizeFunction)(unsigned int index, void* userData, struct KzcVector3* out_size);

/** Function that returns item count of a list box. */
typedef unsigned int (*KzuVirtualItemCountFunction)(void* userData);


/**
* Iterator for KzuVirtualItemList.
* Keeps track of index, offset and item width of the item the iterator is pointing to.
*
* Note: This struct is to be used through the functions provided in kzu_virtual_item_list.h
*       The struct may change arbitrarily at any time and is public only to allow creation in stack.
*/
struct KzuVirtualItemIterator
{
    explicit KzuVirtualItemIterator() :
        itemList(),
        index(0),
        offset(0.0f),
        width(0.0f),
        valid(KZ_FALSE)
    {
    }

    struct KzuVirtualItemList* itemList; /**< The virtual list iterated by the iterator. */

    int index;    /**< How many indices the iterator has been moved. */
    float offset; /**< How much the iterator has been moved. */
    float width;  /**< Width of the current item. */
    kzBool valid; /**< Is iterator valid. */
};

/** Returns whether the virtual item iterator is valid. */
kzBool kzuVirtualItemIteratorIsValid(const struct KzuVirtualItemIterator* iterator);

/** Sets the iterator invalid. */
void kzuVirtualItemIteratorInvalidate(struct KzuVirtualItemIterator* iterator);

/** Asks the iterator to update its width. */
kzsError kzuVirtualItemIteratorUpdateWidth(struct KzuVirtualItemIterator* iterator);

/** Gets offset of the right edge of the item pointed by the the iterator. */
float kzuVirtualItemIteratorGetRightEdge(const struct KzuVirtualItemIterator* iterator);

/** Gets offset of the center of the item pointed by the iterator. */
float kzuVirtualItemIteratorGetCenter(const struct KzuVirtualItemIterator* iterator);

/** Gets offset of the left edge of the item pointed by the iterator. */
float kzuVirtualItemIteratorGetLeftEdge(const struct KzuVirtualItemIterator* iterator);

/** Gets index of the item pointed by the iterator. */
unsigned int kzuVirtualItemIteratorGetIndex(const struct KzuVirtualItemIterator* iterator);

/** Returns whether the iterator has a next item. */
kzBool kzuVirtualItemIteratorHasNext(const struct KzuVirtualItemIterator* iterator);

/** Returns whether the iterator has a previous item. */
kzBool kzuVirtualItemIteratorHasPrevious(const struct KzuVirtualItemIterator* iterator);

/** Gets index of the item after the item pointed by the iterator. */
unsigned int kzuVirtualItemIteratorGetNextIndex(const struct KzuVirtualItemIterator* iterator);

/** Gets index of the item before the item pointed by the iterator. */
unsigned int kzuVirtualItemIteratorGetPreviousIndex(const struct KzuVirtualItemIterator* iterator);

/** Iterates to the next item. */
kzsError kzuVirtualItemIteratorNext(struct KzuVirtualItemIterator* iterator);

/** Iterates to the previous item. */
kzsError kzuVirtualItemIteratorPrevious(struct KzuVirtualItemIterator* iterator);

/**
* Creates a virtual item list that uses the given list box to provide item data.
*
* \param widthFunction Returns width from an object size.
* \param sizeFunction Returns size of an object by index.
* \param countFunction Returns total item count of virtual item list.
*/
kzsError kzuVirtualItemListCreate(const struct KzcMemoryManager* memoryManager,
                                  KzuVirtualItemWidthFunction widthFunction,
                                  KzuVirtualItemSizeFunction sizeFunction, void* sizeFunctionUserData,
                                  KzuVirtualItemCountFunction countFunction, void* countFunctionUserData,
                                  struct KzuVirtualItemList** out_itemList);
/** Deletes a virtual item list. */
kzsError kzuVirtualItemListDelete(struct KzuVirtualItemList* itemList);

/** Sets whether the virtual item list is looping. */
void kzuVirtualItemListSetLooping(struct KzuVirtualItemList* itemList, kzBool looping);
/** Gets whether the virtual item list is looping. */
kzBool kzuVirtualItemListIsLooping(const struct KzuVirtualItemList* itemList);

/** Sets spacing between items in the virtual item list. */
void kzuVirtualItemListSetSpacing(struct KzuVirtualItemList* itemList, float spacing);


/**
* Gets the number of elements that are in between the left and right iterators, including the iterators.
*
* For example:
*     - kzuVirtualItemListGetIntervalElementCount(iterator, iterator) returns 1.
*     - kzuVirtualItemListGetIntervalElementCount(current, next) returns 2.
*
* Calling this function with invalid iterators results in undefined behavior.
*/
unsigned int kzuVirtualItemListGetIntervalElementCount(const struct KzuVirtualItemIterator* leftIterator, const struct KzuVirtualItemIterator* rightIterator);


#endif
