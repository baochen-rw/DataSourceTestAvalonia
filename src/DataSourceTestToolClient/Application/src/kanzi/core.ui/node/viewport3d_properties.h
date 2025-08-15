// Copyright 2008-2021 by Rightware. All rights reserved.

// Properties for Viewport3D.
// Do not include this file directly. Include viewport3d.hpp instead.



    /// Prefab property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setPrefab(), getPrefab()
    static PropertyType<ResourceSharedPtr> PrefabProperty;

    /// Gets the value of #PrefabProperty.
    /// \see setPrefab()
    ResourceSharedPtr getPrefab() const { return getProperty(PrefabProperty); }

    /// Sets the value of #PrefabProperty.
    /// \see getPrefab()
    void setPrefab(ResourceSharedPtr value) { setProperty(PrefabProperty, value); }


    /// Material property.
    /// 
    /// The default value is ResourceSharedPtr().
    /// \see setMaterial(), getMaterial()
    static PropertyType<ResourceSharedPtr> MaterialProperty;

    /// Gets the value of #MaterialProperty.
    /// \see setMaterial()
    ResourceSharedPtr getMaterial() const { return getProperty(MaterialProperty); }

    /// Sets the value of #MaterialProperty.
    /// \see getMaterial()
    void setMaterial(ResourceSharedPtr value) { setProperty(MaterialProperty, value); }


