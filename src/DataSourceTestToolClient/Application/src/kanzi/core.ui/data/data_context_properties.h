// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for DataContext.
// Do not include this file directly. Include data_context.hpp instead.



    /// DataContext property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setDataContext(), getDataContext()
    static PropertyType<ResourceSharedPtr> DataContextProperty;

    /// Gets the value of #DataContextProperty.
    /// \see setDataContext()
    ResourceSharedPtr getDataContext() const { return getProperty(DataContextProperty); }

    /// Sets the value of #DataContextProperty.
    /// \see getDataContext()
    void setDataContext(ResourceSharedPtr value) { setProperty(DataContextProperty, value); }


    /// ItemsSource property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setItemsSource(), getItemsSource()
    static PropertyType<ResourceSharedPtr> ItemsSourceProperty;

    /// Gets the value of #ItemsSourceProperty.
    /// \see setItemsSource()
    ResourceSharedPtr getItemsSource() const { return getProperty(ItemsSourceProperty); }

    /// Sets the value of #ItemsSourceProperty.
    /// \see getItemsSource()
    void setItemsSource(ResourceSharedPtr value) { setProperty(ItemsSourceProperty, value); }


