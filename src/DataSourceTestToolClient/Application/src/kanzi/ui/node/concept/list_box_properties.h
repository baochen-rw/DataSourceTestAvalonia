// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for ListBoxConcept.
// Do not include this file directly. Include list_box.hpp instead.



    /// KeepAliveItemCount property.
    /// 
    /// The default value is 20000000.
    /// \see setKeepAliveItemCount(), getKeepAliveItemCount()
    static PropertyType<int> KeepAliveItemCountProperty;


    /// SelectionBehavior property.
    /// 
    /// The default value is ListBoxConcept::SelectionBehaviorNone.
    /// \see setSelectionBehavior(), getSelectionBehavior()
    static PropertyType<ListBoxConcept::SelectionBehavior> SelectionBehaviorProperty;


    /// ItemGeneratorTypeName property.
    /// 
    /// The default value is "".
    /// \see setItemGeneratorTypeName(), getItemGeneratorTypeName()
    static PropertyType<string> ItemGeneratorTypeNameProperty;


    /// ItemContainerGeneratorTypeName property.
    /// 
    /// The default value is "".
    /// \see setItemContainerGeneratorTypeName(), getItemContainerGeneratorTypeName()
    static PropertyType<string> ItemContainerGeneratorTypeNameProperty;


    /// ItemTemplate property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setItemTemplate(), getItemTemplate()
    static PropertyType<ResourceSharedPtr> ItemTemplateProperty;


    /// ItemContainerTemplate property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setItemContainerTemplate(), getItemContainerTemplate()
    static PropertyType<ResourceSharedPtr> ItemContainerTemplateProperty;


    /// SelectedItemIndex property.
    /// Index of selected list box item.
    /// The default value is -1.
    /// \see setSelectedItemIndex(), getSelectedItemIndex()
    static PropertyType<int> SelectedItemIndexProperty;


